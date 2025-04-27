#pragma once
#include <random>
#include "IWeaponBehavior.hpp"
#include "../AnalysisFunctions/PowerModel.hpp"
#include "../Generators/IStatGenerator.hpp"
#include "../Generators/StatGenerators.cpp"


class DefaultBehaviour : public IWeaponBehavior {
public:
    DefaultBehaviour(DamageGenerator& dG, RofMagGenerator& rG, HandlingGenerator& hG, AmmoStatsGenerator& aG) :
        dG{ dG }, rG{ rG }, hG{ hG }, aG{ aG } {}
    Weapon balance(Weapon& w) override {
        auto newStats = Weapon(w);
        dG.randomise(newStats);
        rG.randomise(newStats);
        hG.randomise(newStats);
        aG.randomise(newStats);
        return newStats;
    }
private:
    DamageGenerator& dG; 
    RofMagGenerator& rG; 
    HandlingGenerator& hG; 
    AmmoStatsGenerator& aG;
};