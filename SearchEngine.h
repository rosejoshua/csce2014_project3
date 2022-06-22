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
    
    void takeInSortedByTitle(string filename);
    void takeInSortedByDateRating(string filename);
    
    Streaming* searchByTitle(string title);
    Streaming* searchByDateRating(int date, string rating);
    
private:
    vector<Streaming*> sortedByTitle;
    vector<Streaming*> sortedByDateRating;

};

#endif /* SEARCHENGINE_H */

