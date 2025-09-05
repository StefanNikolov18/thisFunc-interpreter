#pragma once
#include <string>

// @namespace option
/// @brief Contains configuration constants for the program.
namespace option {

	/// @brief The maximum size for the buffer to be read.
	constexpr unsigned BUFFER_MAX_SIZE = 1024;

	/// @brief Flag indicating whether execution should be done from a file.
	constexpr bool WANT_EXECUTE_FROM_FILE = true;

	/// @brief The filename containing executable commands.
	constexpr const char* FILE_EXECUTABLE = "ThisFuncFile.txt";

	
}

