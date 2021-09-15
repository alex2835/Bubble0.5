#pragma once

#include <string>
#include <locale> 
#include <codecvt>

using namespace std::string_literals;

inline std::string to_string(const std::wstring& str)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(str);
}

template <typename StringType>
StringType ReplaceAll(StringType str, const StringType& from, const StringType& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != StringType::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

inline std::string NormalizePath(const std::string& path)
{
	return ReplaceAll(path, "\\"s, "/"s);
}

inline std::string NormalizePath(const std::wstring& path)
{
	return ReplaceAll(to_string(path), "\\"s, "/"s);
}