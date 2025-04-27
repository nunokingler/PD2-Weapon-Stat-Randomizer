#pragma once
#include <vector>
#include "../WeaponCore/Stat.hpp"

struct GeneratorMeta {

    std::vector<Stat> requireStats;
    std::vector<Stat> produceStats;

    GeneratorMeta& Requires(std::initializer_list<Stat> stats) {
        requireStats.insert(requireStats.end(), stats.begin(), stats.end());
        return *this;
    }

    GeneratorMeta& Produces(std::initializer_list<Stat> stats) {
        produceStats.insert(produceStats.end(), stats.begin(), stats.end());
        return *this;
    }
};

class IStatGenerator {
public:
    virtual const GeneratorMeta meta() const = 0;
    virtual void randomise(Weapon& w) const = 0;
    virtual ~IStatGenerator() = default;
};