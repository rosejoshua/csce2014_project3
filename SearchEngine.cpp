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
using namespace std;

SearchEngine::SearchEngine() {
}

SearchEngine::SearchEngine(const SearchEngine& orig) {
}

SearchEngine::~SearchEngine() {
    
    for(Streaming* ptr : sortedByTitle) 
    {
        delete ptr;
    }
    
    for(Streaming* ptr : sortedByDateRating) 
    {
        delete ptr;
    }
    
}

//for testing only, delete
void SearchEngine::printAllFilms()
{
    for(Streaming* ptr : sortedByTitle) 
    {
        ptr->print();
    }
    
    for(Streaming* ptr : sortedByDateRating) 
    {
        ptr->print();
    }
}

void SearchEngine::takeInSortedFilmData(string filename, vector<Streaming*> *filmVector)
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
            cerr << "Invalid argument: " << exception.what() << endl;
            releaseDate = -1;
            continue;
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
        
        Streaming* streaming = new Streaming(platform, title, releaseDate, rating, categoryKeyWords, description);
        filmVector->push_back(streaming);
    }
    infile.close();
}

void SearchEngine::takeInSortedFilmDataByTitle(string filename)
{
    takeInSortedFilmData(filename, &sortedByTitle);
    cout << "Taking in film data sorted by title complete." << endl;
}

void SearchEngine::takeInSortedFilmDataByDateRating(string filename)
{
    takeInSortedFilmData(filename, &sortedByDateRating);
    cout << "Taking in film data sorted by date and rating complete." << endl;
}

Streaming* SearchEngine::searchByTitle(string title)
{
    Streaming* result = binarySearchByTitle(0, sortedByTitle.size()-1, title);
    
    if(result == NULL)
        cout << "Sorry, your film is not available through any of our services." << endl;
    else result->print();
    
    return result;
}

Streaming* SearchEngine::binarySearchByTitle(int start, int end, string title)
{
    cout << "middleTitle: " << sortedByTitle[(start+end)/2]->getTitle() << endl;
    
    //return middle element (or 1st of 2 remaining when narrowed down to two) if match
    if (sortedByTitle[(start+end)/2]->getTitle()==title)
    {
        return sortedByTitle[(start+end)/2];
    }
    //handle case of 2 remaining vector elements and 1st of two is not a match, check second
    else if (end-start==1 && sortedByTitle[end]->getTitle() != title)
    {
        return NULL;    
    }
    //handle case of 2 remaining vector elements and 1st of two is not a match, check second
    else if (end-start==1 && sortedByTitle[end]->getTitle() == title)
    {
        return sortedByTitle[end];    
    }
    //recursive search when title is earlier in sorting than middle
    else if (title.compare(sortedByTitle[(start+end)/2]->getTitle()) < 0)
    {
        return binarySearchByTitle(start, (start+end)/2, title);
    }
    //recursive search when title is later in sorting than middle
    else if (title.compare(sortedByTitle[(start+end)/2]->getTitle()) > 0)
    {
        return binarySearchByTitle((start+end)/2, end, title);
    }
    //doesn't exist
    else return NULL;
}

void SearchEngine::searchByDateRating(int year, string rating)
{
    int yearMatch = binarySearchByYear(0, sortedByDateRating.size(), year);
    if (yearMatch == -1)
        cout << "Sorry, no films match your search criteria" << endl;    
    else 
    {
        int lowerBound = findLowerIndexOfRatingWithinYear(yearMatch, rating);
        if(lowerBound == -1)
        {
            cout << "Sorry, no films match your search criteria" << endl;
        }
        else
        {
            cout << "Films found! Here are your search results: " << endl;
             int upperBound = findUpperIndexOfRatingWithinYear(lowerBound, rating);
             for(int i = lowerBound; i <= upperBound; i++)
             {
                 sortedByDateRating[i]->print();
             }
        }

    }
    
}

int SearchEngine::findLowerIndexOfRatingWithinYear(int anyYearMatchIndex, string rating)
{
    int index = anyYearMatchIndex;
    while(index < sortedByDateRating.size()-1 && 
            sortedByDateRating[index+1]->getReleaseDate()==sortedByDateRating[anyYearMatchIndex]->getReleaseDate() &&
            sortedByDateRating[index]->getRating() < rating)
    {
        index++;
    }
    while(index > 0 && 
            sortedByDateRating[index-1]->getReleaseDate()==sortedByDateRating[anyYearMatchIndex]->getReleaseDate() &&
            sortedByDateRating[index]->getRating() > rating)
    {
        index--;
    }
    while(index > 0 && 
            sortedByDateRating[index-1]->getReleaseDate()==sortedByDateRating[anyYearMatchIndex]->getReleaseDate() &&
            sortedByDateRating[index-1]->getRating() == rating)
    {
        index--;
    }
    if(sortedByDateRating[index]->getRating() != rating)
        return -1;
    else return index;

}

int SearchEngine::findUpperIndexOfRatingWithinYear(int indexWithMatchingYearAndRating, string rating)
{
    int index = indexWithMatchingYearAndRating;
    
    while(index < sortedByDateRating.size()-1 && 
            sortedByDateRating[index+1]->getReleaseDate()==sortedByDateRating[indexWithMatchingYearAndRating]->getReleaseDate() &&
            sortedByDateRating[index+1]->getRating() == rating)
    {
        index++;
    }
    return index;
}

//simply returns an index for any element with the matching year
int SearchEngine::binarySearchByYear(int start, int end, int year)
{
    
    //return middle element (or 1st of 2 remaining when narrowed down to two) if match
    if (sortedByDateRating[(start+end)/2]->getReleaseDate()==year)
    {
        return (start+end)/2;
    }
    //handle case of 2 remaining vector elements and 1st of two is not a match, check second
    else if (end-start==1 && sortedByDateRating[end]->getReleaseDate() != year)
    {
        return -1;    
    }
    //handle case of 2 remaining vector elements and 1st of two is not a match, check second
    else if (end-start==1 && sortedByDateRating[end]->getReleaseDate() == year)
    {
        return end;    
    }
    //recursive search when year is earlier in sorting than middle
    else if (year < sortedByDateRating[(start+end)/2]->getReleaseDate())
    {
        //cout << "title less than middle title" << endl;
        return binarySearchByYear(start, (start+end)/2, year);
    }
    //recursive search when year is later in sorting than middle
    else if (year > sortedByDateRating[(start+end)/2]->getReleaseDate())
    {
        //cout << "title greater than middle title" << endl;
        return binarySearchByYear((start+end)/2, end, year);
    }
    //doesn't exist
    else return -1;
}