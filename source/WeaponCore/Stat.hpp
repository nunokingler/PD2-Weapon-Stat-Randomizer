#pragma once
#include <array>
#include "Weapon.hpp"

enum class Stat {
    AmmoHigh,
    AmmoLow,
    ReloadSpeed,
    ROF,
    Concealment,
    Accuracy,
    Stability,
    AmmoTotal,
    MagSize
};

constexpr bool isModelDriven(Stat stat) {
    switch (stat) {
    case Stat::AmmoLow:
    case Stat::AmmoHigh:
        return true;
    default:
        return false;
    }
}

// Struct to hold stat-accessor pairs
struct StatExtractor {
    Stat stat;
    float (*extract)(const Weapon&);
    bool isModelDriven;
};

// Static list of stat extractors
inline const std::array<StatExtractor, 9> statExtractors{ {
    { Stat::AmmoHigh,    [](const Weapon& w) { return w.ammoHigh; } ,true},
    { Stat::AmmoLow,     [](const Weapon& w) { return w.ammoLow; } ,true},
    { Stat::ReloadSpeed, [](const Weapon& w) { return w.reloadSpeed; } ,false},
    { Stat::ROF,         [](const Weapon& w) { return w.rof; } ,false},
    { Stat::Concealment, [](const Weapon& w) { return static_cast<float>(w.concealment); },false },
    { Stat::Accuracy,    [](const Weapon& w) { return static_cast<float>(w.accuracy); } ,false},
    { Stat::Stability,   [](const Weapon& w) { return static_cast<float>(w.stability); } ,false},
    { Stat::AmmoTotal,   [](const Weapon& w) { return static_cast<float>(w.ammoTotal); },false },
    { Stat::MagSize,     [](const Weapon& w) { return static_cast<float>(w.magSize); },false }
} };