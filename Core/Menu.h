#define KXMENU_EXIT							(WM_APP + 101)
#define KXMENU_AboutMassageBox				(WM_APP + 105)
#define KXMENU_ReloadCfg					(WM_APP + 106)
#define KXMENU_ReloadCleanCfg				(WM_APP + 107)
#define KXMENU_Uptime						(WM_APP + 108)
#define KXMENU_OnlinePlayers				(WM_APP + 109)
#define KXMENU_ReloadQuest					(WM_APP + 110)
#define KXMENU_ReloadGenMonster				(WM_APP + 111)
#define KXMENU_ReloadInitMonster			(WM_APP + 112)
#define KXMENU_ReloadInitNPC				(WM_APP + 113)
#define KXMENU_ReloadInitItem				(WM_APP + 114)
#define KXMENU_FakePlayers					(WM_APP + 115)
#define KXMENU_CleanInitItem				(WM_APP + 116)
#define KXMENU_CleanInitMonster				(WM_APP + 117)
#define KXMENU_CleanInitNPC					(WM_APP + 118)
#define KXMENU_CleanInitPrefix				(WM_APP + 119)
#define KXMENU_KickPlayer					(WM_APP + 120)


#define ScreenPtr				0x4E1128
#define StatusScreenPtr			0x4E2EDC
#define mainHWND				*reinterpret_cast<HWND*>(0x4E2134)

HMENU CreateMainWindowMenu(HMENU hBaseMenu) {
	if (!hBaseMenu) return nullptr;
	auto hMenuPopupConfig = CreatePopupMenu();
	AppendMenu(hBaseMenu, MF_POPUP, (UINT_PTR)hMenuPopupConfig, TEXT("Configs Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadQuest, TEXT("Quest.txt Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadGenMonster, TEXT("GenMonster.txt Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadInitMonster, TEXT("InitMonster.txt Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadInitNPC, TEXT("InitNPC.txt Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadInitItem, TEXT("InitItem.txt Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadCfg, TEXT("Core Configs Reload"));
	AppendMenu(hMenuPopupConfig, MF_STRING, KXMENU_ReloadCleanCfg, TEXT("Core Configs Clean Load"));

	AppendMenu(hBaseMenu, MF_STRING, KXMENU_FakePlayers, TEXT("Load Fake Players"));
	AppendMenu(hBaseMenu, MF_STRING, KXMENU_Uptime, TEXT("Uptime"));
	AppendMenu(hBaseMenu, MF_STRING, KXMENU_OnlinePlayers, TEXT("Online Players"));


	auto hMenuPopupClean = CreatePopupMenu();
	AppendMenu(hBaseMenu, MF_POPUP, (UINT_PTR)hMenuPopupClean, TEXT("Configs Cleaner"));
	AppendMenu(hMenuPopupClean, MF_STRING, KXMENU_CleanInitItem, TEXT("InitItem.txt Cleaner"));
	AppendMenu(hMenuPopupClean, MF_STRING, KXMENU_CleanInitMonster, TEXT("InitMonster.txt Cleaner"));
	AppendMenu(hMenuPopupClean, MF_STRING, KXMENU_CleanInitNPC, TEXT("InitNPC.txt Cleaner"));
	AppendMenu(hMenuPopupClean, MF_STRING, KXMENU_CleanInitPrefix, TEXT("Prefix.txt Cleaner"));

	AppendMenu(hBaseMenu, MF_STRING, KXMENU_AboutMassageBox, TEXT("About"));

	auto hMenuPopupTools = CreatePopupMenu();
	AppendMenu(hBaseMenu, MF_POPUP, (UINT_PTR)hMenuPopupTools, TEXT("Server Tools"));
	AppendMenu(hMenuPopupTools, MF_STRING, KXMENU_KickPlayer, TEXT("Kick Player"));


	return hBaseMenu;
}


void DrawMainMenu(std::string MenuName) {
	auto hMenuPopup = CreateMainWindowMenu(CreateMenu());
	if(hMenuPopup){
		AppendMenu(GetMenu(*(HWND*)(0x4E2134)), MF_POPUP, (UINT_PTR)hMenuPopup, MenuName.c_str());
		DrawMenuBar(*(HWND*)(0x4E2134));
	}
}


LRESULT CALLBACK Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
	case WM_COMMAND:
		switch (wParam) {
		case KXMENU_ReloadCfg: {
								   ReadConfig(true);
								   if (!modifiedFiles.empty()) {
									   for (auto x = modifiedFiles.rbegin(); x != modifiedFiles.rend(); x++)
										   CConsole::Blue("%s reloaded successfully", x->c_str());
								   }
								   else
									   CConsole::Red("No config files were modified.");

								   break;
		}

		case KXMENU_ReloadCleanCfg: {
										CleanLoadConfig();
										CConsole::Blue("Configs have been cleaned and reloaded.");
										break;
		}

		case KXMENU_FakePlayers: {
									 Console();
									 cout << "Number of fake players to display: ";
									 cin >> EFakePlayers;
									 if (cin.fail()) {
										 cin.clear();
										 cin.ignore();
									 }
									 else {
										 EFakePlayers = (EFakePlayers >= FakePlayers.size()) ? FakePlayers.size() : EFakePlayers;

										 if (EFakePlayers)
											 CConsole::Blue("%d Fake players are now available.", EFakePlayers >= FakePlayers.size() ? FakePlayers.size() : EFakePlayers);
										 else
											 CConsole::Red("Fake players have been disabled.");

									 }
									 FreeConsole();
									 break;
		}

		case KXMENU_Uptime: {
								CConsole::Blue("%s", getUptime().c_str());
								break;
		}

		case KXMENU_OnlinePlayers: {
									   CConsole::Black("There are %d Players Online.", InterlockedExchangeAdd(&OnlinePlayers, 0));
									   break;
		}

		case KXMENU_ReloadQuest: {
									 QuestsReload();
									 break;
		}

		case KXMENU_CleanInitItem: {
									   InitItemCleaner("InitItem", "itemname");
									   break;
		}

		case KXMENU_CleanInitMonster: {
										  InitItemCleaner("InitMonster", "monstername");
										  break;
		}

		case KXMENU_CleanInitNPC: {
									  InitItemCleaner("InitNPC", "npcname");
									  break;
		}

		case KXMENU_CleanInitPrefix: {
										 InitItemCleaner("Prefix", "prefixname");
										 break;
		}

		case KXMENU_ReloadGenMonster: {
										  GenMonsterReload();
										  break;
		}
		case KXMENU_ReloadInitMonster: {
										   InitMonsterReload();
										   break;
		}

		case KXMENU_ReloadInitItem: {
										InitItemReload();
										break;
		}

		case KXMENU_ReloadInitNPC: {
									   isReloadingNPC = 1;
									   break;
		}

		case KXMENU_AboutMassageBox: {
										 CConsole::Black("[KalTechSolutions] KalOnline Main Server Addon, Copyright © Scania - 2023");
										 break;
		}

		case KXMENU_KickPlayer: {
									std::string playerName;
									bool playerFound = false;
									Console();
									cout << "Enter Player Name to kick: ";
									cin >> playerName;
									if (cin.fail()) {
										cin.clear();
										cin.ignore();
									}
									else {
										/* think of another solution, this is not good for mainsrv (iterating + deleting on same collection)
										CIOCriticalSection::Enter((void*)0x004e2078);
										CIOCriticalSection::Enter((void*)0x004e2098);
										CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
										CIOCriticalSection::Leave((void*)0x004e2098);
										for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
										{
											if ((void*)(a - 428))
											{
												IChar IPlayer((void*)(a - 428));
												if (IPlayer.IsOnline() && IPlayer.GetName() == playerName){
													IPlayer.Kick();
													CConsole::Blue("Player %s was kicked", playerName.c_str());
													playerFound = true;
												}
												else {
													CConsole::Red("Player is not online.");
													playerFound = true;
												}

											}
										}
										CIOCriticalSection::Leave((void*)0x004e2078);
										*/
									}
									if (!playerFound)
										CConsole::Red("Player name is incorrect");

									if (playerName.empty())
										CConsole::Red("Failed to kick Player");
										
									FreeConsole();
									break;
		}

		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return _Window::Proc(hWnd, Msg, wParam, lParam);
	}
	return _Window::Proc(hWnd, Msg, wParam, lParam);
}

#pragma once
