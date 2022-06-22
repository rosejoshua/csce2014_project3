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
#include "SearchEngine.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    SearchEngine searchEngine;
    searchEngine.takeInSortedByTitle("streaming-title.txt");
    searchEngine.takeInSortedByDateRating("streaming-year.txt");

    return 0;
}

