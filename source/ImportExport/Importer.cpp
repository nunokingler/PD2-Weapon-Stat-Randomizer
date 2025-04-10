#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Weapon.hpp"
#include "Importer.hpp"
#include <iostream>
#include "WeaponBuilder.hpp"

namespace {
    std::vector<std::string> splitLine(const std::string& line) {
        std::vector<std::string> tokens;
        tokens.reserve(13);
        std::stringstream ss(line);
        std::string item;

        // Split based on commas
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }
        return tokens;
    }

    Weapon createWeaponFromLine(const std::vector<std::string> tokens) {
        WeaponBuilder weaponBuilder;
        //weaponBuilder.SetInternalName(tokens[0]);
        std::string internalName = tokens[0];
        auto type = static_cast<WeaponType>(std::stoi(tokens[1]));
        auto category = static_cast<WeaponClass> (std::stoi(tokens[2]));
        std::string inGameName = tokens[3];
        int damage = std::stoi(tokens[4]);
        int concealment = std::stoi(tokens[5]);
        float rateOfFire = 1.0/std::stoi(tokens[6]);
        int accuracy = std::stoi(tokens[7]);
        int stability = std::stoi(tokens[8]);
        float ammoLow = std::stof(tokens[9]);
        float ammoHigh = std::stof(tokens[10]);
        int magSize = std::stoi(tokens[11]);
        int ammoTotal = std::stoi(tokens[12]);

        // Construct a Weapon object
        return Weapon(
            internalName,
            type,
            category,
            inGameName,
            damage,
            concealment,
            rateOfFire,
            0.0,
            accuracy,
            stability,
            ammoLow,
            ammoHigh,
            magSize,
            ammoTotal
        );
    }
}

std::vector<Weapon> WeaponImporter::importFromCSV() {
    std::vector<Weapon> weapons;

    std::ifstream inFile("originalStats.csv");//TODO define constant
    if (!inFile.is_open()) {
        std::cout << "Error: Unable to open stats file"<< std::endl;
        return weapons; // Return an empty vector on error
    }

    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty())    
            continue;

        auto tokens = splitLine(line);
        // Verify we have exactly 13 fields:
        // internalName, type, category, inGameName, damage, concealment, rateOfFire, accuracy,
        // stability, ammoLow, ammoHigh, magSize, ammoTotal
        if (tokens.size() < 13) {
            std::cout << "Warning: Skipping malformed line: " << line << std::endl;
            continue;
        }
        auto w = createWeaponFromLine(tokens);
        weapons.push_back(w);
    }

    inFile.close();
    return weapons;
}