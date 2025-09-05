#pragma once
#include <string>

#include "../Definitions/Definitions.hpp"

/// @enum TypeInput
/// @brief Represents the type of input line.
enum TypeInput {
    Unknown = -1,   ///< Line type is unknown or empty
    Declaration,    ///< Line is a declaration (contains "<-")
    Execution       ///< Line is an executable command
};

/// @brief Determines the type of input based on its content
/// @param line The input line to analyze.
/// @return The type of the input(Declaration, Execution, or Unknown). 
TypeInput getTypeInput(const std::string& line);

/// @brief Reads lines from a file and executes or stores definitions accordingly.
/// @param fileName The file to read from.
/// @param def Reference to the Definitions object to store declarations.
/// @return True on success, false if a serious error occurs.
bool readFromFile(const std::string& fileName, Definitions& def);

