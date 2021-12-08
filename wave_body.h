#include <string>
#include <vector>
#include <memory>
#include "wave_header.h"

#ifndef WAVE_BODY_WAVE_BODY_H
#define WAVE_BODY_WAVE_BODY_H

typedef struct wav_body: public wav_header
{

    std::vector<char> bytes; // Remainder of wave file is bytes, holds both channels if present
    std::vector<float> monoChannel_sounData; // Holds data for first channel (everything if audio is mono)
    std::vector<float> steroChannel_soundData; // Holds data for second channel (only used when stero)

} wav_body;
#endif //WAVE_BODY_WAVE_BODY_H