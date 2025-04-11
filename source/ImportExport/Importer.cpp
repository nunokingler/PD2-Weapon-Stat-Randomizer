#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../WeaponCore/Weapon.hpp"
#include "Importer.hpp"
#include <iostream>
#include "../WeaponCore/WeaponBuilder.hpp"
using namespace std;

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

    Weapon createWeaponFromLine(const std::vector<std::string> tokens) { //Todo check how the game handles stability of akimbo weapons ( does it store them already with the stability penalty) 
        WeaponBuilder weaponBuilder;
        std::string internalName = tokens[0];
        std::string inGameName = tokens[1];
        auto type = static_cast<WeaponType>(std::stoi(tokens[2]));
        int damage = std::stoi(tokens[3]);
        float rateOfFire = 1.0f / std::stoi(tokens[4]); // same logic as before
        int concealment = std::stoi(tokens[5]);
        int accuracy = std::stoi(tokens[6]);
        int stability = std::stoi(tokens[7]);
        float reloadSpeed = std::stof(tokens[8]);
        int magSize = std::stoi(tokens[9]);
        int ammoTotal = std::stoi(tokens[10]);
        float ammoLow = std::stof(tokens[11]);
        float ammoHigh = std::stof(tokens[12]);

        // Construct a Weapon object
        return Weapon(
            internalName,
            type,
            1,
            inGameName,
            damage,
            concealment,
            rateOfFire,
            reloadSpeed,
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
    weapons.reserve(213);

    auto filename = "scraped_weapon_data.csv";//TODO define constant

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open file: \"" + std::string(filename)+ "\"");                      //No data,no program
    }

    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty())    
            continue;

        auto tokens = splitLine(line);

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