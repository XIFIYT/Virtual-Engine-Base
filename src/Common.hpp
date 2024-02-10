#pragma once
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <xkeycheck.h>

#define BIGBASE_WIDE_IMPL(str) L ## str
#define BIGBASE_WIDE(str) BIGBASE_WIDE_IMPL(str)

#define BIGBASE_STRINGIZE_IMPL(x) #x
#define BIGBASE_STRINGIZE(x) BIGBASE_STRINGIZE_IMPL(x)

#define VIRTUAL_NAME "Lucid Mod Menu"
#define VERSION "1.0"

namespace Big
{
	using namespace std::chrono_literals;
	namespace fs = std::filesystem;

	inline HMODULE g_module{};
	inline HANDLE g_mainThread{};
	inline std::atomic_bool g_Running = true;

	inline std::uint32_t g_SelectedPlayer{};

	inline bool g_LogScriptEvents = false;
}

#include "Settings.hpp"
#include "log/Logger.hpp"
#include "Util.hpp"
#include "GTA/Memory.hpp"
#include "Game.hpp"
#include "ScriptGlobal.hpp"
#include "UI/submenu/RegularSubmenu.hpp"

//Script
#include "Script/pool/FiberPool.hpp"
#include "script/patcher/script_data.hpp"
#include "script/patcher/script_patch.hpp"
#include "script/patcher/script_patcher_service.hpp"

//Pointer / Pattern
#include "pattern/pointers.hpp"
#include "Pattern/pools.hpp"
#include "Pattern/sc_pointers.hpp"

//Renderer ImGui
#include "DX/D3DRenderer.hpp"
#include "LogScript.hpp"