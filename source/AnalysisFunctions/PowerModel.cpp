#include <vector>
#include <cmath>
#include <iostream>
#include <utility>
#include "PowerModel.hpp"
#include <map>
#include "../WeaponCore/Weapon.hpp"
#include "../WeaponCore/WeaponConstants.hpp"
#include "../WeaponCore/Stat.hpp"

namespace {
    // Compute best-fit a and b for y = a * x^b
    PowerLaw  powerLawFit(const std::vector<float>& x, const std::vector<float>& y) {
        if (x.size() != y.size() || x.empty())
            throw std::invalid_argument("Input vectors must have the same non-zero size.");

        double sumLogX = 0.0, sumLogY = 0.0, sumLogX2 = 0.0, sumLogXLogY = 0.0;
        size_t count = 0;

        for (size_t i = 0; i < x.size(); ++i) {
            if (x[i] <= 0 || y[i] <= 0) continue; // skip invalid or zero values
            double logX = std::log(x[i]);
            double logY = std::log(y[i]);

            sumLogX += logX;
            sumLogY += logY;
            sumLogX2 += logX * logX;
            sumLogXLogY += logX * logY;
            ++count;
        }

        if (count == 0) {
            throw std::runtime_error("No valid data points for fitting.");
        }

        double denominator = count * sumLogX2 - sumLogX * sumLogX;
        if (denominator == 0) throw std::runtime_error("Degenerate data.");

        double b = (count * sumLogXLogY - sumLogX * sumLogY) / denominator;
        double logA = (sumLogY - b * sumLogX) / count;
        double a = std::exp(logA);

        return PowerLaw{ static_cast<float>(a), static_cast<float>(b) };
    }
}


PowerModel::PowerModel() {
    currentType = WeaponType::AssaultRifle;
    xDamage.reserve(40);
    for (auto& [stat, vec] : yPerStat)
    {
        vec.reserve(40);
    }
}

void PowerModel::updateWithWeapon(const Weapon& w) 
{    
    currentType = w.type;
    float damage = static_cast<float>(w.damage);
    if (damage <= 0) return; // skip zero or negative damage
    xDamage.push_back(damage);

    for (const auto& [stat, extract, canBeModelDriven] : StatInfo::statExtractors) {
        if (!canBeModelDriven) continue;
        float val = extract(w);
        if (val > 0.0f) {
            yPerStat[stat].push_back(val);
        }
    }
}
void PowerModel::processCurrentType()
{
    if (xDamage.empty())
        return;// Flush everything for the old type
    for (auto& [stat, yVals] : yPerStat) {
        if (xDamage.size() != yVals.size())
            continue;
        try {
            PowerLaw model = powerLawFit(xDamage, yVals);
            models[currentType][stat] = model;
        }
        catch (const std::exception& e) {
            auto type = static_cast<int>(currentType);
            std::cout << "Flush error for type " <<  type << ": With stat " << static_cast<int>(stat) << e.what() << std::endl;
        }
        
    }
    // Reset for the new type
    xDamage.clear();
    yPerStat.clear();
}

void PowerModel::finalize()
{
    processCurrentType();
}
const PowerLaw* PowerModel::tryGetModel(WeaponType t, Stat s) const {
    auto itType = models.find(t);
    if (itType == models.end()) return nullptr;
    auto itStat = itType->second.find(s);
    return (itStat == itType->second.end()) ? nullptr : &itStat->second;
}

