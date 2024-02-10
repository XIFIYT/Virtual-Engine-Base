#include "Game.hpp"
#include "Invoker.hpp"

namespace Big
{										
	GameVariables::GameVariables():
		m_GameState(Signature("83 3D ? ? ? ? ? 75 17 8B 43 20 25", "GS").Scan().Add(2).Rip().Add(1).As<eGameState*>()),
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
		m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", "SC").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),
		m_GlobalPtr(Signature("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", "GP").Scan().Add(3).Rip().As<decltype(m_GlobalPtr)>()),
		m_ped_factory(Signature("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", "PF").Scan().Add(3).Rip().As<decltype(m_ped_factory)>()),
		m_net_game_player(Signature("48 83 EC ? 33 C0 38 05 ? ? ? ? 74 ? 83 F9", "NGP").Scan().As<decltype(m_net_game_player)>()),
		ui_3d_draw_manager(Signature("4C 8B 15 ? ? ? ? F3 0F 11 45 ? F3 0F 10 05 ? ? ? ? BF ? ? ? ? BB ? ? ? ? 41 BE ? ? ? ? F3 0F 11", "U3DM").Scan().Add(3).Rip().As<decltype(ui_3d_draw_manager)>()),
		push_scene_preset_manager(Signature("40 53 48 83 EC 20 8B 02 48 8D 54 24 38 48 8B D9 89 44 24 38 E8 ? ? ? ? 48 8B C8", "PSPM").Scan().As<decltype(push_scene_preset_manager)>()),
		add_element_to_scene(Signature("4C 8B DC 48 83 EC 58 8B", "AETS").Scan().As<decltype(add_element_to_scene)>()),
		set_scene_element_lighting(Signature("48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 83 B9", "SCEL").Scan().As<decltype(set_scene_element_lighting)>()),
		get_scene_preset(Signature("0F B7 81 10 08 00 00", "GSP").Scan().As<decltype(get_scene_preset)>())
		//m_NativeReturn(Signature("FF E3").Scan().As<decltype(m_NativeReturn)>()) no longer in use //rockstar doesnt check on return functions
	{
	}

	void GameVariables::PostInit()
	{
	}

	GameFunctions::GameFunctions():
		m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", "GLT").Scan().Sub(19).As<PVOID>()),
		m_FixVectors(Signature("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", "FV").Scan().As<decltype(m_FixVectors)>()),
		m_assignPhysicalIdxT(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8", "API").Scan().As<decltype(m_assignPhysicalIdxT)>()),
		m_RegisterFile(Signature("84 C0 74 0D 4C 8B 07", "RF").Scan().Sub(0x6C).As<decltype(m_RegisterFile)>()),
		m_network(Signature("48 8B 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 75 17 48 8B 0D ? ? ? ? 48 8B D7", "N").Scan().Add(3).Rip().As<Network**>()),
		m_get_connection_peer(Signature("8D 42 FF 83 F8 FD 77 3D", "GCP").Scan().Add(23).Rip().As<get_connection_peer>()),
		m_GetNetPlayer(Signature("48 83 EC 28 33 C0 38 05 ? ? ? ? 74 0A", "GNP").Scan().As<decltype(m_GetNetPlayer)>())
	{
		auto MainSig = Signature("45 33 F6 8B E9 85 C9 B8", "ST << RST").Scan();
		m_script_threads = MainSig.Sub(4).Rip().Sub(8).As<decltype(m_script_threads)>();
		m_RunScriptThreads = MainSig.Sub(0x1F).As<decltype(m_RunScriptThreads)>();

		auto Sig = Signature("40 B6 01 39 79 2C", "NRT << GNH").Scan();
		m_NativeRegistrationTable = Sig.Add(0xF).Rip().As<decltype(m_NativeRegistrationTable)>();
		m_GetNativeHandler = Sig.Add(0x18).Rip().As<decltype(m_GetNativeHandler)>();
	}
}
