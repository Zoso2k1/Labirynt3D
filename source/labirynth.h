/*****************************************************************//**
 * \file   labirynth.h
 * \brief  Przechowuje deklaracjê plików nag³ówkowych, funkcji i sta³ych u¿ywanych do obs³ugi labiryntu.
 * 
 * \author Micha³ Polak, Rados³aw Barwacz
 * \date   May 2023
 *********************************************************************/

#ifndef LABIRYNTH_H
#define LABIRYNTH_H

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * Zdefiniowanie wielkoœci okna.
 */
#define  WIDTH 960
#define  HEIGHT 540

void Init();
void Display();
void Reload_TextView();
void Keyboard(GLubyte , int , int );
void processSpecialKeys(int, int, int);

void startGame();
void drawCube();
void drawGround(GLuint&);
void drawCircle(float, int);
void loadTexture(const string&, GLuint&);
void timer(int);
void showNotification(float, float, string, void*);
void information();

#endif // !LABIRYNTH_H