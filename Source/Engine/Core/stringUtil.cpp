#include "StringUtils.h"
#include <algorithm>

// Converts a string to uppercase
std::string ToUpper(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Converts a string to lowercase
std::string ToLower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Compares two strings ignoring case
bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    return std::equal(str1.begin(), str1.end(), str2.begin(),
        [](char a, char b) {
            return tolower(a) == tolower(b);
        });
}
std::string CreateUnique(const std::string& str)
{
    static uint32_t unique = 0;

    return str + std::to_string(unique++);
}
