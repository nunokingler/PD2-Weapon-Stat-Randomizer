#include <vector>
#include <cmath>
#include <iostream>
#include <utility>
#include "StatModel.hpp"
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
}// Extracted flush function
void StatModel::flushCurrentType(
    WeaponType type,
    const std::vector<float>& x,
    const std::vector<float>& y,
    Stat stat)
{
    if (!x.empty() && x.size() == y.size()) {
        try {
            PowerLaw model = powerLawFit(x, y);
            models[type][stat] = model;
        }
        catch (const std::exception& e) {
            std::cout << "Flush error for type " << type << ": " << e.what() << std::endl;
        }
    }
}
// Group by WeaponType and fit stats
void StatModel::analyze(const std::vector<Weapon>& weapons) {
    if (weapons.empty()) return;

    WeaponType currentType = weapons.front().type;
    std::vector<float> xDamage;
    std::unordered_map<Stat, std::vector<float>> yPerStat;

    xDamage.reserve(30);
    for (const auto& weapon : weapons) {            // For each group and each stat, fit power law
        if (weapon.type != currentType) {           // we have changed types time to run the model
            for (const auto& [stat, y] : yPerStat) {
                flushCurrentType(currentType, xDamage, y, stat);
            }
            currentType = weapon.type;
            xDamage.clear();
            yPerStat.clear();
        }

        float damage = static_cast<float>(weapon.damage);
        if (damage <= 0) continue;

        xDamage.push_back(damage);
        for (const auto& [stat, extract] : statExtractors) {
            if (!isModelDriven(stat)) continue;

            float value = extract(weapon);
            if (value > 0) {
                yPerStat[stat].push_back(value);
            }
        }
    }                
    for (const auto& [stat, y] : yPerStat) {
        flushCurrentType(currentType, xDamage, y, stat);
    }
}

