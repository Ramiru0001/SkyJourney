#include "UI.h"
std::list<Task*> m_FeatherList[];
UI::UI() :Task(ETaskPrio::eUI, EType::eUI) {
	Center_pos= CVector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 30);
	ExclamationMark_img = COPY_RESOURCE("ExclamationMark", CImage);
}
void UI::Render() {
	FeatherRender();
	if (HOLD(CInput::eMouseR)) {
		//画面にマークを表示
		DestinationRender();
	}
}
void UI::Update() {
	DestinationUpdate();
}
CVector4D UI::ColorSet() {
	return CVector4D(0.91f, 0.56f, 0.36f, 0.3f);
}
void UI::AddThroughList() {
	if (PublicNum::Feather_Count < 1)
		return ;
	float size = 180 / PublicNum::Feather_Count;
	int i = 0;
	int a = 0;
	while (i <= PublicNum::Feather_Count) {
		if (i != 0 && i != PublicNum::Feather_Count) {
			if (PublicNum::Feather_Count < 5) {
				ThroughList[a] = std::round(i * size) - 4;
				a++;
				ThroughList[a] = std::round(i * size) - 3;
				a++;
				ThroughList[a] = std::round(i * size) - 2;
				a++;
				ThroughList[a] = std::round(i * size) - 1;
				a++;
			}
			else if (PublicNum::Feather_Count < 8) {
				ThroughList[a] = std::round(i * size) - 3;
				a++;
				ThroughList[a] = std::round(i * size) - 2;
				a++;
				ThroughList[a] = std::round(i * size) - 1;
				a++;
			}
			else {
				ThroughList[a] = std::round(i * size) - 2;
				a++;
				ThroughList[a] = std::round(i * size) - 1;
				a++;
			}
		}
		ThroughList[a] = std::round(i * size);
		a++;
		if (i != 0 && i != PublicNum::Feather_Count) {
			if (PublicNum::Feather_Count < 5) {
				ThroughList[a] = std::round(i * size) + 1;
				a++;
				ThroughList[a] = std::round(i * size) + 2;
				a++;
				ThroughList[a] = std::round(i * size) + 3;
				a++;
				ThroughList[a] = std::round(i * size) + 4;
				a++;
			}
			else if (PublicNum::Feather_Count < 8) {
				ThroughList[a] = std::round(i * size) + 1;
				a++;
				ThroughList[a] = std::round(i * size) + 2;
				a++;
				ThroughList[a] = std::round(i * size) + 3;
				a++;
			}
			else {
				ThroughList[a] = std::round(i * size) + 1;
				a++;
				ThroughList[a] = std::round(i * size) + 2;
				a++;
			}
		}
		i++;
	}
	maxThroughNum = a;
}   
void UI::FeatherRender() {
	if (CShadow::GetInstance()->GetState() == CShadow::eShadow)return;
	if (PublicNum::Feather_Count > 0) {
		float line_num = 180 / PublicNum::Feather_Count;
		float harf_rot = 180 / PublicNum::Feather_Count / 2;
		if (PublicNum::Feather_Count == 1) {
			for (int i = 0; i < 180; i++) {
				float rad = DtoR(i);
				CVector2D First_pos = Center_pos + CVector2D(0, 8) + CVector2D(cos(rad), sin(rad)) * 8.0f;
				CVector2D pos = Center_pos + CVector2D(0, 8) + CVector2D(cos(rad), sin(rad)) * 40.0f;
				if (PublicNum::LightFeather_Count > 0) {
					Utility::DrawLine(First_pos, pos, LightFeatherColor);
				}
				else {
					Utility::DrawLine(First_pos, pos, DarkFeatherColor);
				}
			}
		}
		else {
			for (int i = 0; i < PublicNum::Feather_Count; i++) {
				float rot = DtoR(180 / PublicNum::Feather_Count * i + harf_rot);
				int line_num_P = std::round(line_num * i);
				int line_num_L = std::round(line_num * (i + 1));
				for (int a = line_num_P + 1; a <= line_num_L; a++) {
					float rad = DtoR(a);
					CVector2D First_pos = (Center_pos + CVector2D(cos(rad), sin(rad)) * 8.0f) + CVector2D(cos(rot), sin(rot)) * 8.0f;
					CVector2D pos = (Center_pos + CVector2D(cos(rad), sin(rad)) * 40.0f) + CVector2D(cos(rot), sin(rot)) * 8.0f;
					if (PublicNum::LightFeather_Count > i) {
						Utility::DrawLine(First_pos, pos, LightFeatherColor);
					}
					else {
						Utility::DrawLine(First_pos, pos, DarkFeatherColor);
					}
				}
			}
		}
		if (PublicNum::FeatherDetail_Count != 0) {
			int i = PublicNum::LightFeather_Count;
			if (i <= PublicNum::Feather_Count) {
				//明るい羽＋１の羽に明るい色で上書き
				float rot = DtoR(180 / PublicNum::Feather_Count * i + harf_rot);
				int line_num_P = std::round(line_num * i);
				int line_num_L = std::round(line_num * (i + 1));
				for (int a = line_num_P + 1; a <= line_num_L; a++) {
					float rad = DtoR(a);
					CVector2D First_pos = (Center_pos + CVector2D(cos(rad), sin(rad)) * 8.0f) + CVector2D(cos(rot), sin(rot)) * 8.0f;
					CVector2D pos = (Center_pos + CVector2D(cos(rad), sin(rad)) * 40.0f) + CVector2D(cos(rot), sin(rot)) * 8.0f;
					CVector2D LightVec = (pos - First_pos) * PublicNum::FeatherDetail_Count / PublicNum::FeatherDetail_CountMax;
					Utility::DrawLine(First_pos, First_pos + LightVec, LightFeatherColor);
				}
			}
		}
	}
}
void UI::DestinationRender() {
	//ステージごとにゴールの位置を取得し、2Dベクトルに治し、その方向に描画
	CVector3D Goal_pos[] = { DEFAULT_POS,
		CVector3D(-120.194,34.3038,8.14138),
	};
	Ex_pos3D = Goal_pos[PublicNum::Stage_Num];
	//2D画像の表示。
	CVector3D pos2d = Utility::WorldToScreen(Ex_pos3D);
	if (pos2d.z < 0) return;
	pos2d.x = min(max(pos2d.x, 0+25), SCREEN_WIDTH - 50+25);
	pos2d.y = min(max(pos2d.y, 0+30+25), SCREEN_HEIGHT - 50 - 80+25);
	ExclamationMark_img.SetSize(50, 50);
	ExclamationMark_img.SetPos(pos2d.x-25, pos2d.y-25);
	ExclamationMark_img.Draw();
}
void UI::DestinationUpdate() {
	
}