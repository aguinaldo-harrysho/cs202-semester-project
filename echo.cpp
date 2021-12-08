#include <iostream>
#include "echo.h"

wav_body Echo::process(wav_body audiofile_body)
{
	float gain;
	int delay;
	
	std::cout << "Please specify a scaling factor for echo adjustment." << std::endl;
	std::cin >> gain;

	std::cout << "Please specify a delay for echo adjustment." << std::endl;
	std::cin >> delay;

	//std::vector<float> output;
	//output.reserve(audiofile_body.monoChannel_sounData.size());
	std::cout << "After Delay input" << std::endl;
	std::cout << "Size: " << audiofile_body.monoChannel_sounData.size() << std::endl;
	int stopSize = audiofile_body.monoChannel_sounData.size();
	for(int i = 0; i < stopSize; i++)
	{
		//std::cout << i << std::endl;
		if(i > delay) 
		{
			audiofile_body.monoChannel_sounData.push_back(audiofile_body.monoChannel_sounData[i] + gain*audiofile_body.monoChannel_sounData[i - delay]);
		
		} else{
			audiofile_body.monoChannel_sounData.push_back(audiofile_body.monoChannel_sounData[i]);
		}
	}
	
	return audiofile_body;
}
