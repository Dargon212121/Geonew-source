#include "headfont.h"
#include "font.h"
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromMemoryTTF(bebrafont,sizeof(bebrafont),14.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

	ImFontConfig font_config;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.PixelSnapH = true;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF,
		0x0400, 0x044F,
		0,
	};

	ImFont* TabsFont;
	ImFont* MenuFont;
	ImFont* NameFont;
	ImFont* IconsFont;



	/* io.Fonts->AddFontFromFileTTF(xorget("C:\\Windows\\Fonts\\Verdana.ttf"), 17.f);
	 ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 17.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	 icons = io.Fonts->AddFontFromMemoryTTF(CheatFont, sizeof(CheatFont), 23.0f);
	 big = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 14.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	 bigger = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 20.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());*/




	io.Fonts->AddFontDefault();
	TabsFont = io.Fonts->AddFontFromFileTTF("../../misc/fonts/arial3.ttf", 13.f);
	NameFont = io.Fonts->AddFontFromFileTTF("../../misc/fonts/arial1.ttf", 17.f);
	MenuFont = io.Fonts->AddFontFromFileTTF("../../misc/fonts/arial2.ttf", 14.f);
	init = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Smallest Pixel-7.ttf", 14.0f, &font_config, ranges);
	io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	g_pMenuFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
	IM_ASSERT(font != NULL);

	// Our state
	auto clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);

	// Main loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	ImGui::StyleColorsDark();

	style->Alpha = 1.f;
	style->WindowRounding = 5;
	style->FramePadding = ImVec2(4, 3);
	style->WindowPadding = ImVec2(0, 0);
	style->ItemInnerSpacing = ImVec2(4, 4);
	style->ItemSpacing = ImVec2(8, 10);
	style->FrameRounding = 12;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 12.f;
	style->PopupRounding = 0.f;

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();

			CreateDirectoryA("C:\\Geonew.cc", NULL);
			SetFileAttributesA("C:\\Geonew.cc", FILE_ATTRIBUTE_HIDDEN);
			PlaySoundA("C:\\Geonew.cc\\sound.wav", NULL, SND_ASYNC | SND_FILENAME);

			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show = !show;
	}
	if (GetAsyncKeyState(VK_F12) & 1)
	{
		Global::Panic = true;
		//unhook();
	}
	if (!Global::Panic) {
		if (Render::Object.NewFrame(pSwapChain))
		{
			InitCheat();
		}

	Render::Object.EndFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if ( Global::Loadem )
	{

			if (Global::ScreenHigh != 0 && Global::ScreenWidth != 0)
			{
				//RenderWatermark();
				if (show){
					invis(backgroundm,dotdraw );
				}
			}
		}
		else
		{
			Init();

		}
		ImGui::End();
		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		}
		return phookD3D11Present(pSwapChain, SyncInterval, Flags);
	}
int MultisampleCount = 1;
LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD __stdcall Start(LPVOID)
{
	Storage::gBase = (DWORD64)GetModuleHandleA("GameAssembly.dll");
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle(L"dxgi.dll");
		Sleep(4000);
	} while (!hDXGIDLL);
	Sleep(100);
	IDXGISwapChain* pSwapChain;
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = MultisampleCount;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	UINT createFlags = 0;
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	IDXGISwapChain* d3dSwapChain = 0;
	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)))
	{
		MessageBox(hWnd, L"Failed to create directX device and swapchain!", L"Error", MB_ICONERROR);
		return NULL;
	}
	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];
	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];
	phookD3D11Present = (D3D11PresentHook)(DWORD_PTR*)pSwapChainVtable[8];
	phookD3D11ResizeBuffers = (D3D11ResizeBuffersHook)(DWORD_PTR*)pSwapChainVtable[13];
	phookD3D11PSSetShaderResources = (D3D11PSSetShaderResourcesHook)(DWORD_PTR*)pContextVTable[8];
	phookD3D11Draw = (D3D11DrawHook)(DWORD_PTR*)pContextVTable[13];
	phookD3D11DrawIndexed = (D3D11DrawIndexedHook)(DWORD_PTR*)pContextVTable[12];
	phookD3D11DrawIndexedInstanced = (D3D11DrawIndexedInstancedHook)(DWORD_PTR*)pContextVTable[20];
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);

	DetourTransactionCommit();
	InitHook();
	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);
	if (!Global::Loadem) {
		Sleep(4000);
		Global::Loadem = true;
	}

	while (true) {
		Sleep(10);
	}
	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();
	return NULL;
}
void ImGui::StyleColorsDark(ImGuiStyle* dst)
{
	ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(225 / 255.f, 225 / 255.f, 225 / 255.f, 1.00f);
	colors[ImGuiCol_All] = ImVec4(100 / 255.f, 100 / 255.f, 100 / 255.f, 200 / 255.f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(22 / 255.f, 22 / 255.f, 26 / 255.f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(26 / 255.f, 26 / 255.f, 30 / 255.f, 1);
	colors[ImGuiCol_TabBar] = ImVec4(26 / 255.f, 26 / 255.f, 30 / 255.f, 1.f);
	colors[ImGuiCol_BackgroundTop] = ImVec4(41 / 255.f, 42 / 255.f, 47 / 255.f, 1);
	colors[ImGuiCol_BackgroundBot] = ImVec4(26 / 255.f, 28 / 255.f, 32 / 255.f, 1);
	colors[ImGuiCol_PopupBg] = ImVec4(50 / 255.f, 53 / 255.f, 58 / 255.f, 1);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(50 / 255.f, 53 / 255.f, 58 / 255.f, 1);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_Combo] = ImVec4(50 / 255.f, 53 / 255.f, 58 / 255.f, 1);
	colors[ImGuiCol_TabLine1] = ImVec4(67 / 255.f, 58 / 255.f, 190 / 255.f, 15 / 255.f);
	colors[ImGuiCol_TabLine2] = ImVec4(67 / 255.f, 58 / 255.f, 190 / 255.f, 0);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(110 / 255.f, 122 / 255.f, 200 / 255.f, 1.f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(110 / 255.f, 122 / 255.f, 200 / 255.f, 1.f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(110 / 255.f, 122 / 255.f, 200 / 255.f, 1.f);
	colors[ImGuiCol_CheckMark] = ImVec4(112 / 255.f, 102 / 255.f, 241 / 255.f, 1);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_Slider] = ImVec4(50 / 255.f, 53 / 255.f, 58 / 255.f, 1);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(50 / 255.f, 53 / 255.f, 58 / 255.f, 1);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 0);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImVec4(33 / 255.f, 36 / 255.f, 41 / 255.f, 1);
	colors[ImGuiCol_TabTextActive] = ImVec4(174 / 255.f, 129 / 255.f, 19 / 255.f, 1.f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_SliderText] = ImVec4(0.f, 0.f, 0.f, 1.f);
}
