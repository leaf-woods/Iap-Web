#ifndef BORDER_PIXEL_DIFF_NODE_H
#define BORDER_PIXEL_DIFF_NODE_H

#include <bitset>
#include <iostream>

#include <opencv2/core.hpp>

enum class direction {
    north_east,
    north,
    north_west,
    west,
    south_west,
    south,
    south_east,
    east
};
class border_pixel_diff_node {
    public:
        int index[2] = {-1};
        int nb_delta[8] = {-1};
        //https://stackoverflow.com/questions/3030829/is-it-possible-to-set-an-object-to-null
        cv::Vec<int, 3> diff[8];
        std::bitset<8> x;

    public:
        void print() {
            std::cout << "index: [ " << index[0] << " , " << index[1] << " ]" << std::endl;
            std::cout << "x: " << x.to_string() << std::endl;
            /*
            std::cout << "north_east: " << nb_delta[0];
            std::cout << " north: " << nb_delta[static_cast<int>(direction::north)];
            std::cout << " north_west: " << nb_delta[static_cast<int>(direction::north_west)];
            std::cout << " west: " << nb_delta[static_cast<int>(direction::west)];
            std::cout << " south_west: " << nb_delta[static_cast<int>(direction::south_west)];
            std::cout << " south: " << nb_delta[static_cast<int>(direction::south)];
            std::cout << " south_east: " << nb_delta[static_cast<int>(direction::south_east)];
            std::cout << " east: " << nb_delta[static_cast<int>(direction::east)];
            std::cout << std::endl;
            */
            
            std::cout << " diff north_east: " << diff[0][0] << " , " << diff[0][1] << " , " << diff[0][2] << std::endl;
            std::cout << " diff north: " << diff[1][0] << " , " << diff[1][1] << " , " << diff[1][2] << std::endl;
            std::cout << " diff north_west: " << diff[2][0] << " , " << diff[2][1] << " , " << diff[2][2] << std::endl;
            std::cout << " diff west: " << diff[3][0] << " , " << diff[3][1] << " , " << diff[3][2] << std::endl;
            std::cout << " diff south_west: " << diff[4][0] << " , " << diff[4][1] << " , " << diff[4][2] << std::endl;
            std::cout << " diff south: " << diff[5][0] << " , " << diff[5][1] << " , " << diff[5][2] << std::endl;
            std::cout << " diff south_east: " << diff[6][0] << " , " << diff[6][1] << " , " << diff[6][2] << std::endl;
            std::cout << " diff east: " << diff[7][0] << " , " << diff[7][1] << " , " << diff[7][2] << std::endl;
            
            std::cout << std::endl;
        }
};
#endif