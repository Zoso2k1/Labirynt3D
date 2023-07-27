/*****************************************************************//**
 * \file   main.cpp
 * \brief  Przechowuje funkcje tworz�c� okno oraz uruchamia rysowanie labiryntu.
 * 
 * \author Micha� Polak, Rados�aw Barwacz
 * \date   April 2023
 *********************************************************************/

#include "labirynth.h"

/**
 * \brief g��wna programu.
 * 
 * \param argc - Liczba argument�w wiersza polece�.
 * \param argv - Tablica argument�w wiersza polece�.
 * \return - Kod zako�czenia programu.
 */
int main(int argc, char** argv)
{
    // Tworzenie okna
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition((1920 - WIDTH) / 2, (1080 - HEIGHT) / 2 );
    glutCreateWindow("Labirynt");

    // Uruchomienie gry
    startGame();

    // P�tla przetwarzania wydarze� GLUT
    glutMainLoop();
    
    return 1;
}