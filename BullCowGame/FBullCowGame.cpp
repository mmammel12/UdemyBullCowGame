#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(3); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

FString FBullCowGame::GetHiddenWord(int32 WordLength) const
{
	int32 SelectWord = rand() % 10;
	FString HiddenWord;

	switch (WordLength)
	{
	case 3:
		HiddenWord = ThreeLetterWords[SelectWord];
		return HiddenWord;
		break;
	case 4:
		HiddenWord = FourLetterWords[SelectWord];
		return HiddenWord;
		break;
	case 5:
		HiddenWord = FiveLetterWords[SelectWord];
		return HiddenWord;
		break;
	case 6:
		HiddenWord = SixLetterWords[SelectWord];
		return HiddenWord;
		break;
	case 7:
		HiddenWord = SevenLetterWords[SelectWord];
		return HiddenWord;
		break;
	}
}

bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 8}, {5, 12}, {6, 18}, {7, 25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(int32 Difficulty)
{
	MyHiddenWord = GetHiddenWord(Difficulty);
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	 if (!IsLetters(Guess))
	{
		return EGuessStatus::Not_Letters;
	}
	else if (!IsIsogram(Guess)) // If guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // If guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != Guess.length()) // If guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWchar = 0; MHWchar < WordLength; MHWchar++)
	{
		// loop through all letters in the guess word
		for (int32 Gchar = 0; Gchar < WordLength; Gchar++)
		{
			if (MHWchar == Gchar && Guess[MHWchar] == MyHiddenWord[Gchar]) // if they are in the right place
			{
				BullCowCount.Bulls++; // increment bulls
			}
			else if (Guess[MHWchar] == MyHiddenWord[Gchar]) // if not in the right place
			{
				BullCowCount.Cows++; // increment cows
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; } // treat 0 and 1 letter words as isograms

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) // for all letters in Guess
	{
		Letter = tolower(Letter); // convert to lowercase
		if (LetterSeen[Letter]) { return false; } // NOT an isogram
		else 
		{
			LetterSeen[Letter] = true;
		}
	}

	return true; // example: if /0 is entered
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) { return false; } // NOT a lowercase letter
	}
	return true;
}

bool FBullCowGame::IsLetters(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (isdigit(Letter)) { return false; }
	}
	return true;
}
