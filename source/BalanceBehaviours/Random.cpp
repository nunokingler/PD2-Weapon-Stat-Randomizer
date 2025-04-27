#pragma once
#include <random>

std::mt19937& GetRNG() {
    static std::mt19937 rng(1234); //for now lets keep the seed the same for debugging purposes
    return rng;
}

int RandomInt(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(GetRNG());
}

float RandomFloat(float low, float high) {
    std::uniform_real_distribution<float> dist(low, high);
    return dist(GetRNG());
}
