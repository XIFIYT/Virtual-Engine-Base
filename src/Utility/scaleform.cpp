#include "GTA/Natives.hpp"
#include "scaleform.hpp"
#include "../Script.hpp"

namespace Big
{
	Scaleform g_scaleform;

	void Scaleform::DrawLargeMessage(const char* title, const char* message, int duration) {
	  Script::GetCurrent()->ScriptYield();
		float startPos = 0.0f;
		for (int i = 0; i < duration; i++) {
			int m_scaleForm = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
			if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleForm)) {
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "OVERRIDE_Y_POSITION");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(startPos - 0.75f);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				if (startPos < 0.5f)startPos += (0.5f - startPos) / 100.0f;
				if (i > duration - 150)startPos -= startPos / 50.0f;
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SHOW_CENTERED_MP_MESSAGE_LARGE");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(title);
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(message);
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(100);
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(m_scaleForm, 255, 255, 255, 0, 0);
			}

			Script::GetCurrent()->ScriptYield();
		};

	}

	void Scaleform::PrepareInstructionalButtons() {
		m_scaleForm = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
		if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleForm)) {
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(m_scaleForm, 255, 255, 255, 0, 0);
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "CLEAR_ALL");
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SET_CLEAR_SPACE");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(200);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SET_MAX_WIDTH");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(1);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SET_DATA_SLOT_EMPTY");
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		m_prepared = true;
	}

	void Scaleform::FinishInstructionalButtons() {

		if (!m_prepared) return;
		if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleForm)) {
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "DRAW_INSTRUCTIONAL_BUTTONS");
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SET_BACKGROUND_COLOUR");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(/*GetRenderer()->m_cOutline.m_r*/ 0);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(/*GetRenderer()->m_cOutline.m_g*/ 0);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(/*GetRenderer()->m_cOutline.m_b*/ 0);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(80);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			m_offset = 0;
		}
		m_prepared = false;
	}

	void Scaleform::DrawInstructional(const char* text, const char* button) {
		if (!m_prepared) return;
		if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleForm)) {
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SET_DATA_SLOT");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_offset);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(("t_" + (std::string)button).c_str());
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(text);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			m_offset++;
		}
	}

	Scaleform* GetScaleform() { return &g_scaleform; }
}
