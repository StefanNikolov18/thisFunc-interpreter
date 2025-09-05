#include "Parser.hpp"

#include <stack>
#include <stdexcept>
#include "../Options/Options.hpp"


bool isValidBracketsSequence(const std::string& str) {
	std::stack<char> s;
	for (std::string::const_iterator it = str.begin();
			it != str.end();++it) {
		if (*it == '(')
			s.push(*it);
		else if (*it == ')') {
			if (s.empty())
				return false;

			s.pop();
		}
	}

	return s.empty();
}

Parser::Parser(const std::string& str):
	tokens({})
{
	if (str.size() >= option::BUFFER_MAX_SIZE)
		throw std::invalid_argument("Input string is too big!");

	if (!isValidBracketsSequence(str))
		throw std::invalid_argument("Input string has invalid brackets!");

	this->tokenize(str);

}

void Parser::tokenize(const std::string& input)
{

	std::string temp{};
	for (std::string::const_iterator it = input.begin();
		it != input.end();++it) {

		if (*it == '(' || *it == ')' || *it == ',') {
			if (!temp.empty()) {
				this->tokens.push_back(temp);
				temp.clear();
			}

			this->tokens.push_back(std::string(1, *it));
		}
		else if (isspace(static_cast<unsigned char>(*it))) {
			//
		}
		else {
			temp.push_back(*it);
		}

	}

	if(!temp.empty())
		this->tokens.push_back(temp);
}
