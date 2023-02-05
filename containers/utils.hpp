/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:19:02 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 11:23:59 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <string>

namespace ft{
	
	/***************************Enable if*****************************/
	// enable_if : its have a member_type type (defined only if B is true)
	//can be used as an additional function argument 
	template <bool B, class T = void>
	struct enable_if {};
	// Especialization to run when B is true
	template <class T>
	struct enable_if<true, T> {typedef T type; };

	/***************************Integral Constant *****************************/
	/* is_integral
	/checks whether T is an integral type. Provides the member constant value which is equal to true
	/value is the member of constans return true if T is an integral type otherwise false
	/its inherit from integral_constant
	/T: Type like (for now is bool in our case) and v is the value(true or false in our case)*/
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return (v);}
		//operator value_type() const throw() { return value; };
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	/***************************Is Integral*****************************/
	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<bool> : public true_type {};
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

	const class nullptr_t{
		public:
			template <class T>
			operator T*() const { return 0;}
			template <class C, class T>
			operator T C::*() const { return 0;}
		private:
			void operator&() const;
	} nullptr_t = {};
}

#endif