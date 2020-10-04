// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
// #include "Math/UnrealMathUtility.h"

/*=================================== BeginPlay ======================================== */

;void UBullCowCartridge::BeginPlay() // When the game starts 
{
    Super::BeginPlay(); // Print Welcome Message below...
    
    Isograms = GetValidWords(AnimalWords);
    // PrintLine(TEXT("%i"), FMath::RandRange(0, 10));
    // GetValidWords(AnimalWords);
    SetUpGame();
    // PrintLine(TEXT("The number of possible words is %i"), AnimalWords.Num());
    // PrintLine(TEXT("The number of valid words is: %i."), GetValidWords(AnimalWords).Num());
}

/*=================================== OnInput ======================================== */

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else // Checking player guess
    {
    ProcessGuess(PlayerInput);
    }
}

/*=================================== SetUpGame ======================================== */

void UBullCowCartridge::SetUpGame()
{
    // welcome the player
    PrintLine(TEXT("Hello and welcome to Bull & Cows!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    // PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug line
    PrintLine(TEXT("You have %i Lives."), Lives);
    PrintLine(TEXT("Type in your guess then \npress enter to continue...")); // prompt player for a guess
}

/*=================================== EndGame ======================================== */

void UBullCowCartridge::EndGame()
{   
    bGameOver = true;
    // prompt to play again
    PrintLine(TEXT("\nPress enter to restart the game."));
}

/*=================================== ProcessGuess ======================================== */

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord) // Player wins
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
            return;
        }
    
    if (Guess.Len() != HiddenWord.Len()) // check right number of chars    
        {
            PrintLine(TEXT("The hidden word is %i letters long. \nPlease try again!"), HiddenWord.Len()); // prompt to guess again
            PrintLine(TEXT("You have %i lives remaining."), Lives); // show lives remaining
            return;
        }
    
    if (!IsIsogram(Guess)) // check if word is an isogram
    {   
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }
    
    PrintLine(TEXT("You've lost a life!"));  // Remove a life
    --Lives; 
        
    if (Lives <= 0) 
        {
            ClearScreen();
            PrintLine(TEXT("Game Over!"));
            PrintLine(TEXT("The hidden word was: %s!"), *HiddenWord);
            EndGame();
            return;
        }
        // Show the player the bulls and cows
        
        FBullCowCount Score = GetBullCows(Guess);

        PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);
}

/*=================================== IsIsogram ======================================== */

bool UBullCowCartridge::IsIsogram(const FString& Word) const 
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

/*=================================== GetValidAnimalWords======================================== */

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

/*=================================== GetBullCows ======================================== */

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 CompareIndex = 0; CompareIndex < HiddenWord.Len(); CompareIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[CompareIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}