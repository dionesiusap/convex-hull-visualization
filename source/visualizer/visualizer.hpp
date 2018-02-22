#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

void InitializeVisualizer(float r, float g, float b, float size, float offset);

void PrintText(string input_text, int x, int y);

void PrintHeader(string header_text, float x, float y);

void DrawGrid(float size, float offset, int increment);

// Callback function for glutKeyboardFunc()
void handleKeypress(unsigned char key, int x, int y);

#endif