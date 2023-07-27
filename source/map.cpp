/*****************************************************************//**
 * \file   map.cpp
 * \brief  Przechowuje funkcje pobieraj¹ca tablicê dwuwymiarow¹ z pliku txt.
 * 
 * \author Micha³ Polak
 * \date   May 2023
 *********************************************************************/

#include "map.h"
#include <fstream>


/**
 * \brief Odczytywanie danych z pliku txt i dodawanie ich do tablicy dwuwymiarowej.
 * 
 * \param fileName - Nazwa pliku.
 * \param size - Rozmiar tablicy.
 * \param Map - WskaŸnik do tablicy dwuwymiarowej.
 * \return - Wartoœæ logiczna informuj¹ca o powodzeniu operacji odczytu danych z pliku.
 */
bool readMapFromFile(const string& fileName, int size, int **Map)
{
    string filePath = "Maps/" + fileName;

    ifstream file(filePath);

    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                file >> Map[i][j];
            }
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Odczytanie danych z pliku txt i dodanie ich do tablicy.
 * 
 * \param fileName - Nazwa pliku.
 * \param size - Rozmiar tablicy.
 * \param Results - WskaŸnik do tablicy.
 * \return - Wartoœæ logiczna informuj¹ca o powodzeniu operacji odczytu danych z pliku.
 */
bool readResultsFromFile(const string& fileName, int size, int* Results)
{
    string filePath = "Maps/" + fileName;

    ifstream file(filePath);

    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            file >> Results[i];
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Zapisanie danych z tablicy do pliku txt.
 *
 * \param fileName - Nazwa pliku.
 * \param size - Rozmiar tablicy.
 * \param Results - WskaŸnik do tablicy.
 * \return - Wartoœæ logiczna informuj¹ca o powodzeniu operacji zapisu danych  pliku.
 */
bool writeResultsToFile(const string& fileName, int size, const int* Results)
{
    string filePath = "Maps/" + fileName;

    ofstream file(filePath);

    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            file << Results[i] << " ";
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}
