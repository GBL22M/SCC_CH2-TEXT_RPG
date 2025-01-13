#include "RandomIntGenerator.h"

int GetRandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);

    return dist(gen);
}