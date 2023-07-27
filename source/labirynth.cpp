/*****************************************************************//**
 * \file   labirynth.cpp
 * \brief  Przechowuje funkcje oraz zmienne u�ywane do rysowania labiryntu.
 * 
 * \author Micha� Polak
 * \date   April 2023
 *********************************************************************/

#include "labirynth.h"
#include "map.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/**
 * \brief Ustawienie sta�ej PI.
 */
#define PI  3.14159265359f

/**
 * \brief Ustawienie pozycji �wiat�a w przestrzeni 3D.
 */
GLfloat Light_Pos[] = { 0.0f, -20.0f, 80.0f, 0.0f };

/**
 * \brief Ustawienie koloru dyfuzyjnego �wiat�a.
 */
GLfloat Light_Dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/**
 * \brief Okre�lenie koloru �wiat�a otoczenia.
 */
GLfloat Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/**
 * \brief Okre�lenie koloru dyfuzyjnego.
 */
GLfloat Diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };

/**
 * \brief Okre�lenie koloru odbicia lustrzanego dla pow. obiekt�w u�ytych do wygenerowania efekt�w �wietlnych na scenie.
 */
GLfloat Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/**
 * \brief Identyfikatory tekstur.
 */
GLuint textureBox, textureGround, textureStart, textureFinish;

/**
 * \brief Zmienna informuj�ca czy klawisz m jest wci�ni�ty.
 */
int mapFlag = 0;

/**
 * \brief K�t obrotu kamery.
 */
float angle = 3.0f;

/**
 * \brief Zmienne reprezentuj�ce aktualny kierunek kamery.
 */
float lx = 0.00f, lz = 1.0f;

/**
 * \brief Zmienne reprezentuj�ce pozycj� kamery w 3D.
 */
float x = -10.0f, y = 1.0f, z = 1.0f;

/**
 * \brief Zmienne pomocnicze do kamery.
 */
float tempX, tempZ, tempY, tempLx, tempLz;
bool blockCamera = false;

/**
 * \brief Zmienne dotycz�ce mapy.
 */
int MAX;
int **Map;
string mapName;

/**
 * \brief Zmienne dotycz�ce odliczania czasu i wynik�w.
 */
int Result[4];
int theBestOnTheMap;
int mapTime = 0;
int endTime;
static bool timerRunning = false;

/**
 * \brief Numer mapy.
 * 
 */
int level = 1;

/**
 * \brief Uruchomienie gry.
 * 
 * \param level - Poziom w grze.
 */
void startGame() {
    // Odczytanie tekstur z plik�w
    string fileName = "vtr.bmp";
    loadTexture(fileName, textureBox);

    string fileName2 = "grass.png";
    loadTexture(fileName2, textureGround);

    string fileName3 = "start.png";
    loadTexture(fileName3, textureStart);

    string fileName4 = "finish.png";
    loadTexture(fileName4, textureFinish);

    // Odczytanie wynik�w z pliku
    readResultsFromFile("theBestTimes.txt", 4, Result);

    // Wyb�r mapy
    string mapFileName;
    switch (level)
    {    
    case 1:
        MAX = 33;
        Map = new int* [MAX];

        for (int i = 0; i < MAX; i++) {
            Map[i] = new int[MAX];
        }
        x = 10.0f, y = 1.0f, z = -14.5f;
        angle = 3.0f;
        lx = 0.00f, lz = 1.0f;

        mapFileName = "map33.txt";
        mapName = "Mapa 1";
        theBestOnTheMap = Result[0];
        mapTime = 0;
        blockCamera = false;
        break;
    case 2:
        MAX = 33;
        Map = new int* [MAX];

        for (int i = 0; i < MAX; i++) {
            Map[i] = new int[MAX];
        }
        x = -10.0f, y = 1.0f, z = -14.5f;
        angle = 3.0f;
        lx = 0.00f, lz = 1.0f;

        mapFileName = "map33v2.txt";
        mapName = "Mapa 2";
        theBestOnTheMap = Result[1];
        mapTime = 0;
        blockCamera = false;
        break;
    case 3:
        MAX = 43;
        Map = new int* [MAX];

        for (int i = 0; i < MAX; i++) {
            Map[i] = new int[MAX];
        }
        x = 15.0f, y = 1.0f, z = -19.5f;
        angle = 3.0f;
        lx = 0.00f, lz = 1.0f;

        mapFileName = "map43.txt";
        mapName = "Mapa 3";
        theBestOnTheMap = Result[2];
        mapTime = 0;
        blockCamera = false;
        break;
    case 4:
        MAX = 63;
        Map = new int* [MAX];

        for (int i = 0; i < MAX; i++) {
            Map[i] = new int[MAX];
        }
        x = 23.0f, y = 1.0f, z = -29.5f;
        angle = 3.0f;
        lx = 0.00f, lz = 1.0f;

        mapFileName = "map63.txt";
        mapName = "Mapa 4";
        theBestOnTheMap = Result[3];
        mapTime = 0;
        blockCamera = false;
        break;
    }

    // Uruchomienie odliczania czasu
    if (!timerRunning)
    {
        timer(0);
    }

    // Odczytanie mapy z pliku
    readMapFromFile(mapFileName, MAX, Map);

    // Information
    printf(" +------------+\n |  LABIRYNT  |\n +------------+\n");

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (Map[i][j] == 0)
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }

    // Wy�wietlanie
    glutDisplayFunc(Display);
    Init();
    glutIdleFunc(Display);

    // Obs�uga klawiatury
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(Keyboard);

    // inicjalizacja testu g��boko�ci OpenGL
    glEnable(GL_DEPTH_TEST);
}


/**
 * \brief Inicjalizacja parametr�w.
 * 
 */
void Init()
{
    // KOLOR NIEBA
    glClearColor(0.420f, 0.604f, 0.922f, 1.0f);
    // W��czenie �r�d�a �wiat�a, ustawienie w�a�ciwo�ci materia�u (kolor, po�ysk, odbicie)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT0, GL_POSITION, Light_Pos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0f);

    //Wy�wietlanie tekstur na mapie
    glNewList(1, GL_COMPILE);
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (Map[i][j] == 0)
            {
                glLoadIdentity();
                glTranslatef(((MAX - 1.0f) / 2.0f) - i, j - ((MAX - 1.0f) / 2.0f), 0.5f);
                drawCube();

                glLoadIdentity();
                glTranslatef(((MAX - 1.0f) / 2.0f) - i, j - ((MAX - 1.0f) / 2.0f), 1.5f);
                drawCube();
            }
            else if (Map[i][j] == 1)
            {
                glLoadIdentity();
                glTranslatef(((MAX - 1.0f) / 2.0f) - i, j - ((MAX - 1.0f) / 2.0f), -0.5f);

                drawGround(textureGround);
            }
            else if (Map[i][j] == 4)
            {
                glLoadIdentity();
                glTranslatef(((MAX - 1.0f) / 2.0f) - i, j - ((MAX - 1.0f) / 2.0f), -0.5f);

                drawGround(textureStart);
            }
            else if (Map[i][j] == 5)
            {
                glLoadIdentity();
                glTranslatef(((MAX - 1.0f) / 2.0f) - i, j - ((MAX - 1.0f) / 2.0f), -0.5f);

                drawGround(textureFinish);
            }
        }
    }
    glEndList();
}


/**
 * \brief Resetowanie widoku kamery i projekcji na scenie.
 * 
 */
void Reload_TextView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}


/**
 * \brief Aktualizowanie widoku kamery i projekcji na scenie.
 * 
 */
void Reload_TableView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //resetowanie macierzy

    float ratio = WIDTH * 1.0f / HEIGHT;

    //ustawienie widzenia perspektywicznego
    gluPerspective(45.0, ratio, 0.5, MAX * 4);  

    //ustawienie pozycji kamery i kierunku patrzenia na scen�
    gluLookAt(x, y, z,
        x + lx, 1.0f, z + lz,
        0.0f, 1.0f, 0.0f);

    //obr�cenie widoku o 90 stopni wok� osi X
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
    glMatrixMode(GL_MODELVIEW);
}


/**
 * \brief Wy�wietlanie grafiki.
 * 
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie buforu
    Reload_TableView(); //ustawienie perspektywy, pozycji kamery i kierunku patrzenia
    glLoadIdentity(); // reset wszystkich przekszta�ce�

    glEnable(GL_LIGHTING); //w��czenie o�wietlenia
    glCallList(1); //wywo�anie listy rysunkowej sk�adaj�cej si� z kostek na mapie gry
    glDisable(GL_LIGHTING); //wy��czenie o�wietlenie

    // Wy�wietlanie punktu na mapie z g�ry.
    if (mapFlag == 1)
    {
        glColor3f(0.0f, 0.0f, 1.0f); // Ustawia kolor na niebieski
        glLoadIdentity();
        glTranslatef(tempX, -tempZ, 0.45f);

        // Rysowanie ko�a
        drawCircle(0.5f, 100);

        glFlush();
    }

    information();
    glutSwapBuffers(); //podmienienie bufor�w
}


/**
 * \brief Odliczanie czasu.
 * 
 * \param value - Informacja o stanie timera.
 */
 void timer(int value) {
    int fieldX = static_cast<int>(-x + ((MAX - 1) / 2));
    int fieldZ = static_cast<int>(-z + ((MAX - 1) / 2));

    if (value == 0) {
        mapTime += 1;
        glutPostRedisplay();

        if (Map[fieldX][fieldZ] == 4 && !timerRunning) {
            timerRunning = true;
            glutTimerFunc(1000, timer, 0);
        }
        else if (Map[fieldX][fieldZ] == 5 && timerRunning) {
            timerRunning = false;
            glutTimerFunc(1000, timer, 1);
        }
        else {
            glutTimerFunc(1000, timer, 0);
        }
    }
    else if (value == 1) {
        endTime = mapTime;
        blockCamera = true;
        
    }
}


/**
 * \brief Sprawdzanie czy kamera nie wchodzi w �cian�.
 * 
 * \param valX - pozycja kamery w p�aszczy�nie x po nast�pnym kroku.
 * \param valZ - pozycja kamery w p�aszczy�nie z po nast�pnym kroku.
 * \return - Zwraca warto�� FALSE, je�eli kamera wchodzi w �cian� lub true, je�eli nie.
 */
bool isWall(float valX, float valZ)
{
    int wallX = static_cast<int>(-valX + ((MAX - 1) / 2));
    int wallZ = static_cast<int>(-valZ + ((MAX - 1) / 2));

    int wallX1 = static_cast<int>(-valX + ((MAX - 1) / 2) - 0.15);
    int wallZ1 = static_cast<int>(-valZ + ((MAX - 1) / 2) - 0.15);

    int wallX2 = static_cast<int>(-valX + ((MAX - 1) / 2) + 1.15);
    int wallZ2 = static_cast<int>(-valZ + ((MAX - 1) / 2) + 1.15);

    if (Map[wallX1][wallZ1] == 0 || Map[wallX2][wallZ1] == 0 || Map[wallX1][wallZ2] == 0 || Map[wallX2][wallZ2] == 0 ||
        Map[wallX][wallZ] == 0 || Map[wallX][wallZ + 1] == 0 || Map[wallX + 1][wallZ] == 0 || Map[wallX + 1][wallZ + 1] == 0)
    {
        return FALSE;
    }
    return TRUE;
}


/**
* \brief Obs�uga specjalnych klawiszy.
* 
*   Lista zdarze�:
*       - Zdarzenia klawiatury:
*           -# Strza�ka w lewo \n
*               Obr�t kamery w lew� stron�.
*           -# Strza�ka w prawo \n
*               Obr�t kamery w praw� stron�.
*           -# Strza�ka w d� \n
*               Przesuni�cie kamery do ty�u.
*           -# Strza�ka w g�r� \n
*               Przesuni�cie kamery w prz�d.
*
* \param key - kod wci�ni�tego klawisza specjalnego.
* \param xx  - pozycja kursora myszy w osi X.
* \param yy  - pozycja kursora myszy w osi Y.
*/
void processSpecialKeys(int key, int xx, int yy) {
    // Zmiana po�o�enia kamery na scenie
    if (mapFlag != 1)
    {
        switch (key)
        {
            case GLUT_KEY_LEFT:
                angle -= 0.1f;
                lx = sin(angle);
                lz = -cos(angle);
                break;
            case GLUT_KEY_RIGHT:
                angle += 0.1f;
                lx = sin(angle);
                lz = -cos(angle);
                break;
            case GLUT_KEY_UP:
                if (!blockCamera)
                {
                    if (isWall(x + lx * 0.1f, z + lz * 0.1f)) {
                        x += lx * 0.1f;
                        z += lz * 0.1f;
                    }
                }
                break;
            case GLUT_KEY_DOWN:
                if (!blockCamera)
                {
                    if (isWall(x - lx * 0.1f, z - lz * 0.1f)) {
                        x -= lx * 0.1f;
                        z -= lz * 0.1f;
                    }
                }
                break;
        }
    }
}


/**
 * \brief Obs�uga wci�ni�tych klawiszy.
 * 
 *  Lista zdarze�:
 *      - Zdarzenia klawiatury:
 *          -# Klawisz 'm' \n
 *              Wy�wietlenie mapy z g�ry.
 *          -# Klawisz 'x' \n
 *              Zako�czenie dzia�ania programu.
 *          -# Klawisz '1' \n
 *              Prze��czenie na map� 1.
 *          -# Klawisz '2' \n
 *              Prze��czenie na map� 2.
 *          -# Klawisz '3' \n
 *              Prze��czenie na map� 3.
 *          -# Klawisz '4' \n
 *              Prze��czenie na map� 4.
 * 
* \param key - kod wci�ni�tego klawisza.
* \param xx  - pozycja kursora myszy w osi X.
* \param yy  - pozycja kursora myszy w osi Y.
 */
void Keyboard(GLubyte key, int xx, int yy)
{
    switch (key) {
    //  Wci�niecie m - rzut kamery na map� z g�ry.
    case 'm':
        if (mapFlag == 0)
        {
            tempX = x;
            tempY = y;
            tempZ = z;
            tempLx = lx;
            tempLz = lz;

            lx = 0.00f;
            lz = 1.0f;

            y = MAX * 1.4f;
            x = 0.0f;
            z = 0.0f;

            mapFlag = 1;
        }
        else {
            x = tempX;
            y = tempY;
            z = tempZ;
            lx = tempLx;
            lz = tempLz;

            mapFlag = 0;
        }
        break;
        // Wci�ni�cie x - koniec gry.
    case 'x':
        glutDestroyWindow(glutGetWindow());
        break;
        // Zmiana mapy na 1
    case '1':
        if (mapFlag != 1)
        {
            for (int i = 0; i < MAX; i++)
                delete[] Map[i];

            delete[] Map;
            level = 1;
            startGame();
        }
        break;
        // Zmiana mapy na 2
    case '2':
        if (mapFlag != 1)
        {
            for (int i = 0; i < MAX; i++)
                delete[] Map[i];

            delete[] Map;
            level = 2;
            startGame();
        }
        break;
        // Zmiana mapy na 3
    case '3':
        if (mapFlag != 1)
        {
            for (int i = 0; i < MAX; i++)
                delete[] Map[i];

            delete[] Map;
            level = 3;
            startGame();
        }
        break;
        // Zmiana mapy na 4
    case '4':
        if (mapFlag != 1)
        {
            for (int i = 0; i < MAX; i++)
                delete[] Map[i];

            delete[] Map;
            level = 4;
            startGame();
        }
        break;
    }
}


/**
 * \brief Rysowanie sze�cianu.
 * 
 */
void drawCube() {

    // Rozpocz�cie nak�adania tekstury
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBox);
    glBegin(GL_QUADS);

    //front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    //right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);

    //back
    glNormal3f(0.0f, 0.0f, -1.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    //left
    glNormal3f(-1.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    //top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    //bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Zako�czenie nak�adania tekstury
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


// Rysowanie pod�o�e
/**
 * \brief Rysowanie pod�o�a.
 * 
 */
void drawGround(GLuint &texture)
{
    // Rozpocz�cie nak�adania tekstury
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);    
    
    // Zako�czenie nak�adania tekstury
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


/**
 * \brief Rysowanie okr�gu.
 * 
 * \param radius - Promie� okr�gu.
 * \param segments - Ilo�� segment�w, na kt�re podzielone jest ko�o.
 */
void drawCircle(float radius, int segments)
{
    glLineWidth(3.5f); // Ustawienie grubo�ci linii
    glBegin(GL_LINE_LOOP); // Rysowanie linii
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}


/**
 * \brief Wczytywanie tekstur.
 * 
 * \param fileName - nazwa pliku z tekstur�.
 * \param texture - identyfikator tekstury.
 */
void loadTexture(const string &fileName, GLuint &texture) {
    
    // Wczytaj tekstur� z pliku
    string filePath = "Textures/" + fileName;
    int width, height, channels;
    unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb);

    // Utw�rz identyfikator tekstury
    glGenTextures(1, &texture);

    // Ustaw bie��c� tekstur�
    glBindTexture(GL_TEXTURE_2D, texture);

    // Przeka� dane tekstury do OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Ustaw parametry tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Zwalnianie pami�ci zaalokowanej dla wczytanego obrazu
    stbi_image_free(image);
}


/**
 * \brief Informacje do wy�wietlenia.
 * 
 */
void information()
{
    Reload_TextView(); //ustawienie perspektywy do wy�wietlenia tekstu
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f); //ustawienie koloru tekstu na bia�y
    showNotification(-0.98f, 0.95f, "m - mapa", GLUT_BITMAP_HELVETICA_10);
    showNotification(-0.98f, 0.90f, "x - koniec gry", GLUT_BITMAP_HELVETICA_10);
    showNotification(-0.98f, 0.85f, "1 - zmiana mapy na 1", GLUT_BITMAP_HELVETICA_10);
    showNotification(-0.98f, 0.80f, "2 - zmiana mapy na 2", GLUT_BITMAP_HELVETICA_10);
    showNotification(-0.98f, 0.75f, "3 - zmiana mapy na 3", GLUT_BITMAP_HELVETICA_10);
    showNotification(-0.98f, 0.70f, "4 - zmiana mapy na 4", GLUT_BITMAP_HELVETICA_10);
    glColor3f(1.0f, 0.0f, 0.0f); //ustawienie koloru tekstu na czerwony
    showNotification(0.0f, 0.9f, mapName, GLUT_BITMAP_HELVETICA_18);
    string timeBest = to_string(theBestOnTheMap);
    showNotification(0.0f, 0.83f, "Najlepszy wynik na tej mapie: " + timeBest + "s" , GLUT_BITMAP_HELVETICA_18);
    string timeStr = to_string(mapTime);
    showNotification(0.0f, 0.75f, "Czas: " + timeStr + "s", GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0f, 0.0f, 1.0f);
    string timeEnd = to_string(endTime);
    int timeToBeat = theBestOnTheMap - endTime;
    string toBeat = to_string(timeToBeat);

    if (endTime != 0 && !timerRunning)
    {
        string notification;
        if (endTime < theBestOnTheMap)
        {
            notification = "Ustanowiles nowy rekord: " + timeEnd + "s";
            Result[level - 1] = endTime;
            writeResultsToFile("theBestTimes.txt", 4, Result);
        }
        else
        {
            notification = "Do ustanowienia rekordu brakuje: " + toBeat + "s";
        }
        showNotification(-0.2f, 0.0f, notification, GLUT_BITMAP_TIMES_ROMAN_24);
        showNotification(-0.2f, -0.1f, "Aby kontynuowac wybierz mape", GLUT_BITMAP_TIMES_ROMAN_24);
    }
}


/**
 * \brief Poka� informacje.
 * 
 * \param x - Wsp�rz�dna x.
 * \param y - Wsp�rz�dna y. 
 * \param text - Tekst.
 * \param font - Nazwa czcionki.
 */
void showNotification(float x, float y, string text, void* font)
{
    glRasterPos2f(x, y);
    const char* txt = text.c_str();
    while (*txt != 0)
    {
        glutBitmapCharacter(font, *txt);
        txt++;
    }
}