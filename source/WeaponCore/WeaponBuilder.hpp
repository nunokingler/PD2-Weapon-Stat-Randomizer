#pragma once

#include <string>
#include "Weapon.hpp"        // For the Weapon class
#include "WeaponConstants.hpp" // For WeaponClass definitions

class WeaponBuilder {
public:
    // Set Names
    WeaponBuilder& SetInternalName(const std::string& name);
    WeaponBuilder& SetIngameName(const std::string& name);
    // Set Weapon categories
    WeaponBuilder& SetType(WeaponType t);
    WeaponBuilder& SetClass(WeaponClass c);
    // Set DPS stats
    WeaponBuilder& SetDamage(int d);
    WeaponBuilder& SetROF(float r);
    WeaponBuilder& SetReloadSpeed(float r);
    WeaponBuilder& SetConcealment(int c);
    // Set Handling stats
    WeaponBuilder& SetAccuracy(int a);
    WeaponBuilder& SetStability(int s);
    // Set Ammo stats
    WeaponBuilder& SetAmmoLow(float a);
    WeaponBuilder& SetAmmoHigh(float a);
    WeaponBuilder& SetMagSize(int m);
    WeaponBuilder& SetAmmoTotal(int a);

    // Build the Weapon object
    Weapon Build() const;

private:
    std::string internalName;
    WeaponType type = WeaponType::AssaultRifle; 
    WeaponClass weaponClass = WeaponClasses::AssaultRifle::dmg50;
    std::string ingameName;
    int damage = 0;
    int concealment = 0;
    float rof = 0;
    int accuracy = 0;
    float reloadSpeed=0;
    int stability = 0;
    float ammoLow = 0.0f;
    float ammoHigh = 0.0f;
    int magSize = 0;
    int ammoTotal = 0;
};