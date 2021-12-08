#include <iostream>
#include <vector>
#include <string>
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
    std::vector<float>process(std::vector<float> data);
};
