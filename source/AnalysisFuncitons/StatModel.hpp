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
    void analyze(const std::vector<Weapon>& weapons);
private:
    std::unordered_map<WeaponType, std::unordered_map<Stat, PowerLaw>> models;
    void flushCurrentType(WeaponType type,const std::vector<float>& xPerStat,const std::vector<float>& yPerStat, Stat stat);
};