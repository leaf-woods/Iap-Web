#include <iostream>

#include "border_pixel_diff_node.h"

using namespace std;
void testDirection() {
    direction dr = direction::north_east;
    int n = static_cast<int>(dr);
    cout << "north_east: " << n << endl;
    dr = direction::north;
    n = static_cast<int>(dr);
    cout << "north: " << n << endl;
    dr = direction::north_west;
    n = static_cast<int>(dr);
    cout << "north_west: " << n << endl;
    dr = direction::west;
    n = static_cast<int>(dr);
    cout << "west: " << n << endl;
    dr = direction::south_west;
    n = static_cast<int>(dr);
    cout << "south_west: " << n << endl;
    dr = direction::south;
    n = static_cast<int>(dr);
    cout << "south: " << n << endl;
    dr = direction::south_east;
    n = static_cast<int>(dr);
    cout << "south_east: " << n << endl;
    dr = direction::east;
    n = static_cast<int>(dr);
    cout << "east: " << n << endl;
    
    cout << endl;    
}

int main(int argc, char* argv[]) {
    cout << "Test direction" << endl;
    testDirection();
    cout << "Test direction: Done" << endl;
    cout << endl;

    border_pixel_diff_node* node = new border_pixel_diff_node();
    node->print();

    return 0;
}