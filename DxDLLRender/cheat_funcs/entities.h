bool mfound = false;
int npeek = 0;
uintptr_t cam = 0;
#include "../hooks.hpp"

void FindMatrix() {
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = read(dwGameObjectManager, DWORD64);
	if (!ObjMgr) return;
	UINT64 end = read(ObjMgr, UINT64);
	for (UINT64 Obj = read(ObjMgr + 0x8, UINT64); (Obj && (Obj != end)); Obj = read(Obj + 0x18, UINT64))
	{
		UINT64 GameObject = read(Obj + 0x10, UINT64);
		WORD Tag = read(GameObject + 0x54, WORD);
		if (Tag == 5)
		{
			UINT64 ObjClass = read(GameObject + 0x30, UINT64);
			UINT64    Entity = read(ObjClass + 0x18, UINT64);
			LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);
			printf(StrA("Found matrix!\n"));
			mfound = true;
			return;
		}
	}
}

void RadarPlayer(BasePlayer* player);
inline void RenderActiveSlot(BasePlayer* player, float Pos_x, float Pos_Y);
void miscvis(DWORD64 ObjectClass, char* buff, bool boolean, bool showDistance, float drawDistance, const char* substring, const wchar_t* targettext, D2D1::ColorF color) {
	if (boolean && strstr(buff, substring)) {
		DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
		DWORD64 transform = read(gameObject + 0x8, DWORD64);
		DWORD64 vector = read(transform + 0x38, DWORD64);
		Vector3 game_Pos = read(vector + 0x90, Vector3);
		Vector2 screen_Pos;
		if (LocalPlayer.WorldToScreen(game_Pos, screen_Pos)) {
			if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), game_Pos) <= drawDistance) {
				wchar_t distance[64];
				_swprintf(distance, L"[ %d m ]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), game_Pos));
				wchar_t text[64];
				_swprintf(text, targettext);
				Render::Object.String({ screen_Pos.x, screen_Pos.y }, text, color, true, true);
				if (showDistance) {
					Render::Object.String(screen_Pos + Vector2(0, 15), distance, color, true, true);
				}
			}
		}
	}
}
void EntityZaLoop()
{
	if (Misc::flyhack_indicator) {
		Render::Object.FillRectangle(Vector2(Global::ScreenWidth / 2 - 214, 200), Vector2(428 * (Misc::flyhack / Misc::max_flyhack), 10), D2D1::ColorF::Lime);
		Render::Object.Rectangle(Vector2(Global::ScreenWidth / 2 - 214, 200), Vector2(428, 10), D2D1::ColorF::Black);

		Render::Object.FillRectangle(Vector2(Global::ScreenWidth / 2 - 214, 230), Vector2(428 * (Misc::hor_flyhack / Misc::max_hor_flyhack), 10), D2D1::ColorF::Lime);
		Render::Object.Rectangle(Vector2(Global::ScreenWidth / 2 - 214, 230), Vector2(428, 10), D2D1::ColorF::Black);
	}

	float FOV = AimBot::Fov;
	float CurFOV;
	bool LP_isValid = false;
	if (!LocalPlayer.pViewMatrix || !mfound) {
		FindMatrix();
	}
	DWORD64 BaseNetworkable;
	BaseNetworkable = read(Storage::gBase + 0x36567B8, DWORD64); //BaseNetworkable_c
	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
	for (int i = 0; i <= EntityCount; i++)
	{
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
		if (Entity <= 100000) continue;
		DWORD64 Object = read(Entity + 0x10, DWORD64);
		if (Object <= 100000) continue;
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64);
		DWORD64 ent = read(Object + 0x28, UINT64);
		if (ObjectClass <= 100000) continue;
		pUncStr name = read(ObjectClass + 0x60, pUncStr);
		if (!name) continue;
		char* buff = name->stub;
		BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
		if (strstr(buff, StrA("Local"))) {
			Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;
			if (Player != LocalPlayer.BasePlayer) {
				printf("LocalPlayer %lld\n", Player->GetSteamID());
				mfound = false;
			}
			LocalPlayer.BasePlayer = Player;
			LP_isValid = true;
		}

		else if (strstr(buff, "player.prefab") || (strstr(buff, "tunneldweller")) || (strstr(buff, "scientist")) && (!strstr(buff, "prop") && !strstr(buff, "corpse")))
		{
			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
			if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;
			OOF(Player, D2D1::ColorF::Blue);
			ESP(Player, LocalPlayer.BasePlayer);
			RadarPlayer(Player);
			float ActiveSlotPos_X = 70.f;
			float ActiveSlotPos_Y = 300.f;
			if (Visuals::ActiveSlotRender && GetFov(Player, head) <= 150) {
				RenderActiveSlot(Player);
			}
			//if (Radar::ActiveSlot && GetFov(Player, head) <= Storage::closestPlayer)
			//	RenderActiveSlot(Player, Radar::ActiveSlotPos_X, Radar::ActiveSlotPos_Y);
			if (PlayerEsp::sleeperignore && Player->HasFlags(16)) continue;
			if (AimBot::IgnoreNpc && Player->IsNpc()) continue;
			if (AimBot::IgnoreTeam && Player->IsTeamMate(LocalPlayer.BasePlayer->GetSteamID())) continue;
			if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), Player->GetBoneByID(head)) > AimBot::Range) continue;

			if (FOV > (CurFOV = GetFov(Player, BoneList(Global::BoneToAim))) && !Player->IsDead()) {
				FOV = CurFOV; Storage::closestPlayer = (uintptr_t)Player, !Player->IsTeamMate(LocalPlayer.BasePlayer->GetSteamID());
			}
		}
		miscvis(ObjectClass, buff, Ores::Stone, Ores::showDistance, Ores::oreDrawDistance, "stone-ore.prefab", L"Stone Ore", D2D1::ColorF::Gray);
		miscvis(ObjectClass, buff, Ores::Stone, Ores::showDistance, Ores::oreDrawDistance, "stone-collectable.prefab", L"Stone Collectable", D2D1::ColorF::Gray);
		miscvis(ObjectClass, buff, Ores::Sulfur, Ores::showDistance, Ores::oreDrawDistance, "sulfur-ore.prefab", L"Sulfur Ore", D2D1::ColorF::Gold);
		miscvis(ObjectClass, buff, Ores::Sulfur, Ores::showDistance, Ores::oreDrawDistance, "sulfur-collectable.prefab", L"Sulfur Collectable", D2D1::ColorF::Gold);
		miscvis(ObjectClass, buff, Ores::Metal, Ores::showDistance, Ores::oreDrawDistance, "metal-ore.prefab", L"Metal Ore", D2D1::ColorF::SaddleBrown);
		miscvis(ObjectClass, buff, Ores::Metal, Ores::showDistance, Ores::oreDrawDistance, "metal-collectable.prefab", L"Metal Collectable", D2D1::ColorF::SaddleBrown);
		miscvis(ObjectClass, buff, Visuals::Supply, Visuals::crateDistance, Visuals::drawCrateDistance, "supply_drop.prefab", L"Airdrop", D2D1::ColorF::DarkCyan);
		miscvis(ObjectClass, buff, Visuals::Chinook, Visuals::crateDistance, Visuals::drawCrateDistance, "codelockedhackablecrate.prefab", L"Chinook Crate", D2D1::ColorF::DarkRed);
		miscvis(ObjectClass, buff, Visuals::Minicopter, Visuals::vehicleDistance, Visuals::drawVehicleDistance, "minicopter.entity.prefab", L"Minicopter", D2D1::ColorF::Blue);
		miscvis(ObjectClass, buff, Visuals::ScrapHeli, Visuals::vehicleDistance, Visuals::drawVehicleDistance, "scraptransporthelicopter.prefab", L"Scrap Heli", D2D1::ColorF::DarkBlue);
		miscvis(ObjectClass, buff, Visuals::Boat, Visuals::vehicleDistance, Visuals::drawVehicleDistance, "rowboat.prefab", L"Boat", D2D1::ColorF::LightBlue);
		miscvis(ObjectClass, buff, Visuals::RHIB, Visuals::vehicleDistance, Visuals::drawVehicleDistance, "rhib.prefab", L"RHIB", D2D1::ColorF::LightCyan);
		miscvis(ObjectClass, buff, Visuals::AutoTurret, Visuals::trapDistance, Visuals::drawTrapDistance, "autoturret_deployed.prefab", L"Auto Turret", D2D1::ColorF::Orange);
		miscvis(ObjectClass, buff, Visuals::FlameTurret, Visuals::trapDistance, Visuals::drawTrapDistance, "flameturret.deployed.prefab", L"Flame Turret", D2D1::ColorF::DarkOrange);
		miscvis(ObjectClass, buff, Visuals::ShotgunTurret, Visuals::trapDistance, Visuals::drawTrapDistance, "guntrap.deployed.prefab", L"Shotgun Trap", D2D1::ColorF::DimGray);
		miscvis(ObjectClass, buff, Visuals::Landmine, Visuals::trapDistance, Visuals::drawTrapDistance, "landmine.prefab", L"Landmine", D2D1::ColorF::BlueViolet);
		miscvis(ObjectClass, buff, Visuals::BearTrap, Visuals::trapDistance, Visuals::drawTrapDistance, "beartrap.prefab", L"Beartrap", D2D1::ColorF::Brown);
		miscvis(ObjectClass, buff, Visuals::Hemp, Visuals::otherDistance, Visuals::drawOtherDistance, "hemp.entity.prefab", L"Hemp", D2D1::ColorF::LimeGreen);
		miscvis(ObjectClass, buff, Visuals::Corpse, Visuals::otherDistance, Visuals::drawOtherDistance, "player_corpse.prefab", L"Corpse", D2D1::ColorF::Firebrick);
		miscvis(ObjectClass, buff, Visuals::Stash, Visuals::otherDistance, Visuals::drawOtherDistance, "small_stash_deployed.prefab", L"Stash", D2D1::ColorF::Yellow);
		miscvis(ObjectClass, buff, Visuals::PatrolHeli, Visuals::otherDistance, 4500.f, "assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab", L"Patrol Helicopter", D2D1::ColorF(0.3f, 0.34f, 1.f));

		miscvis(ObjectClass, buff, Visuals::Berry, Visuals::AnimalsDistance, Visuals::drawBerryDistance, "berry-green-collectable.prefab", L"Зелёные ягодки", D2D1::ColorF::Green);
		miscvis(ObjectClass, buff, Visuals::Berry, Visuals::AnimalsDistance, Visuals::drawBerryDistance, "berry-red-collectable.prefab", L"Красные ягодки", D2D1::ColorF::Red);
		miscvis(ObjectClass, buff, Visuals::Berry, Visuals::AnimalsDistance, Visuals::drawBerryDistance, "berry-blue-collectable.prefab", L"Синие ягодки", D2D1::ColorF::Blue);
		miscvis(ObjectClass, buff, Visuals::Berry, Visuals::AnimalsDistance, Visuals::drawBerryDistance, "berry-white-collectable.prefab", L"Белые ягодки", D2D1::ColorF::White);

		miscvis(ObjectClass, buff, Visuals::Bear, Visuals::AnimalsDistance, Visuals::drawAnimalsDistance, "bear.prefab", L"Медведь ёбанный", D2D1::ColorF::SandyBrown);
		miscvis(ObjectClass, buff, Visuals::Boar, Visuals::AnimalsDistance, Visuals::drawAnimalsDistance, "boar.prefab", L"Кабанчик", D2D1::ColorF::SaddleBrown);
		miscvis(ObjectClass, buff, Visuals::Chicken, Visuals::AnimalsDistance, Visuals::drawAnimalsDistance, "chicken.prefab", L"Курица", D2D1::ColorF::DarkViolet);
		miscvis(ObjectClass, buff, Visuals::Horse, Visuals::AnimalsDistance, Visuals::drawAnimalsDistance, "horse.prefab", L"Лошадь", D2D1::ColorF::MintCream);

	}
	if (Storage::closestPlayer)
	{
		if (FOV < (CurFOV = GetFov((BasePlayer*)Storage::closestPlayer, BoneList(Global::BoneToAim))))
		{
			Storage::closestPlayer = 0;
		}
	}
	if (LP_isValid)
	{
		if (Storage::closestPlayer && !LocalPlayer.BasePlayer->IsMenu()) {
			if (GetAsyncKeyState(Keys::aimKey)) {
				do_aimbot(reinterpret_cast<BasePlayer*>(Storage::closestPlayer));
			}
		}
	}
	else LocalPlayer.BasePlayer = nullptr;

}