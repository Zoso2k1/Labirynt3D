/*****************************************************************//**
 * \file   map.h
 * \brief  Przechowuje deklaracj� plik�w nag��wkowych i funkcji s�u��cej do odczytywanie tablicy dwuwymiarowej z pliku txt.
 * 
 * \author Micha� Polak, Rados�aw Barwacz
 * \date   May 2023
 *********************************************************************/

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

bool readMapFromFile(const string&, int, int**);
bool readResultsFromFile(const string& , int , int*);
bool writeResultsToFile(const string& , int , const int*);

#endif // MAP_H