#ifndef __BFS__
#define __BFS__
#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <set>

class BFS
{
public:
    class Node
    {
        
    public:
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
    std::vector<int >desire_final_state;
    BFS(std::vector<int> val);
    BFS()=default;
    std::queue<Node *> search_queue;
    std::set<std::string> all_record;
    std::vector<Node *> all_address_to_del;
    std::vector<std::vector<int>> final_val;
    Node *head;
    Node *current_node;
    bool randome_or_costume ;
    void make_adjacent_nodes(const std::vector<int> &current_node);
    void move_zero(std::vector<int> &vec1, int x, int y, int loc);
    bool check_if_is_answer(const std::vector<int> &v);
    bool search_for_answer(Node*  cu_node);
    bool is_solvable(const std::vector<int> &v);
    void disp_in_menu(const std::vector<int> &v,const std::vector<int> &v2);
    std::string make_str(const std::vector<int> &v);
    size_t show_path(BFS::Node *n);
    int loop();

};

#endif