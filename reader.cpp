#include "reader.h"

// Attempt to open file
bool Reader::read_file(const std::string filename){
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (file.is_open()) return true;
    else return false;
}

// Read file header to determine if WAV
bool Reader::read_header(const std::string filename){
    return true; // For testing while I figure out the actual implementaton
}