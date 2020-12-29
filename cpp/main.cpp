#include <iostream>
#include "board.h"
#include <algorithm>
#include <menu.h>
#include <bls.h>

void brute_force_test2();

void brute_force_test();
void find_solo()
{
    std::vector<int> init_vec = {2, 4, 6, 5, 8, 3, 0, 1, 7};
    Board a = Board(init_vec);
    a.loop();
}

int main()
{

    std::cerr << "\033[35m"
              << "hello there"
              << "\033[0m" << std::endl;
    
    // brute_force_test2();

    while(true){
    clear();
    menu_loop();
    }
    // std::vector<int> init_vec1 = {1, 2, 3, 4, 0,5, 6,  7,8};
    // std::vector<int> init_vec1 = {1, 2, 3, 4, 5, 6,0,  7,8};
    std::vector<int> init_vec1 = {8, 0, 3, 4, 6, 1,5,  7,2};
    // std::vector<int> init_vec1 = {7, 1, 5, 8, 3, 2, 4,0, 6};
    // std::vector<int> init_vec1 = {2, 4, 6, 5, 8, 3, 0, 1, 7};
    // std::vector<int> init_vec1 = {1, 2, 3, 4, 6, 8, 0, 7, 5};
    // std::vector<int> init_vec1 = {2, 3, 0, 1, 5, 6, 4, 7, 8};
    // std::vector<int> init_vec1 = {1, 2, 3, 4, 6, 8, 7, 5, 0};
    // std::vector<int> init_vec1 = {1, 2, 3, 0, 5, 6, 4, 7, 8};
    
    // std::vector<std::vector<int>> vv{init_vec1, init_vec2, init_vec3, init_vec4,init_vec5};
    // std::vector<int> init_vec = {2, 4, 6, 5, 8, 3, 0, 1, 7};
    int m = 30;
    bool done=false;
        Board bb (init_vec1);
            std::cerr << "return : " <<bb.loop()<< std::endl;
    
        BLS t = BLS(init_vec1);
        t.max_depth=m;
        t.disp_in_menu(*t.current_node->val, *t.current_node->val);
        int a = 0;
        if (t.is_solvable(init_vec1, a)){
            done = t.loop();
            std::cerr << "return : " <<done<< std::endl;
        }
        else
        {
            std::cerr << "not solvable " << std::endl;
        }
        std::vector<std::vector<int>> result = t.final_val;
        t.disp_in_menu(*t.current_node->val, *t.current_node->val);



    std::cerr << "\033[35m"
              << "bye"
              << "\033[0m" << std::endl;
    return 0;
}

void brute_force_test()
{
    size_t i = 100;
    std::vector<int> init_vec = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    while (i--)
    {
        std::random_shuffle(init_vec.begin(), init_vec.end());
        Board a = Board(init_vec);
        int s;
        if (a.is_solvable(init_vec))
        {
            a.loop();
            a.disp(init_vec);
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
        BLS a = BLS(init_vec);
        a.max_depth = 30;
        int s;
        if (a.is_solvable(init_vec,s))
        {
            a.loop();
            a.disp(init_vec);
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

// int main()
// {

//     std::vector<int> init_vec = {2, 4, 6, 5, 8, 3, 0, 1, 7};
//     std::vector<Board::Node*> ve;
//     for (int i = 0; i < 120000; i++) //120000
//     {
//         Board::Node * vv = new Board::Node (std::vector<int>({2, 4, 6, 5, 8, 3, 0, 1, 7}));
//         if (ve.size() >= 1)
//         {
//             vv->down = ve[ve.size() - 1];
//             vv->up = ve[ve.size() - 1];
//             vv->right = ve[ve.size() - 1];
//             vv->left = ve[ve.size() - 1];
//             vv->parent = ve[ve.size() - 1];
//         }
//         ve.push_back(vv);
//     }
//     for (size_t i = 0; i < ve.size(); i++)
//     {
//         delete ve[i];
//         ve[i] = nullptr ;
//     }

//     return 0;
// }