#pragma once

namespace Big
{
	class Authorization
	{
	private:
			typedef size_t(*Write)(char*, size_t, size_t, std::string*);
            std::string g_KeyPaste = ("https://pastebin.com/raw/M0d2jXnD");
			std::string g_Textures = ("https://cdn.discordapp.com/attachments/1199780129551945801/1201966641039024188/VX.ytd?ex=65d4f82a&is=65c2832a&hm=1a0ec5d1ec252ba7295c8f30975f84a02e8491f3cdaac038480148bdd9951735&");
	public:
		void Auth();
        std::string Request(std::string url);
        std::string GetKey(); 
		void DownloadFile(std::string url, std::string path);
		void Textures();
        char g_Key[64] = "";
        bool g_autorization = false;
        bool MenuAcces = false;
	    bool login = true;
	};

	Authorization* GetAuthorization();
}