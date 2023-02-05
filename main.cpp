/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:13:07 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 00:18:18 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include <time.h>
#include <cstring>

int main(int argc, char **argv){
	if (argc > 2){
		std::cout << "invalid number os arguments\n" <<
		"Use: ./ft_container[_st1] [ vector ] " << std::endl;
		return (1);
	}
	clock_t start_time;
	clock_t end_time;
	start_time = clock();

	if (argc == 1){
		test_vector();
	}
	else{
		if (strcmp(argv[1], "vector") == 0)
			test_vector();
		else
		{
			std::cout << "Invalid container name\n" <<
			"Use: ./ft_container[_st1] [ vector ] " << std::endl;
			return (1);
		}
	}
	end_time = clock();
	std::cout << "\nVersion: " << VERSION << ", elapsed time: " << difftime(end_time, start_time) << std::endl;
}