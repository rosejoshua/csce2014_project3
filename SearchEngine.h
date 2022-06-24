/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   SearchEngine.h
 * Author: admin
 *
 * Created on June 22, 2022, 3:00 PM
 */

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <vector>
#include <fstream>
#include "Streaming.h"
using namespace std;

class SearchEngine {
public:
    SearchEngine();
    SearchEngine(const SearchEngine& orig);
    virtual ~SearchEngine();
    
    void takeInSortedFilmDataByTitle(string filename);
    void takeInSortedFilmDataByDateRating(string filename);
    
    
    //for testing only, delete
    void printAllFilms();
    
    Streaming* searchByTitle(string title);
    void searchByDateRating(int date, string rating);
    
private:
    void takeInSortedFilmData(string filename, vector<Streaming*> *filmVector);
    vector<Streaming*> sortedByTitle;
    vector<Streaming*> sortedByDateRating;
    Streaming* binarySearchByTitle(int start, int end, string title);
    int binarySearchByYear(int start, int end, int year);
    int findLowerIndexOfRatingWithinYear(int anyYearMatchIndex, string rating);
    int findUpperIndexOfRatingWithinYear(int indexWithMatchingYearAndRating, string rating);

};

#endif /* SEARCHENGINE_H */

