//--------------------------------------------
//グローバル変数領域
//-------------------------------------------
#include "Global.h"
void MainLoop(void) {
	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------
	Task::DeleteAll();
	Task::UpdateAll(); 
	Task::CollisionAll();
	//２．影の描画＋その他ポストエフェクト
	CRendaring::GetInstance()->Render([]() {
		Task::RenderAll();
		});
	//2D画像の描画
	//Task::Draw2DAll();
}
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);/* 隠面消去 */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);/* カリング */
	glCullFace(GL_BACK);/* カリングする面の指定 */

	//固定シェーダー用
	glEnable(GL_LIGHTING);/* ライティング処理のオン */
	glEnable(GL_LIGHT0);/* ０番目の光源点灯 */
	//glEnable(GL_LIGHT1);
	glEnable(GL_ALPHA_TEST);
	//static GLfloat lightSpecular[3] = { 0.0f,0.0f,0.0f }; //鏡面光
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	CFPS::SetFPS(60);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton10, VK_RETURN); 
	CInput::SetButton(0, CInput::eShift, VK_SHIFT); 
	CInput::SetButton(0, CInput::eSpace, VK_SPACE);
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);

	//マウス非表示
	//	CInput::ShowCursor(false);
	//	CInput::SetMouseInside(true);
	CInput::Update();
	CInput::Update();


	//ライト設定
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(50, 200, 200));
	CLight::SetDir(0, CVector3D(0, -2, 0).GetNormalize());
	CLight::SetColor(0, CVector3D(0.41f, 0.41f, 0.41f), CVector3D(0.68f, 0.68f, 0.68f));
	static GLfloat lightSpecular[3] = { 0.0f,0.0f,0.0f }; //鏡面光
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	static GLfloat lightAmbient[3] = { 1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	{/*
		CLight::SetType(1, CLight::eLight_Hemi);
		CLight::SetPos(1, CVector3D(50, 200, 200));
		CLight::SetDir(1, CVector3D(-1, -2, 1).GetNormalize());
		CLight::SetColor(1, CVector3D(0.2f, 0.2f, 0.2f), CVector3D(1, 1, 1));*/
	}


	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);

	//カメラ初期化
	CCamera::GetCamera()->LookAt(CVector3D(5, 5, 5),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();

	SetCurrentDirectory("data");


	//-----------------------------------------------------
	//初期化の命令を書く
	//ゲーム起動時に一度だけ呼ばれる
	//-----------------------------------------------------
	ADD_RESOURCE("SkyIsland", CModel::CreateModel("Field/IslandPlusTemple.obj", 10, 3, 5));;
	ADD_RESOURCE("Desert", CModel::CreateModel("Field/Desert.obj", 10, 5, 5));
	ADD_RESOURCE("Sky", CModel::CreateModel("Field/SkyBox.obj"));
	ADD_RESOURCE("Player", CModel::CreateModel("Character/PlayerA1005.a3m"));
	ADD_RESOURCE("Feather", CModel::CreateModel("Item/star.obj"));
	ADD_RESOURCE("Glass1", CModel::CreateModel("Item/Glass/Square05NH.obj")); 
	ADD_RESOURCE("Hinokon", CModel::CreateModel("Item/Glass/OnlyHinokon.obj"));
	ADD_RESOURCE("Mant_DesignL", CImage::CreateImage("Character/MantFeather01.png"));
	ADD_RESOURCE("Mant_DesignD", CImage::CreateImage("Character/MantFeatherBlack.png"));
	ADD_RESOURCE("Whale", CModel::CreateModel("Character/whale/whale.a3m"));
	ADD_RESOURCE("SkyBox", CModel::CreateModel("Field/SkyBox.obj"));
	ADD_RESOURCE("TitleImage", CImage::CreateImage("Title/Title.png"));
	ADD_RESOURCE("ExclamationMark", CImage::CreateImage("UI/ExclamationMark.png"));
	ADD_RESOURCE("Volcano", CModel::CreateModel("Field/volcano/volcano.obj",10, 5, 5));
	Task::Add(new Progress());
	//影描画機能を生成		描画範囲　光源の高さ 解像度
	CShadow::CreateInscance(200.0f, 200.0f, 2048, 2046);
	//ポストエフェクトを生成		画面解像度
	CRendaring::CreatInstance(SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Release()
{
	CShader::ClearInstance();
	CInput::ClearInstance();
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}
static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	CCamera::GetCurrent()->Perspective(DtoR(45.0), (float)w / (float)h, 1.0, 10000.0);
	
	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);

	Init();
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();


		CInput::Update();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "math fps:%d dt:%.3f", CFPS::GetFPS(), CFPS::GetDeltaTime());
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}
