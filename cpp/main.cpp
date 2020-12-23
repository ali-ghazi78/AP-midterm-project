#include <iostream>
#include "board.h"
#include <algorithm>
#include <menu.h>
void brute_force_test();
void find_solo(){
    std::vector<int> init_vec = {2, 4, 6, 5, 8, 3, 0, 1, 7};
    Board a = Board(init_vec);
    a.loop();
}
int main()
{

    std::cerr << "\033[35m"
              << "hello there"
              << "\033[0m" << std::endl;

    while(true)
        menu_loop();
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