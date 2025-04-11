#pragma once

#include <string>
#include <vector>
#include "../WeaponCore/Weapon.hpp"  

class WeaponImporter {
public:
    static std::vector<Weapon> importFromCSV();
};