#include <string>
#include <vector>
#include <math.h>
using namespace std;
std::string tweakLetters(std::string s, std::vector<int> arr) {
	for (size_t i = 0; i < s.length(); i++) {
		char c = s[i];
        c += arr[i];
        c = std::min((int)c, 97);
	}
}