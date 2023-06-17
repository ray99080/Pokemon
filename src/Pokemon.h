#pragma once

#include"Skill.h"
#include"enum.h"
#include<set>
#include<string>
#include<vector>

using std::vector;
using std::string;
using std::set;

class Pokemon {

private:
	string name;
	vector<PokemonType> types;
	int maximumHP;
	int HP;
	int attack;
	int defense;
	int specialAttack;
	int specialDefense;
	int speed;
	vector<Skill> skills;
	set<Condition> conditions;

public:
	Pokemon();
	//single type
	Pokemon(string name, PokemonType type, int HP, int attack, int defense, int specialAttack, int specialDefense, int speed);
	//dual type
	Pokemon(string name, PokemonType type1, PokemonType type2, int HP, int attack, int defense, int specialAttack, int specialDefense, int speed);

	string getName();
	vector<PokemonType> getTypes();
	int getMaximumHP();
	int getHP();
	int getAttack();
	int getDefense();
	int getSpecialAttack();
	int getSpecialDefense();
	int getSpeed();
	Skill& getSkill(string skillName);
	vector<Skill>& getSkills();
	set<Condition> getConditions();

	void setSkills(vector<Skill> skills);

	//heal to full HP
	void fullHP();
	void heal(int point);
	void damage(int point);
	//get debuff from opponent
	void debuff(Condition condition);
	//use it when B&P status
	void BurnAndPoison();
	bool isFaint();
	bool isSkillExist(string skillName);

};
