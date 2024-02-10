#pragma once
#include "Types.hpp"
#include <ped/CPedFactory.hpp>
#include <network/CNetworkPlayerMgr.hpp>
#include <script/GtaThread.hpp>
#include <network/Network.hpp>
namespace rage
{
	struct scrNativeRegistrationTable;
	struct scrNativeCallContext;
	using scrNativeHandler = void(*)(scrNativeCallContext*);
}

namespace Big
{
	class netConnectionPeer
	{
	public:
		uint32_t m_internal_ip; //0x0000
		uint16_t m_internal_port; //0x0004
		uint32_t m_external_ip; //0x0008
		uint16_t m_external_port; //0x000C
		uint64_t m_peer_id; //0x0010
		uint32_t unk_0018; //0x0018
		uint16_t unk_001C; //0x001C
		uint8_t m_platform; //0x001E
	};
	class GameVariables {
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;
		void PostInit();
		eGameState* m_GameState;
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
		intptr_t** m_GlobalPtr;
		CPedFactory** m_ped_factory{};
		const char* m_version = VERSION;
		using get_net_game_player = CNetGamePlayer * (*) (uint32_t player);
		get_net_game_player m_net_game_player;
		uintptr_t ui_3d_draw_manager;
		uintptr_t add_element_to_scene;
		uintptr_t push_scene_preset_manager;
		uintptr_t set_scene_element_lighting;
		uintptr_t get_scene_preset;
	};
	inline std::unique_ptr<GameVariables> g_GameVariables;
	class GameFunctions {
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;
		rage::atArray<GtaThread*>* m_script_threads{};
		using run_script_threads = bool(std::uint32_t ops_to_execute);
		run_script_threads* m_RunScriptThreads;
		PVOID m_GetLabelText;
		using GetNativeHandler = rage::scrNativeHandler(rage::scrNativeRegistrationTable*, std::uint64_t);
		GetNativeHandler* m_GetNativeHandler;
		using FixVectors = void(rage::scrNativeCallContext*);
		FixVectors* m_FixVectors;
		rage::scrNativeRegistrationTable* m_NativeRegistrationTable;
		using assignPhysicalIdxT = void* (CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t newIdx);
		assignPhysicalIdxT* m_assignPhysicalIdxT;
		using RegisterFile = std::uint32_t(*)(std::uint32_t* texture_id, const char* path, bool p1, const char* name, bool p2);
		RegisterFile m_RegisterFile;
		Network** m_network;
		using get_connection_peer = netConnectionPeer * (*)(rage::netConnectionManager* manager, int peer_id);
		get_connection_peer m_get_connection_peer{};
		using GetNetPlayer = CNetGamePlayer * (std::uint32_t id);
		GetNetPlayer* m_GetNetPlayer;

	};
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}