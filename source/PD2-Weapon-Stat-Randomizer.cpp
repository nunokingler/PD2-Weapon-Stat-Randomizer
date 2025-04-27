// PD2-Weapon-Stat-Randomizer
// Authored by: 

#include <iostream>
#include "ImportExport/Importer.hpp"
#include "ImportExport/Exporter.hpp"
#include "BalanceBehaviours/Balancer.hpp"
#include "WeaponCore/Stat.hpp"
#include "di-bootStrap.hpp"

namespace di = boost::di;

int main()
{

    auto injector = make_injector(); 
    //main.cpp
    auto& rng = injector.create<std::mt19937&>();                 //  same engine
    //auto rng = injector.create< std::mt19937>();
    auto gen = injector.create<DamageGenerator>();

    std::cout << "Constructing RNG with address: " << &rng << "\n";

    auto& power = injector.create<PowerModel&>();
    auto& analysisCoordinator = injector.create<AnalysisCoordinator&>();
    auto& importer = injector.create<WeaponImporter&>();
    auto& exporter = injector.create<WeaponExporter&>();
    auto& behaviour = injector.create<DefaultBehaviour&>();

    std::vector<Weapon> repo = importer.importFromCSV();
    
    analysisCoordinator.Analyse(repo);     // populate every model first

    std::uniform_real_distribution<float> dist(1.0f, 10.0f);

    for (auto& w : repo)
        if(w.type==WeaponType::AssaultRifle)
        std::cout << behaviour.balance(w) << '\n';


    //WeaponImporter a;
    //Balancer b;
    //std::cout << "Hello World!\n";
    //auto weapons = a.importFromCSV();
    //for (auto weapon : weapons) {
    //    auto a = StatInfo::statExtractorMap.find(Stat::ReloadSpeed)->second->extract(weapon);
    //    //if(is_near_zero(weapon.getReloadspeed()))
    //    std::cout << std::fixed << std::setprecision(2) << std::setw(8)  << b.CalculateDps(weapon) << weapon<<  std::endl;
    //}
}