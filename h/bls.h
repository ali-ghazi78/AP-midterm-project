#ifndef __BLS__
#define __BLS__
#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <set>

class BLS
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
    BLS(std::vector<int> val);
    BLS()=default;
    std::stack<Node *> search_queue;
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
    bool is_solvable(const std::vector<int> &v,int & inver);
    void err_disp(const std::vector<int> &v);
    void disp_in_menu(const std::vector<int> &v,const std::vector<int> &v2);
    std::string make_str(const std::vector<int> &v);
    size_t show_path(BLS::Node *n);
    void loop();

};

#endif