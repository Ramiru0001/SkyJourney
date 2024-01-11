#include "SkyBox.h"
SkyBox::SkyBox(int num):Task(ETaskPrio::eSky, EType::eSky) {
	ColorNum = num; 
	Normal_Model = COPY_RESOURCE("SkyBox", CModelObj);
	Sand_Model = COPY_RESOURCE("SkyBoxSand", CModelObj);
	Purple_Model = COPY_RESOURCE("SkyBoxPurple", CModelObj);
	Night_Model = COPY_RESOURCE("SkyBoxNight", CModelObj);
	LightPurple_Model = COPY_RESOURCE("SkyBoxLightPurple", CModelObj);
}
void SkyBox::Update() {
	if (PublicNum::Stage_Num == PublicNum::StageNum::Desert) {
		ColorNum = Lightpurple;
	}else if (PublicNum::Stage_Num == PublicNum::StageNum::Volcano) {
		ColorNum = Purple;
	}else if(PublicNum::Stage_Num == PublicNum::StageNum::Ending) {
		ColorNum = Purple;
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
	switch (ColorNum) {
	case Normal:
		Normal_Model.Render();
		break;
	case Sand:
		Sand_Model.Render();
		break;
	case Purple:
		Purple_Model.Render();
		break;
	case Lightpurple:
		LightPurple_Model.Render();
		break;
	case Night:
		Night_Model.Render();
		break;
	}
	CLight::SetLighting(true);
	CCamera::SetCurrent(back);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}