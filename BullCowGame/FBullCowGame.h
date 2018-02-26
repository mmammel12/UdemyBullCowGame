#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Not_Letters
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord(int32) const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(int32);

	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString ThreeLetterWords[10] = { "jog", "wax", "gym", "sky", "ivy", "bet", "who", "icy", "fun", "wig" };
	FString FourLetterWords[10] = { "wack", "raid", "gold", "main", "note", "hawk", "daft", "goal", "wand", "myth" };
	FString FiveLetterWords[10] = { "bacon", "fable", "knife", "laser", "party", "vague", "banjo", "feign", "lodge", "prawn" };
	FString SixLetterWords[10] = { "planet", "alcove", "carbon", "orchid", "wealth", "torque", "shield", "antler", "castle", "wisdom" };
	FString SevenLetterWords[10] = { "bayonet", "dispute", "gravity", "harmony", "lunatic", "pasture", "sandbox", "blanket", "dolphin", "gymnast" };
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsLetters(FString) const;
};