#pragma once
#include <string>
#include "WeaponConstants.hpp"

class Weapon {
public:
    friend class Balancer;
    Weapon(
        const std::string& internalName, WeaponType type, WeaponClass weaponClass,
        const std::string& ingameName, int damage, int concealment, float rof,
        float reloadSpeed, int accuracy, int stability, float ammoLow, float ammoHigh, 
        int magSize, int ammoTotal);

    Weapon(const Weapon&) = default;
    Weapon( Weapon&&) = default;

    Weapon& operator= (const Weapon&) = default;
    Weapon& operator=(Weapon&&) = default;
    
    
    std::string internalName;       //Name in .lua files    

private:
    std::string ingameName;         //Name that shows up in game (differs from .lua files most of the time
    WeaponType type;                       //weapon type (SMG, Shotgun, etc)
    WeaponClass weaponClass;                //Weapon category (different damage ranges or new weapon types entirely (bow vs sniper for egz))
    int damage;
    int concealment;
    float rof;
    float reloadSpeed;
    int accuracy;
    int stability;
    float ammoLow;
    float ammoHigh;
    int magSize;
    int ammoTotal;
};