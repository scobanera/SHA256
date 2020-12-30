// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SHA256.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    std::string message;
    SHA256 hash_service;

    cout << "===============================================" << endl;
    cout << "Welcome to SHA256 calculator!" << endl;
    cout << "===============================================\n" << endl;
    
    cout << "Input [-1 to exit]: ";
    cin >> message;
    while (message != "-1") {
        cout << "SHA256: " << hash_service.hash(message) << endl;

        cout << "Input [-1 to exit]: ";
        cin >> message;
    }

    cout << "\nThank you for using the program!" << endl;
}