#pragma once
#include "VMTHook.hpp"

namespace Big
{
	struct Hooks
	{
		static bool RunScriptThreads(std::uint32_t ops_to_execute);
		static void* assignPhyiscalIdx(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, std::uint8_t newIdx);
		static const char* GetLabelText(void* unk, const char* label);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);
		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		friend struct Hooks;
	private:
		void* m_NtQueryVirtualMemory{};
		void* m_RunScriptThreads{};
		void* m_OriginalGetLabelText{};
		void* m_assignPhyiscalIdx{};
		WNDPROC m_OriginalWndProc{};
		VMTHook m_D3DHook;
	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
