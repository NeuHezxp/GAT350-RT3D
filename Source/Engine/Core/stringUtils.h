#pragma once
#include <string>

// Converts a string to uppercase
std::string ToUpper(const std::string& input);

// Converts a string to lowercase
std::string ToLower(const std::string& input);

// Compares two strings ignoring case
bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);

// Appends a unique integer to a string
std::string CreateUnique(const std::string& input);