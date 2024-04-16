#include "menu/main_menu.hpp"
#include "Lists.hpp"
#include "GTA/Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/Framework.hpp"
#include "UI/option/BoolOption.hpp"
#include "UI/option/ChooseOption.hpp"
#include "UI/option/NumberOption.hpp"
#include "UI/option/RegularOption.hpp"
#include "UI/option/SubOption.hpp"
#include "UI/submenu/PlayerSubmenu.hpp"
#include "Notify.hpp"
#include "Vehicle.hpp"
#include "Features.hpp"
#include "UI/optionDesign/OptionDrawers.hpp"
#include "Utility.hpp"
#include "Player.h"
#include "Backend/Authorization.hpp"
#include "shellapi.h"
#include "Utility/scaleform.hpp"
#include "menu/submenu.h"
#include "Features/Self.hpp"
bool aimbot = false;
inline bool godmode1 = true;

namespace Big
{
	//helper for notification
	void Notify(ImGuiToastType_ type, int timer, const char* title, const char* text) {
		ImGuiToast toast(type, timer);
		toast.set_title(title);
		toast.set_content(text);
		ImGui::InsertNotification(toast);
	}
	
	void MainMenu::Init() {
		using namespace UserInterface;
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Virtual Engine is the BEST MOD MENU EVER !");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "Virtual Engine is the BEST MOD MENU EVER !, Anyways , who is your uncle");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_QUITTING"), "Leave , but still Virtual Engine ");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HS_KILLED"), "Fucked Him Up ");
		g_Render->draw_submenu<sub>("Main Menu", SubmenuHome, [](sub* sub)
			{
				if(GetAuthorization()->login)
				{
					addButton("Enter Key", nullptr, [] {
						g_Settings.Authorization = true;
					});
					addButton("Get Key", nullptr, [] {
						ShellExecute(0, 0, "https://link-target.net/1014018/virtual-x-key1", 0, 0, SW_SHOW);
					});
				}
				else
				{
					addSubmenu("Self", nullptr, SubmenuSelf);
					addSubmenu("Player", nullptr, SubmenuPlayerList);
					addSubmenu("Protections", nullptr, SubmenuProtections);
					addSubmenu("Teleport", nullptr, SubmenuTeleport);
					addSubmenu("Weapon", nullptr, SubmenuWeapon);
					addSubmenu("Vehicle", nullptr, SubmenuVehicle);
					addSubmenu("Spawner", nullptr, SubmenuSspawener);
					addSubmenu("World", nullptr, SubmenuWorld);
					addSubmenu("Settings", nullptr, SubmenuSettings);
					addToggle("Click UI", "Click UI", &g_Render->m_ImGuiActive);
				}
				
			});
		g_Render->draw_submenu<sub>("Self", SubmenuSelf, [](sub* sub)
			{
				
				addToggle("Godmode", nullptr, &godmode1, [] {
					if (!godmode1)
					{
						ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
					}
					});
					addButton("Notify", "teste notify", [] {
						Notify(ImGuiToastType_::Playerlist, 5000, "Notify", "teste notify");
					});
			});
		g_Render->draw_submenu<sub>("Player List", SubmenuPlayerList, [](sub* sub)
			{

				addSubmenu("All", nullptr, SubmenuAllPlayers);
				addSubmenu("Saved", nullptr, SubmenuSavedPlayers);
				addSubmenu("Hide Information", nullptr, rage::joaat("HideINFO"));
				addSubmenu("Settings", nullptr, rage::joaat("PlayerInfoSettings"));
				addSubmenu("Ped Preview", nullptr, rage::joaat("RVEV"));
				addScroll("Icon Type", "", &g_Render->icon_type, &g_Render->icon_pos);
				//addBreak(("List"));
				for (std::uint32_t i = 0; i < 32; ++i)
				{


					if (auto ped = Utility::PlayerIndex(i))
					{
						Blip blip = HUD::GET_BLIP_FROM_ENTITY(ped);
						if (sub->GetSelectedOption() == sub->GetNumOptions()) {
							if (hide_information.all) {
								g_players.draw_info(i);
							}
						}
						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (name == "XIFI_ENG") {
							name.append(" ~r~[Dev]");
						}
						if (name == "XIFI_ENG") {
							name.append(" ~r~[Dev]");
						}
						if (i == PLAYER::PLAYER_ID() && tags.self)
							name.append(" ~p~[Self]");
						if (INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) != 0 && tags.interior) {
							name.append(" ~b~[Interior]");
						}
						if (g_Render->icon_pos == 0) {
							addPlayerSubmenu(name.c_str(), nullptr, SubmenuSelectedPlayer, Utility::headshot[i], [=]
								{
									g_SelectedPlayer = i;
									Utility::m_selected_player.m_id = i;
									Utility::m_selected_player.m_net_player_data = g_GameFunctions->m_GetNetPlayer(i);
								});
						}
						else if (g_Render->icon_pos == 1) {
							addPlayerSubmenu(name.c_str(), nullptr, SubmenuSelectedPlayer, Utility::headshot[i], [=]
								{
									g_SelectedPlayer = i;
									Utility::m_selected_player.m_id = i;
									Utility::m_selected_player.m_net_player_data = g_GameFunctions->m_GetNetPlayer(i);
								}, HUD::GET_BLIP_SPRITE(blip));
						}


					}


				}

			});
		g_Render->draw_submenu<sub>("Ped Preview", rage::joaat("RVEV"), [](sub* sub)
			{
				
				
			});
		g_Render->draw_submenu<sub>("Settings", SubmenuSettings, [](sub* sub)
			{
				addSubmenu("Positions", nullptr, Positions);
				addSubmenu("Colors", nullptr, SubmenuColors);
				addSubmenu("Themes", nullptr, SubmenuThemes);
			});
		g_Render->draw_submenu<sub>(("Colors"), SubmenuColors, [](sub* sub)
			{
				addSubmenu("Header Background", nullptr,  SubmenuHeaderColor);
				addSubmenu("Header Text", nullptr,  SubmenuHeaderText);
				addSubmenu("Background Selected", nullptr,  SubmenuOptionSelectedBackground);
				addSubmenu("Background Unselected", nullptr, SubmenuOptionUnselectedBackground);
				addSubmenu("Text Selected", nullptr,  OptionTextSelected);
				addSubmenu("Text Unselected", nullptr,  OptionTextUnselected);
				addSubmenu("Footer Background", nullptr,  FooterBackground);
				addSubmenu("Footer Sprite", nullptr,  FooterSprite);
				addSubmenu("Subheader Background", nullptr,  SubheaderBackground);
				addSubmenu("Subheader Text Left", nullptr,  SubheaderTextLeft);
				addSubmenu("Subheader Text Right", nullptr,  SubheaderTextRight);
				//addSubmenu("Radius Sphere", nullptr, g_Render->m_RadiusSphere, rage::joaat("RadiusSphere"), [] {

					//});

			});
		
	}
	void ScriptImGuiMain() {
		if (g_Render->m_Opened && g_Render->m_ImGuiActive)
		{
			g_Render->m_OpenDelay = false;
			g_Settings.m_LockMouse = true;
			ImGui::SetNextWindowSize(ImVec2(800, 550), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(500, 500), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Menu")) {
				if (ImGui::BeginTabBar("tabbar")) {
					if (ImGui::BeginTabItem("Self")){
						ImGui::Checkbox("List UI", &g_Render->m_ImGuiActive);
						if(ImGui::Button("Notify"))
						{
							Notify(ImGuiToastType_::Playerlist, 5000, "Notify", "teste notify");
						}
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Weapon")){
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Vehicle")){
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Player")){
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Misc")){
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Spawner")){
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Teleport")){
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Settings")){
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();	
			}
			ImGui::End();
			}
		}
	  
	}
	void MainMenu::Tick() {
		g_MainMenu->Init();
		while (true) {
			g_Render->OnTick();
			Script::GetCurrent()->ScriptYield();
		}
	};
}
