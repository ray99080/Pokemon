/*****************************************************************//**
 * \Name:  GameManager.cpp
 * \date:  June 4 2023
 * \Last update:  June 4 2023
 * \brief:   This c++ program implements functions of gamemanager
 * \author:  Benson Hsieh
 *********************************************************************/
#include"GameManager.h"

void GameManager::usePotion(Player& player, int potionType, string pokemon)
{

	if (potionType == 1) {
		player1.getPokemon(pokemon).heal(POTION_HEALS);
	}
	else if (potionType == 2) {
		player1.getPokemon(pokemon).heal(SUPERPOTION_HEALS);
	}
	else if (potionType == 3) {
		player1.getPokemon(pokemon).heal(HYPERPOTION_HEALS);
	}
	else if (potionType == 4) {
		player1.getPokemon(pokemon).fullHP();
	}
}
void GameManager::swapPokemon(Player& player, string pokemon)
{
	player.swapPokemon(pokemon);
}
void GameManager::battle(string move1, string move2)
{
	miss1 = false;
	miss2 = false;
	isParalysis1 = false;
	isParalysis2 = false;

	if (testMode) {
		if (player1.getCurrentPokemon().getConditions().count(Condition::PAR)) {
			isParalysis1 = true;
		}
		else {
			isParalysis1 = false;
		}

		if (player2.getCurrentPokemon().getConditions().count(Condition::PAR)) {
			isParalysis2 = true;
		}
		else {
			isParalysis2 = false;
		}
		
	}
	else {
		if (player1.getCurrentPokemon().getConditions().count(Condition::PAR)) {
			if (rand() % 4 == 0) {
				isParalysis1 = true;
			}
			else {
				isParalysis1 = false;
			}
		}
		else {
			isParalysis1 = false;
		}


		if (player2.getCurrentPokemon().getConditions().count(Condition::PAR)) {
			if (rand() % 4 == 0) {
				isParalysis2 = true;
			}
			else {
				isParalysis2 = false;
			}
		}
		else {
			isParalysis2 = false;
		}
	}
	
	

	//miss
	if (!testMode) {
		if ((rand() % 100) < player1.getCurrentPokemon().getSkill(move1).getAccuracy()) {
			miss1 = false;
		}
		else {
			miss1 = true;
		}

		if ((rand() % 100) < player2.getCurrentPokemon().getSkill(move2).getAccuracy()) {
			miss2 = false;
		}
		else {
			miss2 = true;
		}
	}
	else {
		miss1 = false;
		miss2 = false;
	}

	if (player1.getCurrentPokemon().getSpeed() >= player2.getCurrentPokemon().getSpeed())
	{
		whoIsFirst = true;

		if (move1 != "no" && !isParalysis1 && !miss1)
		{
			crit1 = isCritical();//get crit of player.h (todo)
			effective1 = player1.getEffectiveness(move1, player2);
			damage1 = player1.attack(move1, player2, crit1, effective1);
		}

		if (testMode) {
			if (player2.getCurrentPokemon().getConditions().count(Condition::PAR)) {
				isParalysis2 = true;
			}
			else {
				isParalysis2 = false;
			}
		}
		else {
			if (player2.getCurrentPokemon().getConditions().count(Condition::PAR)) {
				if (rand() % 4 == 0) {
					isParalysis2 = true;
				}
				else {
					isParalysis2 = false;
				}
			}
			else {
				isParalysis2 = false;
			}
		}

		//if player2 hasn't fainted
		if (move2 != "no" && !player2.getCurrentPokemon().isFaint() && !isParalysis2 && !miss2)
		{
			crit2 = isCritical();//get crit of player.h (todo)
			effective2 = player2.getEffectiveness(move2, player1);
			damage2 = player2.attack(move2, player1, crit2, effective2);
		}
	}
	else
	{
		whoIsFirst = false;
		if (move2 != "no" && !isParalysis2 && !miss2) {
			crit2 = isCritical();//get crit of player.h (todo)
			effective2 = player2.getEffectiveness(move2, player1);
			damage2 = player2.attack(move2, player1, crit2, effective2);
		}

		if (testMode) {
			if (player1.getCurrentPokemon().getConditions().count(Condition::PAR)) {
				isParalysis1 = true;
			}
			else {
				isParalysis1 = false;
			}
		}
		else {
			if (player1.getCurrentPokemon().getConditions().count(Condition::PAR)) {
				if (rand() % 4 == 0) {
					isParalysis1 = true;
				}
				else {
					isParalysis1 = false;
				}
			}
			else {
				isParalysis1 = false;
			}
		}

		

		//if player1 hasn't fainted
		if (!player1.getCurrentPokemon().isFaint() && move1 != "no" && !isParalysis1 && !miss1)
		{

			crit1 = isCritical();//get crit of player.h (todo)
			effective1 = player1.getEffectiveness(move1, player2);
			damage1 = player1.attack(move1, player2, crit1, effective1);

		}
	}
}
void GameManager::burnAndPoison()
{
	if (!player1.getCurrentPokemon().isFaint()) {
		player1.getCurrentPokemon().BurnAndPoison();
	}
	if (!player2.getCurrentPokemon().isFaint()) {
		player2.getCurrentPokemon().BurnAndPoison();
	}
}
/**
 * intent: read file of things to start game, first is pokemon, second is move, third is Gamedata
 * pre: name of first, second and third file
 * post: same as intent
 */
bool GameManager::startSeperateFile(string name1, string name2, string name3)
{
	testMode = false;
	ifstream ifs(name2);
	ifstream pokeData(name1);
	ifstream gameData(name3);

	if (!ifs.is_open() || !pokeData.is_open() || !gameData.is_open()) {
		return false;
	}

	string wholeSkill;

	//get all skills
	while (getline(ifs, wholeSkill))
	{
		//cout << wholeSkill << '\n';
		allSkill.push_back(getSkill(wholeSkill));
	}

	//close skill file
	ifs.close();

	string name;
	while (pokeData >> name)
	{
		int times, hp, atk, def, spAtk, spDef, speed;
		string strType1, strType2;
		PokemonType type1, type2;

		//read type numbers
		pokeData >> times;
		pokeData >> strType1;

		//wait for string to type function
		type1 = strToType(strType1);
		if (times == 2)
		{
			pokeData >> strType2;
			type2 = strToType(strType2);
		}
		pokeData >> hp >> atk >> def >> spAtk >> spDef >> speed;

		if (times == 1)
		{//wait for constructor
			allPokemon.push_back(Pokemon(name, type1, hp, atk, def, spAtk, spDef, speed));
		}
		else if (times == 2)
		{
			allPokemon.push_back(Pokemon(name, type1, type2, hp, atk, def, spAtk, spDef, speed));
		}
	}
	pokeData.close();

	int times;
	int pokeIdx;
	gameData >> times;

	vector<Pokemon> player1Poke;
	vector<Pokemon> player2Poke;

	for (int i = 0; i < times; i++)
	{
		string name;
		int skillCount;
		gameData >> name;
		for (int j = 0; j < allPokemon.size(); j++)
		{
			if (allPokemon[j].getName() == name)
			{
				//find who is the pokemon
				pokeIdx = j;
				break;
			}
		}

		gameData >> skillCount;
		vector<Skill> tempSkills;
		string skillName;

		//get skill of the pokemon
		for (int j = 0; j < skillCount; j++)
		{
			gameData >> skillName;
			for (int k = 0; k < allSkill.size(); k++)
			{
				if (allSkill[k].getName() == skillName)
				{
					tempSkills.push_back(allSkill[k]);
					break;
				}
			}
		}

		allPokemon[pokeIdx].setSkills(tempSkills);

		//push back pokemon to total pokemon of player1
		player1Poke.push_back(allPokemon[pokeIdx]);
	}
	player1 = Player("you", PlayerType::HUMAN, player1Poke, 10, 10, 10, 10);

	gameData >> times;
	for (int i = 0; i < times; i++)
	{
		string name;
		int skillCount;
		gameData >> name;
		for (int j = 0; j < allPokemon.size(); j++)
		{
			if (allPokemon[j].getName() == name)
			{
				//find who is the pokemon
				pokeIdx = j;
				break;
			}
		}

		gameData >> skillCount;
		vector<Skill> tempSkills;
		string skillName;

		//get skill of the pokemon
		for (int j = 0; j < skillCount; j++)
		{
			gameData >> skillName;
			for (int k = 0; k < allSkill.size(); k++)
			{
				if (allSkill[k].getName() == skillName)
				{
					tempSkills.push_back(allSkill[k]);
					break;
				}
			}
		}
		allPokemon[pokeIdx].setSkills(tempSkills);
		//push back pokemon to total pokemon of player2
		player2Poke.push_back(allPokemon[pokeIdx]);

	}
	player2 = Player("notYou", PlayerType::HUMAN, player2Poke, 10, 10, 10, 10);

	return true;

}


/**
 * intent: change string into condition
 * pre: string
 * post: same as intent
 */
Condition GameManager::strToCond(string str)
{
	if (str == "PAR")
	{
		return Condition::PAR;
	}
	else if (str == "BRN")
	{
		return Condition::BRN;
	}
	else if (str == "PSN")
	{
		return Condition::PSN;
	}
	else
	{
		return Condition::NONE;
	}
}

/**
 * intent: change string into cataegorie
 * pre: string to change
 * post: same as intent, return categorie
 */
DamageCategories GameManager::strToCat(string str)
{
	if (str == "Physical")
	{
		return DamageCategories::PHYSICAL;
	}
	else if (str == "Special")
	{
		return DamageCategories::SPECIAL;
	}
	else if (str == "Status")
	{
		return DamageCategories::STATUS;
	}
}

PokemonType GameManager::strToType(string str)
{
	if (str == "Normal") {
		return PokemonType::NOR;
	}
	else if (str == "Fire") {
		return PokemonType::FIR;
	}
	else if (str == "Fighting") {
		return PokemonType::FIG;
	}
	else if (str == "Water") {
		return PokemonType::WAT;
	}
	else if (str == "Flying") {
		return PokemonType::FLY;
	}
	else if (str == "Grass") {
		return PokemonType::GRA;
	}
	else if (str == "Poison") {
		return PokemonType::POI;
	}
	else if (str == "Electric") {
		return PokemonType::ELE;
	}
	else if (str == "Ground") {
		return PokemonType::GRO;
	}
	else if (str == "Psychic") {
		return PokemonType::PSY;
	}
	else if (str == "Rock") {
		return PokemonType::ROC;
	}
	else if (str == "Ice") {
		return PokemonType::ICE;
	}
	else if (str == "Bug") {
		return PokemonType::BUG;
	}
	else if (str == "Dragon") {
		return PokemonType::DRA;
	}
	else if (str == "Ghost") {
		return PokemonType::GHO;
	}
	else if (str == "Dark") {
		return PokemonType::DAR;
	}
	else if (str == "Steel") {
		return PokemonType::STE;
	}
	else if (str == "Fairy") {
		return PokemonType::FAI;
	}
}

/**
 * intent: get skill from string
 * pre: string
 * post: return skill
 */
Skill GameManager::getSkill(string wholeStr)
{
	vector<string> tokens;
	string token;

	//get all substring that represent attributes of skill
	while (1)
	{
		tokens.push_back(wholeStr.substr(0, wholeStr.find(' ')));
		wholeStr = wholeStr.substr(wholeStr.find(' ') + 1);
		if (wholeStr.find(' ') == -1)
		{
			tokens.push_back(wholeStr);
			break;
		}
	}

	//transfer type
	PokemonType type = strToType(tokens[1]);
	DamageCategories cat = strToCat(tokens[2]);
	int power = stoi(tokens[3]);
	int accu = stoi(tokens[4]);
	int pp = stoi(tokens[5]);
	Condition cond = Condition::NONE;
	if (tokens.size() == 7)
	{
		cond = strToCond(tokens[6]);
	}
	Skill skill(tokens[0], type, cat, accu, power, pp, cond);
	return skill;
}