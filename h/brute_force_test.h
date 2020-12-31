#ifndef __br_force__
#define __br_force__
#include <iostream>
#include <vector>
#include <algorithm>
#include <bfs.h>
#include <dls.h>

void find_solo()
{
    std::vector<int> init_vec = {2, 4, 6, 5, 8, 3, 0, 1, 7};
    BFS a = BFS(init_vec);
    a.loop();
}

void brute_force_test()
{
    size_t i = 100;
    std::vector<int> init_vec = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    while (i--)
    {
        std::random_shuffle(init_vec.begin(), init_vec.end());
        BFS a = BFS(init_vec);
        int s;
        if (a.is_solvable(init_vec))
        {
            a.loop();
            a.disp_in_menu(init_vec, init_vec);
        }
        else
        {
            std::cerr << "\033[4;31m"
                      << "not solvable"
                      << "\033[0m" << std::endl;
        }
        std::cerr << "\033[34m"
                  << "i: " << i << std::endl;
    }
}
void brute_force_test2()
{
    size_t i = 100;
    std::vector<int> init_vec = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    while (i--)
    {
        std::random_shuffle(init_vec.begin(), init_vec.end());
        DLS a = DLS(init_vec);
        a.max_depth = 30;
        int s;
        if (a.is_solvable(init_vec, s))
        {
            a.loop();
            a.disp_in_menu(init_vec, init_vec);
        }
        else
        {
            std::cerr << "\033[4;31m"
                      << "not solvable"
                      << "\033[0m" << std::endl;
        }
        std::cerr << "\033[34m"
                  << "i: " << i << std::endl;
    }
}
#endif 