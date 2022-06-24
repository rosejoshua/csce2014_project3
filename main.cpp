/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: admin
 *
 * Created on June 22, 2022, 10:29 AM
 */

#include <cstdlib>
#include <iostream>
#include "SearchEngine.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    SearchEngine searchEngine;
    searchEngine.takeInSortedFilmDataByTitle("streaming-title.txt");
    searchEngine.takeInSortedFilmDataByDateRating("streaming-year.txt");
    
    searchEngine.printAllFilms();
    string menuChoice = "";
    string tempString1 = "";
    string tempString2 = "";
    
    while(menuChoice != "quit") 
    {
        while (menuChoice != "1" && menuChoice != "2")
        {
            cout << "Please enter an option (1,2, or \"quit\"):" << endl;
            cout << "\t1. Search by title" << endl;
            cout << "\t2. Search by year and rating" << endl;
            cout << "\t>>";
            cin >> menuChoice;

            if (menuChoice == "quit")
            {
                cout << "Goodbye!" << endl;
                break;
            }

            if (menuChoice != "1" && menuChoice != "2")
            {
                cout << "invalid input, please try again" << endl;
                continue;
            }

            if (menuChoice == "1")
            {
                tempString1="";
                cout << "Enter a title to search for: " << endl;
                cout << "\t>>";
                cin.ignore();
                cin.clear();
                getline(cin, tempString1);
                
                searchEngine.searchByTitle(tempString1);
                menuChoice="";
            }
            else if (menuChoice == "2")
            {
                tempString1 = "";
                tempString2 = "";
                while(true)
                {
                    cout << "Enter a year to search for: " << endl;
                    cout << "\t>>";
                    cin >> tempString1;
                    if (tempString1.compare("1900") < 0 || tempString1.compare("2100") > 0)
                        cout << "Invalid input, enter a valid year (1900-2100)" << endl;
                    else break;
                }                
                    cout << "Enter a rating to search for (NR|ALL|Y|G|PG|PG-13|R|or \"n/a\" for movies with no rating: " << endl;
                    cout << "\t>>";
                    cin.ignore();
                    cin.clear();
                    cin >> tempString2;
                
                    if(tempString2=="n/a")
                        tempString2 = "";
                searchEngine.searchByDateRating(stoi(tempString1), tempString2);                
                menuChoice="";
            }
        }
        
    }

    return 0;
}

