#include "../WeaponCore/Weapon.hpp"
#include "AnalysisCoordinator.hpp"
#include "PowerModel.hpp"
#include <vector>


AnalysisCoordinator::AnalysisCoordinator(std::vector<std::shared_ptr<IModel>> models) : models{ models } {

}

void AnalysisCoordinator::Analyse(std::vector<Weapon>& weapons) {
	if (weapons.size() == 0)
		return;
	//Coordinator class invariant that the weapons vector is ordered by type
	WeaponType currentType = weapons.front().type;
	for (const auto& w : weapons){
		if (w.type != currentType) {
			for(auto& model:models)
			{
				model.get()->processCurrentType();
				currentType = w.type;
			}
		}
		for (auto& model : models)
		{
			model->updateWithWeapon(w);
		}
	}
	for (auto& model : models)
	{
		model->finalize();
	}
}