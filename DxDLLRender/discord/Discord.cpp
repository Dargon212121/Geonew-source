#include "Discord.h"
#include <time.h>
#include "disrpc/include/discord_rpc.h"

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("1062404951831224331", &Handle, 1, NULL); //Your Api Key
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "test";
	discordPresence.details = "test";
	discordPresence.startTimestamp = 1507665886;
	discordPresence.largeImageKey = "f";
	discordPresence.largeImageText = "Numbani";
	discordPresence.smallImageKey = "f";
	Discord_UpdatePresence(&discordPresence);


}