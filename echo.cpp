#include <iostream>
#include "echo.h"

std::vector<float> Echo::process(std::vector<float> data)
{
	float gain;
	int delay;
	
	std::cout << "Please specify a scaling factor for echo adjustment." << std::endl;
	std::cin >> gain;

	std::cout << "Please specify a delay for echo adjustment." << std::endl;
	std::cin >> delay;

	std::vector<float> output;
	output.reserve(data.size());
	for(int i = 0; i < data.size(); i++)
	{
		if(i > delay) 
		{
			output.push_back(data[i] + gain*output[i - delay]);
		
		} else{
			output.push_back(data[i]);
		}
	}
	
	return output;
}
