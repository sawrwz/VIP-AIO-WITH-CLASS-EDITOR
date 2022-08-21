#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include "framework.h"

typedef struct _settings
{

	bool b_menuEnable = false;
	bool b_debugEnable = true;
	bool b_map = false;
	bool b_fov = false;
	bool b_no_flashbang = false;
	bool b_ownership = false;
	bool b_custom_clantag = false;
	bool b_brightmax = false;
	bool b_thirdperson = false;
	bool b_heartcheat = false;
	bool b_norecoil = false;
	bool b_sprint = false;
	bool b_nogun = false;
	bool b_view = false;
	bool b_fog = false;
	bool b_night = false;
	float f_fov = 1.0f;
	float f_map = 1.0f;
	
} settings;

typedef struct _offsets
{
	uintptr_t gamemode;
	uintptr_t camoAddr; //= 0x1A7C7918 + 0x28;
	uintptr_t a_parse;
	uintptr_t clantag_offset;
	uintptr_t unlock_offsets;
	uintptr_t Dvar_FindVarByName;
	uintptr_t Dvar_SetBoolInternal;
	uintptr_t Dvar_SetBoolByName;
	uintptr_t Dvar_SetFloat_Internal;
	uintptr_t Dvar_RegisterFloat;
	uintptr_t Dvar_SetInt_Internal;
	uintptr_t Dvar_SetIntByName;
	//stats
	uintptr_t ddl_loadasset;
	uintptr_t ddl_getrootstate;
	uintptr_t ddl_getdllbuffer;
	uintptr_t ddl_movetoname;
	uintptr_t ddl_movetopath;
	uintptr_t ddl_setint;
	uintptr_t ddl_getint;
	uintptr_t ddl_setstring;
	uintptr_t Logon_Status;

} offsets;

typedef struct _global_vars
{
	DWORD procID;
	HWND hWind;
	HANDLE hProc;
	uintptr_t baseModule;

	offsets goffsets;
	settings msettings;

} global_vars;

extern global_vars* g_vars;

#endif // !GLOBAL_H