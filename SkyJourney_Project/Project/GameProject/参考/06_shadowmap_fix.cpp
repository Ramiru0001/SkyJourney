#include "System/GL.h"

//画面サイズ
float screen_width = 1920;
float screen_height = 1080;

//モデルクラス
Model model1;
Model model2;


//■シャドウマップ用
RenderTarget* shadow_frame_buffer;


/*[mesh_shadow.vert]
#version 430
//頂点座標
layout(location = 0) in vec3	Vertex;
layout(location = 1) in vec3	Normal;
layout(location = 2) in vec2	TexCoord;
//投影xビューxワールド変換行列
uniform mat4 PVWMatrix;
//シャドウマップ変換行列
uniform mat4 ShadowTextureMatrix;

//フラグメントシェーダーに渡す変数
out vec2 vTexCoord;
//シャドウデプスマップでのUV座標
out vec4 vShadowCoord;
void main(void){
	//頂点を変換行列でクリップ空間での座標に変換
	gl_Position = PVWMatrix * vec4(Vertex, 1.0);
	//シャドウマップでのUV座標
	vShadowCoord = ShadowTextureMatrix*vec4(Vertex,1);
	vTexCoord = TexCoord;
}
*/
/*[mesh_shadow.frag]
#version 430
//ベースカラー
uniform vec4 BaseColor;
//テクスチャ
uniform sampler2D texture;
//深度バッファ
uniform sampler2D depth_tex;
//バーテックスシェーダーから受け取る値
in vec2 vTexCoord;
//シャドウデプスマップでのUV座標
in vec4 vShadowCoord;
//描画される色
out vec4 frag_color;
void main(void) {
	vec4 color = texture2D(texture, vTexCoord);
	frag_color = color*BaseColor;
	//明るさ
	float visibility = 1.0;
	//誤差調整用
	float bias = 0.01;
	//深度値取得
	float z = texture2D( depth_tex, vShadowCoord.xy ).z;
	//シャドウマップの深度値が描画ポリゴンより手前なら
	if ( z  <  vShadowCoord.z-bias ){
		//影になる
		visibility=0.0;
	}
	//影込みで色を調整
	frag_color = vec4(frag_color.rgb*visibility,frag_color.a);
}
*/
static float r = 0;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	r += 0.1f;
	if (r >= M_PI * 2) r = 0;
	model1.SetRot(Vec3(0, r, 0));


	//■--ライト視点からの描画（シャドウマップを作成）----------------------
	//原点修正用行列
	static  const Matrix4x4 texMat(0.5f, 0.0f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//光源を視点に
	Camera::s_view = Matrix4x4::MLookAtView(Vec3(-5.0, 10.0, -5.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
	//正投影行列（影として写す範囲を設定）
	Camera::s_proj = Matrix4x4::MOrtho(-15, 15, -15, 15, 1.0, 100.0);
	//■シャドウマップ変換行列
	Camera::s_shadow = texMat * Camera::s_proj * Camera::s_view;

	//シャドウマップ用へ描画
	shadow_frame_buffer->BeginDraw();
	//前面を描画しない
	glCullFace(GL_FRONT);
	//回転するモデル
	model1.Render();
	//背面を描画しない
	glCullFace(GL_BACK);
	//シャドウマップ用描画週終了
	shadow_frame_buffer->EndDraw();

	//7番のテクスチャーをシャドウマップとする
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, shadow_frame_buffer->GetDepthTexture()->m_buf);
	glEnable(GL_TEXTURE_2D);

	//0番テクスチャー操作に戻す
	glActiveTexture(GL_TEXTURE0);
	//---------------------------------------------------------------------


	//--通常の描画------------------------------------
	//ビュー行列（カメラ）
	Camera::s_view = Matrix4x4::MLookAtView(Vec3(20.0, 15.0, 20.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
	//投影行列
	Camera::s_proj = Matrix4x4::MPerspective(30.0 * M_PI / 180, (double)screen_width / (double)screen_height, 1.0, 100.0);
	//回転するモデル
	model1.Render();
	//床としてのモデル
	model2.Render();
	//----------------------------------------------

	//■シャドウマップをデバッグ表示
	RenderTarget::Draw(0, 0, 256, 256, shadow_frame_buffer->GetDepthTexture());
	

	glutSwapBuffers();
	Sleep(20);



}
void resize(int w, int h)
{
	screen_width = w;
	screen_height = h;
	//ウィンドウ全体をビューポートにする
	glViewport(0, 0, w, h);
	//投影行列を設定
	Camera::s_proj = Matrix4x4::MPerspective(DtoR(60.0f), (float)w / float(h), 1.0, 100.0);
}

void idle(void)
{
	glutPostRedisplay();
}
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//カレントディレクトリ移動
	SetCurrentDirectory("data");
	//モデル読み込み
	model1.Load("Cube.obj");
	model2.Load("Cube.obj");

	//model2は地面として利用
	model2.SetPos(Vec3(0, -3, 0));
	model2.SetScale(Vec3(10, 1, 10));
	//■シャドウマップ用レンダーターゲット
	shadow_frame_buffer = new RenderTarget(1024, 1024,Vec4(1,1,1,1));

}
int main(int argc, char* argv[])
{
	glutInitWindowSize(screen_width, screen_height);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);
	// /*変更*//glewの初期化
	glewInit();
	init();
	glutMainLoop();

	return 0;
}


