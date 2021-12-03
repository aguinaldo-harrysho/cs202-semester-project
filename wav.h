#ifndef WAV_H
#define WAV_H
#include <string>
#include "wave_header.h"
 
class Wav {
    //wav_header header;
public:
    Wav(const std::string);
    void printHeader(std::string, wav_header);
};
 
#endif