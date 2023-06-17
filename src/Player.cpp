#include "Player.h"

//constructors/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player()
{
	this->name = "Default Name";
	this->type = PlayerType::HUMAN;
	this->pokemons.resize(3, Pokemon());
	this->currentPokemon_index = 0;
	this->potion = 0;
	this->superPotion = 0;
	this->hyperPotion = 0;
	this->maxPotion = 0;
}

Player::Player(string name, PlayerType type, vector<Pokemon> pokemon_Construct, int potion, int superPotion, int hyperPotion, int maxPotion)
{
	this->name = name;
	this->type = type;
	this->pokemons.resize(pokemon_Construct.size(), Pokemon());
	for (int i = 0; i < this->pokemons.size(); ++i)
	{
		this->pokemons[i] = pokemon_Construct[i];
	}
	this->currentPokemon_index = 0;
	this->potion = potion;
	this->superPotion = superPotion;
	this->hyperPotion = hyperPotion;
	this->maxPotion = maxPotion;
}

//accessors////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Pokemon& Player::getPokemon(string name)
{
	for (int i = 0; i < this->pokemons.size(); ++i)
	{
		if (this->pokemons[i].getName() == name)
		{
			return this->pokemons[i];
		}
	}

	//debug console
	cout << "ERROR: Pokemon of name: " << name << " not found in getPokemon()" << endl;
	system("pause");
}

//mutators/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::setName(string newName) { this->name = newName; }
void Player::setType(PlayerType newType) { this->type = newType; }
void Player::setCurrentPokemon_index(int index)
{
	if (index >= this->pokemons.size() || index < 0)
	{
		//exception
		string log = "ERROR: index from player" + this->name + "'s pokemon out of range";
		throw log;
	}
	else
	{
		this->currentPokemon_index = index;
	}
}
void Player::setPotion(int number) { this->potion = number; }
void Player::setSuperPotion(int number) { this->superPotion = number; }
void Player::setHyperPotion(int number) { this->hyperPotion = number; }
void Player::setMaxPotion(int number) { this->maxPotion = number; }

//functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::isAllFaint()
{
	for (int i = 0; i < this->pokemons.size(); ++i)
	{
		if (!(this->pokemons[i].isFaint()))
		{
			return false;
		}
	}

	return true;
}

bool Player::isFaint(string name)
{
	return this->getPokemon(name).isFaint();
}

void Player::swapPokemon(string name)
{
	for (int i = 0; i < this->pokemons.size(); ++i)
	{
		if (this->pokemons[i].getName() == name)
		{
			this->currentPokemon_index = i;
			return;
		}
	}

	//exception
	string log = "ERROR: Pokemon of name : " + name + " not found in swapPokemon()";
	throw log;
}

void Player::swapToNext()
{
	for (int i = 0; i < this->pokemons.size(); ++i)
	{
		if (!(this->pokemons[i].isFaint()))
		{
			this->currentPokemon_index = i;
			return;
		}
	}

	//exception
	throw "ERROR: Pokemon available not found in swapToNext()";
}

void Player::usePotion(string potionName, string pokeName)
{
	//find pokemon
	Pokemon& target = getPokemon(pokeName);
	bool pokeFound = false;
	for (int i = 0; i < this->pokemons.size(); ++i)
	{
		if (this->pokemons[i].getName() == pokeName)
		{
			Pokemon& target = this->pokemons[i];
			pokeFound = true;
			break;
		}
	}
	//exception
	if (!pokeFound)
	{
		string log = "ERROR: Pokemon of name : " + pokeName + " not found in usePotion()";
		throw log;
	}

	//change potion string to all-lower-case
	potionName = strToLower(potionName);

	//potion type determine
	if (potionName == "potion")
	{
		if (this->potion > 0)
		{
			this->potion--;
			target.heal(POTION_HEALS);
			return;
		}

		//exception
		throw "ERROR: no potion left in usePotion()";
	}
	else if (potionName == "superpotion")
	{
		if (this->superPotion > 0)
		{
			this->superPotion--;
			target.heal(SUPERPOTION_HEALS);
			return;
		}

		//exception
		throw "ERROR: no potion left in useSuperPotion()";
	}
	else if (potionName == "hyperpotion")
	{
		if (this->hyperPotion > 0)
		{
			this->hyperPotion--;
			target.heal(HYPERPOTION_HEALS);
			return;
		}

		//exception
		throw "ERROR: no potion left in useHyperPotion()";
	}
	else if (potionName == "maxpotion")
	{
		if (this->maxPotion > 0)
		{
			this->maxPotion--;
			target.fullHP();
			return;
		}

		//exception
		throw "ERROR: no potion left in useMaxPotion()";
	}
	//exception
	else
	{
		throw "ERROR: no such potion name in usePotion()";
	}
}

int Player::attack(string skillName, Player& target, bool critical, float effectiveness)
{
	Pokemon& pokeTarg = target.getCurrentPokemon();
	if (this->getCurrentPokemon().isSkillExist(skillName))
	{
		Skill& skillUse = this->getCurrentPokemon().getSkill(skillName);

		//damage calculate
		int damage = 0;
		if (skillUse.getDamageCategories() != DamageCategories::STATUS)
		{
			damage = (int)
				(
					(
						((2.0 * (double)LEVEL + 10.0) / 250.0) *
						skillUse.getPower() *	//Power
						(skillUse.getDamageCategories() == DamageCategories::SPECIAL ? this->getCurrentPokemon().getSpecialAttack() : this->getCurrentPokemon().getAttack()) /	//A
						(skillUse.getDamageCategories() == DamageCategories::SPECIAL ? pokeTarg.getSpecialDefense() : pokeTarg.getDefense())	//D
						+ 2.0
						) *
					(critical ? 1.5 : 1.0) *	//Critical
					this->sameTypeAttackBonus(skillUse, this->getCurrentPokemon()) *	//STAB
					effectiveness	//Type
					);

			//do attack (access HP of the target's Pokemon)
			pokeTarg.damage(damage);
		}

		//condition add
		Condition holdCond = skillUse.getCondition();
		pokeTarg.debuff(skillUse.getCondition());
		bool hold = pokeTarg.getConditions().count(Condition::PSN);

		//reduce the pp of the used Skill
		skillUse.useSkill();

		//return value
		if (skillUse.getDamageCategories() == DamageCategories::STATUS)
			return 0;
		else
			return damage;
	}
	else
	{
		throw "ERROR: skill not found in attack()";
	}
}

float Player::getEffectiveness(string skillName, Player& target)
{
	Pokemon& pokeTarg = target.getCurrentPokemon();
	if (this->getCurrentPokemon().isSkillExist(skillName))
	{
		Skill& skillUse = this->getCurrentPokemon().getSkill(skillName);

		float effe = 1.0;
		vector<PokemonType> holdTargTypes = pokeTarg.getTypes();
		for (int i = 0; i < holdTargTypes.size(); ++i)
		{
			effe = effe * attrBoard[static_cast<int>(skillUse.getPokemonType())][static_cast<int>(holdTargTypes[i])];
		}

		return effe;
	}
	else
	{
		throw "ERROR: skill not found in getEffectiveness()";
	}
}

float Player::sameTypeAttackBonus(Skill& skill, Pokemon& attacker)
{
	vector<PokemonType> holdTypes = attacker.getTypes();
	for (int i = 0; i < holdTypes.size(); ++i)
	{
		if (holdTypes[i] == skill.getPokemonType())
		{
			return 1.5;
		}
	}

	return 1.0;
}

bool isCritical()
{
	if (testMode)
		return false;

	int randomValue = (rand() % criticalChance);

	if (randomValue == 0)
		return true;
	else
		return false;
}

string Player::getRandomValidSkill()
{
	vector<Skill>& skills = this->getCurrentPokemon().getSkills();

	vector<Skill> validSkills;
	for (int i = 0; i < skills.size(); i++)
	{
		if (skills[i].getPP() > 0)
		{
			validSkills.push_back(skills[i]);
		}
	}

	if (validSkills.size() > 0)
	{
		int randIndex = rand() % validSkills.size();
		return validSkills[randIndex].getName();
	}
	//no skill valid
	else
	{
		return "NOSKILL";
	}
}

string strToLower(string str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if ('A' <= str[i] && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}

	return str;
}