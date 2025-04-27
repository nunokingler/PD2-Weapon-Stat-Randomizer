#pragma once
#include "IModel.hpp"
#include "../WeaponCore/Weapon.hpp"
#include "../WeaponCore/Stat.hpp"
#include <vector>

template <Stat ModeledStat>
class MinMaxModel :public IModel{

public:
    MinMaxModel();
    // Process each weapon once as part of an ongoing pass:
    void updateWithWeapon(const Weapon& w) override;
    void processCurrentType() override;
    // Once all weapons have been processed, finalize the fitting:
    void finalize() override;

	float getMin(WeaponType type) const { return minOutput.at(static_cast<size_t>(type)); }
	float getMax(WeaponType type)const { return maxOutput.at(static_cast<size_t>(type)); }
	float getMean(WeaponType type) const { return meanOutput.at(static_cast<size_t>(type)); }
private:
    float min{}, max{};
    std::vector<float> values;
    //outputs
    std::vector<float> minOutput, maxOutput, meanOutput;
};

template <Stat ModeledStat>
MinMaxModel<ModeledStat>::MinMaxModel()
{
	auto weaponTypeCount = static_cast<size_t>(WeaponType::count);
	minOutput.reserve(weaponTypeCount);
	maxOutput.reserve(weaponTypeCount);
	meanOutput.reserve(weaponTypeCount);
	max = std::numeric_limits<float>::min();
	min = std::numeric_limits<float>::max();
	values.clear();
}

template <Stat ModeledStat>
void MinMaxModel<ModeledStat>::updateWithWeapon(const Weapon& w)
{
	auto extractor = StatInfo::statExtractorMap.at(ModeledStat)->extract;
	auto value = extractor(w);
	max = max > value ? max : value;
	min = min < value ? min : value;
	values.push_back(value);
}

template <Stat ModeledStat>
void MinMaxModel<ModeledStat>::processCurrentType()
{
	auto currentType = minOutput.size();

	minOutput.push_back(min);
	maxOutput.push_back(max);
	meanOutput.push_back(values.size() ? values[values.size() / 2] : 0);

	max = std::numeric_limits<float>::min();
	min = std::numeric_limits<float>::max();
	values.clear();
}

template <Stat ModeledStat>
void MinMaxModel<ModeledStat>::finalize()
{
	processCurrentType();
}