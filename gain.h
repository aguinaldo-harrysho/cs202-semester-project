#include <iostream>
#include <vector>
#include <string>
#include "wave_body.h"
/**
 * This is the Gain class
 * 
 */
class Gain
{
    public:
    /**
     * @brief Processor that adjusts the gain
     * 
     * @param data - Samples from the data section of the input file.
     */
    static wav_body process(wav_body audiofile_body);
};
