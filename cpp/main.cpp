#include <iostream>
#include "board.h"
#include <algorithm>
void brute_force_test();

int main()
{



    std::cout << "\033[35m"
              << "hello there"
              << "\033[0m" << std::endl;

    // brute_force_test();
    // std::vector<int> init_vec = {1, 2,3,4, 5,6 , 0,7,8};

    std::vector<int> init_vec = {2, 4,6, 5, 8, 3, 0, 1, 7};
    Board a = Board(init_vec);
    // std::vector<std::shared_ptr<Board::Node>> ve;
    // for(int i=0;i<200000;i++)
    // {
    //     std::shared_ptr<Board::Node> vv = std::make_shared<Board::Node>(std::vector<int>({2, 4,6, 5, 8, 3, 0, 1, 7}));
    //     if(ve.size()>=1){
    //         vv->down = ve[ve.size()-1];
    //         vv->up = ve[ve.size()-1];
    //         vv->right = ve[ve.size()-1];
    //         vv->left = ve[ve.size()-1];
    //         vv->parent = ve[ve.size()-1];
    //         // std::cout<<ve[ve.size()-1].use_count()<<std::endl;
    //     }
    //     ve.push_back(vv);
    // }
    // std::cout<<ve.size()<<std::endl;
    // for (size_t i = 0; i < ve.size(); i++)
    // {
    //     // ve[i]->down=nullptr;
    //     // ve[i]->up=nullptr;
    //     // ve[i]->right=nullptr;
    //     // ve[i]->left=nullptr;
    //     // ve[i]->parent=nullptr;

    //     /* code */
    // }
    // std::cout<<a.is_solvable(init_vec);

    // a.search_for_answer(a.head);

    brute_force_test();

    std::cout << "\033[35m"
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
        if (a.is_solvable(init_vec)){
            a.search_for_answer(a.head);
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