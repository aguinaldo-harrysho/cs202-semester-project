#include <iostream>
#include <fstream>
#include "wav.h"



wav_header readHeader(std::ifstream& file);

wav_header readHeader(std::ifstream &file) {
    std::cout << "I made it here too" << std::endl;
    wav_header header;
    file.read((char*) &header.riff_header, 4);
    std::string riff_header(header.riff_header, 4);
    if (riff_header != "RIFF") {
        std::cout << "Not a RIFF file" << std::endl;
        exit(1);
    }
    file.read((char*) &header.wav_size, 4);
    file.read((char*) &header.wave_header, 4);
    std::string wave_header(header.wave_header, 4);
    if (wave_header != "WAVE") {
        std::cout << "Not a WAVE file" << std::endl;
        exit(1);
    }
    file.read((char*) &header.fmt_header, 4);

    std::string fmt_header(header.fmt_header, 4);
    if (fmt_header != "fmt ") {
        std::cout << "Not a fmt file" << std::endl;
        exit(1);
    }
    file.read((char*) &header.fmt_chunk_size, 4);
    file.read((char*) &header.audio_format, header.fmt_chunk_size);

    file.read((char*) &header.data_header, 4);
    std::string data_header(header.data_header, 4);
    if (data_header != "data") {
        std::cout << "Not a data file" << std::endl;
        exit(1);
    }
    file.read((char*) &header.data_bytes, 4);


    return header;
}