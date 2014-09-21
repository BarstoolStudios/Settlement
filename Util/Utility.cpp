#include <vector>
#include <string>
#include "Util/Utility.h"

//==============================================================================
// Returns True When Distance from (x1, y1) to (x2, y2) is < threshold
//==============================================================================
bool Utility::distThreshold(float x1, float y1, float x2, float y2, float threshold) {
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (threshold * threshold);
}

//==============================================================================
// Returns True if str Begins With beg
//==============================================================================
bool Utility::stringStartsWith(std::string& str, std::string beg) {
	if(beg.size() > str.size())
		return false;

	for(int i = 0; i < beg.size(); i++) {
		if(str[i] != beg[i])
			return false;
	}

	return true;
}

//==============================================================================
// Splits str by Delimiter delim and Stores in result
//==============================================================================
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