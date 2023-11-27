#include "System/GL.h"

/*Model.hで定義済み
//頂点配列構造体
struct SVertex {
	Vec3 v;
	Vec3 n;
	Vec2 t;
};
*/
//立方体の頂点配列
SVertex* cube_vertex = nullptr;

//[test.vert]を作成
/*
#version 430
//頂点座標
layout(location = 0) in vec3	Vertex;
//投影xビューxワールド変換行列
uniform mat4 PVWMatrix;

void main(void){
	//頂点を変換行列でクリップ空間での座標に変換
	gl_Position = PVWMatrix * vec4(Vertex, 1.0);
}
*/
//[test.frag]を作成
/*
#version 430

//描画される色
out vec4 frag_color;

void main(void) {
	//(Red=1.0, Green=0.0, Blue=0.0, alpha=1.0(不透明）)
	//赤を出力
	frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}
*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float r = 0;
	r += 0.1f;
	if (r >= M_PI * 2) r = 0;

	
	//ビュー行列（カメラ）
	Camera::s_view = Matrix4x4::MLookAtView(Vec3(10.0, 10.0, 10.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
	//ワールド行列（回転のみ）
	Matrix4x4 matrix = Matrix4x4::MRotationY(r);

	

	//A.固定シェーダー用
	
	//モデルビュー行列の設定
	glLoadMatrixf((Camera::s_view * matrix).f);

	//有効化
	glEnableClientState(GL_VERTEX_ARRAY);
	//データの関連付け
	glVertexPointer(3, GL_FLOAT, sizeof(SVertex), &cube_vertex->v);//座標
	//描画
	glDrawArrays(GL_QUADS, 0, 4 * 6); //描画(4点×6面=24頂点）
	//無効化
	glDisableClientState(GL_VERTEX_ARRAY);
	

	//B.自作シェーダー用
	/*
	Shader* s = Shader::GetInstance("Test");
	//■シェーダー有効化
	s->Enable();

	GLuint p = s->GetProgram();
	//■シェーダーへ各種値を渡す
	//投影xビューxワールド変換行列
	glUniformMatrix4fv(glGetUniformLocation(p, "PVWMatrix"), 1, GL_FALSE, (Camera::s_proj * Camera::s_view * matrix).f);

	//■有効化
	glEnableVertexAttribArray(0);

	//■データの関連付け
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), &cube_vertex->v);//座標
	//描画
	glDrawArrays(GL_QUADS, 0, 4 * 6);	 //描画(4点×6面=24頂点）

	//■無効化
	glDisableVertexAttribArray(0);

	//■シェーダー無効化
	s->Disable();
	*/

	glutSwapBuffers();
	Sleep(20);



}
void resize(int w, int h)
{
	//ウィンドウ全体をビューポートにする
	glViewport(0, 0, w, h);
	//透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	//投影行列を設定
	Camera::s_proj = Matrix4x4::MPerspective(DtoR(60.0f), (float)w / float(h), 1.0, 100.0);
	glLoadMatrixf(Camera::s_proj.f);
	//モデルビュー変換行列の設定
	glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
	glutPostRedisplay();
}
void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };

	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat gray[] = { 0.2, 0.2, 0.2, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	//カレントディレクトリの設定
	SetCurrentDirectory("data");
	{
		Vec3 vertex[] = {
			{ 0.0, 0.0, 0.0 }, /* A */
			{ 1.0, 0.0, 0.0 }, /* B */
			{ 1.0, 1.0, 0.0 }, /* C */
			{ 0.0, 1.0, 0.0 }, /* D */
			{ 0.0, 0.0, 1.0 }, /* E */
			{ 1.0, 0.0, 1.0 }, /* F */
			{ 1.0, 1.0, 1.0 }, /* G */
			{ 0.0, 1.0, 1.0 }  /* H */
		};
		int face[][4] = {
			{ 3, 2, 1, 0 }, /* A-B-C-D を結ぶ面 */
			{ 2, 6, 5, 1 }, /* B-F-G-C を結ぶ面 */
			{ 6, 7, 4, 5 }, /* F-E-H-G を結ぶ面 */
			{ 7, 3, 0, 4 }, /* E-A-D-H を結ぶ面 */
			{ 0, 1, 5, 4 }, /* E-F-B-A を結ぶ面 */
			{ 7, 6, 2, 3 }  /* D-C-G-H を結ぶ面 */
		};
		//立方体の頂点配列の生成
		cube_vertex = new SVertex[4 * 6];
		int idx = 0;
		for (int j = 0; j < 6; ++j) {
			for (int i = 0; i < 4; ++i) {
				cube_vertex[idx].v = vertex[face[j][i]];
				idx++;
			}
		}
	}
	//B.自作シェーダー用
	//シェーダー読み込み
	//Shader::CreateInstance("Test", "shader\\test.vert", "shader\\test.frag");
}
int main(int argc, char* argv[])
{
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
	glewInit();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 0;
}


