#ifndef WAV_H
#define WAV_H
#include <string>
#include <iostream>
#include <fstream>
#include "wave_header.h"
#include "wave_body.h"

//wav.cpp should be responsible for getting the data that isn't the header. Will likely extend the header in some way.

class Wav {
public:
    static wav_body readBodyData(wav_header, std::string); 
};
 
#endif