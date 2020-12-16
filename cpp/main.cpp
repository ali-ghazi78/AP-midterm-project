#include <iostream>
#include "board.h"
int main (){
    std::cout<<"\033[35m"<<"hello there"<<"\033[0m"<<std::endl;
    std::vector<size_t> init_vec = {1,8,2,0,4,3,7,6,5};
    Board a = Board(init_vec);
    a.make_adjacent_nodes(*a.head->val);
    // a.head->right->disp(*a.head->right->val);
    // std::cout<<a.check_if_is_answer(*a.head->val)<<" val"<<std::endl;
    a.search_for_answer(a.head);
    
    
    std::cout<<"\033[35m"<<"bye"<<"\033[0m"<<std::endl;
    return 0;
}
