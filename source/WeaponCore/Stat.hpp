#pragma once
#include <array>
#include "Weapon.hpp"
#include <unordered_map>

enum class Stat {
    Damage,
    ReloadSpeed,
    ROF,
    Concealment,
    Accuracy,
    Stability,
    AmmoTotal,
    MagSize,
    AmmoHigh,
    AmmoLow,
};
namespace StatInfo{
    // Struct to hold stat-accessor pairs
    struct StatExtractor {
        Stat stat;
        float (*extract)(const Weapon&);
        bool canBeModelDriven;
    };

    // Static list of stat extractors
    inline const std::array<StatExtractor, 10> statExtractors{ {
        { Stat::AmmoHigh,    [](const Weapon& w) { return w.ammoHigh; } ,true},
        { Stat::AmmoLow,     [](const Weapon& w) { return w.ammoLow; } ,true},
        { Stat::ReloadSpeed, [](const Weapon& w) { return w.reloadSpeed; } ,false},
        { Stat::ROF,         [](const Weapon& w) { return w.rof; } ,false},
        { Stat::Damage,      [](const Weapon& w) { return static_cast<float>(w.damage); } ,false},
        { Stat::Concealment, [](const Weapon& w) { return static_cast<float>(w.concealment); },false },
        { Stat::Accuracy,    [](const Weapon& w) { return static_cast<float>(w.accuracy); } ,false},
        { Stat::Stability,   [](const Weapon& w) { return static_cast<float>(w.stability); } ,false},
        { Stat::AmmoTotal,   [](const Weapon& w) { return static_cast<float>(w.ammoTotal); },false },
        { Stat::MagSize,     [](const Weapon& w) { return static_cast<float>(w.magSize); },false }
    } };

    // Fast map-based lookup (built at startup)
    inline const std::unordered_map<Stat, const StatExtractor*> statExtractorMap = [] {
        std::unordered_map<Stat, const StatExtractor*> map;
        for (const auto& extractor : statExtractors) {
            map[extractor.stat] = &extractor;
        }
        return map;
    }();
}