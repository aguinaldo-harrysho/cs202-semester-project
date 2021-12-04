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
    //std::cout << headerSize << std::endl;

    audiofile_body.bytes.resize(bodySize);
    //std::vector<char> buffer;// = audiofile_body.bytes;
    //unsigned char* buffer = new unsigned char[bodySize];
    unsigned char buffer[bodySize];
    //std::cout << "bodySize: ";
    //std::cout << bodySize << std::endl;
    std::ifstream myfile(filename, std::ios::binary | std::ios::in);
    //std::cout << "Before file open" << std::endl;
    if(myfile.is_open())
    {
        //std::cout << "Before header read" << std::endl;
        myfile.read((char*) &audiofile_header, headerSize);
        //std::cout << "Before body read" << std::endl;
        myfile.read((char*) &buffer, bodySize);
        //std::cout << "After body read" << std::endl;
    }
    
    //std::cout << "After file open" << std::endl;
    //std::cout << "Print buffer" << std::endl;
    //std::cout << buffer << std::endl;
    //std::cout << "Before for loop" << std::endl;
    
    //bodySize
    //std::cout << "I made it" << std::endl;
    //std::vector<int> soundData;
    
    for(int i = 0; i < bodySize; i++) // - 31999
    {
        //std::cout << i + " ";// << std::endl;
        //std::cout << static_cast<unsigned>(buffer[i]) << std::endl;
        
        // std::bitset<8> x(buffer[i]);
        // std::cout << x << "\n";

        int intbin = buffer[i];
        audiofile_body.monoChannel_sounData.push_back(buffer[i]);
        
        // Test Prinout
        // std::cout << audiofile_body.monoChannel_sounData.at(i) << " ";
        // if((i-3) % 8 == 0)
        // {
        //     if((i-3) % 16 == 0)
        //     {
        //         std::cout << std::endl;
        //     }
        //     else std::cout << "| ";
        // }
    }
    std::cout << std::endl;
    //std::string tester(reinterpret_cast<char*>(buffer));
    //std::cout << tester << std::endl;

    return audiofile_body;
}