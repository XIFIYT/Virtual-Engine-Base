#include "Game.hpp"
#include "Hooking.hpp"
#include "Script.hpp"
#include "LogScript.hpp"
#include "menu/main_menu.hpp"
#include "Invoker.hpp"
#include "CustomText.hpp"
#include "DX/D3DRenderer.hpp"
#include "UI/Framework.hpp"
#include "Translation.hpp"
#include "Notify.hpp"
#include "GTA/Natives.hpp"
#include "Backend/Authorization.hpp"
#include "Backend/BackendMain.hpp"
using namespace Big;
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID) {
	if (reason == DLL_PROCESS_ATTACH) {
		g_module = hInstance;
		g_mainThread = CreateThread(nullptr, 0, [](LPVOID) -> DWORD {
			GetBackendMain()->Init();
			while (g_Running) {
				if (GetAsyncKeyState(VK_END)) g_Running = false;
				std::this_thread::sleep_for(500ms);
			}
			std::this_thread::sleep_for(500ms);
			GetBackendMain()->Destroy();
			CloseHandle(g_mainThread);
			FreeLibraryAndExitThread(g_module, 0);
			
		}, nullptr, 0, nullptr);
	}
	return TRUE;
}