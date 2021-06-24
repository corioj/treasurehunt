//
//  captain.hpp
//  Project 1-Treasure Hunt
//
//  Created by John Corio on 9/12/19.
//  Copyright © 2019 John Corio. All rights reserved.
//

#ifndef captain_hpp
#define captain_hpp

// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <stdio.h>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <utility>

class Captain {
public:
    // default constructor
    Captain()
    {
        huntorder = "nesw";
        tiles_investigated = 0;
        searchmodeIsDefault = true;
    }
    
    // set search mode
    void set_searchmode(bool searchmode)
    {
        searchmodeIsDefault = searchmode;
    }
    
    // set hunt order
    void set_huntorder(std::string &hunt)
    {
        huntorder = hunt;
    }
    
    // execute search algorithm, pass by reference?
    void set_current_location(std::pair<int, int> &curr)
    {
        current_location = curr;
        tiles_investigated++;
    }
    
    int get_tiles_investigated()
    {
        return tiles_investigated;
    }


    void investigate()
    {
        if (searchmodeIsDefault)
        {
            set_current_location(container.front());
            container.pop_front();
            
        }
        else
        {
            set_current_location(container.back());
            container.pop_back();
        }
    }
    
    std::string get_order() const
    {
        return huntorder;
    }
    
    // pass by reference?
    void discover_tile(int row, int col)
    {
        //if (searchmodeIsDefault)
        //{
            // stack, enter at front
            std::pair<int, int> tile(row, col);
            container.push_front(tile);
        //}
        /* STL AND YOU SAYS ONLY EVER PUSHBACK
        else
        {
            // queue, enter at back
            std::pair<int, int> tile(row, col);
            container.push_back(tile);
        }
         */
    }
    
    bool container_empty()
    {
        if (container.empty())
        {
            return true;
        }
        return false;
    }
    
    std::pair<int, int> get_current_location()
    {
        return current_location;
    }
    
private:
    std::deque<std::pair<int, int>> container;
    std::pair<int, int> current_location;
    
    std::string huntorder;
    bool searchmodeIsDefault;
    int tiles_investigated;
    
    // YOU WILL WANT LARGER FUNCTIONS IMPLEMENTED IN .CPP FILE
};

#endif /* captain_hpp */
