#include "SkyBox.h"
SkyBox::SkyBox():Task(ETaskPrio::eSky, EType::eSky) {
	SkyBox_model = COPY_RESOURCE("SkyBox", CModelObj);
}
void SkyBox::Update() {
}
void SkyBox::Render() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	CLight::SetLighting(false);
	CCamera* back = CCamera::GetCurrent();
	CCamera c = *back;
	CMatrix matrix = c.GetViewMatrix();
	matrix.m03 = 0;
	matrix.m13 = -30;
	matrix.m23 = 0;
	c.SetViewMatrix(matrix);
	c.SetProjectionMatrix(back->GetProjectionMatrix());
	CCamera::SetCurrent(&c);
	SkyBox_model.Render();
	CLight::SetLighting(true);
	CCamera::SetCurrent(back);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}