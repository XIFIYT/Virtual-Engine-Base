#include "Authorization.hpp"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "crypt32.lib")
#include <curl/curl.h>
namespace Big
{
	Authorization g_Authorization;
std::string g_Name = ("Virtual Engine");
std::string GetLoaderPath()
{
	std::string appdata = std::getenv("appdata");
	std::string path = appdata + ("\\") + g_Name;
	return path;
}
	void Authorization::Auth()
    {
        std::string key = "";
			std::ifstream keyFileRead(GetLoaderPath() + "\\key.txt");
			while (std::getline(keyFileRead, key)) {
				// Output the text from the file
				if (key.c_str() == GetAuthorization()->GetKey())
				{
					GetAuthorization()->login = false;
					LOG(INFO) << "Succesfuly Login";
					Textures();
				}
				else
				{
					LOG(INFO) << "your key is invalid enter your key";
				}
			}
			keyFileRead.close();
    }
    std::string Authorization::GetKey()
	{
		return Request(g_KeyPaste);
	}
    std::string Authorization::Request(std::string url)
    {
        CURLcode res_code = CURLE_FAILED_INIT;
		CURL* curl = curl_easy_init();
		std::string result;

		curl_global_init(CURL_GLOBAL_ALL);

		if (curl) {
			curl_easy_setopt(curl,
				CURLOPT_WRITEFUNCTION,
				static_cast <Write> ([](char* contents, size_t size,
					size_t nmemb, std::string* data) -> size_t {
						size_t new_size = size * nmemb;
						if (data == NULL) {
							return 0;
						}
						data->append(contents, new_size);
						return new_size;
					}));
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, ("Cock"));

			res_code = curl_easy_perform(curl);

			if (res_code != CURLE_OK) {
				return curl_easy_strerror(res_code);
			}

			curl_easy_cleanup(curl);
		}

		curl_global_cleanup();

		return result;
    }
    static std::size_t WriteData(void* ptr, std::size_t size, std::size_t nmemb, void* stream)
	{
		auto written = fwrite(ptr, size, nmemb, (FILE*)stream);
		return written;
	}
	void Authorization::DownloadFile(std::string url, std::string path)
	{
		CURL* curl;
		FILE* fp;
		CURLcode res;
		curl = curl_easy_init();
		if (curl)
		{
			fp = fopen(path.c_str(), "wb");
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			fclose(fp);
		}
	}
	void Authorization::Textures()
	{
			LOG(INFO) << "Downloading Textures...";
			DownloadFile(g_Textures, GetLoaderPath() + ("\\Textures\\VX.ytd"));
			LOG(INFO) << "Done !";
	}

	Authorization* GetAuthorization() { return &g_Authorization; }
}
