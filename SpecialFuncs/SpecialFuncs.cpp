#include "SpecialFuncs.hpp"

namespace special {

	Value listFunc(const List<Value>& args)
	{
		List<Value> result;

		for (size_t i = 0; i < args.size(); ++i) {
			result.pushBack(args[i]);
		}

		return Value(result);
	}

	Value headFunc(const List<Value>& args)
	{
		if (args.size() != 1)
			throw std::invalid_argument("head() expects only 1 argument");

		if (!args[0].isList())
			throw std::invalid_argument("argument in head() must be list");

		return Value(args[0].getList().Head());
	}

	Value tailFunc(const List<Value>& args)
	{
		if (args.size() != 1)
			throw std::invalid_argument("tail() expects only 1 argument");

		if (!args[0].isList())
			throw std::invalid_argument("argument in tail() must be list");

		return Value(args[0].getList().Tail());
	}

}

