//
//  firstmate.hpp
//  Project 1-Treasure Hunt
//
//  Created by John Corio on 9/12/19.
//  Copyright © 2019 John Corio. All rights reserved.
//

#ifndef firstmate_hpp
#define firstmate_hpp

// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <stdio.h>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <utility>

class Firstmate {
public:
    // default constructor
    Firstmate()
    {
        huntorder = "nesw";
        went_ashore = 0;
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
    
    void increment_wentashore()
    {
        went_ashore++;
    }
    
    int get_tiles_investigated()
    {
        return tiles_investigated;
    }
    
    void increment_tilesinvestigated()
    {
        tiles_investigated++;
    }
    
    int get_wentashore()
    {
        return went_ashore;
    }
    
    // sets current location of Firstmate, could do bool for treasure
    void set_current_location (std::pair<int, int> &cool) {
        current_location = cool;
        tiles_investigated++;
    }
    
    // pass by reference?
    void discover_tile(int row, int col)
    {
        //if (searchmodeIsDefault)
        //{
            std::pair<int, int> tile(row, col);
            container.push_back(tile);
            // push_back() queue
        //}
        /* STL AND YOU SAYS ONLY EVER PUSH BACK
        else
        {
            std::pair<int, int> tile(row, col);
            container.push_front(tile);
            // push_front() stack
        }
         */
    }
    
    // bool function, found treasure or not
    void investigate()
    {
        // pops tile off of deque based on search method, sets as current location
        if (searchmodeIsDefault)
        {
            set_current_location(container.front());
            container.pop_front();
            // pop tile off front, queue
        }
        else
        {
            set_current_location(container.back());
            container.pop_back();
            // pop back, stack
        }
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
    
    std::string get_order() const
    {
        return huntorder;
    }
    
private:
    std::deque<std::pair<int, int>> container;
    std::pair<int, int> current_location;
    std::string huntorder;
    bool searchmodeIsDefault;
    int went_ashore;
    int tiles_investigated;
    
    // YOU WILL WANT LARGER FUNCTIONS IMPLEMENTED IN .CPP FILE
};

#endif /* firstmate_hpp */
