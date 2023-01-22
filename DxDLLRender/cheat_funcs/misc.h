void WeaponPatch() {
	WeaponData* weapon = LocalPlayer.BasePlayer->GetActiveWeapon();
	if (weapon == nullptr) return;

	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info();
	if (!target.id) return;
	if (!target.category) return;
	if (target.category == 1) {
		return;
	}
	if (target.category == -2) {
		weapon->SuperBow();
		return;
	}
	if (target.category == 3) {
		weapon->RapidFire();
		return;
	}
	if (target.category == 2) {
		weapon->RapidFire();
		weapon->SetAutomatic();
		return;
	}
	if (target.category == -1) {
		weapon->SuperEoka();
		return;
	}

}

void MiscFuncs() {
	LocalPlayer.BasePlayer->SetFov();
	if (Misc::SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();
	if (Misc::NightMode)
	{
		LocalPlayer.BasePlayer->NightMode();
	}
	if (Misc::CustomFov)
		LocalPlayer.BasePlayer->SetFov();
	if (Misc::Zoom)
		LocalPlayer.BasePlayer->Zoom();
	if (Misc::InfJump) {
		if (GetAsyncKeyState(VK_SPACE)) {
			LocalPlayer.BasePlayer->InfinityJump();
		}
	}
	if (Misc::CustomTime) {
		LocalPlayer.BasePlayer->Admintime();}
	if (Weapons::NoSway)
		LocalPlayer.BasePlayer->NoSway();
	if (Weapons::NoSpread) {
		LocalPlayer.BasePlayer->NoSpread();}
	if (Weapons::NoRecoil) {
		LocalPlayer.BasePlayer->NoRecoil();}
	if (Misc::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin();
	if (AimBot::RCS)
		LocalPlayer.BasePlayer->SetRA();
	if (Misc::LongNeck && GetAsyncKeyState(Misc::longKey))
		LocalPlayer.BasePlayer->LongNeck();
	if (Misc::LongNeckright && GetAsyncKeyState(Misc::LongNeckkey))
		LocalPlayer.BasePlayer->LongNeckright();
	if (Misc::LongNeckLeft && GetAsyncKeyState(Misc::LongNeckkeyLongNeckLeft))
		LocalPlayer.BasePlayer->LongNeckrLeft();
}
