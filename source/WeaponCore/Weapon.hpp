#pragma once
#include <string>
#include "WeaponConstants.hpp"
#include <sstream>   //  this is crucial!
#include <iostream>  // if using std::ostream or operator<<
#include <iomanip>   // optional: for std::setprecision

class Weapon {
public:
    friend class Balancer;
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);
    Weapon(
        const std::string& internalName, WeaponType type, WeaponClass weaponClass,
        const std::string& ingameName, int damage, int concealment, float rof,
        float reloadSpeed, int accuracy, int stability, float ammoLow, float ammoHigh, 
        int magSize, int ammoTotal);

    Weapon(const Weapon&) = default;
    Weapon( Weapon&&) = default;

    Weapon& operator= (const Weapon&) = default;
    Weapon& operator= (Weapon&&) = default;
    
    std::string toString() const;

    float getReloadspeed() const {
        return reloadSpeed;
    }

    std::string internalName;       //Name in .lua files    
    std::string ingameName;         //Name that shows up in game (differs from .lua files most of the time
    WeaponType type;                       //weapon type (SMG, Shotgun, etc)
    WeaponClass weaponClass;                //Weapon category (different damage ranges or new weapon types entirely (bow vs sniper for egz))
    int damage;
    float rof;
    float reloadSpeed;
    int concealment;
    int accuracy;
    int stability;
    float ammoLow;
    float ammoHigh;
    int magSize;
    int ammoTotal;

private:
};
