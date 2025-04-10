#pragma once

#include <string>
#include <vector>
#include "Weapon.hpp"  

class WeaponImporter {
public:
    static std::vector<Weapon> importFromCSV();
};