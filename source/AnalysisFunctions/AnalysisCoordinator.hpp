#pragma once
#include "PowerModel.hpp"


class AnalysisCoordinator {
public:
	AnalysisCoordinator(std::vector<std::shared_ptr<IModel>> models);
	void Analyse(std::vector<Weapon>& weapons);
private:
	std::vector<std::shared_ptr<IModel>> models;
};