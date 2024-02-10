#include "common.hpp"
#include "Features/Self.hpp"

using namespace Big;

namespace Self
{

    void invisible(bool toggle)
    {
	    if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	    {
		    if (toggle)
		    {
    	    	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
		    }
		    else ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
	    }

    }


   void Self::loop()
   {
        invisible(invisible_bool);
   } 
}