/*****************************************************************//**
 * \file   main.cpp
 * \brief  Przechowuje funkcje tworz¹c¹ okno oraz uruchamia rysowanie labiryntu.
 * 
 * \author Micha³ Polak, Rados³aw Barwacz
 * \date   April 2023
 *********************************************************************/

#include "labirynth.h"

/**
 * \brief g³ówna programu.
 * 
 * \param argc - Liczba argumentów wiersza poleceñ.
 * \param argv - Tablica argumentów wiersza poleceñ.
 * \return - Kod zakoñczenia programu.
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

    // Pêtla przetwarzania wydarzeñ GLUT
    glutMainLoop();
    
    return 1;
}