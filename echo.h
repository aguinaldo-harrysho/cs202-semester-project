#ifndef ECHO_H
#define ECHO_H
#include <vector>
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
	static std::vector<float> process(std::vector<float> data);
};

#endif
