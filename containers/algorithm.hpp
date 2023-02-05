/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:14:36 by snovaes           #+#    #+#             */
/*   Updated: 2023/01/13 22:25:43 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {
/***************************Equal*****************************/
/*Test whether the elements in two ranges are equal
Compares the elements in the range [first1,last1) with those in the range 
beginning at first2, and returns true if all of the elements in both ranges match.
https://cplusplus.com/reference/algorithm/equal/*/
template <typename InputIterator1, typename InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
		  InputIterator2 first2) {
	while (first1 != last1) {
		if (!(*first1 == *first2))
			return (false);
		first1++;
		first2++;
	}
	return (true);
}
/***************************Lexicographical Compare*****************************/
/*Lexicographical less-than comparison
Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
https://cplusplus.com/reference/algorithm/lexicographical_compare/*/
template <typename InputIterator1, typename InputIterator2>
inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				    InputIterator2 first2,
				    InputIterator2 last2) {
	while (first1 != last1){
		if(first2 == last2 || *first2<*first1)
			return false;
		else if (*first1<*first2)
			return true;
		first1++;
		first2++;
	}
	return (first2 != last2);
}
}

#endif