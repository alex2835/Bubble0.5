#pragma once

#include "nfd.h"
#include <string>
#include <stdexcept>

namespace Bubble
{
    inline std::string ReplaceAll(std::string str, const std::string& from, const std::string& to)
    {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }

    inline std::string NormalizePath(const std::string& path)
    {
        return ReplaceAll(path, "\\", "/");
    }

	// Filter
	//### Separators ###
	//
	//	- `;` Begin a new filter.
	//		- `,` Add a separate type to the filter.
	//
	//#### Examples ####
	//
	//		`txt` The default filter is for text files.There is a wildcard option in a dropdown.
	//		`png,jpg; psd` The default filter is for pngand jpg files.A second filter is available for psd files.There is a wildcard option in a dropdown.
	//		`NULL` Wildcard only.

	std::string OpenFileDialog(const std::string& filter = std::string(),
							   const std::string& start_folder = std::string());

	std::string SaveFileDialog(const std::string& filter = std::string(),
							   const std::string& start_folder = std::string());

	std::string PickFolderDialog(const std::string& start_folder = std::string());

}