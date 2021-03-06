#ifndef ECHO_H
#define ECHO_H
#include <vector>
#include "wave_body.h"
/**
 * This is the Echo class
 * 
 */
class Echo
{

public:
	/**
	* @brief Processor that adds an Echo
	* 
	* @param data - Samples from the data section of the input file.
	*/
	static wav_body process(wav_body);
};

#endif
