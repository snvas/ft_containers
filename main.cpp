/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:13:07 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/11 16:47:45 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include <time.h>
#include <cstring>

int main(int argc, char **argv){
	if (argc > 2){
		std::cout << "invalid number os arguments\n" <<
		"Use: ./ft_container[_st1] [ vector | stack | map  ] " << std::endl;
		return (1);
	}
	clock_t start_time;
	clock_t end_time;
	start_time = clock();

	if (argc == 1){
		test_vector();
		test_pair();
		test_map();
		test_stack();
		test_set();
	}
	else{
		if (strcmp(argv[1], "vector") == 0)
			test_vector();
		else if (strcmp(argv[1], "map") == 0)
			test_map();
		else if (strcmp(argv[1], "stack") == 0)
			test_stack();
		else if (strcmp(argv[1], "set") == 0)
			test_set();
		else
		{
			std::cout << "Invalid container name\n" <<
			"Use: ./ft_container[_st1] [ vector  | stack | map | set ] " << std::endl;
			return (1);
		}
	}
	end_time = clock();
	std::cout << "\nVersion: " << VERSION << ", elapsed time: " << difftime(end_time, start_time) << std::endl;
}