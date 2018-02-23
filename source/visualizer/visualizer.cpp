/* -------------------------
 * VISUALIZER MODULE
 * FILE         : visualizer.cpp
 * Description  : Implementation of visualizer.hpp (see visualizer.hpp description).
 * Usage        : -
 * Author       : Dionesius Agung Andika P / 13516043
 * ---Institut Teknologi Bandung, 2018---
*/

#include "visualizer.hpp"

void InitializeVisualizer(float r, float g, float b, float size, float offset)
{
    glClearColor(r, g, b, 0.0);
    glMatrixMode(GL_PROJECTION);
    // gluOrtho2D (-100.0, 100.0, -75.0, 75.0);
    float pixels = size + offset;
    gluOrtho2D(-pixels, pixels, -(pixels+3), pixels+20);
}

void PrintText(string input_text, int x, int y) {
    bool blending = false;
    if (glIsEnabled(GL_BLEND)) {
        blending = true;
    }

    glColor3f(0, 0, 0);
    glRasterPos2f(x,y);

    for (int i = 0; i < input_text.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (char)input_text[i]);
    }

    if (!blending) {
        glDisable(GL_BLEND);
    }
}

void PrintHeader(string header_text,float x, float y) {
    bool blending = false;
    if (glIsEnabled(GL_BLEND)) {
        blending = true;
    }

    glColor3f(0, 0, 0);
    glRasterPos2f(x, y);
    for (int i = 0; i < header_text.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (char)header_text[i]);
    }

    if (!blending) {
        glDisable(GL_BLEND);
    }
}

void DrawGrid(float size, float offset, int increment) {
    // Gridline
    glColor3f(0.75, 0.75, 0.75);
    glLineWidth(1.0);
    for (int i = (int) -size + increment; i < size; i += increment) {
        glBegin(GL_LINES);
          glVertex2i(-size, i);
          glVertex2i(size, i);
        glEnd();

        glBegin(GL_LINES);
          glVertex2i(i, -size);
          glVertex2i(i, size);
        glEnd();
    }

    // Centerline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
      glVertex2i(-size, 0);
      glVertex2i(size, 0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
      glVertex2i(0, -size);
      glVertex2i(0, size);
    glEnd();

    // Borderline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
      glVertex2i(-size, -size);
      glVertex2i(-size, size);
    glEnd();
    glBegin(GL_LINES);
      glVertex2i(-size, size);
      glVertex2i(size, size);
    glEnd();
    glBegin(GL_LINES);
      glVertex2i(size, size);
      glVertex2i(size, -size);
    glEnd();
    glBegin(GL_LINES);
      glVertex2i(size, -size);
      glVertex2i(-size, -size);
    glEnd();
    
    // Axis label
    for (int i = (int) -size; i <= size; i += increment) {
        if (i != 0) {
            // x axis
            PrintText(to_string(i), i-3, -5);

            // y axis
            if (to_string(i).size() == 2) {
                PrintText(to_string(i), -7, i-1);
            }
            else if (to_string(i).size() == 3) {
                PrintText(to_string(i), -10, i-1);
            }
            else if (to_string(i).size() == 4) {
                PrintText(to_string(i), -13, i-1);
            }
        }
    }

    // Copyright
    PrintText("Dionesius A/13516043", 34, -(size+offset));
}

void handleKeypress(unsigned char key, int x, int y){
    if (key==27) {
        exit(0);
    }
}

void ShowWindow(int argc, char** argv, int width, int height, float r, float g, float b, float size, float offset, void (*callback)()) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Convex Hull Visualizer");
    InitializeVisualizer(r, g, b, size, offset);
    glutDisplayFunc(callback);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
}