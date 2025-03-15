/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:32:34 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/15 16:35:32 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cmath>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <iomanip>


ScalarConverter::ScalarConverter() {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

enum LiteralType {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

LiteralType detectType(const std::string& literal){
	if(literal.length() == 3 && literal[0] == '\'' && literal[2] == '\''){
		return CHAR;
	}

	if(literal == "nan" || literal == "+inf" || literal == "-inf"){
		return DOUBLE;
	}

	if(literal == "nanf" || literal == "-inff" || literal == "+inff"){
		return FLOAT;
	}

	bool isInt = true;
	size_t start = 0;
	if(literal[0] == '+' || literal[0] == '-'){
		start = 1;
	}
	for(size_t i = start; i < literal.length(); ++i){
		if(!isdigit(literal[i])){
			isInt = false;
			break;
		}
	}
	if(isInt){
		return INT;
	}

	if(literal.length() > 0 && literal[literal.length() - 1] == 'f'){
		return FLOAT;
	}

	bool hasDecimal = false;
	for (size_t i = start; i < literal.length(); ++i){
		if(literal[i] == '.'){
			hasDecimal = true;
		} else if(!isdigit(literal[i])){
			return INVALID;
		}
	}
	if(hasDecimal){
		return DOUBLE;
	}
	return INVALID;
}

void ScalarConverter::convert(const std::string& literal){
	LiteralType type = detectType(literal);

	char charValue;
	int intValue;
	float floatValue;
	double doubleValue;

	bool charPossible = true;
	bool intPossible = true;
	bool floatPossible = true;
	bool doublePossible = true;

	switch (type)
	{
	case CHAR:
		//convertir depuis un char
		charValue = literal[1]; //indice a 1 dans 'x'
		intValue = static_cast<int>(charValue);
		floatValue = static_cast<float>(charValue);
		doubleValue = static_cast<double>(charValue);
		break;

	case INT:
		try{
			intValue = atoi(literal.c_str()); //verifier si le int puet etre representer en tant que char
			if(intValue < 0 || intValue > 127){
				charPossible = false;
			}else{
				charValue = static_cast<char>(intValue);
				if(!isprint(charValue)){ //est ce qu'il est affichable
					//non affichable mais peut etre converti
				}
			}
			floatValue = static_cast<float>(intValue);
			doubleValue = static_cast<double>(intValue);
		}catch(const std::exception& e){
			charPossible = false;
			intPossible = false;
			floatPossible = false;
			doublePossible = false;
		}
		break;

	case FLOAT:
		try{
			if(literal == "nanf"){
				floatValue = std::numeric_limits<float>::quiet_NaN();
				doubleValue = std::numeric_limits<double>::quiet_NaN();
				charPossible = false;
				intPossible = false;
			}
			else if(literal == "+inff" || literal == "inff"){
				floatValue = std::numeric_limits<float>::infinity();
				doubleValue = std::numeric_limits<double>::infinity();
				charPossible = false;
				intPossible = false;
			}
			else if(literal == "-inff"){
				floatValue = -std::numeric_limits<float>::infinity();
				doubleValue = -std::numeric_limits<double>::infinity();
				charPossible = false;
				intPossible = false;
			}else{
				std::string floatStr = literal.substr(0, literal.length() - 1);
				floatValue = atof(floatStr.c_str());
				doubleValue = static_cast<double>(floatValue);

				if(floatValue > std::numeric_limits<int>::max() ||
					floatValue < std::numeric_limits<int>::min() ||
					std::isnan(floatValue)){
						intPossible = false;
				}else{
					intValue = static_cast<int>(floatValue);
				}
				if(floatValue < 0 || floatValue > 127 || std::isnan(floatValue)){
					charPossible= false;
				}else{
					charValue = static_cast<char>(floatValue);
				}
			}
		}catch(const std::exception& e){
			charPossible = false;
			intPossible = false;
			floatPossible = true;  // Le float d'origine est toujours possible
			doublePossible = true;
		}
		break;

		case DOUBLE:
		try {
			if (literal == "nan") {
				doubleValue = std::numeric_limits<double>::quiet_NaN();
				floatValue = std::numeric_limits<float>::quiet_NaN();
				charPossible = false;
				intPossible = false;
			} else if (literal == "+inf" || literal == "inf") {
				doubleValue = std::numeric_limits<double>::infinity();
				floatValue = std::numeric_limits<float>::infinity();
				charPossible = false;
				intPossible = false;
			} else if (literal == "-inf") {
				doubleValue = -std::numeric_limits<double>::infinity();
				floatValue = -std::numeric_limits<float>::infinity();
				charPossible = false;
				intPossible = false;
			} else {
				doubleValue = strtod(literal.c_str(), NULL);
				floatValue = static_cast<float>(doubleValue);

				if (doubleValue > std::numeric_limits<int>::max() ||
					doubleValue < std::numeric_limits<int>::min() ||
					std::isnan(doubleValue)) {
					intPossible = false;
				} else {
					intValue = static_cast<int>(doubleValue);
				}

				if (doubleValue < 0 || doubleValue > 127 || std::isnan(doubleValue)) {
					charPossible = false;
				} else {
					charValue = static_cast<char>(doubleValue);
				}
			}
		} catch (const std::exception& e) {
			charPossible = false;
			intPossible = false;
			floatPossible = false;
			doublePossible = true;
		}
		break;

	case INVALID:
	default:
		charPossible = false;
		intPossible = false;
		floatPossible = false;
		doublePossible = false;
		std::cout << "Invalid input: " << literal << std::endl;
		return;
	}
	std::cout << "char: ";
	if (!charPossible) {
		std::cout << "impossible";
	} else if (!isprint(charValue)) {
		std::cout << "Non displayable";
	} else {
		std::cout << "'" << charValue << "'";
	}
	std::cout << std::endl;

	std::cout << "int: ";
	if (!intPossible) {
		std::cout << "impossible";
	} else {
		std::cout << intValue;
	}
	std::cout << std::endl;

	std::cout << "float: ";
	if (!floatPossible) {
		std::cout << "impossible";
	} else {
		// Afficher avec la précision décimale et le "f" final
		std::cout << std::fixed << std::setprecision(1) << floatValue << "f";
	}
	std::cout << std::endl;

	std::cout << "double: ";
	if (!doublePossible) {
		std::cout << "impossible";
	} else {
		// Afficher avec la précision décimale
		std::cout << std::fixed << std::setprecision(1) << doubleValue;
	}
	std::cout << std::endl;
}