#include "../Common.hpp"

namespace Big
{
	class BackendRegistry1
	{
		HKEY hKey;
		LPCSTR subKey;
		LPCSTR subValue;
		HKEY resKey;
		DWORD dataLen;

	public:

		bool isRetailKey();
		bool isSteamKey();
		bool isEpicKey();
        void GTAVersion();
		std::string GetValue(bool steam = false);

	private:

        
	};
	BackendRegistry1* GetBackendRegistry1();
}