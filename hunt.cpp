//
//  hunt.cpp
//  Project 1-Treasure Hunt
//
//  Created by John Corio on 9/12/19.
//  Copyright © 2019 John Corio. All rights reserved.
//

// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <stdio.h>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <iostream>
#include <utility>
#include "map.hpp"
#include "captain.hpp"
#include "firstmate.hpp"
#include <getopt.h>
#include "xcode_redirect.hpp"

class Hunt {
public:
    // default constructor
    Hunt() {
        verbose = false;
        stats = false;
        showPath = false;
        pathtype = '\0';
        maptype = '\0';
        pathlength = 0;
    }
    
    // execute hunt, need to think about return type here
    void treasurehunting() {
        bool treasure = false;
        while (!capt.container_empty())
        {
            // we're always short on tiles needed in a lot of the test cases
            // smaller ones we have bigger??
            capt.investigate();
            treasure = (discover_capt(capt.get_current_location().first,
                                      capt.get_current_location().second));
            
            if (treasure)
                break;
        }
        
        if (treasure)
        {
            make_path();
            if (stats)
            {
                std::cout << "--- STATS ---\n";
                std::cout << "Starting location: " << startinglocation.first << ","
                          << startinglocation.second << "\n";
                std::cout << "Water locations investigated: "
                          << capt.get_tiles_investigated() << "\n";
                std::cout << "Land locations investigated: "
                          << first.get_tiles_investigated() << "\n";
                std::cout << "Went ashore: " << first.get_wentashore() << "\n";
                std::cout << "Path length: " << pathlength << "\n";
                std::cout << "Treasure location: " << treasurelocation.first << ","
                          << treasurelocation.second << "\n";
                std::cout << "--- STATS ---\n";
            }
            if (showPath)
            {
                print_path();
            }
            std::cout << "Treasure found at " << treasurelocation.first
                      << "," << treasurelocation.second
                      << " with path length " << pathlength << ".\n";
        }
        
        else
        {
            if (verbose)
            {
                // before or after STATS????
                std::cout << "Treasure hunt failed\n";
            }
            if (stats)
            {
                std::cout << "--- STATS ---\n";
                std::cout << "Starting location: " << startinglocation.first << ","
                << startinglocation.second << "\n";
                std::cout << "Water locations investigated: " << capt.get_tiles_investigated() << "\n";
                std::cout << "Land locations investigated: " << first.get_tiles_investigated() << "\n";
                std::cout << "Went ashore: " << first.get_wentashore() << "\n";
                std::cout << "--- STATS ---\n";
            }
            std::cout << "No treasure found after investigating "
                      << capt.get_tiles_investigated() + first.get_tiles_investigated()
                      << " locations.\n";
        }
    }
    
    // FIRST MATE SHOULDNT IMMEDIATELY GO TO SHORE WHEN $ TILE IS FOUND NEAR CAPT
    bool discover_capt(int row, int col) {
        bool flag = false;
        for (int i = 0; i < 4; i++)
        {
            if (capt.get_order()[i] == 'n')
            {
                if (row - 1 >= 0)
                {
                    if (treasuremap.get_tile(row - 1, col).location == '.'
                        && treasuremap.get_tile(row - 1, col).previous == '\0')
                    {
                        capt.discover_tile(row - 1, col);
                        treasuremap.get_tile(row - 1, col).previous = 's';
                    }
                    else if (treasuremap.get_tile(row - 1, col).location == 'o'
                             && treasuremap.get_tile(row - 1, col).previous == '\0')
                    {
                        first.discover_tile(row - 1, col);
                        treasuremap.get_tile(row - 1, col).previous = 's';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row - 1 << "," << col << "\n";
                        }
                        flag = fm_hunt();
                    }
                    else if (treasuremap.get_tile(row - 1, col).location == '$')
                    {
                        first.discover_tile(row - 1, col);
                        treasuremap.get_tile(row - 1, col).previous = 's';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row - 1 << "," << col << "\n";
                        }
                        flag = fm_hunt();
                    }
                }
            }
            else if (capt.get_order()[i] == 'e')
            {
                if (col + 1 < treasuremap.get_mapsize())
                {
                    if (treasuremap.get_tile(row, col + 1).location == '.'
                        && treasuremap.get_tile(row, col + 1).previous == '\0')
                    {
                        capt.discover_tile(row, col + 1);
                        treasuremap.get_tile(row, col + 1).previous = 'w';
                    }
                    else if (treasuremap.get_tile(row, col + 1).location == 'o'
                             && treasuremap.get_tile(row, col + 1).previous == '\0')
                    {
                        first.discover_tile(row, col + 1);
                        treasuremap.get_tile(row, col + 1).previous = 'w';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row << "," << col + 1 << "\n";
                        }
                        flag = fm_hunt();
                    }
                    else if (treasuremap.get_tile(row, col + 1).location == '$')
                    {
                        first.discover_tile(row, col + 1);
                        treasuremap.get_tile(row, col + 1).previous = 'w';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row << "," << col + 1 << "\n";
                        }
                        flag = fm_hunt();
                    }
                }
            }
            else if (capt.get_order()[i] == 's')
            {
                if (row + 1 < treasuremap.get_mapsize())
                {
                    if (treasuremap.get_tile(row + 1, col).location == '.'
                        && treasuremap.get_tile(row + 1, col).previous == '\0')
                    {
                        capt.discover_tile(row + 1, col);
                        treasuremap.get_tile(row + 1, col).previous = 'n';
                    }
                    else if (treasuremap.get_tile(row + 1, col).location == 'o'
                             && treasuremap.get_tile(row + 1, col).previous == '\0')
                    {
                        first.discover_tile(row + 1, col);
                        treasuremap.get_tile(row + 1, col).previous = 'n';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row + 1 << "," << col << "\n";
                        }
                        flag = fm_hunt();
                    }
                    else if (treasuremap.get_tile(row + 1, col).location == '$')
                    {
                        first.discover_tile(row + 1, col);
                        treasuremap.get_tile(row + 1, col).previous = 'n';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row + 1 << "," << col << "\n";
                        }
                        flag = fm_hunt();
                    }
                }
            }
            else // 'w'
            {
                if (col - 1 >= 0)
                {
                    if (treasuremap.get_tile(row, col - 1).location == '.'
                        && treasuremap.get_tile(row, col - 1).previous == '\0')
                    {
                        capt.discover_tile(row, col - 1);
                        treasuremap.get_tile(row, col - 1).previous = 'e';
                    }
                    else if (treasuremap.get_tile(row, col - 1).location == 'o'
                             && treasuremap.get_tile(row, col - 1).previous == '\0')
                    {
                        first.discover_tile(row, col - 1);
                        treasuremap.get_tile(row, col - 1).previous = 'e';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row << "," << col - 1 << "\n";
                        }
                        flag = fm_hunt();
                    }
                    else if (treasuremap.get_tile(row, col - 1).location == '$')
                    {
                        first.discover_tile(row, col - 1);
                        treasuremap.get_tile(row, col - 1).previous = 'e';
                        if (verbose)
                        {
                            std::cout << "Went ashore at: " << row << "," << col - 1 << "\n";
                        }
                        flag = fm_hunt();
                    }
                }
            }
            // ADDED THIS MON 8:05
            if (flag)
            {
                break;
            }
        }
        return flag;
    }
    
    bool discover_first(int row, int col) {
        for (int i = 0; i < 4; i++)
        {
            if (first.get_order()[i] == 'n')
            {
                if (row - 1 >= 0)
                {
                    if (treasuremap.get_tile(row - 1, col).location == '$')
                    {
                        first.discover_tile(row - 1, col);
                        treasuremap.get_tile(row - 1, col).previous = 's';
                        std::pair<int, int> yes(row - 1, col);
                        treasurelocation = yes;
                        if (verbose)
                        {
                            
                            std::cout << "party found treasure at " << row - 1 << "," << col << ".\n";
                        }
                        return true;
                    }
                    else if (treasuremap.get_tile(row - 1, col).location == 'o'
                             && treasuremap.get_tile(row - 1, col).previous == '\0')
                    {
                        first.discover_tile(row - 1, col);
                        treasuremap.get_tile(row - 1, col).previous = 's';
                    }
                }
            }
            else if (first.get_order()[i] == 'e')
            {
                if (col + 1 < treasuremap.get_mapsize())
                {
                    if (treasuremap.get_tile(row, col + 1).location == '$')
                    {
                        first.discover_tile(row, col + 1);
                        treasuremap.get_tile(row, col + 1).previous = 'w';
                        std::pair<int, int> yes(row, col + 1);
                        treasurelocation = yes;
                        if (verbose)
                        {
                            std::cout << "party found treasure at " << row << "," << col + 1 << ".\n";
                        }
                        return true;
                    }
                    else if (treasuremap.get_tile(row, col + 1).location == 'o'
                             && treasuremap.get_tile(row, col + 1).previous == '\0')
                    {
                        first.discover_tile(row, col + 1);
                        treasuremap.get_tile(row, col + 1).previous = 'w';
                    }
                }
            }
            else if (first.get_order()[i] == 's')
            {
                if (row + 1 < treasuremap.get_mapsize())
                {
                    if (treasuremap.get_tile(row + 1, col).location == '$')
                    {
                        first.discover_tile(row + 1, col);
                        treasuremap.get_tile(row + 1, col).previous = 'n';
                        std::pair<int, int> yes(row + 1, col);
                        treasurelocation = yes;
                        if (verbose)
                        {
                            std::cout << "party found treasure at " << row + 1 << "," << col << ".\n";
                        }
                        return true;
                    }
                    else if (treasuremap.get_tile(row + 1, col).location == 'o'
                             && treasuremap.get_tile(row + 1, col).previous == '\0')
                    {
                        first.discover_tile(row + 1, col);
                        treasuremap.get_tile(row + 1, col).previous = 'n'; // test for here
                    }
                }
            }
            else // w
            {
                if (col - 1 >= 0)
                {
                    if (treasuremap.get_tile(row, col - 1).location == '$')
                    {
                        first.discover_tile(row, col - 1);
                        treasuremap.get_tile(row, col - 1).previous = 'e';
                        std::pair<int, int> yes(row, col - 1);
                        treasurelocation = yes;
                        if (verbose)
                        {
                            std::cout << "party found treasure at " << row << "," << col - 1 << ".\n";
                        }
                        return true;
                    }
                    else if (treasuremap.get_tile(row, col - 1).location == 'o'
                             && treasuremap.get_tile(row, col - 1).previous == '\0')
                    {
                        first.discover_tile(row, col - 1);
                        treasuremap.get_tile(row, col - 1).previous = 'e';
                    }
                }
            }
        }
        return false;
    }
    
    bool fm_hunt ()
    {
        first.increment_wentashore();
        if (verbose)
        {
            std::cout << "Searching island... ";
        }
        while (!(first.container_empty()))
        {
            first.investigate();
            // check for first tile being treasure, ADDED THIS MON 8:05
            if (treasuremap.get_tile(first.get_current_location().first,
                                     first.get_current_location().second).location == '$')
            {
                std::pair<int, int> treasure(first.get_current_location().first,
                                             first.get_current_location().second);
                treasurelocation = treasure;
                if (verbose)
                {
                    std::cout << "party found treasure at " << treasurelocation.first
                              << "," << treasurelocation.second << ".\n";
                }
                return true;
            }
            if (discover_first(first.get_current_location().first,
                               first.get_current_location().second))
            {
                first.increment_tilesinvestigated();
                return true;
            }
            // maybe should be incrementing tiles here???
        }
        if (verbose)
        {
            std::cout << "party returned with no treasure.\n";
        }
        return false;
    }
    
    // set start location
    void set_start (int row, int col)
    {
        capt.discover_tile(row, col);
        std::pair<int, int> start(row, col);
        startinglocation = start;
        if (verbose)
        {
            std::cout << "Treasure hunt started at: " << startinglocation.first << "," << startinglocation.second << "\n";
        }
    }

    // mode based executions (STATS, SHOW MAP, CPT FM MODES)
    void set_capt_searchmode(bool defaultsearch)
    {
        capt.set_searchmode(defaultsearch);
    }
    
    void set_fm_searchmode(bool defaultsearch)
    {
        first.set_searchmode(defaultsearch);
    }
    
    void set_capt_huntorder(std::string &hunt)
    {
        capt.set_huntorder(hunt);
    }
    
    void set_fm_huntorder(std::string &hunt)
    {
        first.set_huntorder(hunt);
    }
    
    // verbose true
    void set_verbose(bool verbose_choice)
    {
        if (verbose_choice)
        {
            verbose = true;
            return;
        }
        verbose = false;
    }
    
    // path true or false and map type
    void set_pathtype(char type, bool map)
    {
        if (map == true)
        {
            showPath = true;
            pathtype = type;
            return;
        }
        showPath = false;
        return;
    }
    
    // sets show stats
    void set_statsmode(bool statsmode)
    {
        if (statsmode)
        {
            stats = true;
        }
        return;
    }
    
    // backtracing
    void make_path()
    {
        treasurecontainer.push_back(treasurelocation);
        std::pair<int, int> temp(treasurelocation.first, treasurelocation.second);
        Tile traceback = treasuremap.get_tile(treasurelocation.first, treasurelocation.second);
        while (traceback.previous != '\0') 
        {
            pathlength++;
            if (traceback.previous == 'n')
            {
                temp.first--;
                treasurecontainer.push_back(temp);
                traceback = treasuremap.get_tile(temp.first, temp.second);
            }
            else if (traceback.previous == 'e')
            {
                temp.second++;
                treasurecontainer.push_back(temp);
                traceback = treasuremap.get_tile(temp.first, temp.second);
            }
            else if (traceback.previous == 's')
            {
                temp.first++;
                treasurecontainer.push_back(temp);
                traceback = treasuremap.get_tile(temp.first, temp.second);
            }
            else // 'w'
            {
                temp.second--;
                treasurecontainer.push_back(temp);
                traceback = treasuremap.get_tile(temp.first, temp.second);
            }
        }
    }
    
    void print_path()
    {
        if (pathtype == 'M')
        {
            // starts at two away from start location
            for (unsigned i = 1; i < treasurecontainer.size(); i++)
            {
                if (treasuremap.get_tile(treasurecontainer[i].first,
                    treasurecontainer[i].second).previous == 'n')
                {
                    if (treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 'e' ||
                        treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 'w')
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '+';
                    } // if
                    
                    else
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '|';
                    } // else
                    
                } // if
                
                else if (treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).previous == 'e')
                {
                    if (treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 'n' ||
                        treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 's')
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '+';
                    } // if
                    
                    else
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '-';
                    } // else
                    
                } // else if
                
                else if (treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).previous == 's')
                {
                    if (treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 'e' ||
                        treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 'w')
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '+';
                    } // if
                    
                    else
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '|';
                    } // else
                    
                } // else if
                
                else // 'w'
                {
                    if (treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 'n' ||
                        treasuremap.get_tile(treasurecontainer[i-1].first, treasurecontainer[i-1].second).previous == 's')
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '+';
                    } // if
                    
                    else
                    {
                        treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location = '-';
                    } // else
                    
                } // else
            }
            treasuremap.get_tile(treasurelocation.first, treasurelocation.second).location
                        = 'X';
            treasuremap.get_tile(startinglocation.first, startinglocation.second).location
                        = '@';
            treasuremap.print_map();
        }
        else
        {
            std::cout << "Sail:\n";
            for (size_t i = treasurecontainer.size() - 1; i > 0; i--)
            {
                if (treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location == '.' || treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location == '@' )
                {
                    std::cout << treasurecontainer[i].first << "," << treasurecontainer[i].second << "\n";
                }
            }
            std::cout << "Search:\n";
            for (size_t i = treasurecontainer.size() - 1; i > 0; i--)
            {
                if ((treasuremap.get_tile(treasurecontainer[i].first, treasurecontainer[i].second).location == 'o')
                    || (treasuremap.get_tile
                        (treasurecontainer[i].first, treasurecontainer[i].second).location == '$') )
                {
                    std::cout << treasurecontainer[i].first << "," << treasurecontainer[i].second << "\n";
                }
            }
            std::cout << treasurecontainer[0].first << "," << treasurecontainer[0].second << "\n";
        }
    }
    
    // resizes map
    void prepare_map(int mapsize)
    {
        treasuremap.set_mapsize(mapsize);
    }
    
    // makes map of type M
    void make_mapM(char maptyping, std::string &data, int row)
    {
        maptype = maptyping;
        treasuremap.fill_map_TYPEM(data, row);
        
        for (unsigned i = 0; i < data.size(); i++)
        {
            if (data[i] == '@')
            {
                set_start(row, i);
            }
        }
    }
    
    // makes map of type L
    void make_mapL(char terrain, int row, int col)
    {
        maptype = 'L';
        treasuremap.create_tile(terrain, row, col);
        if (terrain == '@')
        {
            set_start(row, col);
        }
    }
    
    
private:
    // hunt participants
    Firstmate first;
    Captain capt;
    Map treasuremap;
    
    // important tiles to keep track of
    std::vector<std::pair<int, int>> treasurecontainer; // push back via back tracing
    std::pair<int, int> treasurelocation;
    std::pair<int, int> startinglocation;
    
    // cmd line variables and modes
    bool verbose;
    bool stats;
    bool showPath;
    char pathtype;
    char maptype;
    int pathlength;
};

// helper functions, check command line input validity
bool is_valid_searchmode(std::string &check)
{
    if (check != "queue" && check != "stack")
    {
        return false;
    }
    return true;
}

bool is_valid_huntorder(std::string &huntingorder)
{
    if (huntingorder.size() != 4)
    {
        return false;
    }
    else
    {
        int ncount = 0, ecount = 0, wcount = 0, scount = 0;
        for (int i = 0; i < 4; i++)
        {
            if (huntingorder[i] == 'n')
            {
                ncount++;
            }
            else if (huntingorder[i] == 'e')
            {
                ecount++;
            }
            else if (huntingorder[i] == 's')
            {
                scount++;
            }
            else if (huntingorder[i] == 'w')
            {
                wcount++;
            }
            else
            {
                return false;
            }
        }
        
        if (ncount != 1)
        {
            return false;
        }
        if (ecount != 1)
        {
            return false;
        }
        if (scount != 1)
        {
            return false;
        }
        if (wcount != 1)
        {
            return false;
        }
        return true;
        
    }
}


int main (int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false); // valgrind error here, aight
    xcode_redirect(argc, argv);
    // fixed a case "firstmate" --> "first-mate" in long_opts
    int gotopt;
    int opt_index = 0;
    option long_opts[] = {
        {"help", no_argument, nullptr, 'h'},
        {"captain", required_argument, nullptr, 'c'},
        {"first-mate", required_argument, nullptr, 'f'},
        {"hunt-order", required_argument, nullptr, 'o'},
        {"verbose", no_argument, nullptr, 'v'},
        {"stats", no_argument, nullptr, 's'},
        {"show-path", required_argument, nullptr, 'p'},
        { nullptr, 0, nullptr, '\0'}
    }; // option, REVISE LATER
    
    Hunt treasurehunt; // OVERWRITE DATA VALUES AFTER DEFAULT CONSTRUCTION USING GETOPT
    int pathoption = 0;
    int captcount = 0;
    int fmcount = 0;
    // should &opt_index be just a nullptr??
    while((gotopt = getopt_long(argc, argv, "hc:f:o:vsp:", long_opts, &opt_index)) != -1) {
        switch (gotopt) {
            // HELP OPTION
            case 'h':
                std::cout << "Consider doing something other " <<
                            "than using this option to hunt for treasure :)\n";
                exit(0);

            // CAPTAIN OPTION
            case 'c':
                if (optarg[0] == '\0')
                {
                    std::cerr << "Captain search error!\n";
                    exit(1);
                }
                else if (captcount >= 1)
                {
                    std::cerr << "Captain search error!\n";
                    exit(1);
                }
                else
                {
                    std::string mode(optarg);
                    if (!is_valid_searchmode(mode))
                    {
                        std::cerr << "Captain search error!\n";
                        exit(1);
                    }
                    
                    if (mode == "queue")
                    {
                        treasurehunt.set_capt_searchmode(false);
                    }
                    captcount++;
                }
                break;
                
            
            // FIRST MATE OPTION
            case 'f':
                if (optarg[0] == '\0')
                {
                    std::cerr << "First mate search error!\n";
                    exit(1);
                }
                else if (fmcount >= 1)
                {
                    std::cerr << "First mate search error!\n";
                    exit(1);
                }
                else
                {
                    std::string mode(optarg);
                    if (!is_valid_searchmode(mode))
                    {
                        std::cerr << "First mate search error!\n";
                        exit(1);
                    }
                    
                    if (mode == "stack")
                    {
                        treasurehunt.set_fm_searchmode(false);
                    }
                    fmcount++;
                }
                break;
               
            case 'o':
                if (optarg[0] == '\0') // this never executes
                {
                    std::cerr << "Hunt order error!\n";
                    exit(1);
                }
                else
                {
                    std::string huntstring(optarg);
                    if (!is_valid_huntorder(huntstring))
                    {
                        std::cerr << "Hunt order error!\n";
                        exit(1);
                    }
                    treasurehunt.set_fm_huntorder(huntstring);
                    treasurehunt.set_capt_huntorder(huntstring);
                }
                break;
                
               
            // VERBOSE OPTION
            case 'v':
                treasurehunt.set_verbose(true);
                break;
               
            // STATS OPTION
            case 's':
                treasurehunt.set_statsmode(true);
                break;
                
            // SHOW PATH AND PATH TYPE OPTION
            case 'p':
                if (optarg[0] == '\0' || (optarg[0] != 'L' && optarg[0] != 'M'))
                    // GIVES BAD ACCESS
                {
                    std::cerr << "Path choice error!\n";
                    exit(1);
                }
                if (pathoption >= 1)
                {
                    std::cerr << "Path choice made twice!\n";
                    exit(1);
                }
                else if (optarg[0] == 'M')
                {
                    treasurehunt.set_pathtype('M', true);
                }
                else
                {
                    treasurehunt.set_pathtype('L', true);
                }
                pathoption++;
                break;
                
            default:
                std::cerr << "Flag error, command not recognized!\n";
                exit(1);
            } // switch
    }
    
        // optarg global varial with option arguments, --captain stack makes optarg stack as a char*
        // optarg = std::string(optarg);
        std::string junk;
        while (std::cin)
        {
            getline(std::cin, junk);
            if (junk[0] == '#')
            {
                junk.clear();
            }
            else
            {
                break;
            }
        }
        
        char maptype = junk[0];
        std::string mapsize;
        getline(std::cin, mapsize);
        int mapposize = stoi(mapsize);
        treasurehunt.prepare_map(mapposize);
        
        // read in map data, create map
        if (maptype == 'M')
        {
            int i = 0;
            std::string mapdata;
            // grab one line of map data, use i to denote row, fill cols
            while (std::cin)
            {
                if (i == mapposize)
                {
                    break;
                }
                getline(std::cin, mapdata);
                treasurehunt.make_mapM('M', mapdata, i);
                i++;
                mapdata.clear();
            }
        }
        else
        {
            std::cin.clear();
            // use cin >> int >> int >> char and repeatedly loop this structure?
            // could i maybe do a getline argument with cin that uses the three variables?
            char terrain = '\0';
            int row;
            int col;
            while (std::cin >> row >> col >> terrain)
            {
                treasurehunt.make_mapL(terrain, row, col);
            }
        }

    treasurehunt.treasurehunting();
    
    return(0);
    }
