/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:32:34 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/13 18:06:34 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cmath>
#include <limits>
#include <cstdlib>
#include <cctype>

enum class LiteralType{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

LiteralType detectType(const std::string& literal){
	if(literal.length() == 3 && literal[0] == '\'' && literal[2] == '\''){
		return LiteralType::CHAR;
	}

	if(literal == "nan" || literal == "+inf" || literal == "-int"){
		return LiteralType::DOUBLE;
	}

	if(literal == "nanf" || literal == "-inff" || literal == "+inff"){
		return LiteralType::FLOAT;
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
		return LiteralType::INT;
	}

	if(literal.length() > 0 && literal[literal.length() - 1] == 'f'){
		return LiteralType::FLOAT;
	}

	bool hasDecimal = false;
	for (size_t i = start; i < literal.length(); ++i){
		if(literal[i] == '.'){
			hasDecimal = true;
		} else if(!isdigit(literal[i])){
			return LiteralType::INVALID;
		}
	}
	if(hasDecimal){
		return LiteralType::DOUBLE;
	}
	return LiteralType::INVALID;
}

void ScalarConverter::convert(std::string& literal){
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
	case LiteralType::CHAR:
		//convertir depuis un char
		charValue = literal[1]; //indice a 1 dans 'x'
		intValue = static_cast<int>(charValue);
		floatValue = static_cast<float>(charValue);
		doubleValue = static_cast<double>(charValue);
		break;

	case LiteralType::INT:
		try{
			intValue = std::stoi(literal); //verifier si le int puet etre representer en tant que char
			if(intValue < 0 || intValue > 127){
				charPossible = false;
			}else{
				charValue = static_cast<char>(intValue);
				if(!isprint(charValue)){ //est ce qu'il affifable
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

	case LiteralType::FLOAT:
		try{
			if(literal == "nanf"){
				floatValue = std::numeric_limits<float>::quiet_NaN();
				doubleValue = std::numeric_limits<double>::quiet_NaN();
				charValue = false;
				intValue = false;
			}
			if(literal == "+inff" || literal == "inff"){
				floatValue = std::numeric_limits<float>::infinity();
				doubleValue = std::numeric_limits<double>::infinity();
				charValue = false;
				intValue = false;
			}
			if(literal == "-inff"){
				floatValue = -std::numeric_limits<float>::infinity();
				doubleValue = -std::numeric_limits<double>::infinity();
				charValue = false;
				intValue = false;
			}else{
				std::string floatStr = literal.substr(0, literal.length() - 1);
				floatValue = std::stof(floatStr);
				doubleValue = static_cast<double>(floatValue);

				if(floatValue > std::numeric_limits<int>::max() ||
					floatValue < std::numeric_limits<int>::min() ||
					isnan(floatValue)){
						intPossible = false;
				}else{
					intValue = static_cast<int>(floatValue);
				}
				if(floatValue < 0 || floatValue > 127 || isnan(floatValue)){
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
	}
}