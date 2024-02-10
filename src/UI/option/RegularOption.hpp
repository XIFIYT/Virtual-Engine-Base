#pragma once
#include "optionGetters.hpp"
#include "Features.hpp"

namespace Big::UserInterface
{
	class Button : public OptionGetters<Button>
	{
	public:
		explicit Button() = default;
		explicit Button(const char* text, const char* description = nullptr, std::function<void()> action = [] {}) :
			m_Text(text)
		{
			SetLeftText(text);

			if (description == "NO DESCRIPTION") {
				OptionGetters::SetDescription("");
			}
			if (description != "" || description != nullptr && description != "NO DESCRIPTION") {
				OptionGetters::SetDescription(description);
			}
			if (description == "" || description == nullptr) {
				OptionGetters::SetDescription("Hold V and any key to set a hotkey.");
			}
			SetAction(std::move(action));
		}

		void HandleAction(OptionAction action) override
		{
			

			Base::HandleAction(action);
		}

		~Button() noexcept = default;
		Button(Button const&) = default;
		Button& operator=(Button const&) = default;
		Button(Button&&) = default;
		Button& operator=(Button&&) = default;
	private:
		const char* m_Text;
		using Base = OptionGetters<Button>;
	};
}
