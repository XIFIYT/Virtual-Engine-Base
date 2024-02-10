#include "GTA/Natives.hpp"

using namespace Big;
namespace Utility
{
	inline int PlayerIndex(int player) {
		return PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	}
	class SelectedP {
	public:
		CNetGamePlayer* m_net_player_data;
		int m_id;
	};
	inline SelectedP m_selected_player;
	inline int headshot[32];
}