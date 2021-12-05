#include <vector>
#include <iostream>
#include <cmath>

#include "normalizer.h"

std::vector<float> Normalizer::process(std::vector<float> data)
{
    float max = 0.0f;
    float scale;

    for (int i = 0; i<data.size(); i++)
    {
        if (std::abs(data[i]) >= max)
        {
            max = std::abs(data[i]);
        }
    }

    scale = 1 / max;

    for (int i = 0; i < data.size(); i++)
    {
        data[i] = data[i]*scale;
    }

    return data;
}