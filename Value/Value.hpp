#pragma once

#include <stdexcept>
#include <fstream>
#include <iostream>
#include "../LinkedList/LinkedList.hpp"

/// @class Value
/// @brief Represents either a numeric value or a list of Values.
/// (Ocenka)
class Value 
{
public:
	
	/// @brief Constructs a numeric Value
	/// @param num The number to store
	explicit Value(double num) : 
		islist(false), num(num), list({}) { }

	/// @brief Constructs a list Value
	/// @param list The list of Values to store
	explicit Value(const List<Value>& list) : 
	 islist(true),num(0.0), list(list) { }
	
	/// @brief Constructs a boolean Value
   /// @param b The boolean to store
	Value(bool b);
	/// @brief Returns the Value as a boolean
   /// @return Boolean representation of the value
	bool asBool() const;

	/// @brief Checks if the Value is a list
	bool isList() const { return islist; }

	/// @brief Retrieves the numeric value
	double getNumber() const;
	/// @brief Retrieves the list value
	const List<Value>& getList() const;

	/// @brief Prints the value to the output stream
	/// @param os The output stream (default std::cout)
	void print(std::ostream& os = std::cout) const;

private:
	bool islist;         ///< True if this Value is a list
	double num;          ///< Stored number 
	List<Value> list;    ///< Stored list 

};

/// @brief Outputs a Value to the given stream op<<
/// @param os: output stream
/// @param obj: Value to print
/// @return Reference to the output stream
std::ostream& operator<<(std::ostream& os, const Value& obj);
