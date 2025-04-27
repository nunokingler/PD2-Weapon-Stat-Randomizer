#pragma once
#include <unordered_map>
#include "IModel.hpp"
#include "../WeaponCore/Stat.hpp"
#include "../WeaponCore/WeaponConstants.hpp"

struct PowerLaw {
    float a;
    float b;
};

class PowerModel:public IModel {
public:
    PowerModel();
    // Process each weapon once as part of an ongoing pass:
    void updateWithWeapon(const Weapon& w) override;
    void processCurrentType() override;
    // Once all weapons have been processed, finalize the fitting:
    void finalize() override;
    const PowerLaw* tryGetModel(WeaponType t, Stat s) const;
private:
    //parameters for calculation
    WeaponType currentType;
    std::vector<float> xDamage;
    std::unordered_map<Stat, std::vector<float>> yPerStat;
    //output
    std::unordered_map<WeaponType, std::unordered_map<Stat, PowerLaw>> models;
};