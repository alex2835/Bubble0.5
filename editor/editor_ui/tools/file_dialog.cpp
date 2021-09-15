
#include "bubble.h"
#include "file_dialog.h"

namespace Bubble
{
	
	std::string OpenFileDialog(const std::string& filter,
							   const std::string& start_folder)
	{
		nfdchar_t* raw_path = NULL;
		nfdresult_t result = NFD_OpenDialog(filter.c_str(), start_folder.c_str(), &raw_path);

		if (result != NFD_OKAY)
			throw std::runtime_error("Can't open this file");

		std::string out(raw_path);
		free(raw_path);
		return NormalizePath(out);
	}

	std::string SaveFileDialog(const std::string& filter,
							   const std::string& start_folder)
	{
		nfdchar_t* raw_path = NULL;
		nfdresult_t result = NFD_SaveDialog(filter.c_str(), start_folder.c_str(), &raw_path);

		if (result != NFD_OKAY)
			throw std::runtime_error("Can't open this file");

		std::string out(raw_path);
		free(raw_path);
		return NormalizePath(out);
	}

	std::string PickFolderDialog(const std::string& start_folder)
	{
		nfdchar_t* raw_path = NULL;
		nfdresult_t result = NFD_PickFolder(start_folder.c_str(), &raw_path);

		if (result != NFD_OKAY)
			throw std::runtime_error("Can't open this file");

		std::string out(raw_path);
		free(raw_path);
		return NormalizePath(out);
	}

}