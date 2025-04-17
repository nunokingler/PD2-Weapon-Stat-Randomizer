#include "MinMaxMeanModel.hpp"

MinMaxModel::MinMaxModel(StatInfo::StatExtractor st) :extractor { st.extract }
{
	max = std::numeric_limits<float>::min();
	min = std::numeric_limits<float>::max();
	values.clear();
}

void MinMaxModel::updateWithWeapon(const Weapon& w)
{
	auto value = extractor(w);
	max = max > value ? max : value;
	min = min < value ? min : value;
	values.push_back(value);
}

void MinMaxModel::processCurrentType()
{
	auto currentType = minOutput.size();

	minOutput.push_back(min);
	maxOutput.push_back(max);
	meanOutput.push_back(values.size() ? values[values.size() / 2] : 0);

	max = std::numeric_limits<float>::min();
	min = std::numeric_limits<float>::max();
	values.clear();
}

void MinMaxModel::finalize()
{

}
