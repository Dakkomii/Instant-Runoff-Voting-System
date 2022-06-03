/**
	@file main.cc

	Implementation of the main method for the whole system

	@author King Yiu Suen (suenx008)
*/

#include <iostream>
#include <string>
#include "votingsystem.h"

using namespace std;

/// Main function of the voting system.
int main() {
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "| __     __    _   _               ____            _                  |" << endl;
    cout << "| \\ \\   / /__ | |_(_)_ __   __ _  / ___| _   _ ___| |_ ___ _ __ ___   |" << endl;
    cout << "|  \\ \\ / / _ \\| __| | '_ \\ / _` | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\  |" << endl;
    cout << "|   \\ V / (_) | |_| | | | | (_| |  ___) | |_| \\__ \\ ||  __/ | | | | | |" << endl;
    cout << "|    \\_/ \\___/ \\__|_|_| |_|\\__, | |____/ \\__, |___/\\__\\___|_| |_| |_| |" << endl;
    cout << "|                          |___/         |___/                        |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl << endl;
    string filename;
    VotingSystem* vs = new VotingSystem();
    while (1) {
        cout << "Enter the name of the ballot file: ";
        cin >> filename;
        if (vs->readFileName(filename)) {
            break;
        }
    }
    vs->startAnElection();
    return 0;
}
