#include "CRendaring.h"
CRendaring* CRendaring::m_instance = nullptr;
CRendaring::CRendaring(int screen_width, int screen_height,float focus): m_gbuffer(nullptr), m_scene(nullptr), 
m_blurtmp(nullptr), m_blur(nullptr), m_blur1(nullptr), m_blur2(nullptr),
m_focus(focus)
{

	//�`��惌���_�[�^�[�Q�b�g(�ʏ�A���ˌ�)
	m_gbuffer = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0), 2);
	//�O���A�ς�
	m_scene = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));

	m_tmp_buffer = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 1));

	//�u���[�p
	m_blurtmp = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
	m_blur = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
	m_blur1 = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
	m_blur2 = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
}

CRendaring::~CRendaring()
{
	if (m_gbuffer) {delete m_gbuffer; m_gbuffer = nullptr;}
	if (m_scene) { delete m_scene; m_scene = nullptr; }
	if (m_blurtmp) { delete m_blurtmp; m_blurtmp = nullptr; }
	if (m_blur) { delete m_blur; m_blur = nullptr; }
	if (m_blur1) { delete m_blur1; m_blur1 = nullptr; }
	if (m_blur2) { delete m_blur2; m_blur2 = nullptr; }
}

CRendaring* CRendaring::GetInstance()
{
	return m_instance;
}

void CRendaring::ClearInstance()
{
	if (m_instance) delete m_instance;
	m_instance = nullptr;
}

void CRendaring::CreatInstance(int screen_width, int screen_height,float focus)
{

	if (!m_instance) m_instance = new CRendaring(screen_width, screen_height, focus);
}

//�|�X�g�G�t�F�N�g�ł悭�g�p����̂Ŋ֐���
//��ʂ����ς��Ɏl�p�`�Ƃ��ĕ`��
void CRendaring::DrawFillQuad() {
	CVector3D vertices[] = {
		CVector3D(0,0,0),CVector3D(1,0,0),
		CVector3D(1,1,0),CVector3D(0,1,0)
	};
	glEnableVertexAttribArray(CShader::eVertexLocation);
	glVertexAttribPointer(CShader::eVertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(CShader::eVertexLocation);
}

/// <summary>
/// �u���[
/// </summary>
/// <param name="src">���摜</param>
/// <param name="tmp">�ꎞ���ʗp</param>
/// <param name="result">�o�͌��ʗp</param>
/// <param name="pow">�u���[�W��</param>
/// <param name="pix">�u���[�͈�</param>
void CRendaring::Blur(CTexture* src, CTextureFrame* tmp, CTextureFrame* result, float pow, float pix) {
	//�u���[�̓x��
	float weight[10];
	float t = 0.0;
	float d = pow * pow / 100;
	for (int i = 0; i < 10; i++) {
		float r = 1.0 + 2.0 * i;
		float w = exp(-0.5 * (r * r) / d);
		weight[i] = w;
		if (i > 0) { w *= 2.0; }
		t += w;
	}
	for (int i = 0; i < 10; i++) {
		weight[i] /= t;
	}

	//�u���[�p�V�F�[�_�[
	CShader* s = CShader::GetInstance("GaussianBlur");
	s->Enable();

	//���ځi���u���[�j
	tmp->BeginDraw();
	//���摜���Z�b�g
	src->MapTexture();
	glUniform1i(glGetUniformLocation(s->GetProgram(), "texture"), 0);
	glUniform1i(glGetUniformLocation(s->GetProgram(), "gaussian"), 1);
	glUniform1fv(glGetUniformLocation(s->GetProgram(), "weight"), 10, weight);
	glUniform1i(glGetUniformLocation(s->GetProgram(), "horizontal"), 1);
	glUniform2f(glGetUniformLocation(s->GetProgram(), "scale"), 1.0f / 1920 * pix, 1.0f / 1080 * pix);
	//��ʕ`��
	DrawFillQuad();
	src->UnmapTexture();
	tmp->EndDraw();

	//���ځi����ɏc�u���[�j
	result->BeginDraw();
	tmp->GetTexture()->MapTexture();
	glUniform1i(glGetUniformLocation(s->GetProgram(), "texture"), 0);
	glUniform1i(glGetUniformLocation(s->GetProgram(), "gaussian"), 1);
	glUniform1fv(glGetUniformLocation(s->GetProgram(), "weight"), 10, weight);
	glUniform1i(glGetUniformLocation(s->GetProgram(), "horizontal"), 0);
	glUniform2f(glGetUniformLocation(s->GetProgram(), "scale"), 1.0f / 1920 * pix, 1.0f / 1080 * pix);
	DrawFillQuad();
	s->Disable();
	tmp->GetTexture()->UnmapTexture();
	result->EndDraw();

}

void CRendaring::Render(std::function<void()> render)
{


	//���f���̕`��
	//A.�e�t���`��
	if (CShadow::GetInstance()) {
		CShadow::GetInstance()->Render(render,m_gbuffer);
	} else {
	//B.�e�����`��
		m_gbuffer->BeginDraw();
		render();
		m_gbuffer->EndDraw();
	}
	//�f�v�X�e�X�gOFF
	glDisable(GL_DEPTH_TEST);
	CTexture* t = nullptr;
	//�֊s�`��
	if (0) {
		m_tmp_buffer->BeginDraw();
		CTextureFrame::Draw(0, 0, m_gbuffer->GetWidth(), m_gbuffer->GetHeight(), m_gbuffer->GetTexture());
		//�֊s�`��p�V�F�[�_(�����ŗ֊s��`�悵�Ă���)
		CShader* s = CShader::GetInstance("Edge");
		s->Enable();

		glActiveTexture(GL_TEXTURE0);
		//�f�v�X�o�b�t�@��`��Ŏg�p����
		m_gbuffer->GetDepthTexture()->MapTexture();
		glUniform1i(glGetUniformLocation(s->GetProgram(), "depth"), 0);
		//��ʕ`��
		DrawFillQuad();
		m_gbuffer->GetDepthTexture()->UnmapTexture();
		s->Disable();
		m_tmp_buffer->EndDraw();
		t = m_tmp_buffer->GetTexture();
	}
	else {
		t = m_gbuffer->GetTexture();
	}



	//�O���[
	if(1){
		//���ˌ��Ƀu���[��������
		Blur(m_gbuffer->GetTexture(1), m_blurtmp, m_blur, 60.0f, 2.0f);

		m_scene->BeginDraw();
		//�ʏ�`��{�O���A
		static CShader* s = nullptr;
		if (!s)
			s = new CShader("GlareMix");
		s->Enable();
		//�e�N�X�`���[0�̃X���b�g�֒ʏ�
		glActiveTexture(GL_TEXTURE0);
		t->MapTexture();
		//�e�N�X�`���[1�̃X���b�g�փO���A
		glActiveTexture(GL_TEXTURE1);
		m_blur->GetTexture()->MapTexture();
		//����X���b�g��0�֖߂�
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "texture1"), 0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "texture2"), 1);
		//��ʕ`��
		DrawFillQuad();
		//�V�F�[�_����
		s->Disable();
		m_scene->EndDraw();
	}
	CTextureFrame::Draw(0, 0, m_scene->GetWidth(), m_scene->GetHeight(), m_scene->GetTexture(0));
	return;
	
	//��ʊE�[�x
	if(0){
		//�u���[��
		Blur(m_scene->GetTexture(), m_blurtmp, m_blur1, 30.0f);
		//�u���[��
		Blur(m_scene->GetTexture(), m_blurtmp, m_blur2, 60.0f);

		//���E�[�x�p�V�F�[�_�[
		CShader* s = CShader::GetInstance("DepthOfField");
		s->Enable();
		//�e�N�X�`���[0�̃X���b�g�֐[�x�o�b�t�@
		glActiveTexture(GL_TEXTURE0);
		m_gbuffer->GetDepthTexture()->MapTexture();
		//�e�N�X�`���[1�̃X���b�g�֒ʏ탌���_�����O�摜
		glActiveTexture(GL_TEXTURE1);
		m_scene->GetTexture()->MapTexture();
		//�e�N�X�`���[2�̃X���b�g�փu���[��
		glActiveTexture(GL_TEXTURE2);
		m_blur1->GetTexture()->MapTexture();
		//�e�N�X�`���[3�̃X���b�g�փu���[��
		glActiveTexture(GL_TEXTURE3);
		m_blur2->GetTexture()->MapTexture();
		//����X���b�g��0�֖߂�
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "depthTexture"), 0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "sceneTexture"), 1);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "blurTexture1"), 2);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "blurTexture2"), 3);
		glUniform1f(glGetUniformLocation(s->GetProgram(), "offset"), m_focus);
		//��ʕ`��
		DrawFillQuad();
		//�V�F�[�_����
		s->Disable();
	}
	//�f�v�X�e�X�gON
	glEnable(GL_DEPTH_TEST);

}