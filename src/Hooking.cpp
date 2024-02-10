#include "Hooking.hpp"
#include "Game.hpp"
#include "Script.hpp"
#include "CustomText.hpp"
#include "Util.hpp"
#include "DX/D3DRenderer.hpp"
#include "GTA/Natives.hpp"
#include "UI/Framework.hpp"
#include <MinHook.h>
#include "LogScript.hpp"
#include "common.hpp"
#include "Notify.hpp"
#include "menu/main_menu.hpp"

namespace Big
{
	namespace { std::uint32_t g_HookFrameCount{}; }
	bool Hooks::RunScriptThreads(std::uint32_t ops_to_execute) {
		if (g_Running) {
			g_ScriptManager.ScriptTick();
		}
		return static_cast<decltype(&RunScriptThreads)>(g_Hooking->m_RunScriptThreads)(ops_to_execute);
	}
	void* Hooks::assignPhyiscalIdx(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t newIdx) {
		ImGuiToast toast(Playerlist, 5000);
		toast.set_title("Playerlist");
		toast.set_content("%s has %s", player->get_name(), newIdx == 0xFF ? "left" : "joined");
		ImGui::InsertNotification(toast);
		return static_cast<decltype(&assignPhyiscalIdx)>(g_Hooking->m_assignPhyiscalIdx)(netPlayerMgr, player, newIdx);
	}
	const char* Hooks::GetLabelText(void* unk, const char* label) {
		if (g_Running) {
			if (auto text = g_CustomText->GetText(Joaat(label))) return text;
		}
		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}
	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return CallWindowProcW(g_Hooking->m_OriginalWndProc, hWnd, msg, wParam, lParam);
	}
	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags) {
		if (g_Running) {
			g_D3DRenderer->BeginFrame();
			g_LogScript->OnPresentTick();
			ImGui::DrawNotifications();
			ScriptImGuiMain();
			g_D3DRenderer->EndFrame();
		}
		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}
	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
		if (g_Running) {
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr)) {
				g_D3DRenderer->PostResize();
			}
			return hr;
		}
		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}
	Hooking::Hooking() : m_D3DHook(g_GameVariables->m_Swapchain, 19) {
		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_RunScriptThreads, &Hooks::RunScriptThreads, &m_RunScriptThreads);
		MH_CreateHook(g_GameFunctions->m_assignPhysicalIdxT, &Hooks::assignPhyiscalIdx, &m_assignPhyiscalIdx);
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}
	Hooking::~Hooking() noexcept {
		MH_RemoveHook(g_GameFunctions->m_RunScriptThreads);
		MH_RemoveHook(g_GameFunctions->m_assignPhysicalIdxT);
		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_Uninitialize();
		m_D3DHook.Unhook(Hooks::PresentIndex);
		m_D3DHook.Unhook(Hooks::ResizeBuffersIndex);
	}
	void Hooking::Hook() {
		m_OriginalWndProc = (WNDPROC)SetWindowLongPtrW(g_GameVariables->m_GameWindow, GWLP_WNDPROC, (LONG_PTR)&Hooks::WndProc);
		m_D3DHook.Enable();
		MH_EnableHook(MH_ALL_HOOKS);
	}
	void Hooking::Unhook() {
		SetWindowLongPtrW(g_GameVariables->m_GameWindow, GWLP_WNDPROC, (LONG_PTR)m_OriginalWndProc);
		m_D3DHook.Disable();
		MH_DisableHook(MH_ALL_HOOKS); 
	}
}