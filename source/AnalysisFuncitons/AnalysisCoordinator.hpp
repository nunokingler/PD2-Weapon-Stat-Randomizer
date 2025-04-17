#pragma once
#include "PowerModel.hpp"


class AnalysisCoordinator {
public:
	AnalysisCoordinator(PowerModel& model);
	void Analyse(std::vector<Weapon>& weapons);
private:
	PowerModel& powerModel;
};