#ifndef WAV_H
#define WAV_H
#include <string>
#include <iostream>
#include <fstream>
#include "wave_header.h"
#include "wave_body.h"

/**
 * @brief This is the Wav class. Responsible for reading in and saving Wav data
 * 
 */
class Wav {
public:
    /**
     * @brief pulls the data from a wav_header into a wav_body
     * @param audiofile_header - the wav_header object to pull from
     * @param audiofile_body - the wav_body object to add wav_header data to
     * @return wav_body - the wav_body object with header data
     */
    static wav_body combineHeaderAndBody(wav_header, wav_body);
    /**
     * @brief creates a wav_body object with the audio data from the Wav file
     * @param audiofile_header - the wav_header data of the file you wish to read from
     * @param filename - the file to read audio data from
     * @return wav_body - a wav_body object with header and body (audio) data
     */
    static wav_body readBodyData(wav_header, std::string);
    /**
     * @brief saves and write data of a wav_body into a usable wav file
     * @param audiofile_body - the wav_body data you wish to write into a file
     * @param filename - the name of the file you wish to save it as
     */
    static void writeAudiofile(wav_body, std::string); //Save a wav_body as an actual playable wav file
};
 
#endif
