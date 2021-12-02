#include <iostream>
#include <fstream>
#include "wave_header.h"

wav_header readHeader(std::ifstream& file);

// Reads the file
void readFile(const std::string &fileName){
    std::ifstream file(fileName, std::ios::binary | std::ios::in);
    if (file.is_open()) {
        auto header = readHeader(file);
        auto buffer = new unsigned char[header.data_bytes];
        file.read(( char*) buffer, header.data_bytes);
        file.close();
    }
}

// Reads the header of the file
wav_header readHeader(const std::string& fileName){
    std::cout << "I made it here" << std::endl;
    std::ifstream file(fileName, std::ios::binary | std::ios::in);
    wav_header header;
    if (file.is_open()) {
        file.read(( char*) &header, sizeof(header));
        file.close();
    }
    return header;
}

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