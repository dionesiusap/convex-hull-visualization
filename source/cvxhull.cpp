/************************************
 *  2-D CONVEX HULL ALGORITHM ####  *
 *  #### Using Quick-Hull Approach  *
 * -------------------------------- *
 * Author: Dionesius Agung Andika P *
 *  --Institut Teknologi Bandung--  *
 ************************************/

/*
 * cvxhul.cpp : QuickHull Strategy
 * Using QuickHull strategy for finding the convex hull of a particular set of points
 * Author: Dionesius Agung Andika P / 13516043
 * Institut Teknologi Bandung, 2018
*/

#include <bits/stdc++.h>
#include "visualizer.hpp"

using namespace std;

#define LEFT -1
#define RIGHT 1
#define ON_LINE 0

#define Point pair<int, int>
#define Line pair<Point, Point>

/*** Global Variables ***/
// Global variables are used due to constraints of display callback function
vector<Line> hull;
int n;
vector<Point> set_of_points;

/*** QUICKHULL ALGORITHM ***/
int FindPosition(Line line, Point p) {
    int side = (p.second - line.first.second) * (line.second.first - line.first.first) - (line.second.second - line.first.second) * (p.first - line.first.first);

    if (side > 0) {
        return RIGHT;
    }
    else if (side < 0) {
        return LEFT;
    }
    else {
        return ON_LINE;
    }
}

int SquareDistance(Point p1, Point p2){
    return (pow((p2.second - p1.second), 2) + pow((p2.first - p1.first), 2));
}

int XLineDistance(Line line, Point p) {
    return abs((p.second - line.first.second) * (line.second.first - line.first.first) -
               (line.second.second - line.first.second) * (p.first - line.first.first));
}

void QuickHull(vector<Point> set_of_points, int n, Line line, int pos) {
    int idx_max = -1;
    int max_distance = 0;

    Point left_point = line.first;
    Point right_point = line.second;

    for (int i = 0; i < n; i++) {
        int temp_dist = XLineDistance(line, set_of_points[i]);
        if (FindPosition(line, set_of_points[i]) == pos && temp_dist > max_distance) {
            idx_max = i;
            max_distance = temp_dist;
        }
    }

    if (idx_max == -1) {
        hull.push_back(line);
        return;
    }
    
    Line left = {set_of_points[idx_max], left_point};
    Line right = {set_of_points[idx_max], right_point};
    QuickHull(set_of_points, n, left, -FindPosition(left, right_point));
    QuickHull(set_of_points, n, right, -FindPosition(right, left_point));
}

void InitializeQuickHull(vector<Point> set_of_points, int n) {
    if (n < 3) {
        cout << "No convex hull can be found." << endl;
        return;
    }

    int min_x = 0;
    int max_x = 0;
    for (int i = 1; i < n; i++) {
        if (set_of_points[i].first < set_of_points[min_x].first) {
            min_x = i;
        }
        if (set_of_points[i].first > set_of_points[max_x].first) {
            max_x = i;
        }
    }
    Line separator = {set_of_points[min_x], set_of_points[max_x]};

    QuickHull(set_of_points, n, separator, RIGHT);
    QuickHull(set_of_points, n, separator, LEFT);
}

void PrintHull(vector<Line> hull) {
    if (hull.size() > 1) {
        cout << "EDGES OF CONVEX HULL POLYGON: " << endl;
        for (int i = 0; i < hull.size(); i++) {
            cout << i+1 << ". {(" << hull[i].first.first << "," << hull[i].first.second << "),(" << hull[i].second.first << "," << hull[i].second.second << ")}" << endl;
        }
    }
    else {
        cout << "Convex hull for point set is not possible." << endl;
    }
}

/*** VISUALIZER GRAPHICS ***/
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Print header
    PrintHeader("CONVEX HULL VISUALIZATION", -48, 110);

    // Print info
    PrintText("n = " + to_string(n), -100, -105);

    // Initializing grid
    DrawGrid(100, 5, 10);

    // Draw set of points
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
      for (int i = 0; i < n; i++) {
          glVertex2i(set_of_points[i].first, set_of_points[i].second);
        //   cout << set_of_points[i].first <<"," << set_of_points[i].second << endl;
      }
    glEnd();

    // Draw convex hull lines
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < hull.size(); i++) {
        // cout << "(" << hull[i].first.first << "," << hull[i].first.second << ")(" << hull[i].second.first << "," << hull[i].second.second << ")" << endl;
        glBegin(GL_LINES);
          glVertex2i(hull[i].first.first, hull[i].first.second);
          glVertex2i(hull[i].second.first, hull[i].second.second);
        glEnd();
    }

    glFlush();
}

string PointToString(Point p) {
    return "(" + to_string(p.first) + "," + to_string(p.second) + ")";
}

/*** MAIN ***/
int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc == 2) {
        n = atoi(argv[1]);
    }
    else {
        cout << "Input n: ";
        cin >> n;
    }

    for (int i = 0; i < n; i++) {
        int x = (rand() % 201) - 100;
        int y = (rand() % 201) - 100;
        set_of_points.push_back({x, y});
    }
    
    cout << "POINTS:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". (" << set_of_points[i].first << "," << set_of_points[i].second << ")" << endl;
    }
    cout << endl;

    // Quick Hull
    auto start_time = clock(); // starts the timer

    InitializeQuickHull(set_of_points, n);
    PrintHull(hull);

    auto end_time = clock(); // stops the timer
    cout << "\nExecution time: " << (end_time - start_time)/double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;

    // Visualize Result
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 523);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Convex Hull Visualization");
    InitializeVisualizer(255.0, 255.0, 255.0, 100, 5);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();

    return 0;
}