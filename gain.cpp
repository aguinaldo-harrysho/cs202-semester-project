#include <string>
#include <vector>
#include <iostream>

#include "wave_body.h"
#include "gain.h"

wav_body Gain::process(wav_body audiofile_body)
{   
    float scale;

    std::cout << "Please specify a scaling factor for gain adjustment." << std::endl;
    std::cin >> scale;

    for (int i = 0; i < audiofile_body.monoChannel_sounData.size(); i++)
    {
        audiofile_body.monoChannel_sounData[i] = audiofile_body.monoChannel_sounData[i] * scale;
    }

    return audiofile_body;
}
