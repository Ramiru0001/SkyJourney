#include "System/GL.h"

/*Model.h�Œ�`�ς�
//���_�z��\����
struct SVertex {
	Vec3 v;
	Vec3 n;
	Vec2 t;
};
*/
//�����̂̒��_�z��
SVertex* cube_vertex = nullptr;

//[test.vert]���쐬
/*
#version 430
//���_���W
layout(location = 0) in vec3	Vertex;
//���ex�r���[x���[���h�ϊ��s��
uniform mat4 PVWMatrix;

void main(void){
	//���_��ϊ��s��ŃN���b�v��Ԃł̍��W�ɕϊ�
	gl_Position = PVWMatrix * vec4(Vertex, 1.0);
}
*/
//[test.frag]���쐬
/*
#version 430

//�`�悳���F
out vec4 frag_color;

void main(void) {
	//(Red=1.0, Green=0.0, Blue=0.0, alpha=1.0(�s�����j)
	//�Ԃ��o��
	frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}
*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float r = 0;
	r += 0.1f;
	if (r >= M_PI * 2) r = 0;

	
	//�r���[�s��i�J�����j
	Camera::s_view = Matrix4x4::MLookAtView(Vec3(10.0, 10.0, 10.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
	//���[���h�s��i��]�̂݁j
	Matrix4x4 matrix = Matrix4x4::MRotationY(r);

	

	//A.�Œ�V�F�[�_�[�p
	
	//���f���r���[�s��̐ݒ�
	glLoadMatrixf((Camera::s_view * matrix).f);

	//�L����
	glEnableClientState(GL_VERTEX_ARRAY);
	//�f�[�^�̊֘A�t��
	glVertexPointer(3, GL_FLOAT, sizeof(SVertex), &cube_vertex->v);//���W
	//�`��
	glDrawArrays(GL_QUADS, 0, 4 * 6); //�`��(4�_�~6��=24���_�j
	//������
	glDisableClientState(GL_VERTEX_ARRAY);
	

	//B.����V�F�[�_�[�p
	/*
	Shader* s = Shader::GetInstance("Test");
	//���V�F�[�_�[�L����
	s->Enable();

	GLuint p = s->GetProgram();
	//���V�F�[�_�[�֊e��l��n��
	//���ex�r���[x���[���h�ϊ��s��
	glUniformMatrix4fv(glGetUniformLocation(p, "PVWMatrix"), 1, GL_FALSE, (Camera::s_proj * Camera::s_view * matrix).f);

	//���L����
	glEnableVertexAttribArray(0);

	//���f�[�^�̊֘A�t��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), &cube_vertex->v);//���W
	//�`��
	glDrawArrays(GL_QUADS, 0, 4 * 6);	 //�`��(4�_�~6��=24���_�j

	//��������
	glDisableVertexAttribArray(0);

	//���V�F�[�_�[������
	s->Disable();
	*/

	glutSwapBuffers();
	Sleep(20);



}
void resize(int w, int h)
{
	//�E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, w, h);
	//�����ϊ��s��̐ݒ�
	glMatrixMode(GL_PROJECTION);
	//���e�s���ݒ�
	Camera::s_proj = Matrix4x4::MPerspective(DtoR(60.0f), (float)w / float(h), 1.0, 100.0);
	glLoadMatrixf(Camera::s_proj.f);
	//���f���r���[�ϊ��s��̐ݒ�
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

	//�J�����g�f�B���N�g���̐ݒ�
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
			{ 3, 2, 1, 0 }, /* A-B-C-D �����Ԗ� */
			{ 2, 6, 5, 1 }, /* B-F-G-C �����Ԗ� */
			{ 6, 7, 4, 5 }, /* F-E-H-G �����Ԗ� */
			{ 7, 3, 0, 4 }, /* E-A-D-H �����Ԗ� */
			{ 0, 1, 5, 4 }, /* E-F-B-A �����Ԗ� */
			{ 7, 6, 2, 3 }  /* D-C-G-H �����Ԗ� */
		};
		//�����̂̒��_�z��̐���
		cube_vertex = new SVertex[4 * 6];
		int idx = 0;
		for (int j = 0; j < 6; ++j) {
			for (int i = 0; i < 4; ++i) {
				cube_vertex[idx].v = vertex[face[j][i]];
				idx++;
			}
		}
	}
	//B.����V�F�[�_�[�p
	//�V�F�[�_�[�ǂݍ���
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


