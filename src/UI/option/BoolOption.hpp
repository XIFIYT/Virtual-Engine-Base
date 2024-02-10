#pragma once
#include "optionGetters.hpp"
#include "UI/Framework.hpp"
namespace Big::UserInterface
{
	enum class BoolDisplay
	{
		OnOff,
		YesNo
	};

	class toggle : public OptionGetters<toggle>
	{
	public:
		explicit toggle(const char* text, const char* description, bool* b00l, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l)
		{
			Base::SetLeftText(text);
			Base::SetDescription(description != "" && description != nullptr && description != "NO DESCRIPTION" ? description : description == "" || description == nullptr ? "Hold V and any key to set a hotkey." : "");
			Base::SetAction(std::move(action));
			Base::SetBool(b00l);
		}
		explicit toggle(const char* text, bool* b00l, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l)
		{
			Base::SetLeftText(text);
			Base::SetDescription("Hold V and any key to set a hotkey.");
			Base::SetAction(std::move(action));
		}

		~toggle() noexcept = default;
		toggle(toggle const&) = default;
		toggle& operator=(toggle const&) = default;
		toggle(toggle&&) = default;
		toggle& operator=(toggle&&) = default;



		const char* GetRightText() override
		{


			return Base::GetRightText();
		}

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "none" && secondary == "bool") {
				g_Render->ToggledOn = *m_Bool;
				return true;
			}
			return Base::GetFlag(flag, secondary);
		}
		const char* get_name(int vk) {
			TCHAR keyName[32];
			GetKeyNameText(vk << 16, keyName, 32);
			return keyName;
		}
		void HandleAction(OptionAction action) override
		{

			
			if (action == OptionAction::Enter)
			{
				*m_Bool = !*m_Bool;
			}

			Base::HandleAction(action);
		}
	private:
		bool* m_Bool;
		const char* m_Text;

		using Base = OptionGetters<toggle>;
	};
}
