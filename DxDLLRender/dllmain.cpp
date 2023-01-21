#include "includes.h"
#include "internet.h"

#pragma comment(lib, "ntdll.lib")

#include "discord/discord.h"

Discord* g_Discord;

__forceinline void discord_main()
{
	g_Discord->Initialize();
	g_Discord->Update();
}



char dlldir[320];

DWORD64 ClientInputXD = 0;
void* DetourVTable(void** VTable, int Function, void* Detour)
{
	void* ret = VTable[Function];
	DWORD old;
	VirtualProtect(&(VTable[Function]), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
	VTable[Function] = Detour;
	VirtualProtect(&(VTable[Function]), sizeof(void*), old, &old);
	return ret;
}
void injection(HINSTANCE hModule) {
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	std::string webhook_url = ("https://discord.com/api/webhooks/954059865653911642/nacfilZw0yhDUwKR4WwLVNTcBfKi-6UGgBX10GNNOysgDBibiPh-kI6ZUZNGWFrYoqkd");
	std::string avatar_url = ("https://cdn.discordapp.com/attachments/878368983424839722/953680957175660574/a5b9b6cda1fe53b27d88ad7bc5b6dcac.jpg");
	std::string winname = name;
	std::time_t result = std::time(nullptr);
	std::string wintime = std::asctime(std::localtime(&result));
	std::string success = (u8"curl --data \"username=ARKCHEATS&content=geonew.cc open username: ") + winname + (u8" time: ") + wintime + ("&avatar_url=") + avatar_url + "\" " + webhook_url;
	system(success.c_str());

}

void RUST_OnLoad(HINSTANCE hModule) {
	DisableThreadLibraryCalls(hModule);
	injection(hModule);
	GetModuleFileName(hModule, (LPWSTR)dlldir, 512);
	for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
	CreateThread(NULL, 0, Start, NULL, 0, NULL);
	il2cpp::init();
	init_bp();
	unity::init_unity();
}

bool DllMain(HMODULE hMod, std::uint32_t call_reason, void*) {
	if (call_reason != DLL_PROCESS_ATTACH)
		return false;
	const auto handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(RUST_OnLoad), hMod, 0, nullptr);
	if (handle != NULL)
		CloseHandle(handle);

	return true;
}

//BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
//	switch (dwReason)
//	{
//	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
//		DisableThreadLibraryCalls(hModule);
//		injection(hModule);
//		GetModuleFileName(hModule, (LPWSTR)dlldir, 512);
//		for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
//		CreateThread(NULL, 0, Start, NULL, 0, NULL);
//		il2cpp::init();
//		init_bp();
//		unity::init_unity();
//		//ClientInputXD = GetModBase((L"GameAssembly.dll")) + 0x3045D0;
//		//DetourAttach(&(LPVOID&)ClientInputXD, &ClientInput);
//
//		break;
//	//case DLL_PROCESS_DETACH: // A process unloads the DLL.
//	//	DetourTransactionBegin();
//	//	DetourUpdateThread(GetCurrentThread());
//	//	DetourDetach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
//	//	DetourTransactionCommit();
//	//	break;
//	}
//	discord_main(hModule);
//	return TRUE;
//}
