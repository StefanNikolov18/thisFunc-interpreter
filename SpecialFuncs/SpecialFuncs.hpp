#pragma once
#include "../Value/Value.hpp"
#include "../LinkedList/LinkedList.hpp"

/// @namespace special
/// @brief Contains built-in functions for list operations.
namespace special {
	/// @brief Returns a list constructed from the given arguments
   /// @param args List of Expression pointers to evaluate
   /// @return Value representing the constructed list
	Value listFunc(const List<Value>& args);

	/// @brief Returns the first element of a list
   /// @param args List containing a single list expression
   /// @return Value representing the head element
	Value headFunc(const List<Value>& args);

	/// @brief Returns a new list without the first element
	/// @param args List containing a single list expression
	/// @return Value representing the tail of the list
	Value tailFunc(const List<Value>& args);
	
}