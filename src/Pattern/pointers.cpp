/**
 * @file pointers.cpp
 * @brief All the signature scans are here.
 */

#include "pointers.hpp"

#include "common.hpp"
#include "log/Logger.hpp"
#include "GTA/memory/all.hpp"

namespace Big
{
	pointers::pointers()
	{
		memory::pattern_batch main_batch;

		main_batch.add("Is session started", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr) {
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});

        main_batch.add("Global Ptr", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr) {
			m_GlobalPtr = ptr.add(3).rip().as<intptr_t**>();
		});

		main_batch.add("Ped factory", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", [this](memory::handle ptr) {
			m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
		});

		main_batch.add("Network player manager", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [this](memory::handle ptr) {
			m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
		});

		main_batch.add("Script globals", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr) {
			m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
		});

		main_batch.add("Swapchain", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr) {
			m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
		});

		main_batch.add("Model Spawn Bypass", "48 8B C8 FF 52 30 84 C0 74 05 48", [this](memory::handle ptr) {
			m_model_spawn_bypass = ptr.add(8).as<PVOID>();
		});

		main_batch.add("Queue Dependency", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 8B F2 49 8B F8", [this](memory::handle ptr) {
			m_queue_dependency = ptr.as<PVOID>();
		});

		/*main_batch.add("PEP", "4C 8B 35 ? ? ? ? B8 ? ? ? ? 0F 57 F6 89 05 ? ? ? ? 49 63 76 10 4C 8B FE 85 F6 0F 84 ? ? ? ? 49 8B 46 08 49 FF CF FF CE 42 0F B6 0C 38", [this](memory::handle ptr) {
			m_ped_pool = ptr.add(3).rip().as<GenericPool**>();
		});

		main_batch.add("PRP", "48 8B 05 ? ? ? ? 0F B7 50 10 48 8B 05", [this](memory::handle ptr) {
				m_prop_pool = ptr.add(3).rip().as<GenericPool**>();
			    m_pickup_pool = ptr.add(0xE).rip().as<GenericPool**>();
		});

		main_batch.add("VEP", "4C 8B 25 ? ? ? ? 8B 29 33 F6 49 8B 04 24 33 DB 4C 8D 71 08 44 8B 78 08 45 85 FF 0F 8E ? ? ? ? 4D 8B 0C 24 41 3B 59 08 7D 29 49 8B 51 30 44 8B C3 8B CB 49 C1 E8 05 83 E1 1F 44 8B D3 42 8B 04 82", [this](memory::handle ptr) {
			   m_vehicle_pool = ptr.add(3).rip().as<VehiclePool***>();
		});*/

		main_batch.run(memory::module(nullptr));

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}


	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}