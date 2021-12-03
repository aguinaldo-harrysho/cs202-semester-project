#include <iostream>
#include <fstream>
#include "wav.h"

Wav::Wav(const std::string filename)
{
    wav_header header;
    //std::cout << header.test << std::endl;
    //readHeader(filename);
    printHeader(filename, header);
}

void Wav::printHeader(std::string file, wav_header wavHeader)
{
    std::ifstream myfile;
    myfile.open(file);

    myfile.read((char*) &wavHeader.riff_header, 4); // "RIFF" Header
    myfile.read((char*) &wavHeader.wav_size, 4); // Size of the entire file
    myfile.read((char*) &wavHeader.wave_header, 4); // "WAVE" Header
    myfile.read((char*) &wavHeader.fmt_header, 4);
}


// wav_header readHeader(std::ifstream &file)
// {
//     wav_header header;

//     std::string fmt_header(header.fmt_header, 4);
//     if (fmt_header != "fmt ") {
//         std::cout << "Not a fmt file" << std::endl;
//         exit(1);
//     }
//     file.read((char*) &header.fmt_chunk_size, 4);
//     file.read((char*) &header.audio_format, header.fmt_chunk_size);

//     file.read((char*) &header.data_header, 4);
//     std::string data_header(header.data_header, 4);
//     if (data_header != "data") {
//         std::cout << "Not a data file" << std::endl;
//         exit(1);
//     }
//     file.read((char*) &header.data_bytes, 4);


//     return header;
// }
