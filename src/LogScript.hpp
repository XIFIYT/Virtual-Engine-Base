#pragma once
#include "Script.hpp"

namespace Big
{
	class LogScript
	{
	public:
		explicit LogScript() = default;
		~LogScript() noexcept = default;
		void OnPresentTick();
		static void Tick();
		void Auth(); 
	};
	inline std::shared_ptr<LogScript> g_LogScript;
}