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
        Node(const std::vector<size_t> &initial_state);
        std::shared_ptr<std::vector<size_t>> val;
        std::shared_ptr<Node> self;
        std::shared_ptr<Node> up;
        std::shared_ptr<Node> down;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> parent;
        

        void disp(const std::vector<size_t> &v);
    };
    std::queue<std::shared_ptr<Node>> search_queue;
    std::set<std::shared_ptr<Node>> all_record;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> current_node;
    void make_adjacent_nodes(const std::vector<size_t> &current_node);
    Board(const std::vector<size_t> &val);
    void disp();
    bool check_if_is_answer(const std::vector<size_t> &v);
    bool search_for_answer(std::shared_ptr<Node> cu_node);
};

#endif