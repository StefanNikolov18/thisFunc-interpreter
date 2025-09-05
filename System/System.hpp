#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

#include "../LinkedList/LinkedList.hpp"
#include "../Value/Value.hpp"
#include "../Definitions/Definitions.hpp"


using FuncPtrBuildin = Value(*)(const List<Value>& args);
using FuncPtrSpecial = Value(*)(const List<Value>& args);

/// @class System
/// @brief Executes expressions using built-in, special,
/// or user-defined functions
class System
{
private:
	/// @struct FunctionInfoBuildin
	/// @brief Stores information about a built-in function
	struct FunctionInfoBuildin {
		size_t paramCnt;         ///< Number of parameters
		FuncPtrBuildin function; ///< Pointer to the built-in function
	};

	/// @struct FunctionInfoSpecial
	/// @brief Stores information about a special function
	struct FunctionInfoSpecial {
		size_t paramCnt;           ///< Number of parameters
		FuncPtrSpecial function;   ///< Pointer to the special function
	};


	/// @enum FuncType
    /// @brief Types of functions that can be executed
	enum FuncType {
		NotFound, ///< Function not found
		Builtin,  ///< Built-in function
		Special,  ///< Special function
		Defined   ///< User-defined function
	};

public:
	/// @brief Construct System with tokens and definitions
	System(const std::vector<std::string>& tokens,Definitions& defs) :
		tokens(tokens),defs(defs) {
	}

	/// @brief Execute the expression and return its value
	Value execute() const;

private: //Executables
	static void executeBuildinFunction
	(const std::string& key, std::stack<Value>& res);
	static void executeSpecialFunction
	(const std::string& key, std::stack<Value>& res,
		const std::vector<std::string>& tokens = {},const size_t pos = 0);
	static void executeDefinedFunction
	(const std::string& key,std::stack<Value>& res,Definitions& defs);

private: // Special functions
	static void ifLazyEvaluation(const std::vector<std::string>& tokens,
		size_t& pos,std::stack<Value>& res, Definitions& def);
	static size_t listCntParams(const std::vector<std::string>& tokens,
		const size_t pos);
	static void mapEvaluation(const std::vector<std::string>& tokens,
		size_t& pos, std::stack<Value>& res, Definitions& defs);
	static void filterEvaluation(const std::vector<std::string>& tokens,
		size_t& pos, std::stack<Value>& res, Definitions& defs);
private:
	std::vector<std::string> tokens;	///< Tokens to execute
	Definitions& defs;		///< User-defined functions

	///v Map from name to built-in function info
	static std::unordered_map
		<std::string, FunctionInfoBuildin> buildinFuncMap;
	///v Map from name to special function info
	static std::unordered_map
		<std::string, FunctionInfoSpecial> specialFuncMap;


	/// @brief Determine type of function by key
	FuncType findFunctionType(const std::string& key) const;

	/// @brief Replace # with arguments of stack
	static void replaceDSWithParams
	(std::vector<std::string>& tokens,std::stack<Value>& res,
		size_t paramCnt);

	static bool isDigit(char ch);
	static bool isNumber(const std::string& str);
	static bool isNegativeNumber(const std::string& str);

};

