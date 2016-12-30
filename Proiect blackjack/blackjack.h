#ifndef BLACKJACK_H_INCLUDED
#define BLACKJACK_H_INCLUDED
#endif // BLACKJACK_H_INCLUDED

#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct searchValidationPlayer
{
    string username;
    string password;
    int money;
    int validation;
};

struct Player
{
    string username;
    string card;
    int numberCard;
    int bet;
    int score;
    int money;
};

void displayPlay(Player player, string playerCards[], int indexPlayer,
                 Player computer, string computerCards[], int indexComputer);
void randomCard(Player &player);
void addNumberCheckAce(Player &player);
void getCard(Player &player, string playerCards[],  int &index);
void updateData(Player &player);
void computerPlaying(Player &player, string playerCards[], int indexPlayer,
                     Player &computer,  string computerCards[], int &indexComputer);
void playing(Player &player, string playerCards[], int &indexPlayer,
            Player &computer,  string computerCards[], int &indexComputer);
void wrongBet(Player player);
void playComputer(Player player);
searchValidationPlayer searchForExistatingAccount(string username, string password, bool ok);
void loading(string name);
void menu(Player player);
void logIn();
void newAccount();
void userAccount();
