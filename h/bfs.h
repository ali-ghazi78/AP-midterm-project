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
        static void disp(const std::vector<int> &v);

    public:
        Node(const std::vector<int> & initial_state);
        std::shared_ptr<std::vector<int>> val;
        std::shared_ptr<Node> up;
        std::shared_ptr<Node> down;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> parent;
    };
    std::queue<std::shared_ptr<Node>> search_queue;
    std::set<std::string> all_record;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> current_node;
    void make_adjacent_nodes(const std::vector<int> &current_node);
    BFS(std::vector<int> val);
    BFS()=default;
    void disp();
    void disp( std::vector<int> v);

    bool check_if_is_answer(const std::vector<int> &v);
    bool search_for_answer(std::shared_ptr<Node> cu_node);
    bool is_solvable(const std::vector<int> &v);
    std::string make_str(const std::vector<int> &v);
};

#endif