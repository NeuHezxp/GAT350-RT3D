#include <algorithm>
#include <Core/StringUtils.h>

namespace nc {

	// Converts a string to uppercase
	std::string StringUtils::ToUpper(const std::string& input)
	{
		std::string result = input;
		std::transform(result.begin(), result.end(), result.begin(), ::toupper); //start at the front to the end and convert each character to uppercase
		return result;
	}

	std::string StringUtils::ToLower(const std::string& input) const
	//converts string to lowercase
	{
		std::string result = input;
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}

	bool StringUtils::IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
	{
		if (str1.length() != str2.length()) {
			return false;
		}
		return std::equal(str1.begin(), str1.end(), str2.begin(),
			[](char a, char b) {
				return tolower(a) == tolower(b);
			});
		
	}
	std::string StringUtils::CreateUnique(const std::string& str) const
	{
		static uint32_t unique = 0;

		return str + std::to_string(unique++);
	}
}