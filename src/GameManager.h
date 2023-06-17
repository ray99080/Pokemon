/*****************************************************************//**
 * \Name:  GameManager.h
 * \date:  June 4 2023
 * \Last update:  June 4 2023
 * \brief:   This c++ program is a header for gamemanager
 * \author:  Benson Hsieh

 *********************************************************************/
#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "Player.h"
 //#include"Pokemon.h"
 //#include"Skill.h"
 //#include"Variable.h"
 //#include"enum.h"

using std::string;

class GameManager
{
public:
	GameManager() { allPokemon.clear(); allSkill.clear(); };
	bool startSeperateFile(string name1, string name2, string name3);//setup variables with seperate files
	void usePotion(Player& player, int potionType, string pokemon);
	void swapPokemon(Player& player, string pokemon);
	void battle(string move1, string move2);
	void burnAndPoison();

	Skill getSkill(string wholeSkill);//get skill information from string

	//get functions
	Player& getPlayer1() { return player1; }
	Player& getPlayer2() { return player2; }
	double getEffective1() { return effective1; }
	double getEffective2() { return effective2; }
	bool getCrit1() { return crit1; }
	bool getCrit2() { return crit2; }
	bool getIsParalysis1() { return isParalysis1; }
	bool getIsParalysis2() { return isParalysis2; }
	int getDamage1() { return damage1; }
	int getDamage2() { return damage2; }
	bool getMiss1() { return miss1; }
	bool getMiss2() { return miss2; }
	bool getWhoIsFirst() { return whoIsFirst; }

private:
	Condition strToCond(string str);
	DamageCategories strToCat(string str);
	PokemonType strToType(string str);
	vector<Pokemon> allPokemon;
	vector<Skill> allSkill;
	bool whoIsFirst;
	Player player1;
	Player player2;

	bool crit1, crit2;
	bool isParalysis1, isParalysis2;
	bool miss1, miss2;
	float effective1, effective2;
	int damage1, damage2;


};


/*
gamemananger 每回合的B&P
pokemonNow = player1.getPokemons()[player1.getCurrentPokemon_index()].BurnAndPoison();;

*/