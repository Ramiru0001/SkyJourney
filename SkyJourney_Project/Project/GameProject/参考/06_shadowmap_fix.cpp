#include "System/GL.h"

//��ʃT�C�Y
float screen_width = 1920;
float screen_height = 1080;

//���f���N���X
Model model1;
Model model2;


//���V���h�E�}�b�v�p
RenderTarget* shadow_frame_buffer;


/*[mesh_shadow.vert]
#version 430
//���_���W
layout(location = 0) in vec3	Vertex;
layout(location = 1) in vec3	Normal;
layout(location = 2) in vec2	TexCoord;
//���ex�r���[x���[���h�ϊ��s��
uniform mat4 PVWMatrix;
//�V���h�E�}�b�v�ϊ��s��
uniform mat4 ShadowTextureMatrix;

//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
out vec2 vTexCoord;
//�V���h�E�f�v�X�}�b�v�ł�UV���W
out vec4 vShadowCoord;
void main(void){
	//���_��ϊ��s��ŃN���b�v��Ԃł̍��W�ɕϊ�
	gl_Position = PVWMatrix * vec4(Vertex, 1.0);
	//�V���h�E�}�b�v�ł�UV���W
	vShadowCoord = ShadowTextureMatrix*vec4(Vertex,1);
	vTexCoord = TexCoord;
}
*/
/*[mesh_shadow.frag]
#version 430
//�x�[�X�J���[
uniform vec4 BaseColor;
//�e�N�X�`��
uniform sampler2D texture;
//�[�x�o�b�t�@
uniform sampler2D depth_tex;
//�o�[�e�b�N�X�V�F�[�_�[����󂯎��l
in vec2 vTexCoord;
//�V���h�E�f�v�X�}�b�v�ł�UV���W
in vec4 vShadowCoord;
//�`�悳���F
out vec4 frag_color;
void main(void) {
	vec4 color = texture2D(texture, vTexCoord);
	frag_color = color*BaseColor;
	//���邳
	float visibility = 1.0;
	//�덷�����p
	float bias = 0.01;
	//�[�x�l�擾
	float z = texture2D( depth_tex, vShadowCoord.xy ).z;
	//�V���h�E�}�b�v�̐[�x�l���`��|���S������O�Ȃ�
	if ( z  <  vShadowCoord.z-bias ){
		//�e�ɂȂ�
		visibility=0.0;
	}
	//�e���݂ŐF�𒲐�
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


	//��--���C�g���_����̕`��i�V���h�E�}�b�v���쐬�j----------------------
	//���_�C���p�s��
	static  const Matrix4x4 texMat(0.5f, 0.0f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//���������_��
	Camera::s_view = Matrix4x4::MLookAtView(Vec3(-5.0, 10.0, -5.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
	//�����e�s��i�e�Ƃ��Ďʂ��͈͂�ݒ�j
	Camera::s_proj = Matrix4x4::MOrtho(-15, 15, -15, 15, 1.0, 100.0);
	//���V���h�E�}�b�v�ϊ��s��
	Camera::s_shadow = texMat * Camera::s_proj * Camera::s_view;

	//�V���h�E�}�b�v�p�֕`��
	shadow_frame_buffer->BeginDraw();
	//�O�ʂ�`�悵�Ȃ�
	glCullFace(GL_FRONT);
	//��]���郂�f��
	model1.Render();
	//�w�ʂ�`�悵�Ȃ�
	glCullFace(GL_BACK);
	//�V���h�E�}�b�v�p�`��T�I��
	shadow_frame_buffer->EndDraw();

	//7�Ԃ̃e�N�X�`���[���V���h�E�}�b�v�Ƃ���
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, shadow_frame_buffer->GetDepthTexture()->m_buf);
	glEnable(GL_TEXTURE_2D);

	//0�ԃe�N�X�`���[����ɖ߂�
	glActiveTexture(GL_TEXTURE0);
	//---------------------------------------------------------------------


	//--�ʏ�̕`��------------------------------------
	//�r���[�s��i�J�����j
	Camera::s_view = Matrix4x4::MLookAtView(Vec3(20.0, 15.0, 20.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
	//���e�s��
	Camera::s_proj = Matrix4x4::MPerspective(30.0 * M_PI / 180, (double)screen_width / (double)screen_height, 1.0, 100.0);
	//��]���郂�f��
	model1.Render();
	//���Ƃ��Ẵ��f��
	model2.Render();
	//----------------------------------------------

	//���V���h�E�}�b�v���f�o�b�O�\��
	RenderTarget::Draw(0, 0, 256, 256, shadow_frame_buffer->GetDepthTexture());
	

	glutSwapBuffers();
	Sleep(20);



}
void resize(int w, int h)
{
	screen_width = w;
	screen_height = h;
	//�E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, w, h);
	//���e�s���ݒ�
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

	//�J�����g�f�B���N�g���ړ�
	SetCurrentDirectory("data");
	//���f���ǂݍ���
	model1.Load("Cube.obj");
	model2.Load("Cube.obj");

	//model2�͒n�ʂƂ��ė��p
	model2.SetPos(Vec3(0, -3, 0));
	model2.SetScale(Vec3(10, 1, 10));
	//���V���h�E�}�b�v�p�����_�[�^�[�Q�b�g
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
	// /*�ύX*//glew�̏�����
	glewInit();
	init();
	glutMainLoop();

	return 0;
}


