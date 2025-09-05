#include "System.hpp"

#include <stack>

#include "../Builtins/Builtins.hpp"
#include "../SpecialFuncs/SpecialFuncs.hpp"

std::unordered_map
<std::string, System::FunctionInfoBuildin> System::buildinFuncMap = {
	{"add",{2,&builtin::add}},
	{"sub",{2,&builtin::sub}},
	{"mul",{2,&builtin::mul}},
	{"div",{2,&builtin::div}},
	{"pow",{2,&builtin::pow}},
	{"sqrt",{1,&builtin::sqrt}},
	{"sin",{1,&builtin::sin}},
	{"cos",{1,&builtin::cos}},
	{"eq",{2,&builtin::eq}},
	{"le",{2,&builtin::le}},
	{"nand",{2,&builtin::nand}}
};

std::unordered_map
<std::string, System::FunctionInfoSpecial> System::specialFuncMap = {
	{"list",{SIZE_MAX,special::listFunc}},
	{"head",{1,special::headFunc}},
	{"tail",{1,special::tailFunc}}
};

Value System::execute() const
{
	std::stack<Value> res;
	std::stack<std::string> funcs;

	for (size_t i = 0;i < tokens.size();++i) {
		const std::string curr = tokens[i];

		if (curr == ")") {
			if (funcs.empty()) {
				throw std::invalid_argument
				("Invalid sequence! Stack func is empty in execute()");
			}

			std::string key = funcs.top();funcs.pop();

			FuncType where = findFunctionType(key);
			switch (where) {
			case System::FuncType::Builtin:
				executeBuildinFunction(key, res);
				break;
			case System::FuncType::Special:
				executeSpecialFunction(key, res, tokens, i);
				break;
			case System::FuncType::Defined:
				executeDefinedFunction(key, res, this->defs);
				break;
			}

		}
		else if (isNumber(curr) || isNegativeNumber(curr)) {
			int num = std::stoi(curr);
			res.push(Value(static_cast<double>(num)));
		}
		else if (curr == "if") {
			ifLazyEvaluation(tokens, i, res, this->defs);
		}
		else if (curr == "map") {
			mapEvaluation(tokens, i, res, this->defs);
		}
		else if (curr == "filter") {
			filterEvaluation(tokens, i, res, this->defs);
		}
		else if (curr == "(" || curr == ",") {
			//nothing skip
		}
		else {
			funcs.push(curr);
		}
	}
	

	if (res.size() != 1)
		throw std::invalid_argument("Invalid sequence to be executed");

	Value result = res.top();res.pop();

	return result;
}

void System::executeBuildinFunction(const std::string& key,
	std::stack<Value>& res)
{
	auto it = buildinFuncMap.find(key);

	size_t paramCnt = it->second.paramCnt;
	List<Value> args;
	while (paramCnt--) {
		if (res.empty()) {
			throw std::invalid_argument
			("Invalid sequence! Stack res is empty in execute()");
		}

		Value val = res.top();res.pop();
		args.pushFront(val);
	}

	res.push(Value(it->second.function(args)));
}

void System::executeSpecialFunction(const std::string& key,
	std::stack<Value>& res, const std::vector<std::string>& tokens,
	const size_t pos)
{
	auto it = specialFuncMap.find(key);
	size_t paramCnt = it->second.paramCnt;

	if (paramCnt == SIZE_MAX)	//list unknown count of params
		paramCnt = listCntParams(tokens, pos);

	List<Value> args;
	while (paramCnt--) {

		if (res.empty()) {
			throw std::invalid_argument
			("Invalid sequence! Stack res is empty in execute()");
		}

		Value param = res.top();
		res.pop();
		args.pushFront(param);

	}

	res.push(Value(it->second.function(args)));

}
	

void System::executeDefinedFunction(const std::string& key,
	std::stack<Value>& res,Definitions& defs)
{
	if (!defs.isDefined(key))
		throw std::invalid_argument("Function " + key + " not defined!");

	std::vector<std::string> tokens = defs.findDefinition(key);

	size_t paramCnt = defs.findParams(key);
	replaceDSWithParams(tokens, res, paramCnt);

	System innerSys(tokens, defs);

	Value result = innerSys.execute();
	res.push(result);
}

void System::ifLazyEvaluation(const std::vector<std::string>& tokens,
	size_t& pos, std::stack<Value>& res, Definitions& def)
{
	if (++pos >= tokens.size())
		throw std::invalid_argument("Invalid sequence!");

	if (tokens[pos] != "(")
		throw std::invalid_argument("Missing ( after if");

	std::stack<char> brackets;
	brackets.push('(');

	std::vector<std::string> arg;
	std::vector<std::vector<std::string>> argumentsIF;
	while (!brackets.empty()) {
		++pos;
		if (pos >= tokens.size())
			break;

		std::string token = tokens[pos];
		if (token == "(") {
			arg.push_back(token);
			brackets.push('(');
		}
		else if (token == ")") {
			brackets.pop();
			if(!brackets.empty())
				arg.push_back(token);
		}
		else if (token == "," && brackets.size() == 1) {
			argumentsIF.push_back(arg);
			arg.clear();
		}
		else {
			arg.push_back(token);
		}
	}
	if (!arg.empty()) {
		argumentsIF.push_back(arg);
	}
	
	if (!brackets.empty())
		throw std::invalid_argument("Invalid sequence");

	if (argumentsIF.size() != 3)
		throw std::invalid_argument("if must have 3 arguments");

	System condSys(argumentsIF[0],def);

	Value arg1 = condSys.execute();

	if (arg1.asBool()) {
		System res1Sys(argumentsIF[1],def);
		Value arg2 = res1Sys.execute();
		Value result(arg2);
		res.push(result);
	}
	else {
		System res2Sys(argumentsIF[2],def);
		Value arg3 = res2Sys.execute();
		Value result(arg3);
		res.push(result);
	}
}

size_t System::listCntParams(const std::vector<std::string>& tokens,
	const size_t pos)
{
	if (pos >= tokens.size() || tokens[pos] != ")") {
		throw std::invalid_argument("Invalid pos in listCntParams()");
	}

	size_t start = pos;
	int depth = 0;
	while (start > 0) {
		if (tokens[start] == ")") {
			depth++;
		}
		else if (tokens[start] == "(") {
			depth--;
			if (depth == 0) {
				break; 
			}
		}
		--start;
	}

	if (start == 0 || tokens[start - 1] != "list")
		throw std::invalid_argument("listCntParams: not a valid list call");

	size_t cntArgs = 0;
	std::stack<char> brackets;
	brackets.push('(');

	bool expectValue = true; 

	for (size_t i = start + 1; !brackets.empty() && i < tokens.size(); ++i) {
		const std::string& token = tokens[i];

		if (token == "(") {
			brackets.push('(');
		}
		else if (token == ")") {
			brackets.pop();
			if (brackets.empty() && !expectValue)
				cntArgs++;
		}
		else if (token == "," && brackets.size() == 1) {
			cntArgs++;
			expectValue = true;
		}
		else {
			expectValue = false;
		}
	}
	
	return cntArgs;
}

void System::mapEvaluation(const std::vector<std::string>& tokens,
	size_t& pos, std::stack<Value>& res,Definitions& defs)
{
	if (tokens[pos++] != "map")
		throw std::logic_error("Not map function");

	if (pos >= tokens.size() || tokens[pos] != "(")
		throw std::invalid_argument("Invalid map() function");
	++pos;

	if (pos >= tokens.size())
		throw std::invalid_argument("Invalid map() function");

	
	std::string funcName = tokens[pos++];
	if (!defs.isDefined(funcName))
		throw std::invalid_argument("Function is not defined");

	if (defs.findParams(funcName) != 1)
		throw std::invalid_argument("Function must have exactly 1 argument");

	if (tokens[pos++] != ",")
		throw std::invalid_argument("Expected comma after function name");

	
	std::vector<std::string> listExpr;
	while (pos < tokens.size() && tokens[pos] != ")") {
		listExpr.push_back(tokens[pos++]);
	}
	if (pos >= tokens.size() || tokens[pos] != ")")
		throw std::invalid_argument("Invalid closing of map()");
	listExpr.push_back(tokens[pos++]); //)
	
	System listSystem(listExpr, defs);
	Value lst = listSystem.execute();
	List<Value> items = lst.getList();

	List<Value> result;
	for (size_t i = 0; i < items.size(); ++i) {
		std::vector<std::string> callTokens;
		callTokens.push_back(funcName);
		callTokens.push_back("(");
		callTokens.push_back(std::to_string
		(static_cast<int>(items[i].getNumber())));
		callTokens.push_back(")");

		System innerSys(callTokens, defs);
		Value val = innerSys.execute();
		result.pushBack(val);
	}

	
	res.push(Value(result));

}

void System::filterEvaluation(const std::vector<std::string>& tokens,
	size_t& pos, std::stack<Value>& res, Definitions& defs)
{
	if (tokens[pos++] != "filter")
		throw std::logic_error("Not filter function");

	if (pos >= tokens.size() || tokens[pos] != "(")
		throw std::invalid_argument("Invalid filter() function");
	++pos;

	if (pos >= tokens.size())
		throw std::invalid_argument("Invalid filter() function");


	std::string funcName = tokens[pos++];
	if (!defs.isDefined(funcName))
		throw std::invalid_argument("Function is not defined");

	if (defs.findParams(funcName) != 1)
		throw std::invalid_argument("Function must have exactly 1 argument");

	if (tokens[pos++] != ",")
		throw std::invalid_argument("Expected comma after function name");


	std::vector<std::string> listExpr;
	while (pos < tokens.size() && tokens[pos] != ")") {
		listExpr.push_back(tokens[pos++]);
	}
	if (pos >= tokens.size() || tokens[pos] != ")")
		throw std::invalid_argument("Invalid closing of filter()");
	listExpr.push_back(tokens[pos++]); //)

	System listSystem(listExpr, defs);
	Value lst = listSystem.execute();
	List<Value> items = lst.getList();

	List<Value> result;
	for (size_t i = 0; i < items.size(); ++i) {
		int val = static_cast<int>(items[i].getNumber());
		std::vector<std::string> callTokens;
		callTokens.push_back(funcName);
		callTokens.push_back("(");
		callTokens.push_back(std::to_string(val));
		callTokens.push_back(")");

		System innerSys(callTokens, defs);
		Value condition = innerSys.execute();
		if(condition.asBool())
			result.pushBack(Value(static_cast<double>(val)));
	}


	res.push(Value(result));
}

System::FuncType System::findFunctionType(const std::string& key) const
{
	if (defs.isDefined(key)) //first defined!
		return FuncType::Defined;

	auto it1 = buildinFuncMap.find(key);
	if (it1 != buildinFuncMap.end())
		return FuncType::Builtin;

	auto it2 = specialFuncMap.find(key);
	if (it2 != specialFuncMap.end())
		return FuncType::Special;

	

	return FuncType::NotFound;
}

void System::replaceDSWithParams
(std::vector<std::string>& tokens,
	std::stack<Value>& res,size_t paramCnt)
{
	List<Value> nums;
	
	while (paramCnt--) {
		nums.pushFront(res.top());
		res.pop();
	}

	for (size_t i = 0; i < tokens.size();++i) {
		if (tokens[i].find("#", 0) == 0) {
			int index = std::stoi(tokens[i].substr(1));
			tokens[i] = std::to_string(
				static_cast<int>(nums[index].getNumber()));
		}
	}
}

bool System::isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}
bool System::isNumber(const std::string& str) {
	if (str.empty()) return false;

	const char* iter = str.c_str();
	while (*iter) {

		if (!isDigit(*iter))
			return false;

		++iter;
	}

	return true;
}
bool System::isNegativeNumber(const std::string& str)
{
	if (str.empty()) return false;
	if (str[0] != '-') return false;
	if (str.size() == 1) return false;

	const char* iter = str.c_str();
	++iter; //-
	while (*iter) {
		if (!isDigit(*iter))
			return false;

		++iter;
	}

	return true;
}






