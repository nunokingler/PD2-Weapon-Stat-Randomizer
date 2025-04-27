#include <fstream>
#include <iomanip>
#include <cmath>    // for std::round
#include <vector>
#include "../WeaponCore/Weapon.hpp"
#include "Exporter.hpp"

void WeaponExporter::ExportToLua(const std::vector<Weapon>& weapons) {
	auto filename = "PD2-WeaponStats.lua";
	std::ofstream file(filename);
	
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: \"" + std::string(filename) + "\"");
	}
    for(const auto w:weapons)
    {
        auto name = "self. " + w.internalName + ".stats.";


        file << name << "damage = " << w.damage << "\n";
        file << name << "stats.concealment = " << w.concealment << "\n";

        file << std::fixed << std::setprecision(2);
        file << name << "fire_mode_data = { fire_rate = " << w.rof << " }\n";
        file << name << "auto = {fire_rate = " << w.rof << "}\n";

        int spread = static_cast<int>(std::round(w.accuracy / 4.0f)) + 1;
        int recoil = static_cast<int>(std::round(w.stability / 4.0f)) + 1;

        file << name << "stats.spread = " << spread << "\n";
        file << name << "stats.recoil = " << recoil << "\n";

        file << name << "AMMO_PICKUP = {" << w.ammoLow << ", " << w.ammoHigh << "}\n";
        file << name << "CLIP_AMMO_MAX = " << w.magSize << "\n";
        file << name << "AMMO_MAX = " << w.ammoMax << "\n\n";
    }
}