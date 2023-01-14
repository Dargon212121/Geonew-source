using namespace ImGui;
ImFont* font_main;
ImFont* font_menu;
bool eng = true;
bool rus = false;
ImFont* icons = nullptr;
ImFont* info_big = nullptr;
ImFont* two = nullptr;
ImFont* three = nullptr;
ImFont* tabsf = nullptr;
ImFont* ee = nullptr;
static bool english = true;
ImVec2 pos;
ImDrawList* draw;
ImFont* rere = nullptr;
ImFont* tb = nullptr;
ImFont* tbl = nullptr;
ImFont* NameFont;
ImFont* TabsFont;
ImFont* MainFont;
ImFont* IconsFont;
ImFont* g_pMenuFont;
extern ImFont* g_pMenuFont;
float dpi_scale = 1.f;
static int tabs = 0;
#include <winnt.h>
#include "RenderMenu.h"
static const char* box_style[]{
	english ? "Normal" : u8"Обычные",
	english ? "Cornered" : u8"Угловые",
	english ? "3D" : u8"Кубические",
};
static const char* anti_aim_yaw[]{
	english ? "Down" : u8"В низ",
	english ? "Up" : u8"Вверх",
};
static bool IsKeyPressedMapX(ImGuiKey key, bool repeat)
{
	const int key_index = GImGui->IO.KeyMap[key];
	return (key_index >= 0) ? ImGui::IsKeyPressed(key_index, repeat) : false;
}
bool Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
	const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id) {
		for (auto i = 0; i <= 6; i++) {
			if (io.MouseDown[i] || GetAsyncKeyState(VK_XBUTTON1) || GetAsyncKeyState(VK_XBUTTON2)) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				}
				if (GetAsyncKeyState(VK_XBUTTON2))
					key = VK_XBUTTON2;
				if (GetAsyncKeyState(VK_XBUTTON1))
					key = VK_XBUTTON1;

				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (IsKeyPressedMapX(ImGuiKey_Escape, false)) {
			*k = 0;
			ImGui::ClearActiveID();
		}
		else {
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	const char* buf_display = "None";



	if (*k != 0 && g.ActiveId != id) {
		const char* key_name;
		get_keycode_name(*k, buf_display);
	}
	else if (g.ActiveId == id) {
		buf_display = "Press";
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
	//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}

// I will do it later
void EspPreview()
{
	static bool enabled = true;
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];
	ImGui::SetNextWindowSize(ImVec2(270, 400));

	ImGui::Begin("ESP Preview", &enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	{
		auto cur_window = ImGui::GetCurrentWindow();
		ImVec2 w_pos = cur_window->Pos;
		//if (PlayerEsp::skeleton)
		//{
		//	cur_window->DrawList->AddRect(ImVec2(w_pos.x + 40, w_pos.y + 60), ImVec2(w_pos.x + 200, w_pos.y + 360), ImColor(ColorsNShit::SkeletonColor));
		//}
		//if (Misc::chams)
		//{
		//	cur_window->DrawList->AddRect(ImVec2(w_pos.x + 40, w_pos.y + 60), ImVec2(w_pos.x + 200, w_pos.y + 360), ImColor(ColorsNShit::ChamsESP));
		//}
		if (PlayerEsp::healthbar1)
		{
			cur_window->DrawList->AddRectFilled(ImVec2(w_pos.x + 34, w_pos.y + 60), ImVec2(w_pos.x + 37, w_pos.y + 360), ImColor(ColorsNShit::HpBar));
		}
		if (PlayerEsp::box)
		{
			cur_window->DrawList->AddRect(ImVec2(w_pos.x + 40, w_pos.y + 60), ImVec2(w_pos.x + 200, w_pos.y + 360), ImColor(ColorsNShit::BoxColor));
		}
		if (PlayerEsp::name)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 100, w_pos.y + 30 }, ImColor(ColorsNShit::NameColor), "Holmes");
		}
		if (PlayerEsp::healthbar2)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 90 }, ImColor(ColorsNShit::PlayerHeath), "100");
		}
		if (PlayerEsp::distance)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 105 }, ImColor(ColorsNShit::DistanceColor), "400M");
		}
		if (PlayerEsp::weapon)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 100, w_pos.y + 370 }, ImColor(ColorsNShit::WeaponColor), "Wepons");
		}
	}
	ImGui::End();
}

bool lang(const char* label)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize(label_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(0);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(129 / 255.f, 129 / 255.f, 129 / 255.f, 255 / 255.f));
	ImGui::RenderText(ImVec2(bb.Min.x, bb.Min.y), label);
	ImGui::PopStyleColor();

	return pressed;
}

void apply_fonts() {
	ImGui::CreateContext();

	font_main = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 18, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	font_menu = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 12, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
}
void HelpMarker(const char* desc) {
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
void HelpCheckbox(const char* desc, bool* v, const char* helptext) { ImGui::Checkbox(desc, v); ImGui::SameLine(); HelpMarker(helptext); }
void CheckboxX(const char* eng, const char* rus, bool* v) {
	ImGui::Checkbox((english ? eng : rus), v);
}
static bool sh_save_cfg = false;
static bool sh_load_cfg = false;
#include <chrono>
long getMils() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
namespace Anime {
	bool reverse = false;
	//bool done = false;
	int offset = 0;
	bool show_popup = false;

	void Popup(const char* text, int onScreenMils, bool* done) {
		if (!done)
			show_popup = true;

		ImGuiIO& io = ImGui::GetIO();
		int Wd = io.DisplaySize.x;

		static long oldTime = -1;

		ImGui::SetNextWindowPos(ImVec2(Wd - offset, 500));
		ImGui::Begin("PopUp Window", &show_popup, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		ImGui::BeginChild(xorstr("##linerender"), ImVec2(110, 1)); ImGui::EndChild();
		long currentTime_ms = getMils();

		ImVec2 txtSz = ImGui::CalcTextSize(text);
		ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - txtSz.y / 2);
		ImGui::Text(text);

		/*if (ImGui::Button("Close Me")) {
			reverse = true;
		}*/
		if (!reverse)
		{
			if (offset < ImGui::GetWindowWidth())
				offset += (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);

			if (offset >= ImGui::GetWindowWidth() && oldTime == -1)
			{

				oldTime = currentTime_ms;
			}
		}
		//ImGui::Text("ot: %d", oldTime);

		if (currentTime_ms - oldTime >= onScreenMils && oldTime != -1) // close after x mils
			reverse = true;

		if (reverse)
		{
			if (offset > 0)
				offset -= (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);
			if (offset <= 0)
			{
				offset = 0;
				reverse = false;
				*done = true;
				oldTime = -1;
				show_popup = false;

			}
		}

		ImGui::End();
	}
}
#include <mutex>
#include <iomanip>
#include <tchar.h>
ImVec4 rgb_to_imvec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255, g / 255, b / 255, a / 255);
}

// Becouse i don't like it :)
// if you want to turn on this shit, check start.h
// 
void RenderWatermark()
{
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	std::string winname = name;
	std::time_t result = std::time(nullptr);
	std::string wintime = std::asctime(std::localtime(&result));
	time_t lt;
	struct tm* t_m;
	lt = time(NULL);
	t_m = localtime(&lt);

	int time_h = t_m->tm_hour;
	int time_m = t_m->tm_min;
	int time_s = t_m->tm_sec;

	std::string time;

	if (time_h < 10)
		time += "0";

	time += std::to_string(time_h) + ":";

	if (time_m < 10)
		time += "0";

	time += std::to_string(time_m) + ":";

	if (time_s < 10)
		time += "0";

	time += std::to_string(time_s);
	float sWidth = Global::ScreenWidth;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, rgb_to_imvec4(55, 55, 255, 255));
	uintptr_t bn = read(Storage::gBase + 0x323F1E8, uintptr_t);
	std::string gamestatus;
	if (!bn) {
		gamestatus = (" | wrong version");
		return;
	}
	else {
		gamestatus = (" | valid version");
	}
	const char* _text = (u8"Geonew.cc | ");// Hi
	std::string _text1 = (winname.c_str());
	const char* _text2(" | ");
	const char* _text3(wintime.c_str());
	std::string waterka = _text + _text1 + _text2 + time + gamestatus;
	ImGui::SetNextWindowPos(ImVec2(sWidth - 1500 - ImGui::CalcTextSize(waterka.c_str()).x - 10, 10));
	ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(waterka.c_str()).x + 10, 20));
	ImGui::Begin(xorstr("Watermark"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	{
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild(xorstr("##linerender"), ImVec2(ImGui::CalcTextSize(waterka.c_str()).x + 28, 2)); ImGui::EndChild();

		ImGui::SetCursorPos(ImVec2(5, 5));
		ImGui::Text(waterka.c_str());

	}
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}



void AimTab()
{
	ImGui::SetCursorPos(ImVec2(140, 40));
	ImGui::BeginChild(english ? "Legit" : u8"Легит", ImVec2(193, 300));{
		ImGui::BeginGroup();
		ImGui::Checkbox((english ? "Activate Aimbot" : u8"Аимбот"), &AimBot::Activate);
		if (AimBot::Activate == true) {
			Hotkey((english ? "Aim-Key" : u8"Кнопка"), &Keys::aimKey, ImVec2(120.f, 0));
			ImGui::Checkbox((english ? "Body aim" : u8"На тело"), &AimBot::pBody);
			ImGui::Checkbox((english ? "Smooth" : u8"Плавность"), &AimBot::smooth);
			if (AimBot::smooth == true) {
				ImGui::SliderFloat((english ? "Smooth factor" : u8"Плав."), &AimBot::smooth_factor, 0.f, 10.f);
			}
		}

		ImGui::Checkbox((english ? "Show Fov" : u8"Радиус"), &AimBot::DrawFov);
		if (AimBot::DrawFov == true) {
			ImGui::SameLine(100.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("            ", ColorsNShit::Fov);
			ImGui::Checkbox((english ? "Fill Fov" : u8"Заливка"), &AimBot::FillFov);

		}
		if (AimBot::Activate || AimBot::pSilent == true) {
			ImGui::SliderFloat((english ? "Set Fov" : u8"Радиус"), &AimBot::Fov, 20.f, 200.f);
			ImGui::SliderFloat((english ? "Aim Dist" : u8"Дистанция"), &AimBot::Range, 0.f, 400.f);
		}

		ImGui::EndGroup();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(english ? "Rage" : u8"Рейдж", ImVec2(193, 300));{
		ImGui::BeginGroup();
		ImGui::Checkbox((english ? "AutoMelee" : u8"Авто удары"), &Misc::Meleeatack);
		ImGui::Checkbox((english ? "Only Head" : u8"Только Голова"), &AimBot::AlwaysHeadshot);
		ImGui::Checkbox((english ? "PSilent" : u8"Псало"), &AimBot::pSilent);
		//ImGui::Checkbox((english ? "Silent" : u8"Cало"), &AimBot::silentAim);
		ImGui::Checkbox((english ? "ThickBullet" : u8"Жирная Пуля"), &Weapons::FatBullet);
		ImGui::Checkbox((english ? "Anti-Aiming" : u8"Крутилка"), &AntiAim::anti_aim);
		if (AntiAim::anti_aim) {
			ImGui::SliderInt((english ? "Spin Speed" : u8"Скорость Кручения"), &AntiAim::anti_aim_speed, 1, 50);
			ImGui::PushItemWidth(100);
			ImGui::Combo((english ? "Yaw" : u8"Взгляд"), &AntiAim::anti_aim_yaw, anti_aim_yaw, IM_ARRAYSIZE(anti_aim_yaw));
			ImGui::PopItemWidth();
		}
		ImGui::Checkbox((english ? "Fake-Lags" : u8"Фейк лаги"), &Misc::FakeLag);
		ImGui::EndGroup();
	}
	ImGui::EndChild();
}
void VisualsTab()
{
	//EspPreview();
	ImGui::SetCursorPos(ImVec2(140, 40));
	ImGui::BeginChild(english ? "Players" : u8"Игроки", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		//EspPreview();
		ImGui::Checkbox((english ? "Name" : u8"Ник"), &PlayerEsp::name);
		if (PlayerEsp::name == true) {
			ImGui::SameLine(100.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(" ", ColorsNShit::NameColor);
		}
		ImGui::Checkbox((english ? "Box" : u8"Боксы"), &PlayerEsp::box);
		if (PlayerEsp::box) {
			ImGui::PushItemWidth(100);
			ImGui::Combo((english ? "" : u8""), &PlayerEsp::boxstyle, box_style, IM_ARRAYSIZE(box_style));
			ImGui::PopItemWidth();
			ImGui::SameLine();
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("   ", ColorsNShit::BoxColor);
			ImGui::SliderFloat((english ? "Corner Float" : u8"Углы крутим"), &PlayerEsp::cornerfloat, 1.f, 7.f);
			ImGui::Checkbox((english ? "Fill Box" : u8"Заливка бокса"), &PlayerEsp::fillbox);
		}

		ImGui::Checkbox((english ? "Skeleton" : u8"Скелет"), &PlayerEsp::skeleton);
		if (PlayerEsp::skeleton == true) {
			ImGui::SameLine(100.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("        ", ColorsNShit::SkeletonColor);
		}
		ImGui::Checkbox((english ? "Chams" : u8"Чамсы"), &Misc::chams);
		if (Misc::chams == true) {
			ImGui::SliderFloat((english ? "Red" : u8"Красный"), &Misc::xc, 0.f, 5.f);
			ImGui::SliderFloat((english ? "Green" : u8"Зелёный"), &Misc::yc, 0.f, 5.f);
			ImGui::SliderFloat((english ? "Blue" : u8"Синий"), &Misc::zc, 0.f, 5.f);
			ImGui::Checkbox((english ? "Rainbow-Chams" : u8"Радужные чамсы"), &Misc::rainbow_chams);
			ImGui::Checkbox((english ? "Health-Chams" : u8"Чамсы под цвет жизней"), &Misc::health_chams);
			ImGui::Checkbox((english ? "Only Visible" : u8"Только видимые"), &Misc::OnlyVisible);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SliderFloat((english ? "Up Time" : u8"Время обновления"), &Misc::uptime, 0.f, 15.f);
		}
		ImGui::Checkbox((english ? "healthbar-left" : u8"Хп слева"), &PlayerEsp::healthbar1);
		ImGui::Checkbox((english ? "healthbar-bottom" : u8"Хп снизу"), &PlayerEsp::healthbar2);
		ImGui::Checkbox((english ? "visualize - predict" : u8"Виз. наводка"), &Visuals::visualize_prediction);
		ImGui::Checkbox((english ? "Weapon" : u8"Оружие"), &PlayerEsp::weapon);
		if (PlayerEsp::weapon == true) {
			ImGui::SameLine(100.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("    ", ColorsNShit::WeaponColor);
		}
		ImGui::Checkbox((english ? "Wounded" : u8"Упавшие"), &PlayerEsp::wounded);
		if (PlayerEsp::wounded == true) {
			ImGui::SameLine(100.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("     ", ColorsNShit::Wounded);
		}
		ImGui::Checkbox((english ? "Tracers" : u8"Линии"), &PlayerEsp::tracers);
		if (PlayerEsp::tracers == true) {
			ImGui::SameLine(100.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("      ", ColorsNShit::Target_text);
		}
		ImGui::Checkbox((english ? "Target Tracers" : u8"Линия к цели"), &PlayerEsp::targetline);
		if (PlayerEsp::targetline == true) {
			ImGui::SameLine(130.f, 0.f);
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("       ", ColorsNShit::LineEsp);
		}

		ImGui::Checkbox((english ? "Ignore Sleepers" : u8"Игнор спящих"), &PlayerEsp::sleeperignore);


		ImGui::EndGroup();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(english ? "Other Visuals" : u8"Остальное", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::Checkbox((english ? "Esp Preview" : u8"Esp Preview"), &Visuals::EspPreview);
		if (Visuals::EspPreview == true)
		{
			EspPreview();
		}
		if (ImGui::BeginCombo(english ? "Crosshair" : u8"Прицел", english ? "Chose Crosshair" : u8"Выбрать прицел")) {

			ImGui::Checkbox((english ? "Defolt" : u8"Обычный"), &AimBot::Crosshair);
			ImGui::Checkbox((english ? "Svastika" : u8"Зига"), &AimBot::svaston);
			if (AimBot::svaston)
			{
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::SliderInt((english ? "the size" : u8"Размер"), &Misc::razmer, 1, 10);
				ImGui::Spacing();
				ImGui::SliderFloat((english ? "speed" : u8"Скорость"), &Misc::speed, 0.1f, 4.f);

			}
			ImGui::Checkbox((english ? "Custom" : u8"Настраиваемый"), &AimBot::CustomCrosshair);
			if (AimBot::CustomCrosshair)
			{
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::SliderFloat((english ? "Gap" : u8"Размер от центра"), &AimBot::Gap, 1.f, 50.f);
				ImGui::Spacing();
				ImGui::SliderFloat((english ? "Longht" : u8"Размер"), &AimBot::Longht, 1.f, 50.f);
				ImGui::Checkbox((english ? "Dot" : u8"Точка"), &AimBot::dot);
			}
			End();
			if (ImGui::CollapsingHeader(("Ores")))
			{
				ImGui::Checkbox(("Stone"), &Ores::Stone);
				ImGui::Checkbox(("Sulfur"), &Ores::Sulfur);
				ImGui::Checkbox(("Metal"), &Ores::Metal);
				if (Ores::Sulfur || Ores::Stone || Ores::Metal)
				{
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::SliderFloat(("Ore ESP Distance"), &Ores::oreDrawDistance, 5.f, 400.f);
					ImGui::Checkbox(("Show Distance"), &Ores::showDistance);
				}
			}
			if (ImGui::CollapsingHeader(("Other")))
			{
				if (ImGui::CollapsingHeader(("Crates")))
				{
					ImGui::Checkbox(("Airdrops"), &Visuals::Supply);
					ImGui::Checkbox(("Chinook Crates"), &Visuals::Chinook);
					if (Visuals::Supply || Visuals::Chinook)
					{
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::SliderFloat(("Crate ESP Distance"), &Visuals::drawCrateDistance, 5.f, 3000.f);
						ImGui::Checkbox(("Show Distance "), &Visuals::crateDistance);
					}
				}
				if (ImGui::CollapsingHeader(("Vehicles")))
				{
					ImGui::Checkbox(("Minicopters"), &Visuals::Minicopter);
					ImGui::Checkbox(("Scrap Helis"), &Visuals::ScrapHeli);
					ImGui::Checkbox(("Boats"), &Visuals::Boat);
					ImGui::Checkbox(("RHIB's"), &Visuals::RHIB);
					if (Visuals::Minicopter || Visuals::ScrapHeli || Visuals::Boat || Visuals::RHIB)
					{
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::SliderFloat(("Vehicle ESP Distance"), &Visuals::drawVehicleDistance, 5.f, 3000.f);
						ImGui::Checkbox(("Show Distance  "), &Visuals::vehicleDistance);
					}
				}
				if (ImGui::CollapsingHeader(("Traps")))
				{
					ImGui::Checkbox(("Auto Turrets"), &Visuals::AutoTurret);
					ImGui::Checkbox(("Flame Turrets"), &Visuals::FlameTurret);
					ImGui::Checkbox(("Shotgun Traps"), &Visuals::ShotgunTurret);
					ImGui::Checkbox(("Landmines"), &Visuals::Landmine);
					ImGui::Checkbox(("Beartraps"), &Visuals::BearTrap);
					if (Visuals::AutoTurret || Visuals::FlameTurret || Visuals::ShotgunTurret || Visuals::Landmine || Visuals::BearTrap)
					{
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::SliderFloat(("Trap ESP Distance"), &Visuals::drawTrapDistance, 5.f, 400.f);
						ImGui::Checkbox(("Show Distance   "), &Visuals::trapDistance);
					}
				}
				if (ImGui::CollapsingHeader(("Misc ")))
				{
					ImGui::Checkbox(("Patrol Heli"), &Visuals::PatrolHeli);
					ImGui::Checkbox(("Hemp"), &Visuals::Hemp);
					ImGui::Checkbox(("Corpses"), &Visuals::Corpse);
					ImGui::Checkbox(("Stashes"), &Visuals::Stash);
					if (Visuals::Corpse || Visuals::Stash || Visuals::Hemp || Visuals::PatrolHeli)
					{
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::SliderFloat(("Misc ESP Distance"), &Visuals::drawOtherDistance, 5.f, 400.f);
						ImGui::Checkbox(("Show Distance    "), &Visuals::otherDistance);
					}

				}
				if (ImGui::CollapsingHeader(("Animals ")))
				{
					ImGui::Checkbox(("Bear"), &Visuals::Bear);
					ImGui::Checkbox(("Boar"), &Visuals::Boar);
					ImGui::Checkbox(("Chicken"), &Visuals::Chicken);
					ImGui::Checkbox(("Horse"), &Visuals::Horse);
					if (Visuals::Bear || Visuals::Boar || Visuals::Chicken || Visuals::Horse)
					{
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::SliderFloat(("Misc ESP Distance"), &Visuals::drawAnimalsDistance, 5.f, 400.f);
						ImGui::Checkbox(("Show Distance    "), &Visuals::AnimalsDistance);
					}
				}
			}

		}
		ImGui::SameLine(200.f, 0.f);
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("         ", ColorsNShit::Crosshair2);
		ImGui::Text(english ? "Bots" : u8"Боты");
		ImGui::Checkbox((english ? "Name" : u8"Имя"), &BotsEsp::name);
		ImGui::Checkbox((english ? "Box" : u8"Боксы"), &BotsEsp::box);
		ImGui::Checkbox((english ? "Skeleton" : u8"Скелет"), &BotsEsp::skeleton);
		ImGui::Checkbox((english ? "Health" : u8"Хп"), &BotsEsp::health);
		ImGui::Checkbox((english ? "Weapon" : u8"Оружие"), &BotsEsp::weapons);
		//ImGui::Checkbox(("Info"), &Other::InfoTopLeft);


		ImGui::EndGroup();
	}
	ImGui::EndChild();
}
void MiscTab()
{
	ImGui::SetCursorPos(ImVec2(140, 40));
	ImGui::BeginChild(english ? "Weapons" : u8"Оружие", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::Checkbox(english ? "Weapon Spam" : u8"Спам пулями", &Misc::weapon_spam);
		if (Misc::weapon_spam) {
			Hotkey(english ? "" : u8"", &Keys::weaponspam, ImVec2(150, 20));
		}
		ImGui::Checkbox((english ? "Aiming On Hellicopter" : u8"Оружие на коптере"), &Weapons::canHoldItems);
		ImGui::Checkbox((english ? "No Spread" : u8"Без расброса"), &Weapons::AntiSpread);
		if (Weapons::AntiSpread) {
			ImGui::SliderFloat("Spread Value", &Weapons::spread, 0.f, 100.f);
		}
		ImGui::Checkbox((english ? "Recoil Control System" : u8"Без отдачи"), &AimBot::RCS);
		ImGui::Checkbox((english ? "No Sway" : u8"Без покачивания"), &Weapons::NoSway);
		ImGui::Checkbox((english ? "Automatic Fire" : u8"Авто зажим"), &Weapons::Automatic);
		ImGui::Checkbox((english ? "Rapid Fire" : u8"Быстрая стрельба"), &Misc::RapidFire);
		ImGui::Checkbox((english ? "Instant Eoka" : u8"Быстрая еока"), &Weapons::SuperEoka);
		ImGui::Checkbox((english ? "Instant Bow" : u8"Быстрый лук"), &Weapons::SuperBow);
		ImGui::Checkbox((english ? "No Animation" : u8"Стрельба без анимы"), &Misc::remove_attack_anim);
		ImGui::EndGroup();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(english ? "Player" : u8"Игрок", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::Checkbox(english ? "CustomFov" : u8"Поле зрения", &Misc::CustomFov);
		if (Misc::CustomFov) {
			ImGui::SliderFloat(english ? "CustomFov Value" : u8"Поле зрения", &Misc::FovRange, 0.f, 200.f);
		}
		ImGui::Checkbox(english ? "Zoom" : u8"Приближение зрения", &Misc::Zoom);
		if (Misc::Zoom)
		{
			ImGui::SliderFloat(english ? "Zoom Value" : u8"Приближение зрения", &Misc::Zoomvalue, 60.f, 10.f);
			Hotkey(english ? "" : u8"", &Misc::Zoomkey, ImVec2(150, 30));
		}
		ImGui::Checkbox(english ? "Suicide" : u8"Суицид", &Misc::suicide);
		if (Misc::suicide) {
			Hotkey(english ? "" : u8"", &Keys::suicide, ImVec2(150, 20));
		}
		ImGui::Checkbox(english ? "Mass Suicide" : u8"Лютый Суицид", &Misc::mass_suicide);
		ImGui::Checkbox((english ? "AutoFarm" : u8"Авто фарм"), &Misc::AutoFarm);
		if (Misc::AutoFarm)
		{
			ImGui::Checkbox((english ? "AutoFarmTree" : u8"Авто фарм дерево"), &Misc::AutoFarmTree);
			ImGui::Checkbox((english ? "AutoFarmOre" : u8"Авто фарм Руды"), &Misc::AutoFarmOre);
			ImGui::Checkbox((english ? "AutoFarmBarrel" : u8"Авто фарм бочки"), &Misc::AutoFarmBarrel);
		}
		CheckboxX(("InfinityJump"), u8"Бесконечный прыжок", &Misc::InfJump);
		Hotkey(english ? "LongNeck Key" : u8"Длинная шея", &Misc::longKey, ImVec2(150, 15));
		ImGui::Checkbox(("Trace Bullet"), &Weapons::bullet_trace);
		ImGui::Checkbox(("Fast loot"), &Misc::FastLoot);
		ImGui::Checkbox(xorstr("Rayleigh Changer"), &Misc::rayleigh_changer);
		if (Misc::rayleigh_changer) {
			ImGui::SliderFloat(xorstr("Rayleigh Amount"), &Misc::rayleigh, 1.f, 50.f);
		}
		ImGui::Checkbox(("Custom-Time"), &Misc::CustomTime);
		if (Misc::CustomTime) {
			ImGui::SliderFloat(("Time-value"), &Misc::Time, 0.f, 12.f);
		}
		HelpCheckbox(("Fake-Admin"), &Misc::FakeAdmin, "I didn't do bypass, don't use it");
		ImGui::Checkbox((english ? "Jump-Aiming" : u8"Аим в прыжке"), &Weapons::jumpAim);
		ImGui::Checkbox(("Omni-Sprint"), &Misc::omniSprint);
		ImGui::Checkbox(("Speed-hack"), &Misc::speedhack);
		if (Misc::speedhack) {
			Hotkey(("Speed Key"), &Keys::speedKey, ImVec2(145.f, 0));
		}
		ImGui::Checkbox(("Spiderman"), &Misc::SpiderMan);
		ImGui::Checkbox(("No Colision"), &Misc::no_playercollision);
		ImGui::Checkbox(("Ambient"), &Visuals::NightMode);
		ImGui::SameLine(100.f, 0.f);
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("", ColorsNShit::Ambient);
		HelpCheckbox(("Custom Hit Sound"), &Hit::CustomHitSound, "You can drop your HitSound along the path C:\geonew\sound.wav");
		ImGui::SameLine();
		if (ImGui::Button("Download-Sound", ImVec2(150, 15))) {
			URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/902985284239646742/904473815281709066/sound.wav", "C:\\Geonew.cc\\sound.wav", 0, 0);
		}

		ImGui::EndGroup();
	}
	ImGui::EndChild();
}
void OtherTab()
{
	ImGui::SetCursorPos(ImVec2(140, 40));
	ImGui::BeginChild("Radar", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::Checkbox("Enable", &Vars1::Radar::Enable);
		ImGui::Checkbox("ShowRadarBackground", &Vars1::Radar::ShowRadarBackground);
		ImGui::Checkbox("ShowRadarPlayer", &Vars1::Radar::ShowRadarPlayer);
		ImGui::Checkbox("ShowRadarSleeper", &Vars1::Radar::ShowRadarSleeper);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::SliderFloat("Radar Size", &Vars1::Radar::Radar_Size, 0.f, 500.f);
		ImGui::Spacing();
		ImGui::SliderFloat("Radar Range", &Vars1::Radar::Radar_Range, 0.f, 600.f);
		ImGui::EndGroup();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("ActiveSlot", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::Checkbox(("Target Belt"), &Visuals::ActiveSlotRender);
		ImGui::EndGroup();
	}
	ImGui::EndChild();
}
void ConfigTab()
{
	ImGui::SetCursorPos(ImVec2(140, 40));
	ImGui::BeginChild("Config", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::InputText("", Global::ConfigName, 0x100);
		if (ImGui::Button(("Save"), ImVec2(50, 0))) {
			SaveCFG(Global::ConfigName);
			Other::cfgSaved = true;
			sh_save_cfg = true;
		}
		ImGui::SameLine();
		if (ImGui::Button(("Load"), ImVec2(50, 0))) {
			LoadCFG(Global::ConfigName);
			sh_load_cfg = true;
		}




		// Уведомление, что конфиг загружен/сохранён
		if (sh_save_cfg)
		{
			//save ur cfg
			bool done = false;
			Anime::Popup("Config Saved!", 2000, &done);
			if (done)
				sh_save_cfg = false;
		}

		if (sh_load_cfg)
		{
			//load ur cfg
			bool done = false;
			Anime::Popup("Config Loaded!", 2000, &done);
			if (done)
				sh_load_cfg = false;
		}
		ImGui::EndGroup();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("Other", ImVec2(193, 300));
	{
		ImGui::BeginGroup();
		ImGui::Checkbox("Background", &backgroundm);
		ImGui::Checkbox("DotDraw", &dotdraw);
		ImGui::Checkbox("Watermark", &Misc::Watermark);
		//Checkbox("Discord status", &Misc::Discordstatus);
		
		ImGui::EndGroup();
	}
	ImGui::EndChild();
}
void CreditsTab() {
	ImGui::SetCursorPos(ImVec2(140, 40));
	ImGui::BeginChild("Credits", ImVec2(394, 300));
	{
		ImGui::BeginGroup();
		ImGui::Text("Hello UserName, I'm Holmes#3149!");
		ImGui::Text("This cheat leked by Poves#4495, \nI am only update this cheat");

		if (ImGui::Button(("My discord")))
		{
			system("start https://discord.gg/hmWmarjPz4");
		}
		ImGui::SameLine();
		if (ImGui::Button(("Poves discord")))
		{
			system("start https://discord.gg/uw9W8nyGT9");
		}
		ImGui::EndGroup();
	}
	ImGui::EndChild();

}

ImFont* initx;
void Init()
{

	// Setup
	auto front = ImGui::GetForegroundDrawList(); // also you can use GetWindowDrawList() or GetBackgroundDrawList()
	ImVec2 center = ImGui::GetIO().DisplaySize / 2.f;
	static ImColor fore_color(100,0,255);
	static ImColor back_color(0, 0, 0, 25);
	static float arc_size = 0.45f; // 0.f < x < 2.f
	static float radius = 30.f;
	static float thickness = 4.f;
	static float Alpha = 0.0f;
	int screenWidthX = GetSystemMetrics(SM_CXSCREEN);
	int screenHeightY = GetSystemMetrics(SM_CYSCREEN);
	auto back = ImGui::GetBackgroundDrawList();

	if (Alpha < 0.65f)
		Alpha += 0.005f;
	back->AddRectFilled(ImVec2(0, 0), ImVec2(screenWidthX, screenHeightY), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, Alpha)));


	// Animation
	static float position = 0.f;
	position = ImLerp(position, IM_PI * 2.f, ImGui::GetIO().DeltaTime * 2.3f);

	// Background
	front->PathClear();
	front->PathArcTo(center, radius, 0.f, 2.f * IM_PI, 35.f);
	front->PathStroke(ImGui::GetColorU32(back_color.Value), 0, thickness);

	// Foreground
	front->PathClear();
	front->PathArcTo(center, radius, IM_PI * 1.5f + position, IM_PI * (1.5f + arc_size) + position, 35.f);
	front->PathStroke(ImGui::GetColorU32(fore_color.Value), 0, thickness);
	ImGui::PushFont(initx);
	ImVec2 inject = ImGui::CalcTextSize(xorstr(u8"Initialization Geonew.cc"));
	ImVec2 discord = ImGui::CalcTextSize(xorstr(u8"Holmes#3149"));
	auto MiddleX = Global::ScreenWidth / 2;
	auto MiddleY = Global::ScreenHigh / 2;
	front->AddText({ MiddleX - inject.x / 2 + 3, MiddleY + 35 }, ImColor(255, 255, 255), xorstr(u8"Initialization Geonew.cc"));
	front->AddText({ MiddleX - discord.x / 2 + 3, MiddleY + 515 }, ImColor(255, 255, 255), xorstr(u8"Holmes#3149"));
	ImGui::PopFont();

	// Reset animation
	if (position >= IM_PI * 1.90f)
		position = 0.f;
}

void invis(bool background, bool dotdraw)
{
	if (background) {
		static float Alpha = 0.0f;
		int screenWidthX = GetSystemMetrics(SM_CXSCREEN);
		int screenHeightY = GetSystemMetrics(SM_CYSCREEN);
		auto back = ImGui::GetBackgroundDrawList();

		if (Alpha < 0.65f)
			Alpha += 0.005f;
		back->AddRectFilled(ImVec2(0, 0), ImVec2(screenWidthX, screenHeightY), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, Alpha)));
	}

	auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	{
		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0,0,0,0 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::Begin("##menu2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove);
		{
			if (dotdraw) {
				dot_draw();
			}
		}
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

	}
	ImGui::End();
	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar);
	{
		char name[UNLEN + 1];
		DWORD username_len = UNLEN + 1;
		GetUserNameA(name, &username_len);
		std::string winname = name;
		static int x = 545 * dpi_scale, y = 355 * dpi_scale;
		pos = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();

		ImGui::SetWindowSize(ImVec2(ImFloor(x * dpi_scale), ImFloor(y * dpi_scale)));
		draw->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImColor(38, 38, 42), 9);
		draw->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImGui::GetColorU32(ImGuiCol_WindowBg), 9);
		draw->AddRectFilled(ImVec2(pos.x, pos.y + 30), ImVec2(pos.x + 130, pos.y + 355), ImGui::GetColorU32(ImGuiCol_TabBar), 9, 4);
		draw->AddLine(ImVec2(pos.x, pos.y + 30), ImVec2(pos.x + 545, pos.y + 30), ImColor(38, 38, 42));
		draw->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 29), ImVec2(pos.x + 545, pos.y + 30), ImColor(67, 58, 190), ImColor(67, 58, 190, 0), ImColor(67, 58, 190, 0), ImColor(67, 58, 190));

		ImGui::SetCursorPos(ImVec2(100, 100));
		draw->AddText(NameFont, 18.f, ImVec2(pos.x + 20, pos.y + 5), ImColor(255, 255, 255), u8"Geonew.cc");
		ImGui::SetCursorPos(ImVec2(500, 28 / 2 - ImGui::CalcTextSize(english ? "EN" : "RU").y / 2));
		if (lang(english ? "ENG" : "RUS")) english = !english;
		draw->AddText(g_pMenuFont, 18.f, ImVec2(pos.x + 20, pos.y + 306), ImColor(255, 255, 255), winname.c_str());
		draw->AddText(g_pMenuFont, 16.f, ImVec2(pos.x + 20, pos.y + 327), ImColor(55, 55, 55), "Version:");
		draw->AddText(g_pMenuFont, 16.f, ImVec2(pos.x + 76, pos.y + 327), ImColor(100, 0, 255, 150), "Beta");
		//if (logggo == nullptr)
			//D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &logo, sizeof(logo), 500, 500, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logggo);

		ImGui::SetCursorPos(ImVec2(10, 25));
		/*ImGui::Image(logggo, ImVec2(100, 100));*/

		ImGui::SetCursorPos(ImVec2(10, 35));

		ImGui::BeginGroup();
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 4));
			if (tab("Aimbot", tabs == 0)) tabs = 0;
			if (tab("Visuals", tabs == 1)) tabs = 1;
			if (tab("Misc", tabs == 2)) tabs = 2;
			if (tab("Other", tabs == 3)) tabs = 3;
			if (tab("Config", tabs == 4)) tabs = 4;
			if (tab("Credits", tabs == 5)) tabs = 5;

			ImGui::PopStyleVar();
		}
		ImGui::EndGroup();

		switch (tabs)
		{
		case 0: AimTab();   break;
		case 1: VisualsTab();   break;
		case 2: MiscTab();   break;
		case 3: OtherTab();   break;
		case 4: ConfigTab();   break;
		case 5: CreditsTab();   break;
		}
	}
	ImGui::End();

}
