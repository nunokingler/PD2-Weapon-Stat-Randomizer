#pragma once
#include "../WeaponCore/Weapon.hpp"

class IWeaponBehavior {
public:
    virtual ~IWeaponBehavior() = default;
    virtual void balance(Weapon& w) = 0;
};