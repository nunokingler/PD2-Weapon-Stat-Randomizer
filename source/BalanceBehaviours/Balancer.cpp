#include "Balancer.hpp"

float Balancer::CalculateDps(const Weapon& w) {
	auto fullCycle = (w.magSize * w.rof) + w.reloadSpeed;
	if (w.reloadSpeed <= 0.0001f)return 0.0f;
	auto DPS = w.damage * w.magSize / fullCycle;
	return DPS;
}