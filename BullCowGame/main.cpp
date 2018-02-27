/*
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
int main();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // Instatiates a new game

//entry point for application
int main() 
{
	do
	{
	PrintIntro();
	PlayGame();
	} while (AskToPlayAgain());
	return 0; //exit the application
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "  << BCGame.GetMaxTries() << "\nEnter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (a word without any repeated letters)\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please type your guess in all lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Letters:
			std::cout << "Please enter a word containing no numbers.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get valid input
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "+-+-+-+-+-+-+-+\n";
		std::cout << "|W|I|N|N|E|R|!|\n";
		std::cout << "+-+-+-+-+-+-+-+\n\n";
	}
	else
	{
		std::cout << "No Turns left, better luck next time!\n\n";
	}
	return;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}


void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n";
	std::cout << "You have " << BCGame.GetMaxTries() << " tries to win.\n\n";
	return;
}
