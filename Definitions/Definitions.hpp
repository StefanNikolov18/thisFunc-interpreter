#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

/// @class Definitions
/// @brief Stores and manages user-defined 
/// functions and their information.
class Definitions
{
private:
	/// @struct FunctionDefInfo
   /// @brief Holds the parameter count and tokenized body of a function.
	struct FunctionDefInfo {
		size_t paramsCnt;			///< Number of parameters of the function
		std::vector<std::string> tokens;///< Tokens representing the function body
	};
public:
	/// @brief Default constructor
	Definitions() = default;

	/// @brief Loads definitions from an input stream
	/// @param is Input stream to read definitions from
	void loadFromStream(std::istream& is);

	/// @brief Checks if a definition exists
	bool isDefined(const std::string& def) const;


	/// @brief Retrieves the tokenized definition by name
	/// @param key: Name of the definition
	/// @return Reference to the vector of tokens
	const std::vector<std::string>& 
		findDefinition(const std::string& key) const;

	/// @brief Retrieves the number of parameters for a definition
   /// @param key Name of the definition
   /// @return Number of parameters
	const size_t findParams(const std::string& key) const;

	/// @brief Inserts a new function definition from a line of code
   /// @param line Line containing the function definition
	void insertNewDefinition(const std::string& line);

private:
	///< Map of function names to their definitions
	std::unordered_map
		<std::string, FunctionDefInfo> defFuncMap;

	/// @brief Extracts the name of a function from a line
	/// helping for insertNewDefinition(line)
   /// @param line Line containing the function definition
   /// @return Function name
	static std::string extractName(const std::string& line);

	/// @brief Extracts tokens of a function from a line
	/// helping for insertNewDefinition(line)
	/// @param line Line containing the function definition
	/// @return Vector of tokens
	static std::vector<std::string> extractDef(const std::string& line);

	/// @brief Extracts the number of parameters of a function from a line
	///  helping for insertNewDefinition(line)
   /// @param line Line containing the function definition
   /// @return Number of parameters
	static size_t extractParamCount(const std::string& line);
};

