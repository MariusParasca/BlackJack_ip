#include "blackjack.h"

using namespace std;

void displayPlay(Player player, string playerCards[], int indexPlayer,
                 Player computer, string computerCards[], int indexComputer)
{
    system("cls");
    cout << "        Black Jack\n\n";
    cout << "\n " << player.username << " bet: $" << player.bet;
    cout << "\n Money left: $" << player.money - player.bet;
    cout << "\n\nComputer/House score: " << computer.score;
    cout << "\nComputer/House cards: ";
    for(int i = 0; i < indexComputer; i++)
        cout << computerCards[i] << " " ;
    cout << "\n\n" << player.username << " score: " << player.score;
    cout << "\n" << player.username << " cards: ";
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

void updateData(Player &player, bool ok)
{
    string username, password;
    int money;
    ifstream playersData;
    ofstream temp;
    playersData.open("players.dat", fstream::in);
    temp.open("temp.dat", fstream::out);
    playersData >> username;
    playersData >> password;
    playersData >> money;
    if(playersData.is_open() && temp.is_open())
    {
        while(!playersData.eof())
        {
            if(!ok)
                if(username == player.username)
                {
                    temp << username << " ";
                    temp << password << " ";
                    temp << player.money;
                    temp << endl;
                }
                else
                {
                    temp << username << " ";
                    temp << password << " ";
                    temp << money;
                    temp << endl;
                }
            else if(ok)
            {
                if((username != player.username && password == player.password && money == player.money) ||
                   (username == player.username && password != player.password && money == player.money))
                {
                    temp << player.username << " ";
                    temp << player.password << " ";
                    temp << player.money;
                    temp << endl;
                }
                else
                {
                    temp << username << " ";
                    temp << password << " ";
                    temp << money;
                    temp << endl;
                }
            }
            playersData >> username;
            playersData >> password;
            playersData >> money;
        }
    }
    else
        cout << "Error loading the file!";

    playersData.close();
    temp.close();
    rename("players.dat", "1.dat");
    rename("temp.dat", "players.dat");
    rename("1.dat", "temp.dat");
    ofstream clean;
    clean.open("temp.dat", ofstream::out | ofstream::trunc);
    clean.close();
}

void computerPlaying(Player &player, string playerCards[], int &indexPlayer,
                     Player &computer,  string computerCards[], int &indexComputer, bool blackJack)
{
    do
    {
        Sleep(500);
        if(blackJack)
        {
            getCard(computer, computerCards, indexComputer);
            displayPlay(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
            break;
        }
        else
            getCard(computer, computerCards, indexComputer);
        displayPlay(player, playerCards, indexPlayer, computer, computerCards, indexComputer);
        if(player.score > 21 )
            break;
    }while(computer.score < 17);

    Sleep(500);
    if(blackJack && computer.score != 21)
    {
        cout << "\n\nBlackJack! ";
        player.money += player.bet + player.bet/2;
    }
    else if((computer.score > player.score && player.score <= 21 && computer.score > 21) ||
       (computer.score < player.score && player.score <= 21 && computer.score < 21))
    {
        cout << "\n\nYou won!";
        player.money += player.bet;
    }
    else if(player.score == computer.score && player.score <= 21)
    {
        cout << "\n\nYou made tie!";
    }
    else
    {
        cout << "\n\nYou lost!";
        player.money -= player.bet;
    }

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
                updateData(player, false);
                exit(0);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'y' || option != 'n');
}

void playing(Player &player, string playerCards[], int &indexPlayer,
            Player &computer, string computerCards[], int &indexComputer)
{
    bool blackJack = false;
    char option;
    if(player.score == 21 && indexPlayer == 2)
        cout << "";
    else if(indexPlayer == 2 && player.money >= 2*player.bet)
        cout << "\n\nHit [h] , Stay [s] or Double[d]\n";
    else
        cout << "\n\nHit [h] or Stay [s]\n";
    do
    {
        if(player.score > 21)
            option = 's';
        else if(player.score == 21 && indexPlayer == 2)
        {
            blackJack = true;
            option = 's';
        }
        else
            option = getche();
        switch(option)
        {
            case 'h':
                getCard(player, playerCards, indexPlayer);
                displayPlay(player, playerCards, indexPlayer,
                            computer, computerCards, indexComputer);
                playing(player, playerCards, indexPlayer,
                        computer, computerCards, indexComputer);
                break;
            case 's':
                computerPlaying(player, playerCards, indexPlayer,
                                computer, computerCards, indexComputer, blackJack);
                break;
            case 'd':
                player.bet = 2*player.bet;
                getCard(player, playerCards, indexPlayer);
                displayPlay(player, playerCards, indexPlayer,
                            computer, computerCards, indexComputer);
                computerPlaying(player, playerCards, indexPlayer,
                                computer, computerCards, indexComputer, blackJack);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'h' || option != 's' || option != 'd');
}

void wrongBet(Player &player)
{
    cout << "\nYour bet is wrong! Try again!";
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

void playComputer(Player &player)
{
    srand (time(NULL));
    int indexPlayer = 0;
    player.score = 0;
    string playerCards[11];
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
        updateData(player, false);
        cout << "\nYou are out of money! You can not play on this account!\n\n";
        exit(0);
    }
    else if(player.money - player.bet < 0 || player.bet <= 0)
        wrongBet(player);
    getCard(player, playerCards, indexPlayer);
    getCard(player, playerCards, indexPlayer);
    displayPlay(player, playerCards, indexPlayer,
                computer, computerCards, indexComputer);
    playing(player, playerCards, indexPlayer,
            computer, computerCards, indexComputer);
}

void winner(Player &player, Player &secondPlayer, Player &computer, bool firstBlackJack, bool secondBlackJack)
{
    cout << "\n\n" << player.username << " score: " << player.score << endl;
    cout << secondPlayer.username << " score: " << secondPlayer.score << endl;
    cout << "Computer/House score: " << computer.score << endl;

    if(player.score == 0)
        cout << "\n\n" << player.username << " is out of money!";
    else if(firstBlackJack && computer.score != 21)
    {
        cout << "\n\n" << player.username << ": BlackJack! ";
        player.money += player.bet + player.bet/2;
    }
    else if((computer.score > player.score && player.score <= 21 && computer.score > 21) ||
       (computer.score < player.score && player.score <= 21 && computer.score < 21))
    {
        cout << "\n\n" << player.username << " won!";
        player.money += player.bet;
    }
    else if(player.score == computer.score && player.score <= 21)
    {
        cout << "\n\n" << player.username << " made tie!";
    }
    else
    {
        cout << "\n\n" << player.username << " lost!";
        player.money -= player.bet;
    }

    if(secondPlayer.score == 0)
        cout << "\n\n" << secondPlayer.username << " is out of money!";
    else if(secondBlackJack && computer.score != 21)
    {
        cout << "\n" << secondPlayer.username << ": BlackJack! ";
        secondPlayer.money += secondPlayer.bet + secondPlayer.bet/2;
    }
    else if((computer.score > secondPlayer.score && secondPlayer.score <= 21 && computer.score > 21) ||
       (computer.score < secondPlayer.score && secondPlayer.score <= 21 && computer.score < 21))
    {
        cout << "\n" << secondPlayer.username << " won!";
        secondPlayer.money += secondPlayer.bet;
    }
    else if(secondPlayer.score == computer.score && secondPlayer.score <= 21)
    {
        cout << "\n" << secondPlayer.username << " made tie!";
    }
    else
    {
        cout << "\n" << secondPlayer.username << " lost!";
        secondPlayer.money -= secondPlayer.bet;
    }

    cout << "\n\nDo you want to play again?";
    cout << "\nYes [y] or No [n]\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case 'y':
                system("cls");
                playPlayer(player, secondPlayer);
                break;
            case 'n':
                updateData(player, false);
                updateData(secondPlayer, false);
                exit(0);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'y' || option != 'n');
}

void secondComputerPlaying(Player &player, Player &computer, string computerCards[], int &indexComputer,
            Player &secondPlayer, string secondPlayerCards[],int &indexSecondPlayer,
            bool firstBlackJack, bool secondBlackJack)
{
    do
    {
        Sleep(500);
        if(firstBlackJack && secondBlackJack)
        {
            getCard(computer, computerCards, indexComputer);
            displayPlay(secondPlayer, secondPlayerCards, indexSecondPlayer,
                        computer, computerCards, indexComputer);
            break;
        }
        else
            getCard(computer, computerCards, indexComputer);
        displayPlay(secondPlayer, secondPlayerCards, indexSecondPlayer,
                    computer, computerCards, indexComputer);
        if(player.score > 21 && secondPlayer.score > 21)
            break;
    }while(computer.score < 17);

    Sleep(500);
    winner(player, secondPlayer, computer, firstBlackJack, secondBlackJack);
}

void secondPlayerPlaying(Player &player, Player &computer,  string computerCards[], int &indexComputer,
            Player &secondPlayer, string secondPlayerCards[], int &indexSecondPlayer, bool firstBlackJack)
{
    bool secondBlackJack = false;
    char option;
    if(secondPlayer.score == 21 && indexSecondPlayer == 2)
        cout << "";
    else if(indexSecondPlayer == 2 && secondPlayer.money >= 2*secondPlayer.bet)
        cout << "\n\nHit [h] , Stay [s] or Double[d]\n";
    else
        cout << "\n\nHit [h] or Stay [s]\n";
    do
    {
        if(secondPlayer.score > 21)
            option = 's';
        else if(secondPlayer.score == 21 && indexSecondPlayer == 2)
        {
            secondBlackJack = true;
            option = 's';
        }
        else
            option = getche();
        switch(option)
        {
            case 'h':
                getCard(secondPlayer, secondPlayerCards, indexSecondPlayer);
                displayPlay(secondPlayer, secondPlayerCards, indexSecondPlayer,
                            computer, computerCards, indexComputer);
                secondPlayerPlaying(player, computer, computerCards, indexComputer,
                                    secondPlayer, secondPlayerCards, indexSecondPlayer, firstBlackJack);
                break;
            case 's':
                secondComputerPlaying(player, computer, computerCards, indexComputer,
                                      secondPlayer, secondPlayerCards, indexSecondPlayer,
                                      firstBlackJack, secondBlackJack);
                break;
            case 'd':
                secondPlayer.bet = 2*secondPlayer.bet;
                getCard(secondPlayer, secondPlayerCards, indexSecondPlayer);
                displayPlay(secondPlayer, secondPlayerCards, indexSecondPlayer,
                            computer, computerCards, indexComputer);
                secondComputerPlaying(player, computer, computerCards, indexComputer,
                                      secondPlayer, secondPlayerCards, indexSecondPlayer,
                                      firstBlackJack, secondBlackJack);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'h' || option != 's');
}

void secondWrongBet(Player &player, Player &computer, string computerCards[], int &indexComputer,
                     Player &secondPlayer, bool first, bool firstBlackJack)
{
    cout << "\nYour bet is wrong! Try again!";
    cout << "\nPress [1] to retry\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                if(first == true)
                    playPlayer(player, secondPlayer);
                else
                    firstTwoCardsSecondPlayer(player, computer, computerCards, indexComputer, secondPlayer, firstBlackJack);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1');
}

void firstTwoCardsSecondPlayer(Player &player, Player &computer,  string computerCards[], int &indexComputer,
            Player &secondPlayer, bool firstBlackJack)
{
    int indexSecondPlayer = 0;
    string secondPlayerCards[11];

    cout << "        Black Jack\n\n";
    cout << secondPlayer.username << " money: $" << secondPlayer.money;
    cout << "\nPlace your bet: "; cin >> secondPlayer.bet;
    if(secondPlayer.money == 0)
    {
        secondPlayer.bet = 0;
        cout << "\nYou are out of money! You can not play on this account!\n\n";
        Sleep(2000);
        system("cls");
        secondComputerPlaying(player, computer, computerCards, indexComputer,
                                      secondPlayer, secondPlayerCards, indexSecondPlayer,
                                      firstBlackJack, false);
    }
    else if(secondPlayer.money - secondPlayer.bet < 0 || secondPlayer.bet <= 0)
        secondWrongBet(player, computer, computerCards, indexComputer, secondPlayer, false, firstBlackJack);
    getCard(secondPlayer, secondPlayerCards, indexSecondPlayer);
    getCard(secondPlayer, secondPlayerCards, indexSecondPlayer);
    displayPlay(secondPlayer, secondPlayerCards, indexSecondPlayer,
                computer, computerCards, indexComputer);
    secondPlayerPlaying(player, computer, computerCards, indexComputer,
                        secondPlayer, secondPlayerCards, indexSecondPlayer, firstBlackJack);
}

void firstPlayerPlaying(Player &player, string playerCards[], int &indexPlayer,
            Player &computer,  string computerCards[], int &indexComputer,
            Player &secondPlayer)
{
    bool firstBlackJack = false;
    char option;
    if((player.score == 21 && indexPlayer == 2) || player.score > 21)
        cout << "";
    else if(indexPlayer == 2 && player.money >= 2*player.bet)
        cout << "\n\nHit [h] , Stay [s] or Double[d]\n";
    else
        cout << "\n\nHit [h] or Stay [s]\n";
    do
    {
        if(player.score > 21)
        {
            option = 's';
            cout << "\n\nBusted! " << secondPlayer.username << " wait a second";
            Sleep(3000);
        }
        else if(player.score == 21 && indexPlayer == 2)
        {
            cout << "\n\nBlackJack! " << secondPlayer.username << " wait a second";
            firstBlackJack = true;
            option = 's';
            Sleep(3000);
        }
        else
            option = getche();
        switch(option)
        {
            case 'h':
                getCard(player, playerCards, indexPlayer);
                displayPlay(player, playerCards, indexPlayer,
                            computer, computerCards, indexComputer);
                firstPlayerPlaying(player, playerCards, indexPlayer,
                                   computer, computerCards, indexComputer, secondPlayer);
                break;
            case 's':
                Sleep(500);
                system("cls");
                firstTwoCardsSecondPlayer(player, computer, computerCards, indexComputer, secondPlayer, firstBlackJack);
                break;
            case 'd':
                player.bet = 2*player.bet;
                getCard(player, playerCards, indexPlayer);
                displayPlay(player, playerCards, indexPlayer,
                            computer, computerCards, indexComputer);
                Sleep(500);
                system("cls");
                firstTwoCardsSecondPlayer(player, computer, computerCards, indexComputer, secondPlayer, firstBlackJack);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != 'h' || option != 's');
}

void playPlayer(Player &player, Player &secondPlayer)
{
    srand (time(NULL));
    int indexPlayer = 0;
    player.score = 0;
    secondPlayer.score = 0;
    string playerCards[11];
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
        player.bet = 0;
        cout << "\nYou are out of money! You can not play on this account!\n\n";
        Sleep(2000);
        system("cls");
        firstTwoCardsSecondPlayer(player, computer, computerCards, indexComputer, secondPlayer, false);
    }
    else if(player.money - player.bet < 0 || player.bet <= 0)
        secondWrongBet(player, computer, computerCards, indexComputer,
                       secondPlayer, true, false);
    getCard(player, playerCards, indexPlayer);
    getCard(player, playerCards, indexPlayer);
    displayPlay(player, playerCards, indexPlayer,
                computer, computerCards, indexComputer);
    firstPlayerPlaying(player, playerCards, indexPlayer,
                       computer, computerCards, indexComputer, secondPlayer);
}

void returnToSecondLogIn(Player &player)
{
    cout << "  Press [1] to retry!\n";
    char option;
        do
        {
            option = getche();
            switch(option)
            {
                case '1':
                    system("cls");
                    secondLogIn(player);
                default:
                    cout << "\nYou pressed a wrong button! Try again\n";
            }
        }while(option != '1');
}

void secondLogIn(Player &player)
{
    Player secondPlayer;
    cout << "        Log in!\n\n";
    cout << "Username: "; cin >> secondPlayer.username;
    cout << "Password: ";
    hidePassword(secondPlayer.password);
    searchValidationPlayer checkPlayer = searchForAccount(secondPlayer.username, secondPlayer.password, false);
    secondPlayer.money = checkPlayer.money;
    if(checkPlayer.validation == -1)
    {
        cout << "\nUsername or password wrong!";
        returnToSecondLogIn(player);
    }
    else if(player.username == secondPlayer.username)
    {
        cout << "\nYou can not play with the same username!";
        returnToSecondLogIn(player);
    }
    else
        cout << "\nLog in succesfully!\n";
    Sleep(500);
    system("cls");
    loading(secondPlayer.username);
    playPlayer(player,secondPlayer);
}

void secondNewAccount(Player &player)
{
    Player secondPlayer;
    secondPlayer.money = 100;
    ofstream playersData;
    cout << "        Create new account!\n\n";
    cout << "Username: "; cin >> secondPlayer.username;
    cout << "Password: ";
    hidePassword(secondPlayer.password);
    searchValidationPlayer checkPlayer = searchForAccount(secondPlayer.username, secondPlayer.password, true);
    system ("cls");
    if(checkPlayer.validation == 1)
    {
        cout << "You already have a account!\n";
        secondLogIn(player);
    }
    else
    {
        playersData.open("players.dat", fstream::app);
        playersData << secondPlayer.username << " ";
        playersData << secondPlayer.password << " ";
        playersData << secondPlayer.money;
        playersData << endl;
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
                    secondLogIn(player);
                    break;
                default:
                    cout << "\nYou pressed a wrong button! Try again\n";
            }
        }while(option != '1');
    }
}

void secondPlayer(Player &player)
{
    cout << "        Second player\n\n";
    cout << "Please select one of the options!";
    cout << "\n[1] Create a new account \n[2] I have a account. Log in \n[3] Return to menu\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                secondNewAccount(player);
                break;
            case '2':
                system("cls");
                secondLogIn(player);
                break;
            case '3':
                system("cls");
                menu(player);
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1' || option != '2');
}


searchValidationPlayer searchForAccount(string username, string password, bool ok)
{
    searchValidationPlayer searchPlayer;
    ifstream playersData;
    playersData.open("players.dat", fstream::in);
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
        cout << "Error loading the file!";
    playersData.close();
    if(ok)
        searchPlayer.validation = 2;
    else
        searchPlayer.validation = -1;
    return searchPlayer;
}

void loading(string name)
{
    cout << " Preparing the game with " << name << "\n\n              ";
    for(int i = 0; i < 7; i++)
    {
        cout << "*";
        Sleep(300);
    }
    system("cls");
}

void returnToMenu(Player &player)
{
    cout << " \nPress [1] to return to menu\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                menu(player);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1');
}

void consultPlayerMoney(Player &player)
{
    string username;
    cout << "        Consult money!\n";
    cout << endl;
    cout << player.username << " money are: " << player.money;
    returnToMenu(player);
}

void changeUsername(Player &player)
{
    cout << "        Change username\n\n";
    cout << "The old username is: " << player.username;
    cout << "\nEnter the new username: ";
    string newUsername;
    cin >> newUsername;
    searchValidationPlayer checkUsername = searchForAccount(newUsername, "", true);
    if(checkUsername.validation == 2)
    {
        player.username = newUsername;
        updateData(player, true);
        cout << "\nYou changed the username succesfully!";
        returnToMenu(player);
    }
    else
    {
        cout << "\nThe username already exist!";
        returnToMenu(player);
    }
}

void hidePassword(string &password)
{
    char character;
    character = getch();
    while(character != 13)
    {
        if(character != '\b')
        {
            password.push_back(character);
            cout << "*";
        }
        if(character == 8 && password.length() > 0)
        {
            cout << "\b \b";
            password.pop_back();
        }
        character = getch();
    }
}

void changePassword(Player &player)
{
    cout << "        Change password\n\n";
    cout << "\nEnter the new password: ";
    string newPassword;
    hidePassword(newPassword);
    player.password = newPassword;
    updateData(player, true);
    cout << "\nYou changed your password succesfully!";
    returnToMenu(player);
}

void changeMoney(Player &player)
{
    cout << "        Change money\n\n";
    cout << "\nIf you are administrator enter the password to change money player: ";
    string password;
    hidePassword(password);
    if(password == "parola")
    {
        cout << "\nThe current " << player.username << " money are: $" << player.money;
        int money;
        cout << "\nHow much money do you want to SUBTRACT to the current amount of money? ";
        cin >> money;
        if(money < 0)
            money = 0;
        player.money -= money;
        if(player.money < 0)
            player.money = 0;
        cout << "\nHow much money do you want to ADD to the current amount of money? ";
        cin >> money;
        player.money += money;
        cout << "\nThe new amount of " << player.username << " money is: $" << player.money;
        updateData(player, false);
        cout << "\nYou update the money succesfully!";
        returnToMenu(player);
    }
    else
    {
        cout << "\nPassword wrong!\n";
        returnToMenu(player);
    }
}

void changeData(Player &player)
{
    cout << "        Change/update data\n\n";
    cout << "Please select one of the options!";
    cout << "\n[1] Change username";
    cout << "\n[2] Change password";
    cout << "\n[3] Change the number of money (administrator only)";
    cout << "\n[4] Return to menu\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                changeUsername(player);
                break;
            case '2':
                system("cls");
                changePassword(player);
                break;
            case '3':
                system("cls");
                changeMoney(player);
                break;
            case '4':
                system("cls");
                menu(player);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1' || option != '2' || option != '3' || option != '4');
}

void menu(Player &player)
{
    cout << "        Black Jack\n\n";
    cout << "Please select one of the options!";
    cout << "\n[1] Play with computer \n[2] Play with a friend \n[3] Consult your money \n[4] Change/update your data\n";
    char option;
    do
    {
        option = getche();
        switch(option)
        {
            case '1':
                system("cls");
                loading("the computer");
                playComputer(player);
                break;
            case '2':
                system("cls");
                secondPlayer(player);
                break;
            case '3':
                system("cls");
                consultPlayerMoney(player);
                break;
            case '4':
                system("cls");
                changeData(player);
                break;
            default:
                cout << "\nYou pressed a wrong button! Try again\n";
        }
    }while(option != '1' || option != '2' || option != '3' || option != '4');
}

void logIn()
{
    Player player;
    cout << "        Log in!\n\n";
    cout << "Username: "; cin >> player.username;
    cout << "Password: ";
    hidePassword(player.password);
    searchValidationPlayer checkPlayer = searchForAccount(player.username, player.password, false);
    player.money = checkPlayer.money;
    if(checkPlayer.validation == -1)
    {
        cout << "\nUsername or password wrong! Press [1] to retry!\n";
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
        cout << "\nLog in succesfully!\n";
    Sleep(500);
    system("cls");
    menu(player);
}

void newAccount()
{
    Player player;
    player.money = 100;
    ofstream playersData;
    cout << "        Create new account!\n\n";
    cout << "Username: "; cin >> player.username;
    cout << "Password: ";
    hidePassword(player.password);
    searchValidationPlayer checkPlayer = searchForAccount(player.username, player.password, true);
    system ("cls");
    if(checkPlayer.validation == 1)
    {
        cout << "You already have a account!\n";
        logIn();
    }
    else
    {
        playersData.open("players.dat", fstream::app);
        playersData << player.username << " ";
        playersData << player.password << " ";
        playersData << player.money;
        playersData << endl;
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
    system("color 0a");
    userAccount();
    return 0;
}
