#pragma once
#include <string>

namespace nc
{
	class StringUtils {
	public:
		// Converts a string to uppercase
		static std::string ToUpper(const std::string& input);

		// Converts a string to lowercase
		std::string ToLower(const std::string& input) const;

		// Compares two strings ignoring case
		static bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);

		// Appends a unique integer to a string
		std::string CreateUnique(const std::string& input) const;
	};
}