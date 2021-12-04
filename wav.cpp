#include <iostream>
#include <fstream>
#include <memory>
#include <bitset>
#include <iomanip>
#include "wav.h"
#include "wave_body.h"

wav_body Wav::readBodyData(wav_header audiofile_header, std::string filename)
{
    wav_body audiofile_body;
    int headerSize = 4 + (8 + audiofile_header.fmt_chunk_size) + 8 + 6;
    int bodySize = audiofile_header.wav_size - (headerSize - 8);

    audiofile_body.bytes.resize(bodySize);
    unsigned char buffer[bodySize];

    std::ifstream myfile(filename, std::ios::binary | std::ios::in);
    if(myfile.is_open())
    {
        //std::cout << "Before header read" << std::endl;
        myfile.read((char*) &audiofile_header, headerSize);
        //std::cout << "Before body read" << std::endl;
        myfile.read((char*) &buffer, bodySize);
        //std::cout << "After body read" << std::endl;
    }
    
    for(int i = 0; i < bodySize; i++)
    {
        int intbin = buffer[i];
        audiofile_body.monoChannel_sounData.push_back(buffer[i]);
        
        /*Test Prinout
        std::cout << audiofile_body.monoChannel_sounData.at(i) << " ";
        if((i-3) % 8 == 0)
        {
            if((i-3) % 16 == 0)
            {
                std::cout << std::endl;
            }
            else std::cout << "| ";
        }*/
    }

    return audiofile_body;
}