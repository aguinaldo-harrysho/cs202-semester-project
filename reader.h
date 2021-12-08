#ifndef READER_H
#define READER_H
#include <string>
#include <iostream>
#include <fstream>
#include "wave_header.h"
/**
 * This is the Echo class
 * 
 */
class Reader {
public:

    static wav_header header;
    /**
     * @brief Attempts to open the target file
     * @param filename - the name of the target file to open
     * @return boolean - true or false if the file could be opened
     */
    static bool read_file(const std::string);
    /**
     * @brief Reads in the header of filename into a wav_header object
     * @param filename - the name of the target file to read the header of
     * @return wav_header - Return a wav_header object with attributes filled
     */
    static wav_header read_header(const std::string);
    /**
     * @brief Checks to see if the data in the wav_header object contains data for a WAV file
     * @param header - the wav_header object to check
     * @return boolean -  true or false if the data in header is for a WAV file
     */
    static bool check_header(wav_header);
};

#endif