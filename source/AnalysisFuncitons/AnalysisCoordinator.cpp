#include "../WeaponCore/Weapon.hpp"
#include "AnalysisCoordinator.hpp"
#include "PowerModel.hpp"
#include <vector>


AnalysisCoordinator::AnalysisCoordinator(PowerModel& model) : powerModel{ model } {

}

void AnalysisCoordinator::Analyse(std::vector<Weapon>& weapons) {
	if (weapons.size() == 0)
		return;
	//Coordinator class invariant that the weapons vector is ordered by type
	WeaponType currentType = weapons.front().type;
	for (const auto& w : weapons){
		if (w.type != currentType) {
			powerModel.processCurrentType(); 
			currentType = w.type;
		}
		powerModel.updateWithWeapon(w);
	}
	powerModel.finalize();
}