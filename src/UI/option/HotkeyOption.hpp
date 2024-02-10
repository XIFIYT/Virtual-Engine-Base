#pragma once
#include "UI/option/OptionGetters.hpp"
#include "UI/Framework.hpp"
#include "Features.hpp"
namespace Big::UserInterface
{
	class Hotkey : public OptionGetters<Hotkey>
	{
	public:
		explicit Hotkey() = default;
		explicit Hotkey(const char* text, const char* description, int* hotkey, std::string right = "", std::function<void()> action = [] {}) :
			m_Text(text),
			m_HasPen(false),
			m_Hotkey(hotkey)
		{
			SetLeftText(text);
			if (right == "") {
				SetRightText("None");
			}
			else {
				SetRightText(right.c_str());
			}
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}
		void HandleAction(OptionAction action) override
		{
			

			OptionGetters::HandleAction(action);
		}
		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "keyboard" && secondary == "no_pen")
			{
				return true;
			}

			return OptionGetters::GetFlag(flag, secondary);
		}

		~Hotkey() noexcept = default;
		Hotkey(Hotkey const&) = default;
		Hotkey& operator=(Hotkey const&) = default;
		Hotkey(Hotkey&&) = default;
		Hotkey& operator=(Hotkey&&) = default;
	private:
		const char* m_Text;
		bool m_HasPen{};
		int* m_Hotkey{};
	};
}
