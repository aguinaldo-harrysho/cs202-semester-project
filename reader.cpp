#include "reader.h"

// Attempt to open file
bool Reader::read_file(const std::string filename){
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (file.is_open()) return true;
    else return false;
}

// Read file header to determine if WAV
bool Reader::read_header(const std::string filename){
    //Open the file
    std::ifstream myfile;
    myfile.open(filename);

    char riff_header[4]; // Contains "RIFF"
    int wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    char wave_header[4]; // Contains "WAVE"

    std::string riff = ""; // Will be used later for converting char array to string for comparison
    std::string wave = "";

    // Read for "RIFF"
    myfile.read((char*) &riff_header, 4);
    for(int i = 0; i < sizeof(riff_header); ++i) // Convert char array into string for comparison
    {
        riff = riff + riff_header[i];
    }
    if (riff != "RIFF") {
        return false; // If "RIFF" isn't found, return false as this isn't the right kind of file
    }

    myfile.read((char*) &wav_size, 4); // Not neccessary to test for, however the bits need to be read to reach the WAVE bits

    // Read for "WAVE"
    myfile.read((char*) &wave_header, 4);
    for(int i = 0; i < sizeof(wave_header); ++i)
    {
        wave = wave + wave_header[i];
    }
    if (wave != "WAVE") {
        return false; // If "WAVE" isn't found, return false as this isn't the right kind of file
    }

    return true; // If no issues were found when reading the header, return true
}