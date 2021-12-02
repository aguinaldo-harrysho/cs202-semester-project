#ifndef WAV_H
#define WAV_H
#include <string>
#include "wave_header.h"
 
class Wav {
    wav_header header;
    bool isValid;
public:
    Wav() = default;
    bool read_file(const std::string);
};
 
#endif