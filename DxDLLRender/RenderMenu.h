#pragma once

#include <mutex>

#include <string>
#include "ImGUI/imgui.h"
#include <d3d9.h>
#include <vector>
#include <sstream>
#include "ImGUI/imgui_internal.h"
#include <winnt.h>

// B1G number = b1g accuracy
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989380952572010654858632788659361533818279682303019520353018529689957736225994138912497217752834791315155748572424541506959508295331168617278558890750983817546374649393192550604009277016711390098488240128583616035637076601047101819429555961989467678374494482553797747268471040475346462080466842590694912933136770289891521047521620569660240580


using namespace ImGui;

int ListBoxResultColor;
int ListBoxResultCrosshair;

ImVec2 p;
IDirect3DTexture9* background;
float alphamodulate = 0.0f;





#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 




static int selectedtab = 1;
static int selectedsubtab = 1;
class dot
{
public:
	dot(Vector3 p, Vector3 v) {
		m_vel = v;
		m_pos = p;
	}

	void update();
	void draw();

	Vector3 m_pos, m_vel;
};

std::vector<dot*> dots = { };

void dot::update() {
	auto opacity = 240 / 255.0f;

	m_pos += m_vel * (opacity);
}

void dot::draw() {
	int opacity = 55.0f * (240 / 255.0f);

	ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x - 2, m_pos.y - 2 }, { m_pos.x + 2, m_pos.y + 2 }, ImColor(100, 0, 255, 150));

	auto t = std::find(dots.begin(), dots.end(), this);
	if (t == dots.end()) {
		return;
	}

	for (auto i = t; i != dots.end(); i++) {
		if ((*i) == this) continue;

		auto dist = (m_pos - (*i)->m_pos).length_2d();

		if (dist < 128) {
			int alpha = opacity * (dist / 128);
			ImGui::GetWindowDrawList()->AddLine({ m_pos.x - 1, m_pos.y - 2 }, { (*i)->m_pos.x - 2, (*i)->m_pos.y - 1 }, ImColor(100, 0, 255, 150));
		}
	}
}


void dot_draw() {
	struct screen_size {
		int x, y;
	}; screen_size sc;

	sc.x = 1920, sc.y = 1080;

	int s = rand() % 9;

	if (s == 0) {
		dots.push_back(new dot(Vector3(rand() % (int)sc.x, -16, 0), Vector3((rand() % 7) - 3, rand() % 3 + 1, 0)));
	}
	else if (s == 1) {
		dots.push_back(new dot(Vector3(rand() % (int)sc.x, (int)sc.y + 16, 0), Vector3((rand() % 7) - 3, -1 * (rand() % 3 + 1), 0)));
	}
	else if (s == 2) {
		dots.push_back(new dot(Vector3(-16, rand() % (int)sc.y, 0), Vector3(rand() % 3 + 1, (rand() % 7) - 3, 0)));
	}
	else if (s == 3) {
		dots.push_back(new dot(Vector3((int)sc.x + 16, rand() % (int)sc.y, 0), Vector3(-1 * (rand() % 3 + 1), (rand() % 7) - 3, 0)));
	}

	auto alph = 135.0f * (240 / 255.0f);
	auto a_int = (int)(alph);

	ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

	for (auto i = dots.begin(); i < dots.end();) {
		if ((*i)->m_pos.y < -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
			delete (*i);
			i = dots.erase(i);
		}
		else {
			(*i)->update();
			i++;
		}
	}

	for (auto i = dots.begin(); i < dots.end(); i++) {
		(*i)->draw();
	}
}

bool subtab(const char* label, bool selected, ImVec2 size_arg = ImVec2(0, 0))
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	float t = selected ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.50f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = selected ? (t_anim) : (1.0f - t_anim);
	}

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	ImVec4 col = ImLerp(ImVec4{ 140 / 255.f, 140 / 255.f, 140 / 255.f, alphamodulate }, ImVec4{ 9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate }, t);
	ImVec4 col2 = ImLerp(ImVec4{ 140 / 255.f, 140 / 255.f, 140 / 255.f, 0 / 255.f }, ImVec4{ 9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate }, t);

	ImGui::PushStyleColor(ImGuiCol_Text, col);
	ImGui::RenderText(ImVec2(bb.Min.x + (size_arg.x / 2 - label_size.x / 2), bb.Min.y + (size_arg.y / 2 - label_size.y / 2)), label);
	ImGui::PopStyleColor();

	window->DrawList->AddLine(bb.Min + ImVec2(40, size_arg.y), bb.Max - ImVec2(40, 0), ImGui::GetColorU32(col2));

	return pressed;
}

bool checkbox(const char* label, bool* v)
{
	IM_USE;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos + ImVec2(10, 5), pos + ImVec2(square_sz + (style.ItemInnerSpacing.x + label_size.x + 0), 0 + label_size.y + style.FramePadding.y * 2) + ImVec2(10, 5));
	ItemSize(total_bb, style.FramePadding.y);
	ItemAdd(total_bb, id);

	bool hovered, held;
	bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	if (pressed)
		*v = !(*v);

	window->DrawList->AddRectFilled(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 10), ImColor(37, 37, 37, int(alphamodulate * 253)), 0, 15);
	window->DrawList->AddRect(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 10), ImColor(27, 27, 27, int(alphamodulate * 253)), 0, 15);

	if (*v)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(total_bb.Min.x + 1, total_bb.Min.y + 1), ImVec2(total_bb.Min.x + 9, total_bb.Min.y + 9), ImColor(9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate), ImColor(9 / 255.f, 169 / 255.f, 232 / 255.f, alphamodulate), ImColor(0, 54, 116, int(alphamodulate * 253)), ImColor(0, 54, 116, int(alphamodulate * 253)));
	}

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(214 / 255.f, 214 / 255.f, 214 / 255.f, alphamodulate));
	ImGui::RenderText(ImVec2(total_bb.Min.x + style.ItemInnerSpacing.x + 10, total_bb.Min.y + style.FramePadding.y + -4), label);
	ImGui::PopStyleColor();
	return pressed;
}



bool beginchildex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
{
	IM_USE;

	ImGuiContext& g = *GImGui;
	ImGuiWindow* parent_window = g.CurrentWindow;

	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
	flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

	// Size
	const ImVec2 content_avail = GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
	if (size.x <= 0.0f)
		size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
	if (size.y <= 0.0f)
		size.y = ImMax(content_avail.y + size.y, 4.0f);
	SetNextWindowSize(size);

	// Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
	char title[256];
	if (name)
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%s_%08X", parent_window->Name, name, id);
	else
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%08X", parent_window->Name, id);

	const float backup_border_size = g.Style.ChildBorderSize;
	if (!border)
		g.Style.ChildBorderSize = 0.0f;
	bool ret = Begin(title, NULL, flags);
	g.Style.ChildBorderSize = backup_border_size;

	ImGuiWindow* child_window = g.CurrentWindow;
	child_window->ChildId = id;
	child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

	// Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
	// While this is not really documented/defined, it seems that the expected thing to do.
	if (child_window->BeginCount == 1)
		parent_window->DC.CursorPos = child_window->Pos;

	// Process navigation-in immediately so NavInit can run on first frame
	if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayerActiveMask != 0 || child_window->DC.NavHasScroll))
	{
		FocusWindow(child_window);
		NavInitWindow(child_window, false);
		SetActiveID(id + 1, child_window); // Steal ActiveId with another arbitrary id so that key-press won't activate child item
		g.ActiveIdSource = ImGuiInputSource_Nav;
	}
	parent_window->DrawList->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size_arg, ImColor(12, 12, 12, int(alphamodulate * 170)), 0);
	parent_window->DrawList->AddRect(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size_arg, ImColor(59, 59, 59, int(alphamodulate * 140)), 0);
	parent_window->DrawList->AddRect(ImGui::GetWindowPos() + ImVec2(1, 1), ImGui::GetWindowPos() + size_arg - ImVec2(1, 1), ImColor(2, 2, 2, int(alphamodulate * 170)), 0);
	return ret;
}

bool beginchild(const char* str_id, const ImVec2& size_arg, bool border = false, ImGuiWindowFlags extra_flags = NULL)
{
	IM_USE;

	ImGuiWindow* window = GetCurrentWindow();
	return beginchildex(str_id, window->GetID(str_id), size_arg, border, extra_flags);
}


ImGuiWindowFlags ColorPicker = ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_DisplayHSV;
ImGuiWindowFlags Flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
ImGuiColorEditFlags ColorFlag = ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar;