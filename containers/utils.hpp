/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:19:02 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/12 20:56:06 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <string>

namespace ft{
	
	/***************************Enable if*****************************/
	/** 
	 * enable_if : its have a member_type type (defined only if B is true)
	 * can be used as an additional function argument 
	 * This is a template that provides a way to conditionally define a type based on a boolean value. 
	 * The template has two template parameters: "B", a Boolean value, and "T", 
	 * which is the type that will be defined if "B" is true. 
	 * The "enable_if" struct has an empty body, meaning that it is an empty placeholder.
	 * The purpose of "enable_if" is to allow the definition of a function template or class template 
	 * to be enabled or disabled based on a condition. 
	 * For example, you might want to write a function template that only operates on a specific type of input, 
	 * and only if that type meets certain requirements. In that case, you could use "enable_if" to specify 
	 * the conditions under which the function template should be enabled. 
	 * If the conditions are met, then the type defined by "enable_if" will be used as the return type of the function. 
	 * If the conditions are not met, then the function template will not be defined.
	*/
	template <bool B, class T = void>
	struct enable_if {};
	// Especialization to run when B is true
	/**
	 * This template specialization defines a type member called type if the first template argument, B, is true. 
	 * The type member is defined as T if B is true. 
	 * The template enable_if can be used in function templates to enable or disable a function based on certain conditions. 
	 * The type T is a default type argument that can be customized to the user's needs. 
	 * The primary use case for this template is to enable or disable a function based on a certain condition, 
	 * for example, to enable a function only if the type of its argument is an integral type.
	*/
	template <class T>
	struct enable_if<true, T> {typedef T type; };

	/***************************Integral Constant *****************************/
	/**
	 * is_integral
	 * template class named integral_constant that is used to represent an integral constant. 
	 * This class is part of the C++ Standard Library and is used as a type-level representation of an integral value.
	 * The template takes two arguments: T represents the underlying integral type of the constant, 
	 * and v represents the value of the constant.
	 * The class provides the following member objects and functions:
	 * 		value: a static constant object of type T with the value of v.
	 * 		value_type: a typedef for the underlying integral type T.
	 * 		type: a typedef for the integral_constant type, which is the class itself.
	 * 		operator T(): a conversion operator that returns the value of v.
	 * 		operator value_type() const throw(): another conversion operator that returns the value of value.
	 * This class is typically used to define compile-time constant values, such as those used in metaprogramming
	 * */
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return (v);}
		operator value_type() const throw() { return value; };
	};

	/**
	 * The typedef "true_type" is an alias for the class "integral_constant<bool, true>". 
	 * "integral_constant" is a template class that takes a type (in this case bool) and 
	 * a value of that type (in this case "true"). The class provides a constant value of 
	 * the specified type and value, as well as type information through type members. 
	 * The typedef "true_type" can be used to represent a value of "true" with type information.
	*/
	typedef integral_constant<bool, true> true_type;

	/**
	 * This is defining a type false_type as an alias for integral_constant<bool, false>. 
	 * The integral_constant template is a way to create type-level values that can be used as metadata. 
	 * The false_type type specifically represents the value false at the type level, 
	 * and can be used as a boolean type in templates to represent conditions or selections at compile time.
	*/
	typedef integral_constant<bool, false> false_type;

	/***************************Is Integral*****************************/
	/**
	 * The is_integral template is a type trait class that determines if a given type T is an integral type 
	 * (i.e., an integer type). The class inherits from false_type by default, meaning that, by default, 
	 * the type T is not considered an integral type. This class can be specialized for specific types 
	 * to make the is_integral type trait return true for those types.
	*/
	template <class T> struct is_integral : public false_type {};
	
	/**
	 * This template specialization of is_integral declares that the type bool is an integral type, 
	 * and inherits from the true_type class. The is_integral template is used to determine 
	 * if a type is an integral type, meaning it is either a built-in integer type (e.g., int, long, short, etc.) 
	 * or a user-defined integer type. By specializing the template for the bool type, this declaration 
	 * lets the program know that bool is indeed an integral type, and will inherit the properties of true_type.
	*/
	template <> struct is_integral<bool> : public true_type {};
	/**a specialization of the is_integral template for the char type. 
	 * It inherits from true_type, indicating that char is an integral type. */
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short int> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<long int> : public true_type {};
	template <> struct is_integral<long long int> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long int> : public true_type {};
	template <> struct is_integral<unsigned long long int> : public true_type {};
	template <> struct is_integral<__int128_t> : public true_type {};
	template <> struct is_integral<__uint128_t> : public true_type {};
}

#endif