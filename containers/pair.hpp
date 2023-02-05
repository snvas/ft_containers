/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:14:12 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 15:22:21 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft{
	/**
	 * Pair of values - This class couples together a pair of values, which may be 
	 * of different types (T1 and T2). The individual values can be accessed 
	 * through its public members first and second.
	 * https://cplusplus.com/reference/utility/pair/
	*/
	template <class T1, class T2>
	class pair
	{
	public:
		/***************************Member Types*****************************/
		typedef T1 first_type; //The first template parameter (T1), Type of member first.
		typedef T2 second_type;	//The second template parameter (T), Type of member second.

		/***************************Member variables*****************************/
		first_type first;
		second_type second;
		
		//default constructor - Constructs a pair object with its elements value-initialized.
		pair(void) : first(T1()), second(T2()) {}
		
		/*copy / move constructor (and implicit conversion)
		Initializes first with pr.first and second with pr.second, 
		performing implicit conversion as needed */
		template <class U, class V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		// initialization constructor - Member first is constructed with a and member second with b.
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
		
		//destructor
		~pair(void){}

		/*operator assign - Assigns pr as the new content for the pair object.
		*/
		pair& operator=(pair const& pr){
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}

		//Exchanges the contents of two pairs - The contents of container x are exchanged with those of y. 
		//Both container objects shall be of the same type (same template parameters).
		template<class first_type, class second_type>
		void swap(pair<first_type, second_type> &x, pair<first_type, second_type> &y) {
			first_type tmp = x.first;
			x.first = y.first;
			y.first = tmp;
			second_type tmp2 = x.second;
			x.second = y.second;
			y.second = tmp2;
		}
	};

		/***************************Make Pair*****************************/
		/*Construct a pair <T1, T2> object and iniatializes it with the
		values a and b. The advantage of using make_pair over a simple pair<>
		constructir is taht the compiler can deduce the types T1 and T2 from the values a and b*/
	template<class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y){
		return (pair<T1,T2>(x, y));
	}

		/***************************Relational Operators*****************************/
		//Performs the appropriate comparison operation between the pair objects lhs and rhs.

	/*operator ==
	* Returns treu if a and b are equal, that is, a.first ==b.first && a.second ==b.second
	*/
	template <class T1, class T2>
	inline bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	//operator !=
	template <class T1, class T2>
	inline bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
		return (!(lhs == rhs));
	}

	/*operator <
	* Returns true if a is less than b, assuming the first member is more significant
	* than the second. Thai is, the return value is a.first < b.first || 
	* (!(b.first < a.first) && a.second < b.second)
	*/
	template <class T1, class T2>
	inline bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	//operator <=
	template <class T1, class T2>
	inline bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
		return (!(rhs < lhs));
	}

	//operator >
	template <class T1, class T2>
	inline bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
		return (rhs < lhs);
	}

	//operator >=
	template <class T1, class T2>
	inline bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
		return (!(lhs < rhs));
	}
}

#endif