#pragma once
class Camera :public Task {
public :
	/*enum {
		FixedPoint,
		WithPlayer,
	};*/
	CVector3D m_at;//�����_
	float fov = DtoR(60.0f);//����p
	float m_dist = 10.0f;//�����_�܂ł̋���
	float m_speed = 0.003f;//��]���x�W��
	float z_near = 0.1f;//�ł��߂��`�拗��
	float z_far = 1000.0f;//�ł������`�拗��
	CVector2D mouse_vec;//�}�E�X�̈ړ���
public:
	Camera();
	~Camera();
	void Update();
};