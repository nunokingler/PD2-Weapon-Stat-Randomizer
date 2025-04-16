#pragma once
#include "StatModel.hpp"
#include "StatModel.hpp"


class AnalysisCoordinator {
public:
	AnalysisCoordinator(StatModel& model);
	void Analyse(std::vector<Weapon>& weapons);
private:
	StatModel& powerModel;
};