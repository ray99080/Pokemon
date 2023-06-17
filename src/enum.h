#pragma once

enum class PokemonType {
	NOR = 0,
	FIR = 1,
	WAT = 2,
	ELE = 3,
	GRA = 4,
	ICE = 5,
	FIG = 6,
	POI = 7,
	GRO = 8,
	FLY = 9,
	PSY = 10,
	BUG = 11,
	ROC = 12,
	GHO = 13,
	DRA = 14,
	DAR = 15,
	STE = 16,
	FAI = 17
};

enum class Condition { PAR = 0, BRN = 1, PSN = 2, NONE = 3 };

enum class PlayerType { HUMAN = 0, ROBOT = 1 };

enum class DamageCategories { SPECIAL, PHYSICAL, STATUS };
