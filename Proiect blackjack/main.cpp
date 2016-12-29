#include "blackjack.h"

using namespace std;

void displayPlay(Player player, string playerCards[], int indexPlayer,
                 Player computer, string computerCards[], int indexComputer)
{
    system("cls");
    cout << "        Black Jack\n\n";
    cout << "\n Your bet: $" << player.bet;
    cout << "\n Money left: $" << player.money;
    cout << "\n\nComputer/House score: " << computer.score;
    cout << "\nComputer/House cards: ";
    for(int i = 0; i < indexComputer; i++)
        cout << computerCards[i] << " " ;
    cout << "\n\nYour Score: " << player.score;
    cout << "\nYour cards: ";
    for(int i = 0; i < indexPlayer; i++)
        cout << playerCards[i] << " " ;
}

void randomCard(Player &player)
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
}

void addNumberCheckAce(Player &player)
{
    if(player.numberCard == 11 && (player.score + player.numberCard) > 21)
        player.score += 1;
    else
        player.score += player.numberCard;
}

void getCard(Player &player, string playerCards[],  int &index)
{
    randomCard(player);
    playerCards[index++] = player.card;
    addNumberCheckAce(player);
}

void computerPlaying(Player &player, string playerCards[], int indexPlayer,
                     Player &computer,  string computerCards[], int &indexComputer)
{
    do
    {
        getCard(computer, computerCards, indexComputer);
        Sleep(500);
        displayPlay(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
        if(player.score > 21 || computer.score == 21)
            break;
    }while(player.score >= computer.score);

    if(player.score > 21 || (player.score < computer.score && computer.score <= 21))
        cout << "\n\nComputer/House won!";
    else if(computer.score > player.score)
    {
        cout << "\n\nYou won!";
        player.money += 2*player.bet;
    }
    else if(player.score == 21 && computer.score == 21)
        cout << "\n\nComputer/House won!";
    cout << "\nDo you want to play again?";
    cout << "\nYes [y] or No [n]\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case 'y':
                system("cls");
                playComputer(player);
                break;
            case 'n':
                exit(0);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'y' || option != 'n');
}

void playing(Player &player, string playerCards[], int &indexPlayer,
            Player &computer,  string computerCards[], int &indexComputer)
{
    char option;
    cout << "\nHit [h] or Stay [s]\n";
    do
    {
        option = getche();
        switch(option)
        {
            case 'h':
                getCard(player, playerCards, indexPlayer);
                displayPlay(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
                playing(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
                break;
            case 's':
                computerPlaying(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'h' || option != 's');
}

void wrongBet(Player player)
{
    cout << "\nYou bet to much!";
    cout << "\nPress [1] to retry\n";
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
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1');
}

void playComputer(Player player)
{
    srand (time(NULL));
    int indexPlayer = 0;
    player.score = 0;
    string playerCards[11];
    getCard(player, playerCards, indexPlayer);
    getCard(player, playerCards, indexPlayer);
    string computerCards[11];
    Player computer;
    int indexComputer = 0;
    computer.score = 0;
    getCard(computer, computerCards, indexComputer);
    cout << "        Black Jack\n\n";
    cout << player.username << " money: $" << player.money;
    cout << "\nPlace your bet: "; cin >> player.bet;
    if(player.money == 0)
    {
        cout << "\nYou are out of money! You can not play on this account!\n\n";
        exit(0);
    }
    else if(player.money - player.bet < 0)
        wrongBet(player);
    player.money -= player.bet;
    displayPlay(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
    playing(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
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
    return 0;
}
