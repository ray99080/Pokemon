/*****************************************************************//**
 * \file  Skill.h
 * \create date  May 29 2023
 * \author ±i¦wºÍ
 * \date  May 29 2023
 * \description skill class
 *********************************************************************/
#pragma once
#include<string>
#include"enum.h"

using std::string;


class Skill{
private:
	string name;
	PokemonType pokemonType;
	DamageCategories damageCategories;
	int accuracy;
	int power;
	int maximumPP;
	int PP;
	Condition condition;

public:
	Skill();
	Skill(string name, PokemonType type, DamageCategories damageCategories, int accuracy, int power, int PP, Condition condition);

	string getName();
	PokemonType getPokemonType();
	DamageCategories getDamageCategories();
	int getAccuracy();
	int getPower();
	int getPP();
	int getMaximumPP();
	Condition getCondition();

	//let PP minus 1
	void useSkill();
};
