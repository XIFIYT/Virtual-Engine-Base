#pragma once
#include "UI/option/OptionGetters.hpp"

namespace Big::UserInterface
{
	class Keyboard : public OptionGetters<Keyboard>
	{
	public:
		explicit Keyboard() = default;
		explicit Keyboard(const char* text, const char* description = nullptr, std::string right = "", std::function<void()> action = [] {}, bool has_pen = true) :
			m_Text(text),
			m_HasPen(has_pen)
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
			if (m_HasPen) {
				if (flag == "keyboard" && secondary == "none")
				{
					return true;
				}
			}
			else {
				if (flag == "keyboard" && secondary == "no_pen")
				{
					return true;
				}
			}
			return OptionGetters::GetFlag(flag, secondary);
		}

		~Keyboard() noexcept = default;
		Keyboard(Keyboard const&) = default;
		Keyboard& operator=(Keyboard const&) = default;
		Keyboard(Keyboard&&) = default;
		Keyboard& operator=(Keyboard&&) = default;
	private:
		const char* m_Text{};
		bool m_HasPen{};
	};
}
