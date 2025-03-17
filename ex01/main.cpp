/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:37:20 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/17 12:23:05 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main() {
	// Création d'un objet Data avec des valeurs initiales
	Data originalData;
	originalData.value = 42;
	originalData.text = "Hello, serialization!";

	// Affichage des valeurs originales
	std::cout << "Original data:" << std::endl;
	std::cout << "Address: " << &originalData << std::endl;
	std::cout << "Value: " << originalData.value << std::endl;
	std::cout << "Text: " << originalData.text << std::endl;

	// Sérialiser le pointeur
	uintptr_t serialized = Serializer::serialize(&originalData);
	std::cout << "\nSerialized value (uintptr_t): " << serialized << std::endl;

	// Désérialiser le pointeur
	Data* deserialized = Serializer::deserialize(serialized);

	// Affichage des valeurs après désérialisation
	std::cout << "\nDeserialized data:" << std::endl;
	std::cout << "Address: " << deserialized << std::endl;
	std::cout << "Value: " << deserialized->value << std::endl;
	std::cout << "Text: " << deserialized->text << std::endl;

	// Vérifier que les pointeurs sont identiques
	std::cout << "\nPointer comparison:" << std::endl;
	std::cout << "Original pointer: " << &originalData << std::endl;
	std::cout << "Deserialized pointer: " << deserialized << std::endl;

	if (&originalData == deserialized) {
		std::cout << "SUCCESS: The pointers are identical!" << std::endl;
	} else {
		std::cout << "ERROR: The pointers are different!" << std::endl;
	}

	// Modifier les données via le pointeur désérialisé pour vérifier
	deserialized->value = 24;
	std::cout << "\nAfter modifying through deserialized pointer:" << std::endl;
	std::cout << "Original data value: " << originalData.value << std::endl;
	std::cout << "Deserialized data value: " << deserialized->value << std::endl;

	return 0;
}