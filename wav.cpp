#include <iostream>
#include <fstream>
#include <memory>
#include <bitset>
#include <iomanip>
#include "wav.h"
#include "wave_body.h"

/**
 * @brief Combines data from audiofile_header into audiofile_body so that the data can be used easier
 * 
 * @param audiofile_header struct that only holds data fro the header of a WAV file
 * @param audiofile_body struct that holds both header data and body data
 * @return wav_body 
 */
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

//Taking in the already created wav_header and the filename, this function reads the data of the wav file, saving it to a wav_body in one or two flotas depending on number of channels.
wav_body Wav::readBodyData(wav_header audiofile_header, std::string filename)
{
    wav_body audiofile_body; // Where the body data will be saved. audiofile_header's data will also be copied to here.

    int headerSize = 4 + (8 + audiofile_header.fmt_chunk_size) + 8 + 8; // That last 8 should be 6 but for some reason we started reason part of the header? idk.
    int bodySize = audiofile_header.wav_size - (headerSize - 8); // Amount of bytes that make up the audio data.

    // std::cout << bodySize << std::endl;
    // std::cout << audiofile_header.data_bytes << std::endl;
    // std::cout << audiofile_header.wav_size << std::endl;

    unsigned char headerBuffer[headerSize]; // Used to hold header data, not neccessary but useful for debugging when printed out later
    unsigned char buffer[bodySize]; // Will hold the body data.
    

    audiofile_body = combineHeaderAndBody(audiofile_header, audiofile_body); //Combine the data in audiofile_header into audiofile_body so we can just use that to get all data about a WAV
    
    
    std::ifstream myfile(filename, std::ios::binary | std::ios::in); // Open file in binary mode
    if(myfile.is_open())
    {
        myfile.read((char*) &headerBuffer, headerSize); // Read in the header. While saved, it's not useful except for debugging.
        myfile.read((char*) &buffer, bodySize); // Read in each byte of body data into an unisgned char.
    }


    int sampleAmount = 0;
    if(audiofile_body.bit_depth == 8) sampleAmount = bodySize;
    else sampleAmount = bodySize/2;
    unsigned int sampleBuffer[sampleAmount];
    int normalizer = 0;

    
    // Distinguish each byte.
    if(audiofile_body.bit_depth == 8)
    {
        normalizer = -128;
        int intbin; // buffer values will be saved here to convert them to an int.

        for(int i = 0; i < bodySize; i++) // bodySize
        {
                intbin = buffer[i]; // Convert to int to later save to float vector.
                //std::cout << intbin << std::endl;
                //intbin += normalizer;
                //std::cout << intbin << std::endl;
                sampleBuffer[i] = intbin;
                //std::cout << sampleBuffer[i] << std::endl;
                //sampleBuffer[i] -= 128; // Data will range from -128 to 127
                //std::cout << sampleBuffer[i] << std::endl;
        }

    }
    else if(audiofile_body.bit_depth == 16) // Program will either do nothing or break if we ever get a bit depth that isn't 8 or 16.
    {
        normalizer = -32768;
        unsigned int intbin; // buffer values will be saved here to convert them to an int.
        //std::bitset<16> foo;
        std::bitset<8> test1;
        std::bitset<8> test2;

        int position = -1;
        for(int i = 0; i < sampleAmount; i++) //0,2,4,6
        {
            position++;
            test1 = buffer[position];
            test2 = buffer[position+1];
            //foo = buffer[position] + buffer[position+1];
            //std::string tester1 = test1.to_string();
            //std::string tester2 = test2.to_string();
            //std::string appender = tester1 + tester2;
            std::bitset<16> foo(test1.to_string() + test2.to_string());
            //std::cout << foo << std::endl;
            position++;
            intbin = (int)(foo.to_ulong());
            //intbin += normalizer;
            sampleBuffer[i] = intbin; //0,1,2,3
            //sampleBuffer[i] -= 32768; // Data will range from -32,768 to 32,767
        }
        
    }
    if(audiofile_body.num_channels == 1) // Mono
    {
        
        for(int i = 0; i < sampleAmount; i ++) // sampleAmount
        {
            //sampleBuffer[i] += normalizer; // Data will range from -32,768 to 32,767
            int normalizeHolder = normalizer;
            normalizeHolder = (int)sampleBuffer[i] + normalizer;
            audiofile_body.monoChannel_sounData.push_back(normalizeHolder); // Save to float vector.
            //std::cout << audiofile_body.monoChannel_sounData.at(i);

        }
        
    }
    else if(audiofile_body.num_channels == 2) // Stero
    {
        if(audiofile_body.bit_depth == 8)
        {
            int channelLength = sampleAmount/2; 
            unsigned char bufferMono[channelLength]; // In stero, the size of these buffers should be half the amount of samples.
            unsigned char bufferStereo[channelLength];
            int position = -1;
            //std::cout << sampleBuffer[1] << std::endl;
            for(int i = 0; i < channelLength; i++)
            {
                position++;
                //sampleBuffer[position] += normalizer;
                bufferMono[i] = sampleBuffer[position]; // First sample saved to mono channel
                position++;
                //sampleBuffer[position] += normalizer;
                bufferStereo[i] = sampleBuffer[position]; // Second sample saved to stero channel
            }
            //std::cout << "I made it here" << std::endl;
            for(int i = 0; i < channelLength; i++)
            {
                //bufferMono[i] += normalizer; // Data will range from -128 to 127
                //bufferStereo[i] += normalizer;
                audiofile_body.monoChannel_sounData.push_back(bufferMono[i]);
                audiofile_body.steroChannel_soundData.push_back(bufferStereo[i]);
            }
        }
        else if(audiofile_body.bit_depth == 16)
        {
            int channelLength = sampleAmount/2; 
            unsigned int intbin1;
            unsigned int intbin2;
            //unsigned char bufferMono[channelLength]; // In stero, the size of these buffers should be half the amount of samples.
            //unsigned char bufferStereo[channelLength];
            std::bitset<16> test1;
            std::bitset<16> test2;
            int positioner = -1;
            //std::cout << sampleBuffer[1] << std::endl;
            for(int i = 0; i < channelLength; i++)
            {
                positioner++;
                test1 = sampleBuffer[positioner]; // First sample saved to mono channel
                positioner++;
                test2 = sampleBuffer[positioner]; // Second sample saved to stero channel
                intbin1 = (int)(test1.to_ulong());
                intbin2 = (int)(test2.to_ulong());
                //intbin1 -= normalizer; // Data will range from -32,768 to 32,767
                //intbin2 -= normalizer;
                audiofile_body.monoChannel_sounData.push_back(intbin1);
                audiofile_body.steroChannel_soundData.push_back(intbin2);
            }
            //std::cout << "I made it here" << std::endl;
            // for(int i = 0; i < channelLength; i++)
            // {
                
            // }

             // buffer values will be saved here to convert them to an int.
            //std::bitset<16> foo;
            
            

            // int position = -1;
            // for(int i = 0; i < sampleAmount; i++) //0,2,4,6
            // {
            //     position++;
            //     test1 = buffer[position];
            //     test2 = buffer[position+1];
            //     //foo = buffer[position] + buffer[position+1];
            //     //std::string tester1 = test1.to_string();
            //     //std::string tester2 = test2.to_string();
            //     //std::string appender = tester1 + tester2;
            //     std::bitset<16> foo(test1.to_string() + test2.to_string());
            //     //std::cout << foo << std::endl;
            //     position++;
                
            //     sampleBuffer[i] = intbin; //0,1,2,3
            // }

        }
        
    }

    //Test Prinout
    // for(int i = 0; i < headerSize; i++) //headerSize
    // {
    //     int intbin = headerBuffer[i];
    //     std::cout << std::setfill ('0') << std::setw(2) << std::hex << intbin << " " << std::dec;
    //     if( (i+1) % 8 == 0)
    //     {
    //         if( (i+1) % 16 == 0)
    //         {
    //             std::cout << std::endl;
    //         }
    //         else std::cout << "| ";
    //     }
    // }
    // int position = -1;
    // for(int i = 0; i < 68; i++)
    // {
    //     //int intbin = buffer[i];
    //     int intbin = audiofile_body.monoChannel_sounData.at(i);
    //     std::cout << std::setfill('0') << std::setw(4) << std::hex << intbin << " " << std::dec;
    //     intbin = audiofile_body.steroChannel_soundData.at(i);
    //     std::cout << std::setfill('0') << std::setw(4) << std::hex << intbin << " " << std::dec;
    //     if((i) % 2 == 0)
    //     {
    //         if((i) % 4 == 0)
    //         {
    //             std::cout << std::endl;
    //         }
    //         else std::cout << "| ";
    //     }
    // }
    
    return audiofile_body;
}

void Wav::writeAudiofile(wav_body audiofile_body, std::string filename) //Save a wav_body as an actual playable wav file
{
    int headerSize = 4 + (8 + audiofile_body.fmt_chunk_size) + 8 + 8; // That last 8 should be 6 but for some reason we started reason part of the header? idk.
    int bodySize = audiofile_body.wav_size - (headerSize - 8); // Amount of bytes that make up the audio data.
    std::string writer;
    
    //filename
    std::ofstream myfile("output.wav", std::ios::binary);
    //std::ofstream myfile("example.txt", std::ios::binary | std::ios::in);
    //myfile.open();

    int sampleAmount = bodySize;
    if(audiofile_body.bit_depth == 8) int sampleAmount = bodySize;
    else int sampleAmount = bodySize/2;

    int newSize = audiofile_body.monoChannel_sounData.size();

    //Header writing code, bit_depth and num_channels don't matter for this. wav_size and data_btes need to be modified if an effect like echo made the vector longer.
    myfile.write(audiofile_body.riff_header, 4);
    myfile.write((char*) &audiofile_body.wav_size, 4); // Change as needed
    myfile.write(audiofile_body.wave_header, 4);
    myfile.write(audiofile_body.fmt_header, 4);
    myfile.write((char*) &audiofile_body.fmt_chunk_size, 4);
    myfile.write((char*) &audiofile_body.audio_format, 2);
    myfile.write((char*) &audiofile_body.num_channels, 2);
    myfile.write((char*) &audiofile_body.sample_rate, 4);
    myfile.write((char*) &audiofile_body.byte_rate, 4);
    myfile.write((char*) &audiofile_body.sample_alignment, 2);
    myfile.write((char*) &audiofile_body.bit_depth, 2);
    myfile.write(audiofile_body.data_header, 4);
    myfile.write((char*) &audiofile_body.data_bytes, 4); // Change as needed

    //Header writing seems to work flawlessly but the body writing is having issues. Possible has something to with how it's converted when writen.
    int unNormalizer = 0;
    if(audiofile_body.bit_depth == 8) unNormalizer = 128;
    else unNormalizer = 32768;

    if(audiofile_body.num_channels == 1)
    {
        std::cout << "Mono" << std::endl;
        int tempest = audiofile_body.monoChannel_sounData.at(0);
        unsigned int tempor = audiofile_body.monoChannel_sounData.at(0) + 128;;
        // std::cout << std::dec;
        // std::cout << "Vector value: ";
        // std::cout << audiofile_body.monoChannel_sounData.at(0) << std::endl;
        // std::cout << "Unsigned Int: ";
        // std::cout << tempor << std::endl;
        // std::string tempors = std::bitset<8>(tempor).to_string();
        // std::cout << "String: ";
        // std::cout << tempors << std::endl;
        // std::cout << "Char cast: ";
        // std::cout << (char*) &tempor << std::endl;


        for(int i = 0; i < sampleAmount; i++)//sampleAmount
        {
            int tempory = (int)audiofile_body.monoChannel_sounData.at(i) + unNormalizer;
            //std::cout << audiofile_body.monoChannel_sounData.at(i) << std::endl;
            //std::cout << unNormalizer << std::endl;
            // std::cout << "tempory: ";
            // std::cout << tempory << std::endl;
            unsigned int intbin = audiofile_body.monoChannel_sounData.at(i) + unNormalizer;
            // std::cout << "Unsigned: ";
            // std::cout << intbin << std::endl;
            //std::string writer;// = std::bitset<8>(intbin).to_string();
            //int tempor = audiofile_body.monoChannel_sounData.at(i) 
            
            if(audiofile_body.bit_depth == 8) 
            {
                //writer = std::bitset<8>(intbin).to_string();
                myfile.write((char*) &intbin, 1);
            }
            else 
            {
                //writer = std::bitset<16>(intbin).to_string();
                myfile.write((char*) &intbin, 1);
            }
            
        }
    }
    else
    {
        std::cout << "Stereo" << std::endl;
        //int positioner = -1;
        for(int i = 0; i < sampleAmount/2; i++)
        {
            //positioner++;
            unsigned int intbin = audiofile_body.monoChannel_sounData.at(i);
            unsigned int intbin1 = audiofile_body.steroChannel_soundData.at(i);
            std::string writer;// = std::bitset<8>(intbin).to_string();
            std::string writer1;
            
            if(audiofile_body.bit_depth == 8)
            {
                writer = std::bitset<8>(intbin).to_string();
                writer1 = std::bitset<8>(intbin1).to_string();
            }
            else 
            {
                writer = std::bitset<16>(intbin).to_string();
                writer1 = std::bitset<16>(intbin1).to_string();
            }
            myfile << writer << writer1;
        }
    }
    
    // std::cout << audiofile_body.monoChannel_sounData.at(0) << std::endl;
    // std::cout << intbin << std::endl;
    // std::cout << writer << std::endl;

    
    myfile.close();
}
