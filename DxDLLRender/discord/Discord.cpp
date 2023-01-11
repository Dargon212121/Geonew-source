#include "Discord.h"
#include "include/discord_rpc.h"
#include <time.h>

void Discord::start()
{
	DiscordEventHandlers Handler;
	memset(&Handler, 0, sizeof(Handler));
	Discord_Initialize("1062404951831224331", &Handler, 1, NULL);
}
static void update()
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "test";
    discordPresence.details = "test";
    discordPresence.startTimestamp = 0;
    discordPresence.endTimestamp = 1507665886;
    discordPresence.largeImageText = "Numbani";
    discordPresence.smallImageText = "Rogue - Level 100";
    discordPresence.partyId = "ae488379-351d-4a4f-ad32-2b9b01c91657";
    discordPresence.partySize = 1;
    discordPresence.partyMax = 0;
    discordPresence.joinSecret = "MTI4NzM0OjFpMmhuZToxMjMxMjM= ";
    Discord_UpdatePresence(&discordPresence);
}