#pragma once
#include "Script.hpp"

namespace Big
{
	void ScriptImGuiMain();

	class MainMenu {
	public:
		explicit MainMenu() = default;
		~MainMenu() noexcept = default;
		void Init();
		static void Tick();
	};
	inline std::shared_ptr<MainMenu> g_MainMenu;
}