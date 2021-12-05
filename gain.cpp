#include <string>
#include <vector>
#include <iostream>

#include "gain.h"

std::vector<float> Gain::process(std::vector<float> data)
{   
    float scale;

    std::cout << "Please specify a scaling factor for gain adjustment." << std::endl;
    std::cin >> scale;

    for (int i = 0; i < data.size(); i++)
    {
        data[i] = data[i] * scale;
    }

    return data;
}
