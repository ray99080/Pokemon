#include "Pokemon.h"

Pokemon::Pokemon()
{
	this->name = "";
	this->HP = 100;
	this->maximumHP = 100;
	this->attack = 10;
	this->defense = 10;
	this->specialAttack = 10;
	this->specialDefense = 10;
	this->speed = 50;
}

Pokemon::Pokemon(string name, PokemonType type, int HP, int attack, int defense, int specialAttack, int specialDefense, int speed)
{
	this->name = name;
	this->types.push_back(type);
	this->HP = HP;
	this->maximumHP = HP;
	this->attack = attack;
	this->defense = defense;
	this->specialAttack = specialAttack;
	this->specialDefense = specialDefense;
	this->speed = speed;

}

Pokemon::Pokemon(string name, PokemonType type1, PokemonType type2, int HP, int attack, int defense, int specialAttack, int specialDefense, int speed)
	:Pokemon(name, type1, HP, attack, defense, specialAttack, specialDefense, speed)
{
	this->types.push_back(type2);
}

string Pokemon::getName()
{
	return name;
}

vector<PokemonType> Pokemon::getTypes()
{
	return types;
}

int Pokemon::getMaximumHP()
{
	return maximumHP;
}

int Pokemon::getHP()
{
	return HP;
}

int Pokemon::getAttack()
{
	return attack;
}

int Pokemon::getDefense()
{
	return defense;
}

int Pokemon::getSpecialAttack()
{
	return specialAttack;
}

int Pokemon::getSpecialDefense()
{
	return specialDefense;
}

int Pokemon::getSpeed()
{
	return speed;
}

Skill& Pokemon::getSkill(string skillName)
{
	for (int i = 0; i < skills.size(); i++) {
		if (skillName == skills[i].getName()) {
			return skills[i];
		}
	}
}
vector<Skill>& Pokemon::getSkills()
{
	return skills;
}

set<Condition> Pokemon::getConditions()
{
	return conditions;
}

void Pokemon::setSkills(vector<Skill> skills)
{
	this->skills = skills;
}

void Pokemon::fullHP()
{
	HP = maximumHP;
}

void Pokemon::heal(int point)
{
	HP += point;
	if (HP > maximumHP) {
		HP = maximumHP;
	}
}

void Pokemon::damage(int point)
{
	HP -= point;
	if (HP < 0) {
		HP = 0;
	}
}

void Pokemon::debuff(Condition condition)
{
	conditions.insert(condition);
	if (condition == Condition::PAR) {
		speed /= 2;
	}
}

void Pokemon::BurnAndPoison()
{
	if (conditions.count(Condition::BRN)) {
		HP -= maximumHP / 16;
	}
	if (conditions.count(Condition::PSN)) {
		HP -= maximumHP / 16;
	}
	if (HP < 0) {
		HP = 0;
	}
}

bool Pokemon::isFaint()
{
	return HP == 0;
}

bool Pokemon::isSkillExist(string skillName)
{
	for (int i = 0; i < skills.size(); i++) {
		if (skills[i].getName() == skillName) {
			return true;
		}
	}
	return false;
}
