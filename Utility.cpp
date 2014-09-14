#include <vector>
#include <string>
#include "Utility.h"

bool Utility::distThreshold(float x1, float y1, float x2, float y2, float threshold) {
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (threshold * threshold);
}

bool Utility::stringStartsWith(std::string& str, std::string beg) {
	if(beg.size() > str.size())
		return false;

	for(int i = 0; i < beg.size(); i++) {
		if(str[i] != beg[i])
			return false;
	}

	return true;
}

void Utility::stringSplit(std::string& str, char delim, std::vector<std::string>& result) {

	int prevLoc = 0;

	for(int i = 0; i < str.size(); i++) {
		if(str[i] == delim) {
			result.push_back(str.substr(prevLoc, i - prevLoc));
			prevLoc = i + 1;
		}
	}

	result.push_back(str.substr(prevLoc));

}