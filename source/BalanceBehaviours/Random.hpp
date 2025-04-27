#pragma once
#include <random>

std::mt19937& GetRNG();

int RandomInt(int low, int high);

float RandomFloat(float low, float high);