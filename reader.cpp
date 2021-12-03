#include "reader.h"

// Attempt to open file
bool Reader::read_file(const std::string filename){
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (file.is_open()) return true;
    else return false;
}

// Only reads the header of the specified file. No Validation
wav_header Reader::read_header(const std::string filename){
    std::ifstream myfile;
    myfile.open(filename);

    wav_header header;
    // RIFF Header
    myfile.read((char*) &header.riff_header, 4); // "RIFF"
    myfile.read((char*) &header.wav_size, 4); // Size of the WAV portion of file
    myfile.read((char*) &header.wave_header, 4); // "WAVE"
    // Format Header
    myfile.read((char*) &header.fmt_header, 4); // "fmt "
    myfile.read((char*) &header.fmt_chunk_size, 4); // Size of the following subchunk, should be 16
    myfile.read((char*) &header.audio_format, 2); // 1 for PCM or 3 for IEEE float
    myfile.read((char*) &header.num_channels, 2); // Either 1 or 2 for mono or stereo
    myfile.read((char*) &header.sample_rate, 4); // 8000, 441000, etc.
    myfile.read((char*) &header.byte_rate, 4); // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    myfile.read((char*) &header.sample_alignment, 2); // num_channels * Bytes Per Sample
    myfile.read((char*) &header.bit_depth, 2); // Number of bits per sample
    // Data
    myfile.read((char*) &header.data_header, 4); // "data"
    myfile.read((char*) &header.data_bytes, 4); // Number of bytes in the data, NumSamples * NumChannels * BitsPerSample/8
    // The actual sound data would be beyond this but we don't need it for the purpose of validation

    return header;
    
}

// Read file header to determine if WAV
bool Reader::check_header(wav_header header){
    // Will be used later for converting char array to string for comparison
    std::string riff = ""; 
    std::string wave = "";
    std::string fmt_ = "";
    std::string data = "";

    // Check for "RIFF"
    for(int i = 0; i < sizeof(header.riff_header); ++i) // Convert char array into string for comparison
    {
        riff = riff + header.riff_header[i];
    }
    if (riff != "RIFF") {
        return false; // If "RIFF" isn't found, return false as this isn't the right kind of file
    }

    // Check for "WAVE"
    for(int i = 0; i < sizeof(header.wave_header); ++i)
    {
        wave = wave + header.wave_header[i];
    }
    if (wave != "WAVE") {
        return false; // Return false if "WAVE" isn't present
    }
    
    // Check for "fmt "
    for(int i = 0; i < sizeof(header.fmt_header); ++i)
    {
        fmt_ = fmt_ + header.fmt_header[i];
    }
    if (fmt_ != "fmt ") {
        return false; // Return false if "fmt " isn't present
    }

    // Check for "data"
    for(int i = 0; i < sizeof(header.data_header); ++i)
    {
        data = data + header.data_header[i];
    }
    if (data != "data") {
        return false; // Return false if "data" isn't present
    }


    return true; // If no issues were found when checking the header, return true
}