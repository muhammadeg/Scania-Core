void __fastcall MyProcessMsg(void *Player, void *edx, char *Msg)
{
	std::string FullMsg = (std::string)Msg;
	IChar IPlayer(Player);
	vector<string> arr = explode(" ", Msg);

	if (!arr.empty() && arr[0] == "/s") {

		if (arr.size() > 1){
			if (CPlayer::FindItem(Player, 515, 1)){
				std::string url = ShoutsWebhook;
				std::string avatar = Avatar;
				std::string playerName = std::string(IPlayer.GetName());
				std::string additionalMessage = FullMsg.substr(3);
				std::string msg = additionalMessage;

				SendShoutWebhookMessage(url.c_str(), msg.c_str(), avatar.c_str(), std::string(playerName));
			}
		}
	}

	CPlayer::ProcessMsg(Player, Msg);
}
