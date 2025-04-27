#pragma once
#define BOOST_DI_CFG_DIAGNOSTICS_LEVEL 2
#include "Libraries/boost/di.hpp"
#include <random>
#include "AnalysisFunctions/AnalysisCoordinator.hpp"
#include "AnalysisFunctions/PowerModel.hpp"
#include "AnalysisFunctions/MinMaxMeanModel.hpp"
#include "Generators/StatGenerators.cpp"          // contains the four concrete generators
#include "BalanceBehaviours/DefaultBehavior.hpp"         // DefaultBehaviour

namespace di = boost::di;

// ---------- helper aliases --------------------------------------------------
template<Stat S> using MM = MinMaxModel<S>;

/*  A helper that returns the right extractor for the compiletime Stat. */
template<Stat S>
constexpr StatInfo::StatExtractor extractor() {
    return *StatInfo::statExtractorMap.at(S);
}

/*  All MinMax models that your generators need.                        */
using DamageMM = MM<Stat::Damage>;
using RofMM = MM<Stat::ROF>;
using ConMM = MM<Stat::Concealment>;
using MagMM = MM<Stat::MagSize>;
using StabMM = MM<Stat::Stability>;
using AccMM = MM<Stat::Accuracy>;

// ---------- the injector ----------------------------------------------------
inline auto make_injector()
{

    return di::make_injector(


        /*  A single, seeded RNG instance shared by everything that needs one. */
        di::bind<std::mt19937>()(std::random_device{}()),


        //    /* ---------- lowlevel singletons ---------- */
        di::bind<PowerModel>.in(boost::di::singleton),

        di::bind<DamageMM>.to<DamageMM>().in(di::singleton),
        di::bind<RofMM>.to<RofMM>().in(di::singleton),
        di::bind<ConMM>.to<ConMM>().in(di::singleton),
        di::bind<MagMM>.to<MagMM>().in(di::singleton),
        di::bind<StabMM>.to<StabMM>().in(di::singleton),
        di::bind<AccMM>.to<AccMM>().in(di::singleton),



        /* ---------- generators (DI will fetch the above singletons) ---------- */

        di::bind<DamageGenerator>.in(di::singleton),
        di::bind<RofMagGenerator>.in(di::singleton),
        di::bind<HandlingGenerator>.in(di::singleton),
        di::bind<AmmoStatsGenerator>.in(di::singleton),

        di::bind<IModel* []>().to<PowerModel, DamageMM, RofMM, ConMM, MagMM, StabMM, AccMM>(),
        //di::bind<AnalysisCoordinator>.to([](const auto& injector) {
        //    auto& power = injector.template create<PowerModel&>();
        //    auto& dmg = injector.template create<DamageMM&>();
        //    auto& rof = injector.template create<RofMM&>();
        //    auto& mag = injector.template create<MagMM&>();
        //    auto& stab = injector.template create<StabMM&>();
        //    auto& acc = injector.template create<AccMM&>();

        //    return AnalysisCoordinator{
        //        std::vector<IModel*>{ &power,& dmg,& rof,& mag,& stab,& acc }
        //    };
        //    }).in(di::singleton),

        di::bind<DefaultBehaviour>.to<DefaultBehaviour>().in(di::singleton)
   );
}