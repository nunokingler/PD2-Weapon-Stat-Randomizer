#pragma once
#include <random>
#include <vector>
#include "../WeaponCore/Weapon.hpp"

class IWeaponBehavior {
public:
    virtual ~IWeaponBehavior() = default;
    virtual Weapon balance(Weapon& w) = 0;
    virtual void AnalyseWeapons(const std::vector<Weapon> weapons);
    virtual float CalculateDps(const Weapon& w);
    virtual float CalculateEffectiveDps(const Weapon& w, int weaponConcealment, int otherWeaponConcealment = 25);
private:
    struct StatResult {
        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::lowest();
        double sum = 0;
        size_t count = 0;

        void add(double val) {
            min = std::min(min, val);
            max = std::max(max, val);
            sum += val;
            ++count;
        }

        double avg() const {
            return count > 0 ? sum / count : 0.0;
        }
    };
    struct WeaponStats {
        StatResult damage;
        StatResult concealment;
        StatResult rof;
        StatResult accuracy;
        StatResult stability;
        StatResult reloadSpeed;
    };
};