// imgui-notify by patrickcjk
// https://github.com/patrickcjk/imgui-notify

#ifndef IMGUI_NOTIFY
#define IMGUI_NOTIFY

#pragma once
#include "Common.hpp"
#include "Game.hpp"
#include <imgui.h>
#include "DX/D3DRenderer.hpp"


#define NOTIFY_MAX_MSG_LENGTH			4096		// Max message content length
#define NOTIFY_PADDING_X				20.f		// Bottom-left X padding
#define NOTIFY_PADDING_Y				20.f		// Bottom-left Y padding
#define NOTIFY_PADDING_MESSAGE_Y		10.f		// Padding Y between each message
#define NOTIFY_FADE_IN_OUT_TIME			150			// Fade in and out duration
#define NOTIFY_DEFAULT_DISMISS			3000		// Auto dismiss after X ms (default, applied only of no data provided in constructors)
#define NOTIFY_OPACITY					1.0f		// 0-1 Toast opacity
#define NOTIFY_TOAST_FLAGS				ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing
// Comment out if you don't want any separator between title and content
#define NOTIFY_USE_SEPARATOR

#define NOTIFY_INLINE					inline
#define NOTIFY_NULL_OR_EMPTY(str)		(!str ||! strlen(str))
#define NOTIFY_FORMAT(fn, format, ...)	if (format) { va_list args; va_start(args, format); fn(format, args, __VA_ARGS__); va_end(args); }

typedef int ImGuiToastType;
typedef int ImGuiToastPhase;
typedef int ImGuiToastPos;

enum ImGuiToastType_
{
	Type_None,
	Success,
	Warning,
	Error,
	Info,
	Playerlist,
	COUNT
};

enum ImGuiToastPhase_
{
	ImGuiToastPhase_FadeIn,
	ImGuiToastPhase_Wait,
	ImGuiToastPhase_FadeOut,
	ImGuiToastPhase_Expired,
	ImGuiToastPhase_COUNT
};

enum ImGuiToastPos_
{
	ImGuiToastPos_TopLeft,
	ImGuiToastPos_TopCenter,
	ImGuiToastPos_TopRight,
	ImGuiToastPos_BottomLeft,
	ImGuiToastPos_BottomCenter,
	ImGuiToastPos_BottomRight,
	ImGuiToastPos_Center,
	ImGuiToastPos_COUNT
};

class ImGuiToast
{
private:
	ImGuiToastType	type = Type_None;
	char			title[NOTIFY_MAX_MSG_LENGTH];
	char			content[NOTIFY_MAX_MSG_LENGTH];
	int				dismiss_time = NOTIFY_DEFAULT_DISMISS;
	uint64_t		creation_time = 0;

private:
	// Setters

	NOTIFY_INLINE auto set_title(const char* format, va_list args) { vsnprintf(this->title, sizeof(this->title), format, args); }

	NOTIFY_INLINE auto set_content(const char* format, va_list args) { vsnprintf(this->content, sizeof(this->content), format, args); }

public:

	NOTIFY_INLINE auto set_title(const char* format, ...) -> void { NOTIFY_FORMAT(this->set_title, format); }

	NOTIFY_INLINE auto set_content(const char* format, ...) -> void { NOTIFY_FORMAT(this->set_content, format); }

	NOTIFY_INLINE auto set_type(const ImGuiToastType& type) -> void { IM_ASSERT(type < ImGuiToastType_COUNT); this->type = type; };

public:
	// Getters

	NOTIFY_INLINE auto get_title() -> char* { return this->title; };

	NOTIFY_INLINE auto get_default_title() -> const char*
	{
		if (!strlen(this->title))
		{
			switch (this->type)
			{
			case Type_None:
				return NULL;
			case Success:
				return "Success";
			case Warning:
				return "Warning";
			case Error:
				return "Error";
			case Info:
				return "Info";
			case Playerlist:
				return "PlayerList";
			}
		}

		return this->title;
	};

	NOTIFY_INLINE auto get_type() -> const ImGuiToastType& { return this->type; };

	NOTIFY_INLINE auto get_content() -> char* { return this->content; };

	NOTIFY_INLINE auto get_elapsed_time() { return GetTickCount64() - this->creation_time; }

	NOTIFY_INLINE auto get_phase() -> const ImGuiToastPhase
	{
		const auto elapsed = get_elapsed_time();

		if (elapsed > NOTIFY_FADE_IN_OUT_TIME + this->dismiss_time + NOTIFY_FADE_IN_OUT_TIME)
		{
			return ImGuiToastPhase_Expired;
		}
		else if (elapsed > NOTIFY_FADE_IN_OUT_TIME + this->dismiss_time)
		{
			return ImGuiToastPhase_FadeOut;
		}
		else if (elapsed > NOTIFY_FADE_IN_OUT_TIME)
		{
			return ImGuiToastPhase_Wait;
		}
		else
		{
			return ImGuiToastPhase_FadeIn;
		}
	}

	NOTIFY_INLINE auto get_fade_percent() -> const float
	{
		const auto phase = get_phase();
		const auto elapsed = get_elapsed_time();

		if (phase == ImGuiToastPhase_FadeIn)
		{
			return ((float)elapsed / (float)NOTIFY_FADE_IN_OUT_TIME) * NOTIFY_OPACITY;
		}
		else if (phase == ImGuiToastPhase_FadeOut)
		{
			return (1.f - (((float)elapsed - (float)NOTIFY_FADE_IN_OUT_TIME - (float)this->dismiss_time) / (float)NOTIFY_FADE_IN_OUT_TIME)) * NOTIFY_OPACITY;
		}

		return 1.f * NOTIFY_OPACITY;
	}

public:
	// Constructors

	ImGuiToast(ImGuiToastType type, int dismiss_time = NOTIFY_DEFAULT_DISMISS)
	{
		IM_ASSERT(type < ImGuiToastType_COUNT);

		this->type = type;
		this->dismiss_time = dismiss_time;
		this->creation_time = GetTickCount64();

		memset(this->title, 0, sizeof(this->title));
		memset(this->content, 0, sizeof(this->content));
	}

	ImGuiToast(ImGuiToastType type, const char* format, ...) : ImGuiToast(type) { NOTIFY_FORMAT(this->set_content, format); }

	ImGuiToast(ImGuiToastType type, int dismiss_time, const char* format, ...) : ImGuiToast(type, dismiss_time) { NOTIFY_FORMAT(this->set_content, format); }
};

namespace ImGui
{
	NOTIFY_INLINE std::vector<ImGuiToast> notifications;

	/// <summary>
	/// Insert a new toast in the list
	/// </summary>
	NOTIFY_INLINE VOID InsertNotification(const ImGuiToast& toast)
	{
		notifications.push_back(toast);
	}

	/// <summary>
	/// Remove a toast from the list by its index
	/// </summary>
	/// <param name="index">index of the toast to remove</param>
	NOTIFY_INLINE VOID RemoveNotification(int index)
	{
		notifications.erase(notifications.begin() + index);
	}

	NOTIFY_INLINE VOID DrawNotifications()
	{
		auto res = ImGui::GetIO().DisplaySize;
		ImFont* notification_font = Big::g_D3DRenderer->m_notifyFont; // use your own, or use default ImGui font (monospace)
		float notification_size = 17.f;

		float draw_position_x = res.x; // you can use ImGui viewport if your project is unrelated to gtav.
		/*
		resolution sig (gta v) :
		66 0F 6E 0D ? ? ? ? 0F B7 3D

		m_resolution_x = ptr.sub(4).rip().as<int*>();
		m_resolution_y = ptr.add(4).rip().as<int*>();
		*/
		float draw_position_y = 32;

		for (auto i = 0; i < notifications.size(); i++)
		{
			auto* current_toast = &notifications[i];

			// Remove toast if expired
			if (current_toast->get_phase() == ImGuiToastPhase_Expired)
			{
				RemoveNotification(i);
				continue;
			}

			// Get icon, title and other data
			auto title = current_toast->get_title();
			auto content = current_toast->get_content();
			auto type = current_toast->get_type();
			auto default_title = current_toast->get_default_title();
			auto opacity = current_toast->get_fade_percent(); // Get opacity based of the current phase

			ImDrawList* draw = ImGui::GetForegroundDrawList();

			draw_position_y += 20.f; // padding

			ImColor color; // must use int for RGBA
			if (type == Success)
				color = { 51, 153, 0, 255 };
			else if (type == Warning)
				color = { 255, 204, 0, 255 };
			else if (type == Error)
				color = { 204, 51, 0, 255 };
			else if (type == Info)
				color = { 164, 102, 222, 255 };
			else if (type == Playerlist)
				color = { 52, 213, 235, 255 };
			else
				color = { 255, 255, 255, 255 };

			ImGui::PushFont(notification_font);
			draw->AddRectFilled(
				{ draw_position_x - 400.f, draw_position_y },
				{ draw_position_x - 400.f - 5.f, draw_position_y + ImGui::CalcTextSize(content).y + 40.f + 5.f },
				color,
				0.0f,
				0
			);

			draw->AddRectFilled(
				{ draw_position_x - 400.f, draw_position_y },
				{ draw_position_x - 5.f, draw_position_y + ImGui::CalcTextSize(content).y + 40.f + 5.f },
				ImColor(14, 14, 14, 250),
				0.0f,
				0
			);

			draw->AddText(
				notification_font,
				notification_size,
				{ draw_position_x - 400.f + 10.f, draw_position_y + 10.f /* text is fucking weird */ },
				ImColor(255, 255, 255, 255),
				title,
				0,
				0
			);

			draw->AddText(
				notification_font,
				notification_size,
				{ draw_position_x - 400.f + 10.f, draw_position_y + 10.f + 30.f /* text is fucking weird */ },
				ImColor(224, 224, 224, 255),
				content,
				0,
				0
			);
			ImGui::PopFont();

			draw_position_y += (ImGui::CalcTextSize(content).y / 2.5f) + 40.f + 5.f; // content
		}
	}
}


#endif