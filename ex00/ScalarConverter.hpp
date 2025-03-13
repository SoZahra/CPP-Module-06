/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:32:36 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/13 14:12:57 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter{

	private :
		ScalarConverter() = delete;
		~ScalarConverter() = delete;
		ScalarConverter(const ScalarConverter& other) = delete;
		ScalarConverter& operator=(const ScalarConverter& other)= delete;

	public :
		static void convert(std::string& literal);
};


#endif