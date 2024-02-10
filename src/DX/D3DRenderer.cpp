#include "D3DRenderer.hpp"
#include "UI/Framework.hpp"
#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <iostream>
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include "HeaderFontData.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Big
{
	D3DRenderer::D3DRenderer() :
		m_Swapchain(g_GameVariables->m_Swapchain)
	{
		if (FAILED(m_Swapchain->GetDevice(__uuidof(ID3D11Device), (void**)(&m_Device))))
			LOG(INFO) << "Failed to get D3D Device";
		m_Device->GetImmediateContext(&m_Context);

		ImGui::CreateContext();
		ImGui_ImplDX11_Init(m_Device, m_Context);
		ImGui_ImplWin32_Init(g_GameVariables->m_GameWindow);

		auto&& style = ImGui::GetStyle(); auto&& colors = style.Colors;
		style.WindowPadding = { 10.f, 10.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 8.f, 4.f };
		style.ItemSpacing = { 10.f, 5.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 0.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 15.f;
		style.GrabMinSize = 8.f;
		style.WindowBorderSize = 2.f;
		style.WindowRounding = 5.f;
		style.TabBorderSize = 1.f;
		style.ChildRounding = 2.f;
		style.FrameRounding = 2.f;
		style.ScrollbarRounding = 6.f;
		style.GrabRounding = 4.f;
		style.TabRounding = 3.f;
		style.WindowTitleAlign = { 1.0f, 0.5f };
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };
		colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
		colors[ImGuiCol_TextDisabled] = ImColor(200, 200, 200, 255);
		colors[ImGuiCol_WindowBg] = ImColor(13, 13, 13, 255);
		colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 0);
		colors[ImGuiCol_PopupBg] = ImColor(20, 20, 20, 255);
		colors[ImGuiCol_Border] = ImColor(0, 255, 255, 255);
		colors[ImGuiCol_BorderShadow] = ImColor(10, 10, 10, 200);
		colors[ImGuiCol_FrameBg] = ImColor(45, 45, 45, 200);
		colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30, 200);
		colors[ImGuiCol_FrameBgActive] = ImColor(30, 30, 30, 220);
		colors[ImGuiCol_TitleBg] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_TitleBgActive] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_TitleBgCollapsed] = ImColor(10, 10, 10, 200);
		colors[ImGuiCol_MenuBarBg] = ImColor(10, 10, 10, 155);
		colors[ImGuiCol_ScrollbarBg] = ImColor(10, 10, 10, 205);
		colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 255, 255, 225);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(255, 255, 255, 255);
		colors[ImGuiCol_ScrollbarGrabActive] = ImColor(255, 255, 255, 255);
		colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
		colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255, 225);
		colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255, 225);
		colors[ImGuiCol_Button] = ImColor(10, 10, 10, 205);
		colors[ImGuiCol_ButtonHovered] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_ButtonActive] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_Header] = ImColor(0, 0, 0, 255);
		colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 255);
		colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 255);
		colors[ImGuiCol_Separator] = ImColor(255, 255, 255, 255);
		colors[ImGuiCol_SeparatorHovered] = ImColor(255, 255, 255, 255);
		colors[ImGuiCol_SeparatorActive] = ImColor(255, 192, 255, 255);
		colors[ImGuiCol_ResizeGrip] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_ResizeGripHovered] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_ResizeGripActive] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_Tab] = ImColor(0, 255, 255, 215);
		colors[ImGuiCol_TabHovered] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_TabActive] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_TabUnfocused] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_TabUnfocusedActive] = ImColor(10, 10, 10, 255);
		colors[ImGuiCol_PlotLines] = ImColor(100, 100, 100, 255);
		colors[ImGuiCol_PlotLinesHovered] = ImColor(100, 100, 100, 255);
		colors[ImGuiCol_PlotHistogram] = ImColor(100, 100, 100, 255);
		colors[ImGuiCol_PlotHistogramHovered] = ImColor(100, 100, 100, 255);
		colors[ImGuiCol_TextSelectedBg] = ImColor(20, 20, 20, 255);
		colors[ImGuiCol_DragDropTarget] = ImColor(255, 255, 0, 255);
		colors[ImGuiCol_NavHighlight] = ImColor(105, 105, 105, 255);
		colors[ImGuiCol_NavWindowingHighlight] = ImColor(255, 255, 255, 185);
		colors[ImGuiCol_NavWindowingDimBg] = ImColor(205, 205, 205, 55);
		colors[ImGuiCol_ModalWindowDimBg] = ImColor(205, 205, 205, 75);
		ImGui::GetIO().IniFilename = nullptr;
		m_fontConfig.FontDataOwnedByAtlas = false;
		static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.OversampleH = 3;
		icons_config.OversampleV = 3;
		m_notifyFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ArialBD.ttf", 19.f, &m_fontConfig);
		m_headerFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\LightningFiles\\Fonts\\TitleFont.ttf", 40.f, &m_fontConfig);
	}

	D3DRenderer::~D3DRenderer() noexcept
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void D3DRenderer::BeginFrame()
	{
		if (g_Render->m_Opened && g_Settings.m_LockMouse)
		{
			ImGui::GetIO().MouseDrawCursor = true;
			ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}
		else
		{
			ImGui::GetIO().MouseDrawCursor = false;
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

	
	}

	void D3DRenderer::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void D3DRenderer::PreResize()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	void D3DRenderer::PostResize()
	{
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void D3DRenderer::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_KEYUP && wParam == 'X' && g_Render->controlsEnabled) {
			g_Settings.m_LockMouse = !g_Settings.m_LockMouse;
		}

		if (ImGui::GetCurrentContext())
			ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	}
}
