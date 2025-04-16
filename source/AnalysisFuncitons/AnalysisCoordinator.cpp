#include "../WeaponCore/Weapon.hpp"
#include "AnalysisCoordinator.hpp"
#include "StatModel.hpp"
#include <vector>


AnalysisCoordinator::AnalysisCoordinator(StatModel& model) : powerModel{ model } {

}

void AnalysisCoordinator::Analyse(std::vector<Weapon>& weapons) {
	if (weapons.size() == 0)
		return;
	//Coordinator class invariant that the weapons vector is ordered by type
	WeaponType currentType = weapons.front().type;
	for (const auto& w : weapons){
		if (w.type != currentType) {
			powerModel.processCurrentType();
		}
		powerModel.updateWithWeapon(w);
	}
	powerModel.finalize();
}