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
    int money;
};

Player randomCard(Player &player)
{
    string suits[] = {"Club", "Diamond", "Hart", "Spade"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Ace", "Jack", "Queen", "King"};
    int indexRank = rand()%13;
    int indexSuit = rand()%4;
    if(indexRank >= 10)
        player.numberCard = 10;
    else
        player.numberCard = indexRank + 2;
    switch(indexSuit)
    {
        case 0:
            player.card = ranks[indexRank] + "_of_" + suits[indexSuit];
            break;
        case 1:
            player.card = ranks[indexRank] + "_of_" + suits[indexSuit];
            break;
        case 2:
            player.card = ranks[indexRank] + "_of_" + suits[indexSuit];
            break;
        case 3:
            player.card = ranks[indexRank] + "_of_" + suits[indexSuit];
            break;
    }
    return player;

}

void playComputer(Player player)
{
    int bet;
    int currentNumberCard;
    srand (time(NULL));
    randomCard(player);
    int firstNumberCard = player.numberCard;
    string firstCard = player.card;
    randomCard(player);
    int secondNumberCard = player.numberCard;
    string secondCard = player.card;
    cout << "        Black Jack\n\n";
    cout << player.username << " money: $" << player.money;
    cout << "\nPlace your bet: "; cin >> bet;
    cout << "\n Your bet: $" << bet;
    cout << "\n Money left: $" << player.money - bet;
    cout << "\nScore: " << firstNumberCard + secondNumberCard;
    cout << "\nYour first two cards: " << firstCard << " " << secondCard;
}

searchValidationPlayer searchForExistatingAccount(string username, string password, bool ok)
{
    searchValidationPlayer searchPlayer;
    fstream playersData;
    playersData.open("players.dat", ios::in);
    if(playersData.is_open())
    {
        while(!playersData.eof())
        {
            playersData >> searchPlayer.username;
            playersData >> searchPlayer.password;
            playersData >> searchPlayer.money;
            if(!ok && searchPlayer.username == username && searchPlayer.password != password)
            {
                searchPlayer.validation = -1;
                return searchPlayer;
            }
            if(!ok && searchPlayer.username == username && searchPlayer.password == password)
            {
                searchPlayer.validation = 0;
                return searchPlayer;
            }
            if(ok && searchPlayer.username == username)
            {
                searchPlayer.validation = 1;
                return searchPlayer;
            }
        }
    }
    else
        cout << "Error file!";
    playersData.close();
    if(ok)
        searchPlayer.validation = 2;
    else
        searchPlayer.validation = -1;
    return searchPlayer;
}

void menu(Player player)
{
    cout << "        Black Jack\n\n";
    cout << "Please select one of the options!";
    cout << "\n[1] Play with computer \n[2] Play with a friend \n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                playComputer(player);
                break;
            case '2':
                //playPlayer();
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1' || option != '2');
}

void logIn()
{
    string username, password;
    cout << "        Log in!\n\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    searchValidationPlayer checkPlayer = searchForExistatingAccount(username, password, false);
    if(checkPlayer.validation == -1)
    {
        cout << "Username or password wrong! Press [1] to retry!\n";
        char option;
        do
        {
            option = getche();
            switch(option)
            {
                case '1':
                    system("cls");
                    logIn();
                default:
                    cout << "\nYou pressed a wrong button! Try again\n";
            }
        }while(option != '1');
    }
    else
        cout << "Log in succesfully!\n";
    Sleep(1000);
    system("cls");
    Player player;
    player.username = checkPlayer.username;
    player.money = checkPlayer.money;
    menu(player);
}

void newAccount()
{
    string username, password;
    const int money = 100;
    fstream playersData;
    cout << "        Create new account!\n\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    searchValidationPlayer checkPlayer = searchForExistatingAccount(username, password, true);
    system ("cls");
    if(checkPlayer.validation == 1)
    {
        cout << "You already have a account!\n";
        logIn();
    }
    else
    {
        playersData.open("players.dat", ios::app);
        playersData << username << " ";
        playersData << password << " ";
        playersData << money << endl;
        playersData.close();
        cout << "You have registered successfully\n";
        cout << "Press [1] to log in\n";
        char option;
        do
        {
            option = getche();
            switch(option)
            {
                case '1':
                    system("cls");
                    logIn();
                    break;
                default:
                    cout << "\nYou pressed a wrong button! Try again\n";
            }
        }while(option != '1');
    }
}

void userAccount()
{
    system("cls");
    cout << "        Welcome to Black Jack\n\n";
    cout << "Please select one of the options!";
    cout << "\n[1] Create a new account \n[2] I have a account. Log in \n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                newAccount();
                break;
            case '2':
                system("cls");
                logIn();
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1' || option != '2');
}


int main()
{
    userAccount();
}
