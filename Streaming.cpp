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
#include <iostream>
#include "Streaming.h"
using namespace std;

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
    
string Streaming::getPlatform()
{
    return platform;
}

string Streaming::getTitle()
{
    return title;
}

int Streaming::getReleaseDate()
{
    return releaseDate;
}

string Streaming::getRating()
{
    return rating;
}

string Streaming::getCategoryKeyWords()
{
    return categoryKeyWords;
}

string Streaming::getDescription()
{
    return description;
}

void Streaming::setPlatform(string platform)
{
    this->platform = platform;
}

void Streaming::setTitle(string title)
{
    this->title = title;
}

void Streaming::setReleaseDate(int releaseDate)
{
    this->releaseDate = releaseDate;
}

void Streaming::setRating(string rating)
{
    this->rating = rating;
}

void Streaming::setCategoryKeyWords(string categoryKeyWords)
{
    this->categoryKeyWords = categoryKeyWords;
}

void Streaming::setDescription(string description)
{
    this->description = description;
}

void Streaming::print()
{
    cout << "platform: " << platform << endl;
    cout << "title: " << title << endl;
    cout << "release date: " << releaseDate << endl;
    cout << "rating: " << rating << endl;
    cout << "category key words: " << categoryKeyWords << endl;
    cout << "description: " << description << endl;
}
