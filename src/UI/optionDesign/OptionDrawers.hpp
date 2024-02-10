#pragma once
#include "UI/submenu/SubmenuBase.hpp"
#include "UI/option/BoolOption.hpp"
#include "UI/option/ChooseOption.hpp"
#include "UI/option/NumberOption.hpp"
#include "UI/option/SubOption.hpp"
#include "UI/submenu/PlayerSubmenu.hpp"
#include "UI/option/RegularOption.hpp"
#include "UI/option/HotkeyOption.hpp"
#include "UI/option/keyboard.hpp"
#include "UI/option/BoolwithChoose.hpp"
#include "UI/option/BoolwithNumber.hpp"
#include "UI/submenu/ColorSubmenu.hpp"

namespace Big {
	template <typename ...TArgs>
	void addToggle(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::toggle>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addBreak(TArgs&&... args)
	{
		//UserInterface::m_Options.push_back(std::make_unique<UserInterface::BreakOption>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addToggleWithScroll(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::ToggleWithScroller>(std::forward<TArgs>(args)...));
	}
	template <typename NumberType, typename ...TArgs>
	void addNumber(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::number<NumberType>>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addScroll(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Scroll>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addSubmenu(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::submenu>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addColorSubmenu(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::color_submenu>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addButton(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Button>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addKeyboard(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Keyboard>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addPlayerSubmenu(TArgs&&... args)
	{
		//UserInterface::m_Options.push_back(std::make_unique<UserInterface::playersubmenu>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addHotkey(TArgs&&... args)
	{
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Hotkey>(std::forward<TArgs>(args)...));
	}

	class GetMenuOptions {
	public:
		void pushButton(const char* name, std::function<void()> action = [] {}) {
			addButton(name, "", action);
		}
	};
	GetMenuOptions* menu;



}

