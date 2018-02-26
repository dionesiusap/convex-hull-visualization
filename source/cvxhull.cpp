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

// Defining Point type as pair of integers and Line as pair of Point
typedef pair<int, int> Point;
typedef pair<Point, Point> Line;
/* 
 * Example:
 * Point P = {x, y}
 * Line L = {{x1, y1}, {x2, y2}}
 * Access:
 * x = P.first;
 * y = P.second;
 * x1 = L.first.first;
 * y1 = L.first.second;
 * x2 = L.second.first;
 * y2 = L.second.second;
*/

/*** Global Variables ***/
// Global variables are used due to constraints of display callback function
vector<Line> hull; // lines which construct convex hull are stored in this vector
vector<Point> set_of_points; // points are stored in this vector

/*** QUICKHULL ALGORITHM ***/
int FindPosition(Line line, Point p) {
// Finding point position relative to base line
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
// calculating the squared distance between points p1 and p2
    return (pow((p2.second - p1.second), 2) + pow((p2.first - p1.first), 2));
}

int XLineDistance(Line line, Point p) {
// calculating a factor of distance between a line and a point
    return abs((p.second - line.first.second) * (line.second.first - line.first.first) -
               (line.second.second - line.first.second) * (p.first - line.first.first));
}

void QuickHull(vector<Point> set_of_points, int n, Line line, int pos) {
// recursive function for quick hull algorithm
    Point left_point = line.first;
    Point right_point = line.second;

    // finding the farthest point beyond the baseline as a new hull point
    int idx_max = -1;
    int max_distance = 0;
    for (int i = 0; i < n; i++) {
        int temp_dist = XLineDistance(line, set_of_points[i]);
        if (FindPosition(line, set_of_points[i]) == pos && temp_dist > max_distance) {
            idx_max = i;
            max_distance = temp_dist;
        }
    }

    // if no point is found then the baseline is one of the hull edge
    if (idx_max == -1) {
        hull.push_back(line);
        return;
    }
    else {
        /* recursively finding the hull line */
        Line left = {set_of_points[idx_max], left_point};
        Line right = {set_of_points[idx_max], right_point};
        // quick hull for the line on the left of the current baseline
        QuickHull(set_of_points, n, left, -FindPosition(left, right_point));
        // quick hull for the line on the right of the current baseline
        QuickHull(set_of_points, n, right, -FindPosition(right, left_point));
    }
}

void InitializeQuickHull(vector<Point> set_of_points, int n) {
// initializing the quickhull recursive algorithm; calling the first QuickHull function
    // if there are less than 3 points convex hull cannot be made
    if (n < 2) {
        cout << "No convex hull can be found." << endl;
        return;
    }
    else {
        // finding leftmost and rightmost point in the set as baseline
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
        Line baseline = {set_of_points[min_x], set_of_points[max_x]};
        QuickHull(set_of_points, n, baseline, RIGHT);
        QuickHull(set_of_points, n, baseline, LEFT);
    }
}

void PrintHull(vector<Line> hull) {
// printing edges of convex hull in the form of point pairs
    // e.g. {(x1,y1),(x2,y2)}
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
// callback function for drawing graphics

    // clears buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // prints header
    PrintHeader("CONVEX HULL VISUALIZATION", -48, 110);

    // prints info
    PrintText("n = " + to_string(set_of_points.size()), -100, -105);

    // initializing grid
    DrawGrid(100, 5, 10);

    // drawing set of points
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < set_of_points.size(); i++) {
        glVertex2i(set_of_points[i].first, set_of_points[i].second);
    }
    glEnd();

    // drawing convex hull lines
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < hull.size(); i++) {
        glBegin(GL_LINES);
        glVertex2i(hull[i].first.first, hull[i].first.second);
        glVertex2i(hull[i].second.first, hull[i].second.second);
        glEnd();
    }

    glFlush();
}

/*** MAIN ***/
int main(int argc, char **argv) {
    int n; // number of points

    // seed for random integer generation
    srand(time(NULL));

    // checks number of arguments
    if (argc == 2) {
        // if 1 argument input, n of points = argument
        n = atoi(argv[1]);
    }
    else if (argc == 1) {
        // if no argument input, prompt user to input n of points
        cout << "Input n: ";
        cin >> n;
    }
    else {
        cerr << "Error: too many arguments.\n";
        return -1;
    }

    for (int i = 0; i < n; i++) {
        Point p;
        int x = (rand() % 201) - 100;
        int y = (rand() % 201) - 100;
        for (int j = 0; j < i; j++) {
            if (p == set_of_points[j]) {
                x = (rand() % 201) - 100;
                y = (rand() % 201) - 100;
                break;
            }
        }
        p = {x,y};
        set_of_points.push_back({x, y});
    }
    
    // printing points in command line
    cout << "POINTS:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". (" << set_of_points[i].first << "," << set_of_points[i].second << ")" << endl;
    }
    cout << endl;

    // quickhull algorithm
    auto start_time = clock(); // starts the timer

    InitializeQuickHull(set_of_points, n);
    PrintHull(hull);

    auto end_time = clock(); // stops the timer
    cout << "\nExecution time: " << (end_time - start_time)/double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;

    // visualize Result in a window
    ShowWindow(argc, argv, 500, 523, 255.0, 255.0, 255.0, 100, 5, display);

    return 0;
}