/*
Cameron Tyree
CIS 1202 101
Janurary 24 2024
*/

#include "personalLibrary.h"

void loadArrays(string[], float[], int&);
void showArrays(string[], float[], int);
void lookUpPrice(string[], float[], int);
void sortPrices(string[], float[], int);
void highestPrice(string[], float[], int);
int showMenu();

int main() {
    const int MAX_CONSOLE = 100;
    string name[MAX_CONSOLE];
    float price[MAX_CONSOLE];
    int consoleNum = 0;

    loadArrays(name, price, consoleNum);

    int userChoice;
    do {
        userChoice = showMenu();

        switch (userChoice) {
        case 1:
            showArrays(name, price, consoleNum);
            break;
        case 2:
            lookUpPrice(name, price, consoleNum);
            break;
        case 3:
            sortPrices(name, price, consoleNum);
            showArrays(name, price, consoleNum);
            break;
        case 4:
            highestPrice(name, price, consoleNum);
            break;
        }
    } while (userChoice != 5);

    endProgram();
}

void loadArrays(string names[], float prices[], int& numConsoles) { // This function reads in the file and everything in it
    const int MAX_CONSOLE = 100;
    ifstream fin("prices.txt");
    if (!fin.is_open()) {
      cout << "Unable to open file. Please press enter to exit and run the program again.";
      cin.ignore();
      exit(EXIT_FAILURE); // terminates the program if the file isnt able to be opened
    
    }
   
    numConsoles = 0;
    while (getline(fin, names[numConsoles]) && numConsoles < MAX_CONSOLE) {
        fin >> prices[numConsoles];
        fin.ignore();
        numConsoles++;
    }
    fin.close();
}


void showArrays(string names[], float prices[], int numConsoles) { // this function sets the menu up
    cout << setw(30) << left << "\n\nConsole Name" << setw(10) << right << "Price" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < numConsoles; i++) {
        cout << setw(30) << left << names[i] << setw(10) << fixed << setprecision(2) << right << prices[i] << endl;
    }
    cout << "------------------------------------------" << endl;
}

void lookUpPrice(string names[], float prices[], int numConsoles) { // this function finds the item that is typed into the program
    string search;
    cout << "Enter the console name to look up: ";
    getline(cin, search);

    bool found = false;
    for (int i = 0; i < numConsoles; i++) {
        if (search == names[i]) {
            cout << "Price of " << search << ": $" << fixed << setprecision(2) << prices[i] << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Console not found. (Make sure everything is spelled right)" << endl;
    }
}

void sortPrices(string names[], float prices[], int numConsoles) { // this function shows the prices in descending order
    for (int i = 0; i < numConsoles - 1; i++) {
        for (int j = 0; j < numConsoles - i - 1; j++) {
            if (prices[j] < prices[j + 1]) {

                float tempPrice = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = tempPrice;


                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;
            }
        }
    }

    cout << "Prices sorted in descending order." << endl;
}

void highestPrice(string names[], float prices[], int numConsoles) { // this function calculates the highest price 
    if (numConsoles > 0) {
        cout << "\n\nConsole with the highest price: " << names[0] << " ($" << fixed << setprecision(2) << prices[0] << ")" << endl;
        cout << "\n\n";
    }
    else {
        cout << "No consoles available." << endl;
    }
}

int showMenu() { // this function displays the menu so the user can input their choice
    int choice;
    cout << "\n\nMenu:" << endl;
    cout << "1. Display all console prices" << endl;
    cout << "2. Look up the price of a particular console" << endl;
    cout << "3. Sort prices in descending order" << endl;
    cout << "4. Display the console with the highest price" << endl;
    cout << "5. Exit the program";
    choice = validateIntRange("Enter your choice: ", 1, 5);
    return choice;
}
