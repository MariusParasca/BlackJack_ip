#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

bool searchForAccount(string name)
{

    string username, password;
    int money;
    fstream playersData;
    playersData.open("players.dat", ios::in);
    if(playersData.is_open()){

        while(!playersData.eof())
        {
            playersData >> username;
            playersData >> password;
            playersData >> money;
            if(username == name)
            {
                cout << "You already have a account!\n";
                return false;
            }
        }
    }
    else
        cout << "Error file!";
    playersData.close();
    return true;
}

void logIn()
{
    string username, password;
    cout << "        Log in!\n\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
}

void newAccount()
{
    string username, password;
    const int money = 100;
    fstream playersData;
    cout << "        Create new account!\n\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    system ("cls");
    if(!searchForAccount(username))
    {
        logIn();
    }
    else
    {
        cout << "You have registered successfully\n";
        cout << "Press 1 to play\n";
        //play();
    }
    playersData.open("players.dat", ios::app);
    playersData << username << " ";
    playersData << password << " ";
    playersData << money << endl;
    playersData.close();

}


void userAccount()
{
    system("cls");
    cout << "        Black Jack\n\n";
    cout << "Please select one of the options!";
    cout << "\n1. Create a new account \n2. I have a account. Log in \n";
    char option;
    do
    {
        cin >> option;
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

void menu()
{
    cout << "        Welcome to Black Jack\n\n";
    cout << "Please select one of the options!";
    cout << "\n1. Play with computer \n2. Play with a friend \n";
    char option;
    do
    {
        cin >> option;
        if(option == '1' || option == '2')
            userAccount();
        else
            cout << "\nYou pressed a wrong button! Try again\n";
    }while(option != '1' || option != '2');
}

int main()
{
    menu();
}
