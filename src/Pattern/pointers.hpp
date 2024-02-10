#pragma once
#include "common.hpp"

#include "GTA/memory/handle.hpp"
#include <player/CPlayerInfo.hpp>
#include <script/scrProgram.hpp>

namespace Big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();

	public:
		HWND m_hwnd{};

		bool* m_is_session_started{};

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};
		std::int64_t** m_script_globals{};
        intptr_t** m_GlobalPtr;
		PVOID m_init_native_tables{};

		IDXGISwapChain** m_swapchain{};

		PVOID m_model_spawn_bypass;

		/*GenericPool** m_ped_pool;
		GenericPool** m_prop_pool;
		GenericPool** m_pickup_pool;
		VehiclePool*** m_vehicle_pool;*/

		PVOID m_queue_dependency;
	};

	inline pointers* g_pointers{};
}