
#define get_keycode_name(vk, name)\
switch (vk) {\
case VK_CONTROL: name = "control"; break;\
case VK_SHIFT: name = "shift"; break;\
case VK_LSHIFT: name = "shift"; break;\
case VK_MENU: name = "alt"; break;\
case VK_TAB: name = "tab"; break;\
case VK_LBUTTON: name = "mouse 1"; break;\
case VK_RBUTTON: name = "mouse 2"; break;\
case VK_MBUTTON: name = "mouse 3"; break;\
case VK_XBUTTON1: name = "mouse 4"; break;\
case VK_XBUTTON2: name = "mouse 5"; break;\
case VK_PRIOR: name = "page up"; break;\
case VK_NEXT: name = "page down"; break;\
case VK_END: name = "end"; break;\
case VK_HOME: name = "home"; break;\
case VK_LEFT: name = "left arrow"; break;\
case VK_UP: name = "up arrow"; break;\
case VK_RIGHT: name = "right arrow"; break;\
case VK_DOWN: name = "down arrow"; break;\
case VK_INSERT: name = "insert"; break;\
case VK_DELETE: name = "delete"; break;\
case 'A': name = "a"; break;\
case 'B': name = "b"; break;\
case 'C': name = "c"; break;\
case 'D': name = "d"; break;\
case 'E': name = "e"; break;\
case 'F': name = "f"; break;\
case 'G': name = "g"; break;\
case 'H': name = "h"; break;\
case 'I': name = "i"; break;\
case 'J': name = "j"; break;\
case 'K': name = "k"; break;\
case 'L': name = "l"; break;\
case 'M': name = "m"; break;\
case 'N': name = "n"; break;\
case 'O': name = "o"; break;\
case 'P': name = "p"; break;\
case 'Q': name = "q"; break;\
case 'R': name = "r"; break;\
case 'S': name = "s"; break;\
case 'T': name = "t"; break;\
case 'U': name = "u"; break;\
case 'V': name = "v"; break;\
case 'W': name = "w"; break;\
case 'X': name = "x"; break;\
case 'Y': name = "y"; break;\
case 'Z': name = "z"; break;\
case VK_NUMPAD0: name = "numpad 0"; break;\
case VK_NUMPAD1: name = "numpad 1"; break;\
case VK_NUMPAD2: name = "numpad 2"; break;\
case VK_NUMPAD3: name = "numpad 3"; break;\
case VK_NUMPAD4: name = "numpad 4"; break;\
case VK_NUMPAD5: name = "numpad 5"; break;\
case VK_NUMPAD6: name = "numpad 6"; break;\
case VK_NUMPAD7: name = "numpad 7"; break;\
case VK_NUMPAD8: name = "numpad 8"; break;\
case VK_NUMPAD9: name = "numpad 9"; break;\
case VK_F1: name = "F1"; break;\
case VK_F2: name = "F2"; break;\
case VK_F3: name = "F3"; break;\
case VK_F4: name = "F4"; break;\
case VK_F5: name = "F5"; break;\
case VK_F6: name = "F6"; break;\
case VK_F7: name = "F7"; break;\
case VK_F8: name = "F8"; break;\
case VK_F9: name = "F9"; break;\
case VK_F10: name = "F10"; break;\
case VK_F11: name = "F11"; break;\
case VK_F12: name = "F12"; break;\
default: name = "unknown";\
}

extern ImDrawList* draw;
extern ImFont* iconfont;
extern bool theme;

bool tab(const char* label, bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize(ImVec2(120, 25), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	if (selected) {
		draw->AddRectFilledMultiColor(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_TabLine1), ImGui::GetColorU32(ImGuiCol_WindowBg), ImGui::GetColorU32(ImGuiCol_WindowBg), ImGui::GetColorU32(ImGuiCol_TabLine1));
		draw->AddLine(bb.Min, ImVec2(bb.Min.x, bb.Max.y), ImColor(14, 14, 16), 2);
		draw->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), ImColor(14, 14, 16), 2);
		draw->AddLine(bb.Max, ImVec2(bb.Min.x, bb.Max.y), ImColor(14, 14, 16), 2);
		draw->AddLine(bb.Min, ImVec2(bb.Min.x, bb.Max.y), ImColor(38, 38, 42));
		draw->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), ImColor(38, 38, 42));
		draw->AddLine(bb.Max, ImVec2(bb.Min.x, bb.Max.y), ImColor(38, 38, 42));
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(ImGuiCol_CheckMark));
		ImGui::RenderText(ImVec2(bb.Min.x + 15, bb.Min.y + size.y / 2 - label_size.y / 2), label);
		ImGui::PopStyleColor();
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(78 / 255.f, 78 / 255.f, 83 / 255.f, 1));
		ImGui::RenderText(ImVec2(bb.Min.x + 15, bb.Min.y + size.y / 2 - label_size.y / 2), label);
		ImGui::PopStyleColor();
	}

	return pressed;
}
