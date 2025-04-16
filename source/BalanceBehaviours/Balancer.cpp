#include "Balancer.hpp"

float Balancer::CalculateDps(const Weapon& w) {
	auto fullCycle = (w.magSize * w.rof) + w.reloadSpeed;
	auto DPS = w.damage * w.magSize / fullCycle;
	return DPS;
}