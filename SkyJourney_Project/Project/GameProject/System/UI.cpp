#include "UI.h"
std::list<Task*> m_FeatherList[];
UI::UI() :Task(ETaskPrio::eUI, EType::eUI) {
	Center_pos= CVector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 30);
}
void UI::Render() {
	if (PublicNum::Feather_Count > 0) {
		float line_num = 180 / PublicNum::Feather_Count;
		float harf_rot = 180 / PublicNum::Feather_Count / 2;
		if(PublicNum::Feather_Count==1){
			for (int i = 0; i < 180; i++) {
				float rad = DtoR(i);
				CVector2D First_pos = Center_pos + CVector2D(0, 8)+CVector2D(cos(rad), sin(rad)) * 8.0f;
				CVector2D pos = Center_pos + CVector2D(0, 8)+CVector2D(cos(rad), sin(rad)) * 40.0f;
				if(PublicNum::LightFeather_Count>0){
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
				//–¾‚é‚¢‰H{‚P‚Ì‰H‚É–¾‚é‚¢F‚Åã‘‚«
				float rot = DtoR(180 / PublicNum::Feather_Count * i + harf_rot);
				int line_num_P = std::round(line_num * i);
				int line_num_L = std::round(line_num * (i + 1));
				for (int a = line_num_P + 1; a <= line_num_L; a++) {
					float rad = DtoR(a);
					CVector2D First_pos = (Center_pos + CVector2D(cos(rad), sin(rad)) * 8.0f) + CVector2D(cos(rot), sin(rot)) * 8.0f;
					CVector2D pos = (Center_pos + CVector2D(cos(rad), sin(rad)) * 40.0f) + CVector2D(cos(rot), sin(rot)) * 8.0f;
					CVector2D LightVec = (pos - First_pos)*PublicNum::FeatherDetail_Count/ PublicNum::FeatherDetail_CountMax;
					Utility::DrawLine(First_pos, First_pos+ LightVec, LightFeatherColor);
				}
			}
		}
		//AddThroughList();
		/*int a = 0;
		for (int i = 0; i < 180; i++) {
			float rad = DtoR(i);
			CVector2D First_pos = Center_pos + CVector2D(cos(rad), sin(rad)) * 8.0f;
			CVector2D pos = Center_pos + CVector2D(cos(rad), sin(rad)) * 40.0f;
			if (ThroughList[a] != i) {
				Utility::DrawLine(First_pos, pos, CVector4D(0.39f, 0.4f, 0.3f, 1.0f));
			}
			else {
				a++;
			}
		}*/
	}
}
void UI::Update() {
	
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