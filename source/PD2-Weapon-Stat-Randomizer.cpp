// PD2-Weapon-Stat-Randomizer
// Authored by: 

#include <iostream>
#include "Importer.hpp"
#include "Balancer.hpp"
int main()
{
    WeaponImporter a;
    Balancer b;
    std::cout << "Hello World!\n";
    auto weapons = a.importFromCSV();
    for (auto weapon : weapons) {
        std::cout << b.CalculateDps(weapon) <<std::endl;
    }
}
