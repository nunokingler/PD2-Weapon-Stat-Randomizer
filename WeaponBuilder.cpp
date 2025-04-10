#include <string>
#include "Weapon.hpp"
#include "WeaponConstants.hpp"
#include "WeaponBuilder.hpp"
using wb = WeaponBuilder;

// Set Names
wb& WeaponBuilder::SetInternalName(const std::string& name) {
        internalName = name;
        return *this;
}

wb& WeaponBuilder::SetIngameName(const std::string& name) {
    ingameName = name;
    return *this;
}

//Set Weapon categories
wb& WeaponBuilder::SetType(WeaponType t) {
        type = t;
        return *this;
}

wb& WeaponBuilder::SetClass(WeaponClass c) {
        weaponClass = c;
        return *this;
}

//Set DPS stats
wb& WeaponBuilder::SetDamage(int d) {
    damage = d;
    return *this;
}

wb& WeaponBuilder::SetROF(float r) {
    rof = r;
    return *this;
}

wb& WeaponBuilder::SetReloadSpeed(float r) {
    reloadSpeed = r;
    return *this;
}

wb& WeaponBuilder::SetConcealment(int c) {
    concealment = c;
    return *this;
}

//Set Handling stats
wb& WeaponBuilder::SetAccuracy(int ac) {
    accuracy = ac;
    return *this;
}

wb& WeaponBuilder::SetStability(int sb) {
    stability = sb;
    return *this;
}

//Set Ammo stats
wb& WeaponBuilder::SetAmmoLow(float al) {
    ammoLow = al;
    return *this;
}
wb& WeaponBuilder::SetAmmoHigh(float ah) {
    ammoHigh = ah;
    return *this;
}
wb& WeaponBuilder::SetMagSize(int mag) {
    magSize = mag;
    return *this;
}
wb& WeaponBuilder::SetAmmoTotal(int at) {
    ammoTotal = at;
    return *this;
}

//builder
Weapon WeaponBuilder::Build() const{
    return Weapon(
        internalName, type, weaponClass, ingameName, damage, concealment,
        rof, reloadSpeed, accuracy, stability, ammoLow, ammoHigh, magSize, ammoTotal
    );
}
