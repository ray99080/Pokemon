#include "Skill.h"

Skill::Skill()
{
	this->name = "";
	this->accuracy = 100;
	this->power = 100;
	this->PP = 10;
	this->maximumPP = 10;
}

Skill::Skill(string name, PokemonType type, DamageCategories damageCategories, int accuracy, int power, int PP, Condition condition)
{
	this->name = name;
	this->pokemonType = type;
	this->damageCategories = damageCategories;
	this->accuracy = accuracy;
	this->power = power;
	this->PP = PP;
	this->maximumPP = PP;
	this->condition = condition;
}

string Skill::getName()
{
	return name;
}

PokemonType Skill::getPokemonType()
{
	return pokemonType;
}

DamageCategories Skill::getDamageCategories()
{
	return damageCategories;
}

int Skill::getAccuracy()
{
	return accuracy;
}

int Skill::getPower()
{
	return power;
}

int Skill::getPP()
{
	return PP;
}

int Skill::getMaximumPP()
{
	return maximumPP;
}

Condition Skill::getCondition()
{
	return condition;
}

void Skill::useSkill()
{
	PP -= 1;
	if (PP < 0) {
		PP = 0;
	}
}
