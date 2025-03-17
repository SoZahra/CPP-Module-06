/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:51:05 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/17 14:28:38 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base(){}

Base * generate(void){
	static bool init = false;
	if(!init){
		srand(time(NULL));
		init = true;
	}

	int randomValue = rand() % 3; //generer un nb aleatoire entre 0 et 2

	switch(randomValue){
		case 0:
			std::cout << "Generated class A" << std::endl;
			return (new A());
		case 1:
			std::cout << "Generated class B" << std::endl;
			return (new B());
		case 2:
			std::cout << "Generated class C" << std::endl;
			return (new C());
		default:
			return NULL;
	}
}

void identify(Base* p){
	if(dynamic_cast<A*>(p) != NULL){
		std::cout << "A" << std::endl;
	}
	else if(dynamic_cast<B*>(p) != NULL){
		std::cout <<"B" << std::endl;
	}else if(dynamic_cast<C*>(p) != NULL){
		std::cout <<"C" << std::endl;
	}else{
		std::cout << "Unknow type" << std::endl;
	}
}

void identify(Base& p){
	try{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}catch(...) {}

	try{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}catch(...){}

	try{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}catch(...){}

	std::cout << "Unknown type" << std::endl;
}