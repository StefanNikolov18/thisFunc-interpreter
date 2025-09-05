#include "Builtins.hpp"
#include <cmath>

namespace builtin {
	Value add(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("add() expects two arguments");

		return Value(params[0].getNumber() + params[1].getNumber());
	}
	Value sub(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("sub() expects two arguments");

		return Value(params[0].getNumber() - params[1].getNumber());
	}
	Value mul(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("mul() expects two arguments");

		return Value(params[0].getNumber() * params[1].getNumber());
	}
	Value div(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("div() expects two arguments");

		if (params[1].getNumber() == 0)
			throw std::invalid_argument("Cannot divide by zero!");

		return Value(params[0].getNumber() / params[1].getNumber());
	}
	Value pow(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("pow() expects two arguments");

		double base = params[0].getNumber();
		double exp = params[1].getNumber();

		if (exp == 0)
			return Value(1.0);
		else if (exp == 1)
			return Value(base);
		else if (exp == 2)
			return Value(base * base);

		return Value(std::pow(base, exp));
	}
	Value sqrt(const List<Value>& param)
	{
		if (param.size() != 1)
			throw std::invalid_argument("sqrt() expects exactly one argument.");

		double val = param[0].getNumber();

		if (val < 0.0)
			throw std::invalid_argument("Value must be positive!");

		return Value(std::sqrt(val));
	}
	Value sin(const List<Value>& param)
	{
		if (param.size() != 1)
			throw std::invalid_argument("sin() expects exactly one argument.");

		return Value(std::sin(param[0].getNumber()));
	}
	Value cos(const List<Value>& param)
	{
		if (param.size() != 1)
			throw std::invalid_argument("cos() expects exactly one argument");

		return Value(std::cos(param[0].getNumber()));
	}
	Value eq(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("eq() expects two arguments");

		return Value(params[0].getNumber() == params[1].getNumber());
	}
	Value le(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("le() expects two arguments");

		return Value(params[0].getNumber() <= params[1].getNumber());
	}
	Value nand(const List<Value>& params)
	{
		if (params.size() != 2)
			throw std::invalid_argument("nand() expects two arguments");

		bool a = params[0].asBool();
		bool b = params[1].asBool();


		return Value(!a || !b);
	}
}


