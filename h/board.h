#ifndef __BOARD__
#define __BOARD__
#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <set>

class Board
{
public:
    class Node
    {
        
    public:
        static void disp(const std::vector<int> &v);
        static size_t Node_no;
        Node(const std::vector<int> & initial_state);
        ~Node();
        std::shared_ptr<std::vector<int>> val;
        Node* up;
        Node* down;
        Node* right;
        Node* left;
        Node* parent;
    };
    Board(std::vector<int> val);
    Board()=default;
    std::queue<Node *> search_queue;
    std::set<std::string> all_record;
    std::vector<Node *> all_address_to_del;
    std::vector<std::vector<int>> final_val;
    Node *head;
    Node *current_node;
    bool randome_or_costume ;
    void make_adjacent_nodes(const std::vector<int> &current_node);
    void move_zero(std::vector<int> &vec1, int x, int y, int loc);
    void disp();
    void disp( std::vector<int> v);
    bool check_if_is_answer(const std::vector<int> &v);
    bool search_for_answer(Node*  cu_node);
    bool is_solvable(const std::vector<int> &v);
    void err_disp(const std::vector<int> &v);
    void disp_in_menu(const std::vector<int> &v,const std::vector<int> &v2);
    std::string make_str(const std::vector<int> &v);
    size_t show_path(Board::Node *n);
    void loop();

};

#endif