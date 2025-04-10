#include <cstdint>
#pragma once
enum WeaponType {
	AssaultRifle,
	Shotgun,
	LightMachineGun,
	Sniper,
	AkimboPistols,
	AkimboSubMachineGun,
	AkimboShotgun,
	SawAndMisc,
	Pistols,
	SubMachineGuns,
	SawAndMiscSecondary,
	ShotgunsSecondary,
	SniperSecondary
};

using WeaponClass = uint8_t;

// per-Type grouping
// keep in mind most of these types dont have hard bounderies
// ie some of the dmg100 assault rifles might have 90 or 120 damage
// however these classes are defined by the game so there isnt any margin to change them
namespace WeaponClasses {

	namespace AssaultRifle {
		static constexpr WeaponClass dmg50 = 1;
		static constexpr WeaponClass dmg60 = 2;
		static constexpr WeaponClass dmg100 = 3;
		static constexpr WeaponClass dmg160 = 4;
	}
	namespace Shotgun {
		static constexpr WeaponClass dmg50 = 1;
		static constexpr WeaponClass dmg100 = 2;
		static constexpr WeaponClass dmg155 = 3;
	}
	namespace LightMachineGun {
		static constexpr WeaponClass dmg80 = 1;
		static constexpr WeaponClass dmg120 = 2;
		static constexpr WeaponClass dmg100 = 3;
	}
	namespace Sniper {
		static constexpr WeaponClass dmg160 = 1;
		static constexpr WeaponClass dmg246 = 2;
		static constexpr WeaponClass dmg480 = 3;
		static constexpr WeaponClass dmg3500 = 4;
	}
	namespace AkimboPistols {
		static constexpr WeaponClass fullAuto = 1;
		static constexpr WeaponClass dmg40 = 2;
		static constexpr WeaponClass dmg70 = 3;
		static constexpr WeaponClass dmg120 = 4;
		static constexpr WeaponClass dmg180 = 5;
	}
	namespace AkimboSubMachineGun {
		static constexpr WeaponClass dmg50 = 1;
		static constexpr WeaponClass dmg60 = 2;
		static constexpr WeaponClass dmg100 = 3;
	}
	namespace AkimboShotgun {
		static constexpr WeaponClass akimboGrimm = 1;
		static constexpr WeaponClass akimboGoliath = 2;
		static constexpr WeaponClass akimboJudge = 3;
	}
	namespace SawAndMisc {
		static constexpr WeaponClass saw = 1;
		static constexpr WeaponClass vulkanMinigun = 7;
		static constexpr WeaponClass MicroGun = 8;
		static constexpr WeaponClass Flamethrower = 10;
	}
	namespace Pistols {
		static constexpr WeaponClass fullAuto = 1;
		static constexpr WeaponClass dmg53 = 2;
		static constexpr WeaponClass dmg80 = 3;
		static constexpr WeaponClass dmg120 = 4;
		static constexpr WeaponClass dmg180 = 5;
		static constexpr WeaponClass dmg200 = 6;
	}	
	namespace SubMachineGuns {
		static constexpr WeaponClass dmg40 = 1;
		static constexpr WeaponClass dmg60 = 2;
		static constexpr WeaponClass dmg100 = 3;
	}
	namespace SawAndMiscSecondary {
		static constexpr WeaponClass saw = 1;
		static constexpr WeaponClass flamethrower = 9;
	}
	namespace ShotgunsSecondary {
		static constexpr WeaponClass dmg20 = 1;
		static constexpr WeaponClass dmg40 = 2;
		static constexpr WeaponClass dmg100 = 3;
		static constexpr WeaponClass dmg155 = 4;
	}
	namespace SniperSecondary {
		static constexpr WeaponClass pronghorn = 1;
	}

}