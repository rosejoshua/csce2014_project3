/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Streaming.cpp
 * Author: admin
 * 
 * Created on June 22, 2022, 10:41 AM
 */

#include "Streaming.h"

Streaming::Streaming() {
    platform = "";
    title = "";
    releaseDate = -1;
    rating = "";
    categoryKeyWords = "";
    description = "";
}

Streaming::Streaming(string platform, string title, int releaseDate, 
        string rating, string categoryKeyWords, string description) 
{
    this->platform = platform;
    this->title = title;
    this->releaseDate = releaseDate;
    this->rating = rating;
    this->categoryKeyWords = categoryKeyWords;
    this->description = description;
}

Streaming::Streaming(const Streaming& orig) 
{
    this->platform = orig.platform;
    this->title = orig.title;
    this->releaseDate = orig.releaseDate;
    this->rating = orig.rating;
    this->categoryKeyWords = orig.categoryKeyWords;
    this->description = orig.description;
}

Streaming::~Streaming() {
}
    
string getPlatform()
{
    return "";
}

string getTitle()
{
    return "";
}

int getReleaseDate()
{
    return -1;
}

string getRating()
{
    return "";
}

string getCategoryKeyWords()
{
    return "";
}

string getDescription()
{
    return "";
}

void setPlatform(string platform)
{

}

void setTitle(string title)
{

}

void setReleaseDate(int releaseDate)
{

}

void setRating(string rating)
{

}

void setCategoryKeyWords(string categoryKeyWords)
{

}

void setDescription(string description)
{

}

void print()
{

}
