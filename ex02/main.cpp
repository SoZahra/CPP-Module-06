/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:20:38 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/17 14:21:48 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main() {
	// Tester la generation et l'identification 5 fois
	for (int i = 0; i < 5; i++) {
		std::cout << "\nTest #" << i+1 << ":" << std::endl;

		// instance aléatoire
		Base* instance = generate();

		// identifier avec un pointeur
		std::cout << "Identifying with pointer: ";
		identify(instance);

		// identifier avec une ref
		std::cout << "Identifying with reference: ";
		identify(*instance);

		delete instance;
	}
	return 0;
}