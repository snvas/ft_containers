/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:14:29 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/12 20:42:05 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft{

/**
 * used to obtain information about the type of an iterator. 
 * It provides a way to query the properties of an iterator through its member types.
 * The member types of iterator_traits are:
 * @param difference_type - the type of the difference between two iterators.
 * @param value_type - the type of the values that can be accessed through the iterator.
 * @param pointer - a type that represents a pointer to an element of the underlying sequence.
 * @param reference - a type that represents a reference to an element of the underlying sequence.
 * @param iterator_category - a type that represents the category of the iterator, e.g. std::random_access_iterator_tag.
*/

template<typename Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
}

#endif