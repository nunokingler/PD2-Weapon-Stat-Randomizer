#pragma once
#include "../WeaponCore/Weapon.hpp"
class IModel {
public:
    virtual ~IModel() = default;
    // Process each weapon once as part of an ongoing pass:
    virtual void updateWithWeapon(const Weapon& w) = 0;
    virtual void processCurrentType() = 0;
    // Once all weapons have been processed, finalize the fitting:
    virtual void finalize() = 0;
};