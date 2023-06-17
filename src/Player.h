#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include "variable.h"
#include "Pokemon.h"

#include <set>

using namespace std;

class Player
{
private:
	string name;
	PlayerType type;
	vector<Pokemon> pokemons;
	int currentPokemon_index;
	int potion;
	int superPotion;
	int hyperPotion;
	int maxPotion;

public:
	//constructors/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Player();
	Player(string name, PlayerType type, vector<Pokemon> pokemon_Construct, int potion, int superPotion, int hyperPotion, int maxPotion);

	//accessors////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	string getName() { return this->name; }
	PlayerType getPlayerType() { return this->type; }
	Pokemon& getPokemon(string name);
	vector<Pokemon>& getPokemons() { return this->pokemons; }
	Pokemon& getCurrentPokemon() { return this->getPokemons()[currentPokemon_index]; }
	int getCurrentPokemon_index() { return this->currentPokemon_index; }
	int getPotion() { return this->potion; }
	int getSuperPotion() { return this->superPotion; }
	int getHyperPotion() { return this->hyperPotion; }
	int getMaxPotion() { return this->maxPotion; }

	//mutators/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void setName(string newName);
	void setType(PlayerType newType);
	void setCurrentPokemon_index(int index);
	void setPotion(int number);
	void setSuperPotion(int number);
	void setHyperPotion(int number);
	void setMaxPotion(int number);

	//functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Intent: check if all of the player's pokemon are fainted
	// Pre: none
	// Post: true if all pokemons of the player are fainted, vice versa
	bool isAllFaint();

	// Intent: check if the player's pokemon is fainted
	// Pre: a string stand for the name of the pokemon
	// Post: true if the pokemon of the player is fainted, vice versa
	bool isFaint(string name);

	// Intent: swap to specified pokemon
	// Pre: a string stand for the name of the pokemon
	// Post: none
	void swapPokemon(string name);

	// Intent: automatic swap when current one is fainted
	// Pre: none
	// Post: none
	void swapToNext();

	// Intent: allow player use potion
	// Pre: potion target pokemon of the player
	// Post: none
	void usePotion(string potionName, string pokeName);

	// Intent: 以Skill攻擊對方，包含傷害計算、攻擊行為實作(扣HP)、附加狀態、技能pp減少
	// Pre: name of the skill and the target passed by reference, critical hit or not, effectiveness
	// Post: a number of damage dealed
	int attack(string skillName, Player& target, bool critical, float effectiveness);

	// Intent: get a random usable skill
	// Pre: none
	// Post: name of a skill as string, if all skill is not usable, returns "NOSKILL"
	string getRandomValidSkill();

	// Intent: 計算屬性傷害倍率
	// Pre: name of the skill and the target passed by reference
	// Post: the Effectiveness as a float
	float getEffectiveness(string skillName, Player& target);

	//private functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

	// Intent: 計算same Type Attack Bonus, only used by attack()
	// Pre: skill & attacker passed by reference
	// Post: the bonus value as a float
	float sameTypeAttackBonus(Skill& skill, Pokemon& attacker);
};

// Intent: return a bool base on RNG and critical chance
// Pre: none
// Post: a boolean
bool isCritical();

// Intent: change string to all-lower-case
// Pre: a string
// Post: a string
string strToLower(string str);