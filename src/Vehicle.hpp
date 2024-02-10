#include "GTA/Natives.hpp"
#include "ScriptGlobal.hpp"
#include "Game.hpp"
#include "Script.hpp"
#include "Util.hpp"
#include "Common.hpp"
#include "Notify.hpp"
namespace Big
{
	inline bool MaxVehiclespawn = true;
	inline bool Sitinvehicle = true;
	inline bool bSpawnWithEffect = true;
	void SpawnVehicle(std::uint32_t model) {
		STREAMING::REQUEST_MODEL(model);
		for (uint8_t i = 25; i && !STREAMING::HAS_MODEL_LOADED(model); --i) {
			STREAMING::REQUEST_MODEL(model);
			Script::GetCurrent()->ScriptYield();
		}
		if (!STREAMING::HAS_MODEL_LOADED(model)) {

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			return;
		}
		auto PedDirection = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		const auto location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 2.f, 2.f, 0.f);
		static Vehicle veh;
		*ScriptGlobal(4539659).As<bool*>() = true;
		executeUnderScr(getThrUsingHash(NETWORK::NETWORK_IS_SESSION_ACTIVE() ? Joaat("freemode") : Joaat("main_persistent")), [=] {
			veh = VEHICLE::CREATE_VEHICLE(model, location.x, location.y, location.z, PedDirection + 90.f, true, false, false);
			});
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
		ENTITY::SET_ENTITY_HEADING(veh, PedDirection);
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE()) {
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
			auto networkId = NETWORK::VEH_TO_NET(veh);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, FALSE);
		}
		if (Sitinvehicle) {
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
		if (VEHICLE::IS_THIS_MODEL_A_HELI(model) || VEHICLE::IS_THIS_MODEL_A_PLANE(model))
			VEHICLE::SET_HELI_BLADES_FULL_SPEED(veh);
		if (VEHICLE::IS_THIS_MODEL_A_PLANE(model)) {
			VEHICLE::SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED(veh, true);
		}
		if (MaxVehiclespawn) {
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18 /* Turbo */, TRUE);
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20 /* Tire Smoke */, TRUE);
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 17 /* Xenon Headlights */, TRUE);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
			for (int i = 0; i < 50; i++) {
				VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, true);
			}
		}
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		if (bSpawnWithEffect) {
			ENTITY::SET_ENTITY_ALPHA(veh, 0, 0);
			Script::GetCurrent()->ScriptYield(100ms);
			ENTITY::RESET_ENTITY_ALPHA(veh);
		}
	}
}