#include "BackendMain.hpp"
#include "BackendRegistry.hpp"
#include "Authorization.hpp"
#include "Game.hpp"
#include "Hooking.hpp"
#include "Script.hpp"
#include "LogScript.hpp"
#include "menu/main_menu.hpp"
#include "Invoker.hpp"
#include "CustomText.hpp"
#include "DX/D3DRenderer.hpp"
#include "UI/Framework.hpp"
#include "Translation.hpp"
#include "Notify.hpp"
#include "GTA/Natives.hpp"
#include "GTA/thread_pool.hpp"
#include "Script/patcher/script_patcher_service.hpp"
#include "Pattern/pointers.hpp"

bool isRetailKey = false;
bool isSteamKey = false;
bool isEpicKey = false;
namespace Big
{
	BackendMain g_BackendMain;

    void BackendMain::Init()
    {
        auto logger_instance = std::make_unique<logger>("Virtual Engine", g_file_manager.get_project_file("./cout.log"));
	    	GetAuthorization()->Auth();
            GTAVersion();
			auto pointers_instance = std::make_unique<pointers>();
			auto thread_pool_instance = std::make_unique<thread_pool>();
			auto script_patcher_service_instance    = std::make_unique<script_patcher_service>();
			LOG(INFO) << "Service Patcher Initialized";
			LOG(INFO) << "BigBase Injecting...";
			//g_TranslationManager = std::make_unique<TranslationManager>();		//not for now
			//g_TranslationManager->LoadTranslations("English");
			g_GameVariables = std::make_unique<GameVariables>();
			g_GameFunctions = std::make_unique<GameFunctions>();
			if (*g_GameVariables->m_GameState != eGameState::Playing) {
				LOG(INFO) << "Waiting GTA V";
				while (*g_GameVariables->m_GameState != eGameState::Playing)
					std::this_thread::sleep_for(10ms);
			}
			g_GameVariables->PostInit();
			g_Invoker = std::make_unique<Invoker>();
			g_Invoker->MapNatives(); LOG(INFO) << "Cached all natives!";
			g_CustomText = std::make_unique<CustomText>();
			g_D3DRenderer = std::make_unique<D3DRenderer>();
			g_Render = std::make_unique<UserInterface::Framework>();
			g_MainMenu = std::make_shared<MainMenu>();
			g_LogScript = std::make_shared<LogScript>();
			g_FiberPool = std::make_unique<FiberPool>();
			LOG(INFO) << "Script Regisered";
			g_ScriptManager.AddScript(std::make_unique<Script>(&LogScript::Tick));
			g_ScriptManager.AddScript(std::make_unique<Script>(&MainMenu::Tick));
			LOG(INFO) << "Initialized Renderer";
			g_Hooking = std::make_unique<Hooking>();
			g_Hooking->Hook();
			LOG(INFO) << "BigBase loaded.";
            while (g_Running) {
				if (GetAsyncKeyState(VK_END)) g_Running = false;
				std::this_thread::sleep_for(500ms);
			}
			std::this_thread::sleep_for(500ms);
            logger_instance->destroy();
			logger_instance.reset();
			thread_pool_instance->destroy();
			thread_pool_instance.reset();
			script_patcher_service_instance.reset();
    }

    void BackendMain::GTAVersion()
    {
        HANDLE hProcess = NULL;
        if (!hProcess)
        {
            BackendRegistry1 reg;

            isSteamKey = reg.isSteamKey();

            isRetailKey = reg.isRetailKey();

            isEpicKey = reg.isEpicKey();

            if (isRetailKey)//RETAIL
            {
                LOG(INFO) << "Version -> Rockstar";
            }
            //STEAM
            else if (isSteamKey)
            {
                LOG(INFO) << "Version -> Steam";
            }
            //EPIC
            else if (isEpicKey)
            {
                LOG(INFO) << "Version -> Epic Game";
            }

        }
    }
    void BackendMain::Destroy()
    {
            g_Hooking->Unhook();
			g_LogScript.reset();
			g_MainMenu.reset();
			g_FiberPool.reset();
			g_ScriptManager.RemoveAllScripts();
			g_Render.reset();
			g_D3DRenderer.reset();
			g_CustomText.reset();
			g_Invoker.reset();
			std::this_thread::sleep_for(500ms);
			g_Hooking.reset();
		//	g_TranslationManager.reset();
			g_GameVariables.reset();
			g_GameFunctions.reset();		
			LOG(INFO) << "BigBase unloaded.";
    }

	BackendMain* GetBackendMain() { return &g_BackendMain; }
}