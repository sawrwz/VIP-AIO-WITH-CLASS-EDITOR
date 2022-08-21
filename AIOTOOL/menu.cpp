#include "menu.h"

void SetCamo(int Class, int Weapon, int Camo)
{
	char context[255];
	char state[255];
	int navStringCount;
	char* navStrings[16]{};
	const char* mode = "";

	if (gameMode == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (gameMode == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}



	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);

	DDL_GetRootState((__int64)state, ddl_file);
	char buffer[200];
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.%i.camo"), Class, Weapon);
	ParseShit(buffer, (const char**)navStrings, 16, &navStringCount);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
	{
		DDL_SetInt((__int64)state, (__int64)context, Camo);
	}

}

ImFont* MainCaps;
ImFont* Main;
ImFont* FMenu;
float color_menu[4]{ 255 / 255.f, 0 / 255.f , 0 / 255.f, 1.0f };
char customtag[6] = "";

char score[256] = "";
char games[256] = "";
char timeplayed[256] = "";
char wins[256] = "";
char top5[256] = "";
char kills[256] = "";
char deaths[256] = "";
char downs[256] = "";
int i_score = 1; //1 ~ 5555555555
int i_timeplayed = 1;
int i_games = 1; //1 ~ 5555555555
int i_wins = 1; //1 ~ 5555555555
int i_kills = 1; //1 ~ 5555555555
int i_deaths = 1; //1 ~ 5555555555
int i_downs = 1; //1 ~ 5555555555;
int i_top5 = 1; //1 ~ 5555555555
int i_top10 = 1; //1 ~ 5555555555
int i_top25 = 1; //1 ~ 5555555555
void STATS()
{
	ImGui::Dummy(ImVec2(0.0f, 7.0f));
	for (int i = 0; i < 5; i++)
	{
		ImGui::Spacing();
		ImGui::SameLine();
	}
	static const char* items[] = { "Rebirth", "Battle Royale" }; //"Custom Rebirth","Custom Battle Royale", "MultiPlayer Core S&D"
	static const char* current_item = "Rebirth";
	if (ImGui::BeginCombo(xorstr_("##GAMEMODE"), current_item))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == items[n]);
			if (ImGui::Selectable(items[n], is_selected))
				current_item = items[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	if (current_item == "Rebirth")
	{
		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		//ImGui::Spacing();
		ImGui::TextDisabled(xorstr_(" Step 1. Select game Mode\n Step 2. Change the number for Stats and hit Set.\n Step 3. Go into a game start and kill yourself."));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::SliderInt("##WINS", &i_wins, 1, 9999999, "Wins %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Wins"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"wins");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_wins);
		}

		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::SliderInt("##TOP5", &i_top5, 1, 9999999, "Top 5 %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Top5"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"topFive");
			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_top5);

		}

		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::SliderInt("##KILLS", &i_kills, 1, 9999999, "Kills %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Kills"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"kills");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_kills);
		}

		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::SliderInt("##DEATHS", &i_deaths, 1, 9999999, "Deaths %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Deaths"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"deaths");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_deaths);
		}
	}

	if (current_item == "Battle Royale")
	{
		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::SliderInt("##BRSOCRE", &i_score, 1, 5555555555, "Score %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Score"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"score");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_score);
		}
		//ImGui::Dummy(ImVec2(0.0f, 3.0f));

		ImGui::SliderInt("##BRGAMES", &i_games, 1, 5555555555, "Games Played %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Games"), ImVec2(-1,30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"gamesPlayed");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_games);
		}
	/*	ImGui::Dummy(ImVec2(0.0f, 3.0f));*/
		ImGui::SliderInt("##BRTIME", &i_timeplayed, 1, 5555555555, "Time Played %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Time"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"timePlayed");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_timeplayed);
		}

		/*ImGui::Dummy(ImVec2(0.0f, 3.0f));*/
		ImGui::SliderInt("##BRWINS", &i_wins, 1, 5555555555, "Wins %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Wins"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"wins");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_wins);
		}

		/*ImGui::Dummy(ImVec2(0.0f, 3.0f));*/
		ImGui::SliderInt("##BRTOP5", &i_top5, 1, 5555555555, "Top 5 %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Top5"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"topFive");
			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_top5);

		}

	/*	ImGui::Dummy(ImVec2(0.0f, 3.0f));*/
		ImGui::SliderInt("##BRKILLS", &i_kills, 1, 5555555555, "Kills %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Kills"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"kills");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_kills);
		}

		//ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::SliderInt("##BRDEATHS", &i_deaths, 1, 5555555555, "Deaths %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Deaths"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"deaths");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_deaths);
		}

		//ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::SliderInt("##BRDOWNS", &i_downs, 1, 5555555555, "Downs %d");
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("Set Downs"), ImVec2(-1, 30)))
		{
			char context[255];
			char state[255];

			__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

			CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

			DDL_GetRootState((__int64)state, ddl_file);

			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
			DDL_MoveToName((__int64)state, (__int64)state, (__int64)"downs");

			DDL_SetInt((__int64)state, (__int64)context, (unsigned int)i_downs);
		}
	}

	
}

void cMenu::DrawMenu()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::SetNextWindowSize({ 409, 475 });
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style.GrabRounding = style.FrameRounding = 2.3f;

	if (ImGui::Begin("ExeModzz AIO TOOL", &g_vars->msettings.b_menuEnable, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysUseWindowPadding |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
	
		if (ImGui::BeginTabBar("tabs"))
		{
			if (ImGui::BeginTabItem("MAIN"))
			{
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				ImGui::Checkbox(xorstr_("FOV "), &g_vars->msettings.b_fov);
				if (g_vars->msettings.b_fov) {
					dvar_set2("NSSLSNKPN", g_vars->msettings.f_fov);
				}
				ImGui::SameLine();
				ImGui::SliderFloat(xorstr_("##FOVSLIDER"), &g_vars->msettings.f_fov, 1.0f, 2.0f, "%.1f");
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				ImGui::Checkbox(xorstr_("MAP "), &g_vars->msettings.b_map);
				if (g_vars->msettings.b_map) {
					dvar_set2("MKMRRLNRTM", g_vars->msettings.f_map);
				}
				ImGui::SameLine();
				ImGui::SliderFloat(xorstr_("##MAPSLIDER"), &g_vars->msettings.f_map, 1.0f, 2.0f, "%.1f");
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				if (ImGui::Button(xorstr_("Skip Tutorial"), ImVec2(125, 30)))
				{
					dvar_set2(xorstr_("LSPSKLPNQT"), 1);
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr_("Private Match"), ImVec2(125, 30)))
				{
					dvar_set2(xorstr_("LOQQOSNQKN"), 1);
					dvar_set2(xorstr_("PKMLMMTSN"), 1);
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr_("FPS Boost"), ImVec2(125, 30)))
				{
					dvar_set2("OPOTTRRNQ", 0);
					dvar_set2("NNRQTQNLRL", 0);
					dvar_set2("NNTOQLMSLO", 3);
					dvar_set2("NTROOKOSPM", 3);
					dvar_set2("NNKRMTSNPL", 0);
					dvar_set2("MOLLKMTMRS", 0);
					dvar_set2("MQOPRPQLQL", 0);
					dvar_set2("NLNKQNROQM", 0);
					dvar_set2("LTOKRMRTMM", 0);
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				ImGui::Separator();
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				if (ImGui::Button(xorstr_("Unlock All"), ImVec2(-1, 35)))
				{
					unlock();
				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				static const char* itemclantag[] = { "Logo IW", "Logo RVN", "Logo SHG","Logo DW","Logo HMS","Logo BNOX","Logo 3ARC","Logo VV","Logo TFB", "Logo KING", "Logo BLIZZARD", "Red 1W","Red LW","Red IW DEV","Red RAVN","Red RAVEN","Red R4VEN", "Red OW", "Red BN0X","Red 34RC","Red ATVI" };
				static const char* current_clantag = "Select Clan Tag";
				if (ImGui::BeginCombo("##combo4", current_clantag)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(itemclantag); n++)
					{
						bool is_selected4 = (current_clantag == itemclantag[n]); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(itemclantag[n], is_selected4))
							current_clantag = itemclantag[n];
						if (is_selected4)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
					ImGui::EndCombo();
				}
				ImGui::SameLine();

				if (ImGui::Button(xorstr_("Set Tag"), ImVec2(-1, 30))) {
					if (current_clantag == "Logo IW")
						CL_PlayerData_SetCustomClanTag("iw");
					if (current_clantag == "Logo RVN")
						CL_PlayerData_SetCustomClanTag("rvn");
					if (current_clantag == "Logo SHG")
						CL_PlayerData_SetCustomClanTag("shg");
					if (current_clantag == "Logo DW")
						CL_PlayerData_SetCustomClanTag("dw");
					if (current_clantag == "Logo HMS")
						CL_PlayerData_SetCustomClanTag("hms");
					if (current_clantag == "Logo BNOX")
						CL_PlayerData_SetCustomClanTag("bnox");
					if (current_clantag == "Logo 3ARC")
						CL_PlayerData_SetCustomClanTag("3arc");
					if (current_clantag == "Logo VV")
						CL_PlayerData_SetCustomClanTag("vv");
					if (current_clantag == "Logo TFB")
						CL_PlayerData_SetCustomClanTag("tfb");
					if (current_clantag == "Logo KING")
						CL_PlayerData_SetCustomClanTag("king");
					if (current_clantag == "Logo BLIZZARD")
						CL_PlayerData_SetCustomClanTag("bliz");
					if (current_clantag == "Red 1W")
						CL_PlayerData_SetCustomClanTag("1W");
					if (current_clantag == "Red LW")
						CL_PlayerData_SetCustomClanTag("LW");
					if (current_clantag == "Red IW DEV")
						CL_PlayerData_SetCustomClanTag("IWDev");
					if (current_clantag == "Red RAVN")
						CL_PlayerData_SetCustomClanTag("RAVN");
					if (current_clantag == "Red RAVEN")
						CL_PlayerData_SetCustomClanTag("RAVEN");
					if (current_clantag == "Red R4VEN")
						CL_PlayerData_SetCustomClanTag("R4VEN");
					if (current_clantag == "Red OW")
						CL_PlayerData_SetCustomClanTag("OW");
					if (current_clantag == "Red BN0X")
						CL_PlayerData_SetCustomClanTag("BN0X");
					if (current_clantag == "Red 34RC")
						CL_PlayerData_SetCustomClanTag("34RC");
					if (current_clantag == "Red ATVI")
						CL_PlayerData_SetCustomClanTag("ATVI");
				}
					ImGui::InputTextWithHint(xorstr_("##KeyInput"), xorstr_("Custom Clan Tag"), customtag, 6);
					ImGui::SameLine();
					if (ImGui::Button(xorstr_("Set Custom"), ImVec2(-1, 30)))
					{
						CL_PlayerData_SetCustomClanTag(customtag);
					}
				
				ImGui::Spacing();
				static const char* items[] = { "(MW) Gold", "(MW) Platinum", "(MW) Damascus", "(MW) Obsidian", "(CW) Gold", "(CW) Diamond", "(CW) DMU", "(CW) Golden Viper", "(CW) Plague Diamond", "(CW) Dark Aether", "(VG) Gold", "(VG) Diamond", "(VG) Atomic", "(VG) Fake Diamond", "(VG) Golden Viper", "(VG) Plague Diamond", "(VG) Dark Aether", "(CW) Cherry Blossom",  "(MW) Acticamo", "(MW) Banded", "(VG) False Prospector", "(VG) Death Prospector", "(VG) Titanium Chrome", "(VG) Liquid Metal", "(VG) Skynet" };
				static const char* current_item = "Select Camo";
				static int item_current_2 = 0;
				ImGui::Combo("          ", &item_current_2, xorstr_("Class 1\0Class 2\0Class 3\0Class 4\0Class 5\0Class 6\0Class 7\0Class 8\0Class 9\0Class 10\0\0"));
				static int item_current_3 = 0;
				ImGui::Combo("                   ", &item_current_3, xorstr_("Primary\0Secondary\0\0"));
				if (ImGui::BeginCombo(xorstr_("##combo"), current_item))
				{
					for (int n = 0; n < IM_ARRAYSIZE(items); n++)
					{
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected))
							current_item = items[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				ImGui::SameLine();

				if (ImGui::Button(xorstr_("Set Camo"), ImVec2(-1, 30)))
				{

					if (current_item == "(MW) Gold")
						SetCamo(item_current_2, item_current_3, 111);

					if (current_item == "(MW) Platinum")
						SetCamo(item_current_2, item_current_3, 112);

					if (current_item == "(MW) Damascus")
						SetCamo(item_current_2, item_current_3, 113);

					if (current_item == "(MW) Obsidian")
						SetCamo(item_current_2, item_current_3, 114);

					if (current_item == "(CW) Gold")
						SetCamo(item_current_2, item_current_3, 133);

					if (current_item == "(CW) Diamond")
						SetCamo(item_current_2, item_current_3, 134);

					if (current_item == "(CW) DMU")
						SetCamo(item_current_2, item_current_3, 135);

					if (current_item == "(CW) Golden Viper")
						SetCamo(item_current_2, item_current_3, 242);

					if (current_item == "(CW) Plague Diamond")
						SetCamo(item_current_2, item_current_3, 243);

					if (current_item == "(CW) Dark Aether")
						SetCamo(item_current_2, item_current_3, 244);

					if (current_item == "(VG) Gold")
						SetCamo(item_current_2, item_current_3, 345);

					if (current_item == "(VG) Diamond")
						SetCamo(item_current_2, item_current_3, 346);

					if (current_item == "(VG) Atomic")
						SetCamo(item_current_2, item_current_3, 350);

					if (current_item == "(VG) Fake Diamond")
						SetCamo(item_current_2, item_current_3, 349);

					if (current_item == "(VG) Golden Viper")
						SetCamo(item_current_2, item_current_3, 402);

					if (current_item == "(VG) Plague Diamond")
						SetCamo(item_current_2, item_current_3, 403);

					if (current_item == "(VG) Dark Aether")
						SetCamo(item_current_2, item_current_3, 404);

					if (current_item == "(CW) Cherry Blossom")
						SetCamo(item_current_2, item_current_3, 160);

					if (current_item == "(MW) Acticamo")
						SetCamo(item_current_2, item_current_3, 2);

					if (current_item == "(MW) Banded")
						SetCamo(item_current_2, item_current_3, 3);

					if (current_item == "(VG) False Prospector")
						SetCamo(item_current_2, item_current_3, 509);

					if (current_item == "(VG) Death Prospector")
						SetCamo(item_current_2, item_current_3, 510);

					if (current_item == "(VG) Titanium Chrome")
						SetCamo(item_current_2, item_current_3, 511);

					if (current_item == "(VG) Liquid Metal")
						SetCamo(item_current_2, item_current_3, 512);

					if (current_item == "(VG) Skynet")
						SetCamo(item_current_2, item_current_3, 513);
				}

				ImGui::RadioButton(xorstr_("MP"), &gameMode, 0);

				ImGui::SameLine();

				ImGui::RadioButton(xorstr_("WZ"), &gameMode, 1);

				ImGui::EndTabItem();
			}
				if (ImGui::BeginTabItem("DVARS"))
				{
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("No Gun "), &g_vars->msettings.b_nogun);
					if (g_vars->msettings.b_nogun)
					{
						dvar_set2("SROLTPQLK", 0);
					}
					else
					{
						dvar_set2("SROLTPQLK", 1);
					}
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("No Fog "), &g_vars->msettings.b_fog);
					if (g_vars->msettings.b_fog)
					{
						dvar_set2("LTOKRMRTMM", 0);
					}
					else
					{
						dvar_set2("LTOKRMRTMM", 1);
					}
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("Max Bright "), &g_vars->msettings.b_brightmax);
					if (g_vars->msettings.b_brightmax) {
						dvar_set2("NQKKOONQPR", 0);
						dvar_set2("MTLMSQMNTR", 0);
						dvar_set2("RNPPKQOTN", 0);
						dvar_set2("LKOLRONRNQ", 0);
						dvar_set2("LTOKRMRTMM", 0);
					}
					else
					{
						dvar_set2("NQKKOONQPR", 1);
						dvar_set2("MTLMSQMNTR", 1);
						dvar_set2("RNPPKQOTN", 1);
						dvar_set2("LKOLRONRNQ", 1);
						dvar_set2("LTOKRMRTMM", 1);
					}

					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("Third Person "), &g_vars->msettings.b_thirdperson);
					if (g_vars->msettings.b_thirdperson)
					{
						dvar_set2("NOSLRNTRKL", 1);
					}
					else
					{
						dvar_set2("NOSLRNTRKL", 0);
					}

					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("Mess up View "), &g_vars->msettings.b_view);
					if (g_vars->msettings.b_view)
					{
						dvar_set2("LLLRKRROOP", 1);
					}
					else
					{
						dvar_set2("LLLRKRROOP", 0);
					}
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("No Flash Bangs "), &g_vars->msettings.b_no_flashbang);
					if (g_vars->msettings.b_no_flashbang)
					{
						dvar_set2("cg_drawShellshock", 0);
					}
					else
					{
						dvar_set2("cg_drawShellshock", 1);
					}

					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("Unlimited Sprint "), &g_vars->msettings.b_sprint);
					if (g_vars->msettings.b_sprint)
					{
						dvar_set2("NNQTKSTRPK", 20);
						dvar_set2("MSOOMPMPQS", 1);
					}
					else
					{
						dvar_set2("MSOOMPMPQS", 0);
					}
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("Heartcheat Sensor "), &g_vars->msettings.b_heartcheat);
					if (g_vars->msettings.b_heartcheat)
					{
						dvar_set2("NSKNMSMOLP", 2);
						dvar_set2("NLLRSSOQMQ", 10000);
					}
					else
					{
						dvar_set2("NSKNMSMOLP", 5);
						dvar_set2("NLLRSSOQMQ", 500);
					}
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					ImGui::Checkbox(xorstr_("Ownership Check Bypass "), &g_vars->msettings.b_ownership);
					if (g_vars->msettings.b_ownership)
					{
						dvar_set2("NRQQOMLOQL", 0);
						dvar_set2("RRTLRKKTT", 0);
						dvar_set2("MKQPRPLQKL", 0);
					}
					else
					{
						dvar_set2("NRQQOMLOQL", 1);
						dvar_set2("RRTLRKKTT", 1);
						dvar_set2("MKQPRPLQKL", 1);
					}
					ImGui::Dummy(ImVec2(0.0f, 1.0f));
					if (ImGui::Button(xorstr_("Profanity Name Bypass"), ImVec2(-1, 35)))
					{
						dvar_set2("PLTMTSLKT", 0);
						Beep(523, 500);
					}
					ImGui::EndTabItem();
				}


				if (ImGui::BeginTabItem("STATS"))
				{
					STATS();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}

		}
		//ImGui::EndGroup();
		//ImGui::PopFont();
	
