#ifndef READER_H
#define READER_H
#include <string>
#include <iostream>
#include <fstream>
#include "wave_header.h"
 
class Reader {
public:
    static wav_header header;
    static bool read_file(const std::string);
    static bool read_header(const std::string);
};
 
#endif