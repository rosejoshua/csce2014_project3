/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Streaming.h
 * Author: admin
 *
 * Created on June 22, 2022, 10:41 AM
 */

#ifndef STREAMING_H
#define STREAMING_H

#include <cstdlib>
#include <string>
using namespace std;

class Streaming {
public:
    Streaming();
    Streaming(string platform, string title, int releaseDate, 
        string rating, string categoryKeyWords, string description);
    Streaming(const Streaming& orig);
    virtual ~Streaming();
    
    void print();
    string getPlatform();
    string getTitle();
    int getReleaseDate();
    string getRating();
    string getCategoryKeyWords();
    string getDescription();
    
    void setPlatform(string platform);
    void setTitle(string title);
    void setReleaseDate(int releaseDate);
    void setRating(string rating);
    void setCategoryKeyWords(string categoryKeyWords);
    void setDescription(string description);
    
private:
    string platform;
    string title;
    int releaseDate;
    string rating;
    string categoryKeyWords;
    string description;

};

#endif /* STREAMING_H */

