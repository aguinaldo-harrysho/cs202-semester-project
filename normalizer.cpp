#include <vector>
#include <iostream>
#include <cmath>

#include "wave_body.h"
#include "normalizer.h"

wav_body Normalizer::process(wav_body audiofile_body)
{
    float max = 0.0f;
    float scale;

    for (int i = 0; i<audiofile_body.monoChannel_sounData.size(); i++)
    {
        if (std::abs(audiofile_body.monoChannel_sounData[i]) >= max)
        {
            max = std::abs(audiofile_body.monoChannel_sounData[i]);
        }
    }

    scale = 1 / max;

    for (int i = 0; i < audiofile_body.monoChannel_sounData.size(); i++)
    {
        audiofile_body.monoChannel_sounData[i] = audiofile_body.monoChannel_sounData[i]*scale;
    }

    if (audiofile_body.num_channels == 2){

        for (int i = 0; i<audiofile_body.steroChannel_soundData.size(); i++)
        {
            if (std::abs(audiofile_body.steroChannel_soundData[i]) >= max)
            {
                max = std::abs(audiofile_body.steroChannel_soundData[i]);
            }
        }

        scale = 1 / max;

        for (int i = 0; i < audiofile_body.steroChannel_soundData.size(); i++)
        {
            audiofile_body.steroChannel_soundData[i] = audiofile_body.steroChannel_soundData[i]*scale;
        }

    }

    return audiofile_body;
}