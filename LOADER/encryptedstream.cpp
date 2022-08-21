#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <WinInet.h>
#pragma comment(lib, "Wininet.lib")
//guidedhacking.com
#include <blowfish/blowfish.h>

#include "xorstr.hpp"
#include "encryptedstream.h"

//init blowfish encryption using random key
//ideally you would use 4 different types of encryption instead of the same one
BLOWFISH blowfish1(xorstr_("$2y$10$24c678af5"));
BLOWFISH blowfish2(xorstr_("$2y$10$c64e11e72"));
BLOWFISH blowfish3(xorstr_("$2y$10$81b74e1w3"));
BLOWFISH blowfish4(xorstr_("$2y$10$5225fdf82"));

bool replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::string Decrypt(EncryptedData_t encryptedData)
{
	//decrypt each part
	std::string BufferDecrypted = blowfish1.Decrypt_CBC(encryptedData.a);
	BufferDecrypted += blowfish2.Decrypt_CBC(encryptedData.b);
	BufferDecrypted += blowfish3.Decrypt_CBC(encryptedData.c);
	BufferDecrypted += blowfish4.Decrypt_CBC(encryptedData.d);

	//rebuild the DLL from decrypted data


	return BufferDecrypted;
}

std::string StreamFileToMemString(std::string URL)
{
	const char* header = "Accept: *" "/" "*\r\n\r\n";
	HANDLE hInterWebz = InternetOpen(xorstr_("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HANDLE hURL = InternetOpenUrl(hInterWebz, URL.c_str(), header, lstrlen(header), INTERNET_FLAG_DONT_CACHE, 0);

	char* Buffer = new char[100000000]; //100mb
	memset(Buffer, 0, 100000000);
	DWORD BytesRead = 1;

	std::string data;

	if (InternetReadFile(hURL, Buffer, 100000000, &BytesRead))
	{
		data = std::string(Buffer);
	}

	delete[] Buffer;
	InternetCloseHandle(hInterWebz);
	InternetCloseHandle(hURL);

	return data;
}

std::string GetDecryptedDLL()
{
	std::string data1 = StreamFileToMemString(xorstr_(R"(https://apihawkie.exploitcheat.com/downloads/1)"));
	std::string data2 = StreamFileToMemString(xorstr_(R"(https://apihawkie.exploitcheat.com/downloads/2)"));
	std::string data3 = StreamFileToMemString(xorstr_(R"(https://apihawkie.exploitcheat.com/downloads/3)"));
	std::string data4 = StreamFileToMemString(xorstr_(R"(https://apihawkie.exploitcheat.com/downloads/4)"));

	std::string decryptedDLL = Decrypt({ data1, data2, data3, data4 });

	return decryptedDLL;
}

std::string GetDecryptedSys()
{
	std::string data1 = StreamFileToMemString(xorstr_(R"(https://api.exploitcheat.com/downloads/kerenal/1)"));
	std::string data2 = StreamFileToMemString(xorstr_(R"(https://api.exploitcheat.com/downloads/kerenal/2)"));
	std::string data3 = StreamFileToMemString(xorstr_(R"(https://api.exploitcheat.com/downloads/kerenal/3)"));
	std::string data4 = StreamFileToMemString(xorstr_(R"(https://api.exploitcheat.com/downloads/kerenal/4)"));

	std::string decryptedSys = Decrypt({ data1, data2, data3, data4 });

	return decryptedSys;
}
