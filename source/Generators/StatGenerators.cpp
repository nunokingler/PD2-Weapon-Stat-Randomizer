#pragma once
#include "IStatGenerator.hpp"
#include <random>
#include "../AnalysisFunctions/PowerModel.hpp"
#include "../AnalysisFunctions/MinMaxMeanModel.hpp"


class DamageGenerator : public IStatGenerator {
public:
    DamageGenerator(MinMaxModel<Stat::Damage>& damageModel, std::mt19937& rng) : 
        model{ damageModel }, rng{ rng } {}

    const GeneratorMeta meta() const override {
        return GeneratorMeta()
            .Requires({})
            .Produces({ Stat::Damage});
    }

    void randomise(Weapon& w) const override {
        std::uniform_real_distribution<float> dmgHigh(model.getMin(w.type), model.getMax(w.type));
        w.damage = static_cast<int>(dmgHigh(rng));
    }

private:
    MinMaxModel<Stat::Damage>& model;
    std::mt19937& rng;
};

class RofMagGenerator : public IStatGenerator {
public:
    RofMagGenerator(MinMaxModel<Stat::ROF>& rofModel, MinMaxModel<Stat::MagSize>& magModel, std::mt19937& rng) :
        rofModel{ rofModel },magModel{magModel}, rng{rng} {}

    const GeneratorMeta meta() const override {
        return GeneratorMeta()
            .Requires({ Stat::Damage })
            .Produces({ Stat::ROF ,Stat::MagSize});
    }

    void randomise(Weapon& w) const override {
        std::uniform_real_distribution<float> rofDist(rofModel.getMin(w.type), rofModel.getMax(w.type));
        std::uniform_real_distribution<float> magDist(magModel.getMin(w.type), magModel.getMax(w.type));
        w.rof = rofDist(rng);
        w.magSize = static_cast<int>(magDist(rng));
    }

private:
    MinMaxModel<Stat::ROF>& rofModel;
    MinMaxModel<Stat::MagSize>& magModel;
    std::mt19937& rng;
};

class HandlingGenerator : public IStatGenerator {
public:
    HandlingGenerator(MinMaxModel<Stat::Stability>& stbModel,MinMaxModel<Stat::Accuracy>& accModel, std::mt19937& rng) :
        stbModel{ stbModel }, accModel{ accModel }, rng{ rng } {}

    const GeneratorMeta meta() const override {
        return GeneratorMeta()
            .Requires({})
            .Produces({ Stat::Stability ,Stat::Accuracy });
    }

    void randomise(Weapon& w) const override {
        std::uniform_real_distribution<float> stbDist(stbModel.getMin(w.type), stbModel.getMax(w.type));
        std::uniform_real_distribution<float> accDist(accModel.getMin(w.type), accModel.getMax(w.type));
        w.stability = static_cast<int>(stbDist(rng));
        w.accuracy = static_cast<int>(accDist(rng));
    }

private:
    MinMaxModel<Stat::Stability>& stbModel;
    MinMaxModel<Stat::Accuracy>& accModel;
    std::mt19937& rng;
};

class AmmoStatsGenerator : public IStatGenerator {

public:
    AmmoStatsGenerator(PowerModel& model, std::mt19937& rng)
        : model(model), rng(rng) {}

     const GeneratorMeta meta() const override {
        return GeneratorMeta()
            .Requires({ Stat::Damage,Stat::ROF })
            .Produces({ Stat::AmmoLow,Stat::AmmoHigh });
    }

    void randomise(Weapon& w) const override {
        const auto* high = model.tryGetModel(w.type, Stat::AmmoHigh);
        const auto* low = model.tryGetModel(w.type, Stat::AmmoLow);
        const auto* max = model.tryGetModel(w.type, Stat::AmmoMax);
        if (!high || !low ||!max) return;                       // no curve  leave asis

        const float dmg = static_cast<float>(w.damage);
        float meanHigh = high->a * std::pow(dmg, high->b);
        float meanLow = low->a * std::pow(dmg, low->b);
        float meanMax = max->a * std::pow(dmg, max->b);

        // 10% jitter around the curve (tweak as you like)
        std::uniform_real_distribution<float>
            dHigh(meanHigh * 0.9f, meanHigh * 1.1f),
            dLow(meanLow * 0.9f, meanLow * 1.1f),
            dMax(meanMax * 0.9f, meanMax * 1.1f);

        w.ammoHigh = dHigh(rng);
        w.ammoLow = dLow(rng);
        w.ammoMax = static_cast<int>(dMax(rng));
    }
private:
    PowerModel& model;
    std::mt19937& rng;
}; 
