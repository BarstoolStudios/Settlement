#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

namespace Utility {
	bool distThreshold(float x1, float y1, float x2, float y2, float threshold);

	bool stringStartsWith(std::string& str, std::string beg);

	void stringSplit(std::string& str, char delim, std::vector<std::string>& result);

	void exitOnGLError(std::string errorMessage);

	void printToOutput(std::string str);

	template<class T> inline void remove(std::vector<T>& vec, const T& elem) {
		vec.erase(find(vec.begin(), vec.end(), elem));
	}

	template<class T> inline T find(const std::vector<T>& vec, const T& elem) {
		return *find(vec.begin(), vec.end(), elem);
	}

	template<class T> inline bool contains(const std::vector<T>& vec, const T& elem) {
		return std::find(vec.begin(), vec.end(), elem) != vec.end();
	}
}

#endif