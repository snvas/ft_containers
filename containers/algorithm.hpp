/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:14:36 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/12 20:45:40 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {
/***************************Equal*****************************/
/**
 * Test whether the elements in two ranges are equal
 * Compares the elements in the range [first1,last1) with those in the range 
 * beginning at first2, and returns true if all of the elements in both ranges match.
 * https://cplusplus.com/reference/algorithm/equal/
 * compares the elements in two ranges [first1, last1) and [first2, [sentinel value]) 
 * and returns true if they are equal, false otherwise. The function iterates through 
 * both ranges using the input iterators first1 and first2 until either first1 reaches 
 * last1 or an element in the two ranges is not equal. The elements are compared using 
 * the equality operator ==. If all elements are equal, the function returns true.
 * */
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
/** 
 * Lexicographical less-than comparison
 * Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
 * https://cplusplus.com/reference/algorithm/lexicographical_compare/
 * 
 * Compares two ranges of elements lexicographically, meaning that the elements are compared one by one 
 * in the order they appear in the ranges. 
 * The function takes as inputs two pairs of iterators, first1 and last1 which define the range of the first sequence, 
 * and first2 and last2 which define the range of the second sequence.
 * The function returns false if the first sequence is not less than the second sequence. 
 * It returns true if the first sequence is less than the second sequence.
 * The comparison is done element by element using the < operator. 
 * If an element in the first sequence is less than an element in the second sequence, 
 * then the function returns true, indicating that the first sequence is less than the second sequence. 
 * If all elements in the first sequence are equal to the corresponding elements in the second sequence, 
 * and the second sequence has more elements, then the function returns true, 
 * indicating that the first sequence is less than the second sequence.
*/
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