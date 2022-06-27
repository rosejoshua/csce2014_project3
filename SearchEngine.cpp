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
        
        //find first comma which will be after 'platform' string
        currCommaIndex = inputString.find(',');
        platform = inputString.substr(firstIndexAfterComma, currCommaIndex);        
        firstIndexAfterComma = currCommaIndex+1;
        
        //use index after first comma as start of second token, 'title' and up to following comma
        currCommaIndex = inputString.find(',', firstIndexAfterComma);        
        title = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);
        firstIndexAfterComma = currCommaIndex+1;
        
        //same logic as above plus catch block for bad input data that can't be parsed as an int
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
        
        //same logic of walking indexes to get 'rating'
        currCommaIndex = inputString.find(',', firstIndexAfterComma);
        rating = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);        
        firstIndexAfterComma = currCommaIndex+1;
        
        //same logic as above for 'categoryKeyWords'
        currCommaIndex = inputString.find(',', firstIndexAfterComma);
        categoryKeyWords = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);        
        firstIndexAfterComma = currCommaIndex+1;
        
        //final token 'description' uses the entire input line size as the final end index
        currCommaIndex = inputString.length();
        description = inputString.substr(firstIndexAfterComma, currCommaIndex-firstIndexAfterComma);
        
        //call constructor for new Streaming object, assign to pointer, add pointer to vector
        Streaming* streaming = new Streaming(platform, title, releaseDate, rating, categoryKeyWords, description);
        filmVector->push_back(streaming);
    }
    infile.close();
}

//public method for starting film data input
void SearchEngine::takeInSortedFilmDataByTitle(string filename)
{
    takeInSortedFilmData(filename, &sortedByTitle);
    cout << "Taking in film data sorted by title complete." << endl;
}

//public method for starting film data input
void SearchEngine::takeInSortedFilmDataByDateRating(string filename)
{
    takeInSortedFilmData(filename, &sortedByDateRating);
    cout << "Taking in film data sorted by date and rating complete." << endl;
}

//public method for searching by title that hides implementation
Streaming* SearchEngine::searchByTitle(string title)
{
    Streaming* result = binarySearchByTitle(0, sortedByTitle.size()-1, title);
    
    if(result == NULL)
        cout << "Sorry, your film is not available through any of our services." << endl;
    else result->print();
    
    return result;
}

//recursive binary search for film by title string
Streaming* SearchEngine::binarySearchByTitle(int start, int end, string title)
{
    
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

//public method for searching for range of films by Date and Rating
void SearchEngine::searchByDateRating(int year, string rating)
{
    //first check if ANY films exist by year
    int yearMatch = binarySearchByYear(0, sortedByDateRating.size(), year);
    if (yearMatch == -1)
        cout << "Sorry, no films match your search criteria" << endl;
    //succeeded in finding at least one film by that year,
    //look for lower index of films with that year AND rating
    else 
    {
        int lowerBound = findLowerIndexOfRatingWithinYear(yearMatch, rating);
        //if lowerBound = -1, entire range of films with given year were traversed with no match for rating
        if(lowerBound == -1)
        {
            cout << "Sorry, no films match your search criteria" << endl;
        }
        //at least one film was found with year AND rating, upperBound is the 
        //index of the last film found with matching year AND rating, walking forward from our lowerBound
        else
        {
            cout << "Films found! Here are your search results: " << endl;
             int upperBound = findUpperIndexOfRatingWithinYear(lowerBound, rating);
             //print range of films
             for(int i = lowerBound; i <= upperBound; i++)
             {
                 sortedByDateRating[i]->print();
             }
        }

    }
    
}

//take index of ANY film with matching year then find lowest index with a matching rating. If no film found, return -1
int SearchEngine::findLowerIndexOfRatingWithinYear(int anyYearMatchIndex, string rating)
{
    int index = anyYearMatchIndex;
    //if our index puts us in a film with a rating later than the one we want, 
    //make sure next index is same year and increment index
    while(index < sortedByDateRating.size()-1 && 
            sortedByDateRating[index+1]->getReleaseDate()==sortedByDateRating[anyYearMatchIndex]->getReleaseDate() &&
            sortedByDateRating[index]->getRating() < rating)
    {
        index++;
    }
    //if above while loop is not triggered, rating of film where our index 
    //put us is equal or later than the rating we need. This block is for a rating that is earlier in the list
    while(index > 0 && 
            sortedByDateRating[index-1]->getReleaseDate()==sortedByDateRating[anyYearMatchIndex]->getReleaseDate() &&
            sortedByDateRating[index]->getRating() > rating)
    {
        index--;
    }
    //if we ended up with the last of a group of films with a matching year and rating, 
    //this will walk the index back until we have the first of the group
    while(index > 0 && 
            sortedByDateRating[index-1]->getReleaseDate()==sortedByDateRating[anyYearMatchIndex]->getReleaseDate() &&
            sortedByDateRating[index-1]->getRating() == rating)
    {
        index--;
    }
    //after all of the above, if we have no match, then the combo of year and rating don't exist, return -1
    if(sortedByDateRating[index]->getRating() != rating)
        return -1;
    else return index;

}

//keep walking index forward until the following index does not have a matching year AND rating
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

//simply returns an index for any element with the matching year,
//binary recursive method
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