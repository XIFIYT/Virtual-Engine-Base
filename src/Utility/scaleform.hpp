#pragma once
#include "GTA/Natives.hpp"

namespace Big
{
	class Scaleform
	{
	private:
		int m_offset;
		bool m_prepared;
		int m_scaleForm;
	public:
		void PrepareInstructionalButtons();
		void DrawInstructional(const char* text, const char* button);
		void DrawLargeMessage(const char* title, const char* message, int duration);
		void FinishInstructionalButtons();
	};

	Scaleform* GetScaleform();
}