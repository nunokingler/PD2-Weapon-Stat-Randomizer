#pragma once
#include <random>
#include "../WeaponCore/Weapon.hpp"
#include "IWeaponBehavior.hpp"

void IWeaponBehavior::AnalyseWeapons(const std::vector<Weapon> weapons){
    auto categoryNumber = weapons.back().type;
}

float IWeaponBehavior::CalculateDps(const Weapon& w) {
    auto fullCycle = (w.magSize * w.rof) + w.reloadSpeed;
    if (w.reloadSpeed <= 0.0001f)  return 0.0f;
    auto DPS = w.damage * w.magSize / fullCycle;
    return DPS;
}

float IWeaponBehavior::CalculateEffectiveDps(const Weapon& w, int weaponConcealment, int otherWeaponConcealment ) {
    int totalConcealment = weaponConcealment + otherWeaponConcealment + 61; // 61 from suit+melee TODO make constant variable 
    //TODO also make otherWEaponConcealment constant to iterate and see how generation changes with that consideration
    int critThresholdConcealment = 119 - 61; // =58 for max crit 

    float critChance;
    if (totalConcealment >= critThresholdConcealment) {
        critChance = 0.30f; // max crit
    }
    else if (totalConcealment >= 100) {
        critChance = 0.15f; // approximate mid crit
    }
    else {
        critChance = 0.0f; // no significant crit
    }

    float baseDps = CalculateDps(w);
    float effectiveMultiplier = 3.0f + 6.0f * critChance;
    return baseDps * effectiveMultiplier;
}