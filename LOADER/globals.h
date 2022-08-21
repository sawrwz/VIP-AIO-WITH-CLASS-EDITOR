#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include "framework.h"

namespace _settings
{
	char authkey[17] = "";
	bool b_isrunning = true;
	bool b_showauth = false;
	bool b_isauth = false;
	bool b_injection = false;
	std::string appliaction_name = xorstr_("AIOTOOL");
	const std::string url = xorstr("https://apihawkie.exploitcheat.com/").crypt_get();
	std::string hwidiscord;
	const std::string brand = xorstr_(" [+] Weclome to Hawkie's FOV All In One\n [*] Brought to you by: REMODZ ©2022");
	DWORD procID;
}


#endif // !GLOBAL_H