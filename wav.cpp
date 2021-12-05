#include <iostream>
#include <fstream>
#include <memory>
#include <bitset>
#include <iomanip>
#include "wav.h"
#include "wave_body.h"

wav_body Wav::combineHeaderAndBody(wav_header audiofile_header, wav_body audiofile_body){
    // For loops are for atrributes that are arrays
    for(int i = 0; i < 4; i++) audiofile_body.riff_header[i] = audiofile_header.riff_header[i]; // char riff_header[4]
    audiofile_body.wav_size = audiofile_header.wav_size; // int wav_size
    for(int i = 0; i < 4; i++) audiofile_body.wave_header[i] = audiofile_header.wave_header[i]; // char wave_header[4]
    for(int i = 0; i < 4; i++) audiofile_body.fmt_header[i] = audiofile_header.fmt_header[i];// char fmt_header[4]
    audiofile_body.fmt_chunk_size = audiofile_header.fmt_chunk_size;// int fmt_chunk_size
    audiofile_body.audio_format = audiofile_header.audio_format;// short audio_format
    audiofile_body.num_channels = audiofile_header.num_channels;// short num_channels
    audiofile_body.sample_rate = audiofile_header.sample_rate;// int sample_rate
    audiofile_body.byte_rate = audiofile_header.byte_rate;// int byte_rate
    audiofile_body.sample_alignment = audiofile_header.sample_alignment;// short sample_alignment
    audiofile_body.bit_depth = audiofile_header.bit_depth;// short bit_depth
    for(int i = 0; i < 4; i++) audiofile_body.data_header[i] = audiofile_header.data_header[i];// char data_header[4]
    audiofile_body.data_bytes = audiofile_header.data_bytes;// int data_bytes

    return audiofile_body;
}

wav_body Wav::readBodyData(wav_header audiofile_header, std::string filename)
{
    wav_body audiofile_body;
    int headerSize = 4 + (8 + audiofile_header.fmt_chunk_size) + 8 + 8; // That last 8 should be 6 but for some reason we started reason part of the header? idk.
    int bodySize = audiofile_header.wav_size - (headerSize - 8);

    

    audiofile_body = combineHeaderAndBody(audiofile_header, audiofile_body);

    if(audiofile_body.num_channels == 1) // Mono channel
    {
        //audiofile_body.bytes.resize(bodySize);
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
            
            //Test Prinout
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

        return audiofile_body;
    }
    else // Stero Channel. This will break horribly if we ever get a WAV that is more than 2 channels
    {
        //Left Channel, then right channel. Alternating sequentially.
        audiofile_body.bytes.resize(bodySize); // If it's stero then we should have an even number of samples
        unsigned char bufferMono[bodySize/2];
        unsigned char bufferStereo[bodySize/2];

        std::ifstream myfile(filename, std::ios::binary | std::ios::in);
        if(myfile.is_open())
        {
            //std::cout << "Before header read" << std::endl;
            myfile.read((char*) &audiofile_header, headerSize);
            //std::cout << "Before body read" << std::endl;
            for(int i = 0; i < bodySize; i++) // Both buffers take turns reading a sample until the end of the data.
            {
                myfile.read((char*) &bufferMono, 1);
                myfile.read((char*) &bufferStereo, 1);
            }
            //std::cout << "After body read" << std::endl;
        }
        
        for(int i = 0; i < (bodySize/2)-155000; i++)
        {
            int intbin = bufferMono[i];
            audiofile_body.monoChannel_sounData.push_back(bufferMono[i]);
            //Test Prinout
            std::cout << audiofile_body.monoChannel_sounData.at(i) << " ";
            if((i-3) % 8 == 0)
            {
                if((i-3) % 16 == 0)
                {
                    std::cout << std::endl;
                }
                else std::cout << "| ";
            }
        }
        for(int i = 0; i < (bodySize/2); i++)
        {
            int intbin = bufferStereo[i];
            audiofile_body.monoChannel_sounData.push_back(bufferStereo[i]);
        }

        return audiofile_body;
    }

    
}