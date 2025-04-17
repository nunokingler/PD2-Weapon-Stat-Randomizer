#pragma once
#include "IModel.hpp"
#include "../WeaponCore/Weapon.hpp"
#include "../WeaponCore/Stat.hpp"
#include <vector>

class MinMaxModel :public IModel{

public:
    MinMaxModel(StatInfo::StatExtractor st);
    // Process each weapon once as part of an ongoing pass:
    void updateWithWeapon(const Weapon& w) override;
    void processCurrentType() override;
    // Once all weapons have been processed, finalize the fitting:
    void finalize() override;
private:
    float min{}, max{};
    std::vector<float> values;
    float(*extractor)(const Weapon&);
    //outputs
    std::vector<float> minOutput, maxOutput, meanOutput;
};