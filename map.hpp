//
//  map.hpp
//  Project 1-Treasure Hunt
//
//  Created by John Corio on 9/12/19.
//  Copyright © 2019 John Corio. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <stdio.h>
#include <iostream>
#include <vector>

struct Tile {
    char location = '.';
    char previous = '\0';
};

class Map {
public:
    
    Map() : size(0)
    {
        
    }
    
    // resize map
    void set_mapsize(int size_in)
    {
        size = size_in;
        map.resize(size_in, std::vector<Tile>(size));
    }
    
    int get_mapsize()
    {
        return size;
    }
    
    void create_tile(char terrain, int row, int col)
    {
        map[row][col].location = terrain;
    }
    
    // M type map fill
    void fill_map_TYPEM(std::string &data, int row)
    {
        for (int j = 0; j < size; j++)
        {
            create_tile(data[j], row, j);
        }
    }

    // how to use this within other classes?
    Tile& get_tile(int row, int col) {
        return map[row][col];
    }
    
    void print_map()
    {
        for (unsigned i = 0; i < map.size(); i++)
        {
            for (unsigned j = 0; j < map.size(); j++)
            {
                std::cout << map[i][j].location;
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<Tile>> map;
    int size;
};



#endif /* map_hpp */
