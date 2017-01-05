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
    string password;
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
void updateData(Player &player, bool ok);
void computerPlaying(Player &player, string playerCards[], int &indexPlayer,
                     Player &computer,  string computerCards[], int &indexComputer);
void playing(Player &player, string playerCards[], int &indexPlayer,
            Player &computer,  string computerCards[], int &indexComputer);
void wrongBet(Player &player);
void playComputer(Player &player);
void winner(Player &player, Player &secondPlayer, Player &computer);
void secondComputerPlaying(Player &player, Player &computer, string computerCards[], int &indexComputer,
            Player &secondPlayer, string secondPlayerCards[],int &indexSecondPlayer);
void secondPlayerPlaying(Player &player, Player &computer,  string computerCards[], int &indexComputer,
            Player &secondPlayer, string secondPlayerCards[], int &indexSecondPlayer);
void secondWrongBet(Player &player, Player &computer, string computerCards[], int &indexComputer,
                     Player &secondPlayer, bool first);
void firstTwoCardsSecondPlayer(Player &player, Player &computer,  string computerCards[], int &indexComputer,
            Player &secondPlayer, bool firstBlackJack);
void firstPlayerPlaying(Player &player, string playerCards[], int &indexPlayer,
            Player &computer,  string computerCards[], int &indexComputer,
            Player &secondPlayer);
void playPlayer(Player &player, Player &secondPlayer);
void returnToSecondLogIn(Player &player);
void secondLogIn(Player &player);
void secondNewAccount(Player &player);
void secondPlayer(Player &player);
searchValidationPlayer searchForAccount(string username, string password, bool ok);
void loading(string name);
void returnToMenu(Player &player);
void consultPlayerMoney(Player &player);
void changeUsername(Player &player);
void hidePassword(string &password);
void changePassword(Player &player);
void changeMoney(Player &player);
void changeData(Player &player);
void menu(Player &player);
void logIn();
void newAccount();
void userAccount();
