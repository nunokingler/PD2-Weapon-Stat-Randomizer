#pragma once
#include <unordered_map>
#include "../WeaponCore/Stat.hpp"
#include "../WeaponCore/WeaponConstants.hpp"

struct PowerLaw {
    float a;
    float b;
};

class StatModel {
public:
    StatModel();
    // Process each weapon once as part of an ongoing pass:
    void updateWithWeapon(const Weapon& w);
    void processCurrentType();
    // Once all weapons have been processed, finalize the fitting:
    void finalize();
private:
    //parameters for calculation
    WeaponType currentType;
    std::vector<float> xDamage;
    std::unordered_map<Stat, std::vector<float>> yPerStat;
    //output
    std::unordered_map<WeaponType, std::unordered_map<Stat, PowerLaw>> models;
};