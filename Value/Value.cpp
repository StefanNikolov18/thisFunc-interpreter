#include "Value.hpp"
#include <cmath>
 
Value::Value(bool b)
	: islist(false), num(b ? 1.0 : 0.0) {
}

bool Value::asBool() const
{
	if (!islist)
		return !!this->num;
	else
		return (list.size() != 0);
}

double Value::getNumber() const
{
	if (islist)
		throw std::invalid_argument("Value is list!");

	return this->num;
}

const List<Value>& Value::getList() const
{
	return this->list;
}

void Value::print(std::ostream& os) const
{
	if (!islist) {
		const double EPS = 1e-9;
		double rounded = std::round(num);
		if (std::fabs(num - rounded) < EPS)
			os << static_cast<long long int>(rounded);
		else
			os << num;

		return;
	}

	list.print();
}

std::ostream& operator<<(std::ostream& os, const Value& obj)
{
	obj.print(os);
	return os;
}