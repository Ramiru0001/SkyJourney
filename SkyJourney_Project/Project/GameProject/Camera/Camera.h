#pragma once
class Camera :public Task {
public :
	/*enum {
		FixedPoint,
		WithPlayer,
	};*/
	CVector3D m_at;//’‹“_
	float fov = DtoR(60.0f);//‹–ìŠp
	float m_dist = 10.0f;//’‹“_‚Ü‚Å‚Ì‹——£
	float m_speed = 0.003f;//‰ñ“]‘¬“xŒW”
	float z_near = 0.1f;//Å‚à‹ß‚¢•`‰æ‹——£
	float z_far = 1000.0f;//Å‚à‰“‚¢•`‰æ‹——£
	CVector2D mouse_vec;//ƒ}ƒEƒX‚ÌˆÚ“®—Ê
public:
	Camera();
	~Camera();
	void Update();
};