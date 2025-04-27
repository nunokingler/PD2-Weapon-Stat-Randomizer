#pragma once 
#include <fstream>
#include <iomanip>
#include <cmath>    // for std::round
#include <vector>
#include "../WeaponCore/Weapon.hpp"

class WeaponExporter {
public:
	void ExportToLua(const std::vector<Weapon>& weapons);
private:

};