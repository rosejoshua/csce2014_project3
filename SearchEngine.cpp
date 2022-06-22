/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   SearchEngine.cpp
 * Author: admin
 * 
 * Created on June 22, 2022, 3:00 PM
 */

#include "SearchEngine.h"
#include <iostream>

SearchEngine::SearchEngine() {
}

SearchEngine::SearchEngine(const SearchEngine& orig) {
}

SearchEngine::~SearchEngine() {
}

void SearchEngine::takeInSortedByTitle(string filename)
{
    int firstIndexAfterComma = 0;
    int currCommaIndex = 0;
    string inputString = "";
    
    string platform = "";
    string title = "";
    int releaseDate = 0;
    string rating = "";
    string categoryKeyWords = "";
    string description = "";
    
    ifstream infile;
    infile.open(filename);
    
    if(infile.fail())
    {
        cout << "Open file failed... exiting now.\n" << endl;
    }
    while(infile.peek() != EOF)
    {
        platform = "";
        title = "";
        releaseDate = 0;
        rating = "";
        categoryKeyWords = "";
        description = "";
        
        firstIndexAfterComma = 0;
        currCommaIndex = 0;
        getline(infile, inputString);
        
        currCommaIndex = inputString.find(',');
        platform = inputString.substr(firstIndexAfterComma, currCommaIndex);        
        firstIndexAfterComma = currCommaIndex+1;
        
        currCommaIndex = inputString.find(',', firstIndexAfterComma);        
        title = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);
        firstIndexAfterComma = currCommaIndex+1;
        
        currCommaIndex = inputString.find(',', firstIndexAfterComma);
        try
        {
            releaseDate = stoi(inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma));
        }
        catch (const std::invalid_argument& exception) {
            cerr << "Invalid argument: " << exception.what() << endl;;
            releaseDate = -1;
        }
        firstIndexAfterComma = currCommaIndex+1;
        
        currCommaIndex = inputString.find(',', firstIndexAfterComma);
        rating = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);        
        firstIndexAfterComma = currCommaIndex+1;
        
        currCommaIndex = inputString.find(',', firstIndexAfterComma);
        categoryKeyWords = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);        
        firstIndexAfterComma = currCommaIndex+1;
        
        currCommaIndex = inputString.length();
        description = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);
        cout << description << endl;
        
    }
    infile.close();
}

void SearchEngine::takeInSortedByDateRating(string filename)
{
    string inputString = "";
    ifstream infile;
    infile.open(filename);
    
    if(infile.fail())
    {
        cout << "Open file failed... exiting now.\n" << endl;
    }
    while(infile.peek() != EOF)
    {
        getline(infile, inputString);
        
        
    }
    infile.close();
}

Streaming* SearchEngine::searchByTitle(string title)
{
    return NULL;
}
Streaming* SearchEngine::searchByDateRating(int date, string rating)
{
    return NULL;
}