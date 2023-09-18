#include <d3d9.h>

#include "../ImGUI/imgui_internal.h"
Vector2 screen_center = { 0, 0 };
D3DCOLOR rainbow() {

	static float x = 0, y = 0;
	static float r = 0, g = 0, b = 0;

	if (y >= 0.0f && y < 255.0f) {
		r = 255.0f;
		g = 0.0f;
		b = x;
	}
	else if (y >= 255.0f && y < 510.0f) {
		r = 255.0f - x;
		g = 0.0f;
		b = 255.0f;
	}
	else if (y >= 510.0f && y < 765.0f) {
		r = 0.0f;
		g = x;
		b = 255.0f;
	}
	else if (y >= 765.0f && y < 1020.0f) {
		r = 0.0f;
		g = 255.0f;
		b = 255.0f - x;
	}
	else if (y >= 1020.0f && y < 1275.0f) {
		r = x;
		g = 255.0f;
		b = 0.0f;
	}
	else if (y >= 1275.0f && y < 1530.0f) {
		r = 255.0f;
		g = 255.0f - x;
		b = 0.0f;
	}

	x += Visuals::time;//скорость изменения цветов
	if (x >= 255.0f)
		x = 0.0f;

	y += Visuals::time; //скорость изменения цветов
	if (y > 1530.0f)
		y = 0.0f;


	return D3DCOLOR_ARGB((int)r, (int)g, (int)b, 255);
}

D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}

void Skeleton(BasePlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}
	if ((int)BasePlayer->GetHealth() > 0)
	{
		if (LocalPlayer.BasePlayer->IsTeamMate(BasePlayer->GetSteamID()))
		{
			for (int j = 0; j < 15; j += 3) {
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::LimeGreen, 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::LimeGreen);
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::LimeGreen, 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::LimeGreen);
			}

			//draw add lines
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen);
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen);
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen);
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen);
		}
		else
		{
			for (int j = 0; j < 15; j += 3) {
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			}

			//draw add lines
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
		}

	}
	else
	{
		for (int j = 0; j < 15; j += 3) {
			Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Red, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Red);
			Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Red, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Red);
		}

		//draw add lines
		Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red);
		Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red);
		Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red);
		Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red);
	}
	//draw main lines

	//draw main lines
}
void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color) {
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / PlayerEsp::cornerfloat, Entity_y }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / PlayerEsp::cornerfloat, Entity_y }, color);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / PlayerEsp::cornerfloat }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / PlayerEsp::cornerfloat }, color);

	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / PlayerEsp::cornerfloat, Entity_y }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / PlayerEsp::cornerfloat, Entity_y }, color);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / PlayerEsp::cornerfloat }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / PlayerEsp::cornerfloat }, color);

	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / PlayerEsp::cornerfloat, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / PlayerEsp::cornerfloat, Entity_y + Entity_h }, color);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / PlayerEsp::cornerfloat }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / PlayerEsp::cornerfloat }, color);

	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / PlayerEsp::cornerfloat, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / PlayerEsp::cornerfloat, Entity_y + Entity_h }, color);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / PlayerEsp::cornerfloat }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / PlayerEsp::cornerfloat }, color);
}

namespace string
{

	inline char buffer[512];

	inline const char* format(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		LI_FIND(vsnprintf)(buffer, 512, fmt, args);
		va_end(args);
		return buffer;
	}
}

namespace Vars1 {
	namespace Radar {
		bool ShowRadarNpc = false;
		bool Enable1 = false;
		bool Enable = false;
		bool ShowRadarBackground = false;
		bool ShowRadarPlayer = false;
		bool ShowRadarSleeper = false;
		float Pos_X = 0;
		float Pos_Y = 0;
		float Radar_Size = 200.f;
		float Radar_Range = 300.f;
		bool EnableDinamicRadar = false;
		bool ShowRadarNpcname = false;
	}
}


double deg2rad(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}

inline D2D1::ColorF ConverToRGB(float R, float G, float B)
{
	return (D2D1::ColorF::ColorF(R / 255.f, G / 255.f, B / 255.f));
}
bool OOFF(BasePlayer* ply) {
	Vector3 pos = ply->GetBoneByID(head);
	Vector2 screen;

	if (!w2s(pos, screen))
		return true;

	float num = Math::Distance_2D(screen_center, screen);
	return num > 1000.f;
}
void OOF(BasePlayer* ply, const D2D1::ColorF color) {
	if (PlayerEsp::sleeperignore && ply->HasFlags(PlayerFlags::Sleeping)) return;
	if (!ply) return;
	if (!LocalPlayer.BasePlayer->isCached()) return;

	if (PlayerEsp::oof_arrows) {
		if (OOFF(ply)) {
			Vector3 local = LocalPlayer.BasePlayer->GetBoneByID(head);
			float y = local.x - ply->GetBoneByID(head).x;
			float x = local.z - ply->GetBoneByID(head).z;
			Vector2 eulerAngles = LocalPlayer.BasePlayer->GetVA();
			float num = atan2(y, x) * 57.29578f - 180.f - eulerAngles.y;
			Vector2 point = Render::Object.CosTanSinLineH(num, 5.f, screen_center.x, screen_center.y, 200.f);

			Render::Object.RectangleFillPoint(point, 9.f, 9.f, D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f));
			Render::Object.RectanglePoint(point, 9.f, 9.f, color);
		}
	}
}
class CBounds {
public:
	Vector3 center;
	Vector3 extents;
};
typedef bool(__stdcall* IsDucked)(BasePlayer*);
void Box3D(BasePlayer* player, D2D1::ColorF color) {
	CBounds bounds = CBounds();

	IsDucked ducked = (IsDucked)(Storage::gBase + 0x7CF1D0); // public bool IsDucked()
	if (ducked(player)) {
		bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->HasFlags(PlayerFlags::Wounded) || player->HasFlags(PlayerFlags::Sleeping)) {
			bounds.center = player->GetBoneByID(pelvis);
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		else {
			bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}

	float y = Math::EulerAngles(player->eyest()->get_rotation()).y;
	Vector3 center = bounds.center;
	Vector3 extents = bounds.extents;
	Vector3 frontTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 frontBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 backTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector3 backBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);

	Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
	if (w2s(frontTopLeft, frontTopLeft_2d) &&
		w2s(frontTopRight, frontTopRight_2d) &&
		w2s(frontBottomLeft, frontBottomLeft_2d) &&
		w2s(frontBottomRight, frontBottomRight_2d) &&
		w2s(backTopLeft, backTopLeft_2d) &&
		w2s(backTopRight, backTopRight_2d) &&
		w2s(backBottomLeft, backBottomLeft_2d) &&
		w2s(backBottomRight, backBottomRight_2d)) {

		Render::Object.LineP(frontTopLeft_2d, frontTopRight_2d, color, 1.5f, true);
		Render::Object.LineP(frontTopRight_2d, frontBottomRight_2d, color, 1.5f, true);
		Render::Object.LineP(frontBottomRight_2d, frontBottomLeft_2d, color, 1.5f, true);
		Render::Object.LineP(frontBottomLeft_2d, frontTopLeft_2d, color, 1.5f, true);
		Render::Object.LineP(backTopLeft_2d, backTopRight_2d, color, 1.5f, true);
		Render::Object.LineP(backTopRight_2d, backBottomRight_2d, color, 1.5f, true);
		Render::Object.LineP(backBottomRight_2d, backBottomLeft_2d, color, 1.5f, true);
		Render::Object.LineP(backBottomLeft_2d, backTopLeft_2d, color, 1.5f, true);
		Render::Object.LineP(frontTopLeft_2d, backTopLeft_2d, color, 1.5f, true);
		Render::Object.LineP(frontTopRight_2d, backTopRight_2d, color, 1.5f, true);
		Render::Object.LineP(frontBottomRight_2d, backBottomRight_2d, color, 1.5f, true);
		Render::Object.LineP(frontBottomLeft_2d, backBottomLeft_2d, color, 1.5f, true);
	}
}

void ESP(BasePlayer* BP, BasePlayer* LP)
{
	bool PlayerSleeping = BP->HasFlags(16);
	bool PlayerWounded = BP->HasFlags(64);
	if (PlayerEsp::sleeperignore && PlayerSleeping)
		return;

	if (PlayerEsp::skeleton && !BP->IsNpc())
		Skeleton(BP);

	Vector2 tempFeetR, tempFeetL;

	if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL))
	{
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;

		Vector2 ScreenPos;
		Vector2 tempHead;
		if (LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
		{
			Vector2 leftTopCorner = tempHead - Vector2(0.4f, 0.f);
			Vector2 rightBottomCorner = tempFeetR;


			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->GetBoneByID(l_foot).midPoint(BP->GetBoneByID(r_foot));
			int CurPos = 0;
			auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (LocalPlayer.WorldToScreen(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && LocalPlayer.WorldToScreen(middlePointWorld, middlePointPlayerFeet))
			{
				if (PlayerEsp::box) {
					if (PlayerEsp::boxstyle == 0 && !BP->IsNpc()) {
						if ((int)BP->GetHealth() > 0)
						{
							if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
							{
								Render::Object.RoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, 2.5f, D2D1::ColorF::Black, 1.f);
								Render::Object.RoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, 2.5f, D2D1::ColorF::LimeGreen, 1.f);
							}
							else
							{
								Render::Object.RoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, 2.5f, D2D1::ColorF::Black, 1.f);
								Render::Object.RoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, 2.5f, FLOAT4TOD3DCOLOR(ColorsNShit::BoxColor), 1.f);
							}
						}
						else
						{
							Render::Object.RoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, 2.5f, D2D1::ColorF::Black, 1.f);
							Render::Object.RoundedRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, 2.5f, D2D1::ColorF::OrangeRed, 1.f);
						}
					}
					if (PlayerEsp::boxstyle == 1 && !BP->IsNpc()) {
						if ((int)BP->GetHealth() > 0)
						{
							if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
							{
								CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::LimeGreen);
							}
							else
							{
								CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, FLOAT4TOD3DCOLOR(ColorsNShit::BoxColor));
							}
						}
						else
						{
							CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::OrangeRed);
						}
					}
					if (PlayerEsp::boxstyle == 2 && !BP->IsNpc()) {
						if ((int)BP->GetHealth() > 0)
						{
							if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
							{
								Box3D(BP, D2D1::ColorF::LimeGreen);
							}
							else
							{
								Box3D(BP, FLOAT4TOD3DCOLOR(ColorsNShit::BoxColor));
							}
						}
						else
						{
							Box3D(BP, D2D1::ColorF::OrangeRed);
						}
					}
				}
				if (PlayerEsp::healthbar && !BP->IsNpc())
				{
					float maxheal = 100.f;
					int health = BP->GetHealth();
					Render::Object.FillRectangle({ Entity_x + (Entity_w / 2) + -50, Entity_y + 0 }, { 100, 5 }, D2D1::ColorF::Black);
					//Render::Object.FillRectangle({ Entity_x + (Entity_w / 2) + -49, Entity_y + 32  }, { 99 * (health / maxheal), 7 }, D2D1::ColorF::Yellow);
					if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(r_foot)) < 301)
					{
						if ((int)BP->GetHealth() <= 33)
						{
							Render::Object.FillRectangle({ Entity_x + (Entity_w / 2) + -50, Entity_y + 0 }, { 100 * (health / maxheal), 5 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
						{
							Render::Object.FillRectangle({ Entity_x + (Entity_w / 2) + -50, Entity_y + 0 }, { 100 * (health / maxheal), 5 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 67)
						{
							Render::Object.FillRectangle({ Entity_x + (Entity_w / 2) + -50, Entity_y + 0 }, { 100 * (health / maxheal), 5 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
					}
				}
				if (PlayerEsp::healthbar1 && !BP->IsNpc())
				{
					int separators = 0;
					float flHeight = Entity_h / separators;
					int health = (int)BP->GetHealth();
					float maxheal = 100.f;
					if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201)
					{
						if ((int)BP->GetHealth() <= 33)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 67)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						Render::Object.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						for (int i = 1; i < separators; i++)
							Render::Object.Line(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + i * flHeight }, Vector2{ Entity_x + Entity_w - 4.f ,Entity_y + i * flHeight }, D2D1::ColorF::Black());
						int i = i - 1;
					}
				}
				if (PlayerEsp::healthbar2 && !BP->IsNpc()) {
					int health = (int)BP->GetHealth();
					float maxheal = 100.f;
					//float maxheal = (BP->IsNpc() ? 300.f : 100.f);
					if ((int)BP->GetHealth() <= 33) {
						Render::Object.FillRectangle(Vector2{ middlePointPlayerFeet.x - 15, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 30 * (health / maxheal), 3 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
					}
					if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66) {
						Render::Object.FillRectangle(Vector2{ middlePointPlayerFeet.x - 15, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 30 * (health / maxheal), 3 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
					}
					if ((int)BP->GetHealth() >= 67) {
						Render::Object.FillRectangle(Vector2{ middlePointPlayerFeet.x - 15, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 30 * (health / maxheal), 3 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
					}
					Render::Object.Rectangle(Vector2{ middlePointPlayerFeet.x - 15, middlePointPlayerFeet.y + CurPos + 5 }, Vector2{ 30, 3 }, D2D1::ColorF::Black, 0.5f);
				}
				if (PlayerEsp::name && !BP->IsNpc())
				{
					int health = (int)BP->GetHealth();
					wchar_t name[64];
					_swprintf(name, L"%s [%d M]", BP->GetName(), (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)));
					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 15.f }, name, FLOAT4TOD3DCOLOR(ColorsNShit::NameColor), true, true);

					CurPos += 15;
				}
				if (PlayerEsp::weapon)
				{
					int health = (int)BP->GetHealth();
					const wchar_t* ActiveWeaponName;
					WeaponData* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->GetName();
					if (!ActWeapon)
					{

						ActiveWeaponName = L"None";
					}
					else
					{
						ActiveWeaponName = ActWeapon->GetName();
					}

					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 30.f }, ActiveWeaponName, FLOAT4TOD3DCOLOR(ColorsNShit::WeaponColor), true, true);

				}
				if (PlayerEsp::wounded)
				{
					bool PlayerWounded = BP->HasFlags(64);
					wchar_t wounded[64];
					if (!PlayerWounded) {
						_swprintf(wounded, L"", BP->HasFlags(64));
						Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 60.f }, wounded, FLOAT4TOD3DCOLOR(ColorsNShit::Wounded), true, true);
					}
					else {
						_swprintf(wounded, L"Wounded", BP->HasFlags(64));
						Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 60.f }, wounded, FLOAT4TOD3DCOLOR(ColorsNShit::Wounded), true, true);
					}
				}
				if (PlayerEsp::tracers && !PlayerSleeping && !BP->IsNpc())
				{
					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					static Vector2 startPos = Vector2(screenX / 2.f, screenY - 0.f);
					if ((int)BP->GetHealth() > 0)
					{
						if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
						{
							Render::Object.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::LimeGreen, 0.5f);
						}
						else
						{
							Render::Object.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, FLOAT4TOD3DCOLOR(ColorsNShit::Target_text), 0.5f);
						}
					}
					else
					{
						Render::Object.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::Red, 0.5f);
					}
				}
				// GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY 
				// GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY

				if (BotsEsp::box && BP->IsNpc())
				{
					Render::Object.Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF::Black, 3.f);
					Render::Object.Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF::Orange);
				}
				if (BotsEsp::name && BP->IsNpc())
				{
					wchar_t name[64];
					_swprintf(name, L"%s [%d]", BP->GetName(), (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)));
					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 40.f }, name, D2D1::ColorF::Orange, true, true);
					CurPos += 15;
				}
				if (BotsEsp::health && BP->IsNpc())
				{
					int health = (int)BP->GetHealth();
					float maxheal = 300.f;
					wchar_t healtht[64];
					_swprintf(healtht, L"%d HP", (int)BP->GetHealth());
					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 55.f }, healtht, D2D1::ColorF::Orange, true, true);
					CurPos += 15;
					if (BotsEsp::healthbar)
					{
						if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF::Orange);
							Render::Object.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
				}
				if (BotsEsp::weapons && BP->IsNpc())
				{
					const wchar_t* ActiveWeaponName;
					WeaponData* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->GetName();
					if (!ActWeapon)
					{

						ActiveWeaponName = L"None";
					}
					else
					{
						ActiveWeaponName = ActWeapon->GetName();
					}

					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 25.f }, ActiveWeaponName, D2D1::ColorF::Orange, true, true);

				}

			}
		}
	}
}
inline void RenderActiveSlot(BasePlayer* player)
{
	if (!player->IsNpc() && !player->IsDead()) {
		ImGui::SetNextWindowSize(ImVec2(160, 180));
		ImGui::Begin("EEE", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
		ImVec2 pos = ImGui::GetWindowPos();
		const float Height = 180.f;
		const float With = 160.f;
		Render::Object.FillRoundedRectangle({ pos.x, pos.y }, { With, Height }, D2D1::ColorF::Black, 2);
		Render::Object.RenderString({ pos.x + (With / 2), pos.y + 5 }, player->GetName(), true, D2D1::ColorF::White);
		float Pos = 0;
		Render::Object.Line({ pos.x, pos.y + 20 }, { pos.x + With, pos.y + 20 }, D2D1::ColorF::White, 3);
		for (int i = 0; i < 6; i++)
		{
			WeaponData* GetWeaponInfo = player->GetWeaponInfo(i);
			if (GetWeaponInfo)
			{
				const wchar_t* Item = player->GetWeaponInfo(i)->GetName();
				if (wcslen(Item) < 20)
				{
					Render::Object.RenderString({ pos.x + (With / 2), pos.y + 40 + Pos }, Item, true);
				}
			}
			else
			{
				Render::Object.RenderString({ pos.x + (With / 2), pos.y + 40 + Pos }, L"---", true, D2D1::ColorF::White);
			}
			Pos += 15;
		}
		float health = player->GetHealth();
		float maxheal = 100.f;
		D2D1::ColorF::Enum colorf;
		if (health > 75 && health < 100)
			colorf = D2D1::ColorF::Lime;
		else if (health > 50 && health < 75)
			colorf = D2D1::ColorF::Yellow;
		else if (health > 25 && health < 50)
			colorf = D2D1::ColorF::Orange;
		else if (health > 0 && health < 25)
			colorf = D2D1::ColorF::Tomato;

		Render::Object.Rectangle({ pos.x + (With / 2) - 50, pos.y + 40 + Pos }, { 100, 15 }, D2D1::ColorF::LightSlateGray);
		Render::Object.FillRectangle({ pos.x + (With / 2) + -49, pos.y + 41 + Pos }, { 96 * (health / maxheal), 13 }, colorf);

		ImGui::End();
	}
}
inline void RadarPlayer(BasePlayer* player)
{
	if (LocalPlayer.BasePlayer && Vars1::Radar::Enable && (Vars1::Radar::ShowRadarPlayer || Vars1::Radar::ShowRadarSleeper))
	{
		if (!player->IsDead() && player->GetHealth() >= 0.2f)
		{
			ImGui::SetNextWindowSize(ImVec2(Vars1::Radar::Radar_Size, Vars1::Radar::Radar_Size));
			ImGui::Begin("xxx", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
			ImVec2 pos = ImGui::GetWindowPos();
			if (Vars1::Radar::ShowRadarBackground) {
				Render::Object.FillCircle({ pos.x + Vars1::Radar::Radar_Size / 2, pos.y + Vars1::Radar::Radar_Size / 2 }, D2D1::ColorF(0.f, 0.f, 0.f, 0.05f), Vars1::Radar::Radar_Size / 2);
			}
			Render::Object.Сircle({ pos.x + Vars1::Radar::Radar_Size / 2, pos.y + Vars1::Radar::Radar_Size / 2 }, ConverToRGB(91, 91, 91), Vars1::Radar::Radar_Size / 2, 0.7f);
			const Vector3 LocalPos = LocalPlayer.BasePlayer->GetPosition();
			const Vector3 PlayerPos = player->GetPosition();
			const float Distance = Math::Calc3D_Dist(LocalPos, PlayerPos);
			const float y = LocalPos.x - PlayerPos.x;
			const float x = LocalPos.z - PlayerPos.z;
			Vector2 LocalEulerAngles = LocalPlayer.BasePlayer->GetVA();
			const float num = atan2(y, x) * 57.29578f - 270.f - LocalEulerAngles.y;
			float PointPos_X = Distance * cos(num * 0.0174532924f);
			float PointPos_Y = Distance * sin(num * 0.0174532924f);
			PointPos_X = PointPos_X * (Vars1::Radar::Radar_Size / Vars1::Radar::Radar_Range) / 2.f;
			PointPos_Y = PointPos_Y * (Vars1::Radar::Radar_Size / Vars1::Radar::Radar_Range) / 2.f;
			Render::Object.FillCircle({ pos.x + Vars1::Radar::Radar_Size / 2, pos.y + Vars1::Radar::Radar_Size / 2 }, D2D1::ColorF::Green, 3);
			if (!player->HasFlags(16) && Vars1::Radar::ShowRadarPlayer)
			{
				if (Distance <= Vars1::Radar::Radar_Range)
				{
					Render::Object.FillCircle({ pos.x + Vars1::Radar::Radar_Size / 2.f + PointPos_X - 3.f, pos.y + Vars1::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF::Red, 3.f);
				}
			}
			else if (player->HasFlags(16) && Vars1::Radar::ShowRadarSleeper)
			{
				if (Distance <= Vars1::Radar::Radar_Range)
				{
					Render::Object.FillCircle({ pos.x + Vars1::Radar::Radar_Size / 2.f + PointPos_X - 3.f, pos.y + Vars1::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF::Yellow, 3.f);
				}
			}
			ImGui::End();
		}
	}
}

