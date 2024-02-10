#include "Game.hpp"
#include "LogScript.hpp"
#include "UI/Framework.hpp"
#include <imgui.h>
#include "GTA/Natives.hpp"
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include "Backend/Authorization.hpp"
namespace Big
{
	namespace { std::size_t s_LastLogCount = 0; }
	void LogScript::OnPresentTick() {
		if (g_Settings.m_LogWindow) {
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Log")) {
			
				ImGui::End();
			}
		}
		if (g_Settings.Authorization) {
		ImGui::SetNextWindowSize(ImVec2(452, 172), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(700, 850), ImGuiCond_FirstUseEver);
			g_Settings.m_LockMouse = true;
			if (ImGui::Begin("Authorization"))
			{
				ImGui::InputTextWithHint(("###key_input"), (""), GetAuthorization()->g_Key, 55);
				if (ImGui::Button("Login Now"))
				{
					if (GetAuthorization()->g_Key == GetAuthorization()->GetKey()) {
						GetAuthorization()->MenuAcces = true;
						GetAuthorization()->login = false;
						g_Settings.m_LockMouse = false;
						g_Settings.Authorization = false;
						GetAuthorization()->Textures();
						
					}
					else
					{
						
					}

				}
			}
		}
	}
		
	
	void LogScript::Tick() {
		//Send/put single load functions sent here only load during runtime.
		while (true) {
			//Loop funcs here
			Script::GetCurrent()->ScriptYield();
		}
	}
}