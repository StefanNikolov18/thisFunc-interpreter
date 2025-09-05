#pragma once
#include <vector>
#include <string>


/// @class Parser
/// @brief Splits an input string into tokens for further processing.
class Parser {
public:

	/// @brief Constructs a Parser and tokenizes the given string
	/// @param string Input string to be tokenized
	explicit Parser(const std::string& string);

	/// @brief Retrieves the tokens generated from the input string
	/// @return Reference to the vector of tokens
	const std::vector<std::string>& getTokens() const {
		return this->tokens;
	}

private:
	///< Stores the tokens extracted from input
	std::vector<std::string> tokens;

	/// @brief Splits the input string into tokens
	/// helping for constructor
   /// @param input The string to tokenize
	void tokenize(const std::string& input);
};