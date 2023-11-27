	#pragma once

//#include "GL.h"
#include <map>
#include <string>
class Shader {
public:
	//�V�F�[�_�[����location�ɑΉ�
	enum {
		eVertexLocation,	//layout(location = 0) 
		eNormalLocation,	//layout(location = 1) 
		eTexcoordlLocation,	//layout(location = 2) 
	};

private:
	GLuint vertexShader;
	GLuint fragShader;

	GLuint program;
	GLint linked;
	static std::map<std::string, Shader*> m_instances;


	/*!
	@brief	�R�[�h����V�F�[�_�v���O�������쐬
	@param program	[in]	�V�F�[�_�[�v���O����
	@param shader	[in]	�V�F�[�_�[�I�u�W�F�N�g�@glCreateShader(GL_VERTEX_SHADER),glCreateShader(GL_FRAGMENT_SHADER)
	@param file		[in]	�V�F�[�_�[�t�@�C����
	@retval	����
	**/
	bool Load(GLuint shader, const char* file);
	/*!
	@brief	�R�[�h����V�F�[�_�v���O�������쐬
	@param program	[in]	�V�F�[�_�[�v���O����
	@param shader	[in]	�V�F�[�_�[�I�u�W�F�N�g�@glCreateShader(GL_VERTEX_SHADER),glCreateShader(GL_FRAGMENT_SHADER)
	@param code		[in]	�V�F�[�_�[�\�[�X�R�[�h
	@retval	����
	**/
	bool ReadCode(GLuint shader, const char* code);

public:

	/*!
	@brief	�R���p�C���ς݃V�F�[�_�[�̎擾
	@param name [in] ���O
	@retval	�V�F�[�_�[�C���X�^���X
	**/
	static Shader* GetInstance(std::string name);

	/*!
	@brief	�g�ݍ��ݍς݃V�F�[�_�[�̐���
	@param name [in] ���O
	@param vertex_shader_file	[in]	���_�V�F�[�_�̃t�@�C����
	@param fragment_shader_file	[in]	�t���O�����g�V�F�[�_�̃t�@�C����
	@retval	�V�F�[�_�[�C���X�^���X
	**/
	static Shader* CreateInstance(std::string name,const char *vertex_shader_file, const char* fragment_shader_file);
	/*!
	@brief	�R���X�g���N�^
			�V�F�[�_�I�u�W�F�N�g�̐����̂�
	**/
	Shader();

	/*!
	@brief	�R���X�g���N�^
			�V�F�[�_�[�t�@�C�����琶��
	@param vertex_shader_file	[in]	���_�V�F�[�_�̃t�@�C����
	@param fragment_shader_file	[in]	�t���O�����g�V�F�[�_�̃t�@�C����
	**/
	Shader(const char* vertex_shader_file,const char* fragment_shader_file);
	/*!
	@brief	�f�X�g���N�^
	**/
	~Shader();

	/*!
	@brief	�t�@�C������V�F�[�_�v���O�������쐬
	@param vertexPath	[in]	���_�V�F�[�_�̃t�@�C����
	@param fragPath	[in]		�t���O�����g�V�F�[�_�̃t�@�C����
	@retval	����
	**/
	bool Load(const char* vertexPath,const char*  fragPath);
	/*!
	@brief	�t�@�C������V�F�[�_�v���O�������X�ɍ쐬
	@param	path	[in]	�V�F�[�_�[�̃t�@�C����
	@param	type	[in]	�V�F�[�_�[�I�u�W�F�N�g�̎��(GL_VERTEX_SHADER,GL_FRAGMENT_SHADER)
	@retval	����
	**/
	bool Load(const char* path, GLuint type);
	/*!
	@brief	�\�[�X�R�[�h����V�F�[�_�v���O�������X�ɍ쐬
	@param	code	[in]	�V�F�[�_�[�̃\�[�X�R�[�h
	@param	type	[in]	�V�F�[�_�[�I�u�W�F�N�g�̎��(GL_VERTEX_SHADER,GL_FRAGMENT_SHADER)
	@retval	����
	**/
	bool ReadCode(const char* path,GLuint type);

	/*!
	@brief	�\�[�X�R�[�h����V�F�[�_�v���O�������쐬
	@param vertexcode	[in]	���_�V�F�[�_�̃\�[�X�R�[�h
	@param fragcode		[in]	�t���O�����g�V�F�[�_�̃\�[�X�R�[�h
	@retval	����
	**/
	bool ReadCode(const char* vertexcode, const char* fragcode);

	/*!
	@brief	�V�F�[�_�[�L����
	@retval	����
	**/
	void Enable();
	/*!
	@brief	�V�F�[�_�[������
	@retval	����
	**/
	void Disable();
	/*!
	@brief	�V�F�[�_�[�v���O�����̎擾
	@retval	�V�F�[�_�[�v���O����
	**/
	GLuint GetProgram() const{
		return program;
	}


};