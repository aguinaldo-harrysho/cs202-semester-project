#ifndef WAV_H
#define WAV_H
#include <string>
#include "wave_header.h"

//wav.cpp should be responsible for getting the data that isn't the header. Will likely extend the header in some way.

class Wav {
    //wav_header header;
public:
    Wav(const std::string);
    //void printHeader(std::string, wav_header);
};
 
#endif