// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge2.h"
// #include "Math/UnrealMathUtility.h"

/*=================================== Welcome Terminal ======================================== */

;void UBullCowCartridge2::WelcomeTerminal() // When player clicks terminal
{
    PrintLine(TEXT("Hello and welcome to Bull & Cows!"));
    PrintLine(TEXT("There are a variety of games to play, including: \n"));
    PrintLine(TEXT("Guess the Isogram \nFish Farm and \n Moo Seek Moo!"));
    PrintLine(TEXT("Take a look around. To access the games, hit Enter at a terminal."));
};