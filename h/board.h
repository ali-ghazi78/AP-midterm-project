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
        static void disp(const std::vector<int> &v);

    public:
        Node(const std::vector<int> &initial_state);
        std::unique_ptr<std::vector<int>> val;
        std::unique_ptr<Node> self;
        std::unique_ptr<Node> up;
        std::unique_ptr<Node> down;
        std::unique_ptr<Node> right;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> parent;
    };
    std::queue<std::shared_ptr<Node>> search_queue;
    std::set<std::string> all_record;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> current_node;
    void make_adjacent_nodes(const std::vector<int> &current_node);
    Board(const std::vector<int> &val);
    void disp();
    void disp(const std::vector<int> &v);

    bool check_if_is_answer(const std::vector<int> &v);
    bool search_for_answer(std::shared_ptr<Node> cu_node);
    bool is_solvable(const std::vector<int> &v);
    std::string make_str(const std::vector<int> &v);
};

#endif