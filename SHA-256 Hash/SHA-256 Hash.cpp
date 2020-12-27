// SHA-256 Hash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SHA256.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    SHA256 hash_service;
    cout << hash_service.hash("abc");
}