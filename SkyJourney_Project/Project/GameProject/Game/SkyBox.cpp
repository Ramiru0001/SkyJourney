#include "SkyBox.h"
SkyBox::SkyBox(int num):Task(ETaskPrio::eSky, EType::eSky) {
	ColorNum = num;
	if (ColorNum == Normal) {
		SkyBox_model = COPY_RESOURCE("SkyBox", CModelObj);
	}
	else if(ColorNum==Sand){
		SkyBox_model = COPY_RESOURCE("SkyBoxSand", CModelObj);
	}
}
void SkyBox::Update() {
	if (PublicNum::Stage_Num == PublicNum::StageNum::Desert) {
		ColorNum = Sand;
	}
	if (ColorNum == Normal) {
		SkyBox_model = COPY_RESOURCE("SkyBox", CModelObj);
	}
	else if (ColorNum == Sand) {
		SkyBox_model = COPY_RESOURCE("SkyBoxSand", CModelObj);
	}
}
void SkyBox::Render() {
	if (CShadow::GetInstance()->GetState() == CShadow::eShadow)return;
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