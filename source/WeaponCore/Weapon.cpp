#pragma once
#include"Weapon.hpp"
#include <sstream>   // for std::ostringstream
#include <iostream>  // for std::ostream (if using operator<< too)

Weapon::Weapon(
    const std::string& internalName, WeaponType type, WeaponClass weaponClass,
    const std::string& ingameName, int damage, int concealment, float rof,
    float reloadSpeed, int accuracy, int stability, float ammoLow, float ammoHigh, 
    int magSize, int ammoMax) :
    internalName{ internalName }, type{ type }, weaponClass{ weaponClass },
    ingameName{ ingameName }, damage{ damage }, concealment{ concealment },
    rof{ rof }, reloadSpeed{reloadSpeed},accuracy {accuracy}, 
    stability{ stability }, ammoLow{ ammoLow }, ammoHigh{ ammoHigh },
    magSize{ magSize }, ammoMax{ ammoMax }
{}

std::string Weapon::toString() const {
    std::ostringstream oss;
    const std::string RED = "\033[1;31m";
    const std::string GREEN = "\033[1;32m";
    const std::string YELLOW = "\033[1;33m";
    const std::string BLUE = "\033[1;34m";
    const std::string MAGENTA = "\033[1;35m";
    const std::string CYAN = "\033[1;36m";
    const std::string RESET = "\033[0m";

    // Format name and tab pad if short
    auto nameVisualLength = internalName.length()+ingameName.length(); 
    long long paddingSpaces = 38-nameVisualLength;
    auto paddedName = ingameName;
    for (int i = 0; i < paddingSpaces; ++i) {
        paddedName += ' ';
    }
    oss << RESET << "[" << internalName << "]" << paddedName;
    // Print remaining data
    oss << RESET << "Type: " << BLUE << static_cast<int>(type) << "  "
        << RESET << "Class: " << BLUE << static_cast<int>(weaponClass) << "  "
        << RESET << "DMG: " << RED << damage << "  "
        << RESET << "ROF: " << RED << rof << "  "
        << RESET << "Reload: " << RED << reloadSpeed << "  "
        << RESET << "Acc: " << YELLOW << accuracy << "  "
        << RESET << "Stab: " << YELLOW << stability << "  "
        << RESET << "Conceal: " << YELLOW << concealment << "  "
        << RESET << "Mag: " << CYAN << magSize << "  "
        << RESET << "Ammo: " << CYAN << ammoMax << "  "
        << RESET << "Pickup: " << CYAN << ammoLow << "-" << ammoHigh ;

    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
    return os << weapon.toString();
}