#pragma once

#include "../Value/Value.hpp"
#include "../LinkedList/LinkedList.hpp"

/// @namespace builtin
/// @brief Contains built-in mathematical and logical functions.
namespace builtin {
	/// @brief Adds 2 values in the list.
   /// @param params List of values to be summed.
   /// @return Sum of 2 parameters.
	Value add(const List<Value>& params);

	/// @brief Subtracts subsequent values from the first one.
   /// @param params List of values.
   /// @return Result of subtraction.
	Value sub(const List<Value>& params);

	/// @brief Multiplies 2 values in the list.
	/// @param params List of values to be multiplied.
	/// @return Product of 2 parameters.
	Value mul(const List<Value>& params);

	/// @brief Divides the first value by the second one.
	/// @param params List of values.
	/// @return Result of division.
	Value div(const List<Value>& params);

	/// @brief Raises the first value to the power of the second.
	/// @param params List containing base and exponent.
	/// @return Result of exp.
	Value pow(const List<Value>& params);

	/// @brief Calculates the square root of the value.
   /// @param param List containing the number to process.
   /// @return Square root of the parameter.
	Value sqrt(const List<Value>& param);

	/// @brief Calculates the sin of the value.
	/// @param param List containing the angle in radians.
	/// @return Sine of the parameter.
	Value sin(const List<Value>& param);

	/// @brief Calculates the cosine of the value.
	/// @param param List containing the angle in radians.
	/// @return Cosine of the parameter.
	Value cos(const List<Value>& param);

	/// @brief Checks if two values are equal.
   /// @param params List containing values to compare.
   /// @return Boolean value (true if equal).
	Value eq(const List<Value>& params);

	/// @brief Checks if the first value is less than or equal to the second.
   /// @param params List containing values to compare.
   /// @return Boolean value (true if first <= second).
	Value le(const List<Value>& params);

	/// @brief Performs a NAND logical operation on the parameters.
   /// @param params List of 2 boolean values.
   /// @return Boolean value (result of NAND).
	Value nand(const List<Value>& params);
}




