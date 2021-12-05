#ifndef ECHO_H
#define ECHO_H
#include <vector>

class Echo
{

public:
	static std::vector<float> process(const std::vector<float>& input, float gain, int delay);
};

#endif
