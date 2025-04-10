#pragma once
#include"Weapon.hpp"


Weapon::Weapon(
    const std::string& internalName, WeaponType type, WeaponClass weaponClass,
    const std::string& ingameName, int damage, int concealment, float rof,
    float reloadSpeed, int accuracy, int stability, float ammoLow, float ammoHigh, 
    int magSize, int ammoTotal) :
    internalName{ internalName }, type{ type }, weaponClass{ weaponClass },
    ingameName{ ingameName }, damage{ damage }, concealment{ concealment },
    rof{ rof }, reloadSpeed{reloadSpeed},accuracy {accuracy}, 
    stability{ stability }, ammoLow{ ammoLow }, ammoHigh{ ammoHigh },
    magSize{ magSize }, ammoTotal{ ammoTotal }
{}
