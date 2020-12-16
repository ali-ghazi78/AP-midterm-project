#include <board.h>
#include <algorithm>
#include <vector>
#include <string>

Board::Board(const std::vector<size_t> &val)
{
    head = std::make_shared<Node>(val);
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);
    // head->disp(*(head->val));
}
Board::Node::Node(const std::vector<size_t> &initial_state)
{
    // disp(initial_state);
    val = std::make_shared<std::vector<size_t>>(initial_state);
    this->self = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->up = nullptr;
    this->down = nullptr;
    this->parent = nullptr;
}
void Board::make_adjacent_nodes(const std::vector<size_t> &current_node)
{
    auto p = std::find(current_node.begin(), current_node.end(), 0);
    int loc = p - current_node.begin();
    int x = p - current_node.begin();
    int y = x / 3;
    x = x % 3;

    int y_down = (y + 1 <= 2) ? (y + 1) : (-1);
    int x_down = x;
    int x_right = (x + 1 <= 2) ? (x + 1) : (-1);
    int y_right = y;
    int y_up = (y - 1 >= 0) ? (y - 1) : (-1);
    int x_up = x;
    int x_left = (x - 1 >= 0) ? (x - 1) : (-1);
    int y_left = y;
    std::vector<size_t> down = current_node;
    std::vector<size_t> up = current_node;
    std::vector<size_t> right = current_node;
    std::vector<size_t> left = current_node;
    auto la = [=](auto &vec1, int x, int y) {
        std::swap(vec1[loc], vec1[x + y * 3]);
    };
    if (y_down != -1)
    {
        la(down, x_down, y_down);
    }
    if (y_up != -1)
    {
        la(up, x_up, y_up);
    }
    if (x_right != -1)
    {
        la(right, x_right, y_right);
    }
    if (x_left != -1)
    {
        la(left, x_left, y_left);
    }
    auto set_parent = [&](std::shared_ptr<Node> n){
        if(n!=nullptr)
            n->parent = this->current_node;  
    };
    this->current_node->right = (x_right != -1) ? std::make_shared<Node>(right) : nullptr;
    this->current_node->left = (x_left != -1) ? std::make_shared<Node>(left) : nullptr;
    this->current_node->up = (y_up != -1) ? std::make_shared<Node>(up) : nullptr;
    this->current_node->down = (y_down != -1) ? std::make_shared<Node>(down) : nullptr;

    set_parent(this->current_node->right);
    set_parent(this->current_node->left);
    set_parent(this->current_node->up);
    set_parent(this->current_node->down);
    

}
void Board::Node::disp(const std::vector<size_t> &v)
{
    std::cout << "\033[2;33m" << std::string(20, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            std::cout << v[i * 3 + j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::string(20, '-') << "\033[0m" << std::endl;
}
void Board::disp()
{
    std::cout << "\033[2;33m" << std::string(12, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            std::cout << (*current_node->val)[i * 3 + j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::string(12, '-') << "\033[0m" << std::endl;
}
bool Board::check_if_is_answer(const std::vector<size_t> &v)
{
    return std::is_sorted(v.begin(), v.end() - 1) && v[v.size() - 1] == 0;
}
bool Board::search_for_answer(std::shared_ptr<Node> cu_node)
{
    auto show_path = [](std::shared_ptr<Node> n){
        while(n!=nullptr)
        {
            n->disp(*n->val);
            n = n->parent;
        }
        
    };
    if (search_queue.size() >= 1)
        search_queue.pop();

    current_node = cu_node;
    make_adjacent_nodes(*(cu_node->val));
    if (cu_node != nullptr)
    {
        if (check_if_is_answer(*cu_node->val))
        {
            current_node = cu_node;

            std::cout << "yes"
                      << "khodesh" << std::endl;
            disp();
            show_path(current_node);
            return 0;
        }
    }
    if (cu_node->up != nullptr)
    {
        if (all_record.contains(cu_node->up) == false)
        {
            all_record.insert(cu_node->up);
            search_queue.push(cu_node->up);
        }
        if (check_if_is_answer(*cu_node->up->val))
        {
            current_node = cu_node->up;

            std::cout << "yes"
                      << "up";
            disp();
            show_path(current_node);

            return 0;
        }
    }
    if (cu_node->down != nullptr)
    {
        if (all_record.contains(cu_node->down) == false)
        {
            all_record.insert(cu_node->down);
            search_queue.push(cu_node->down);
        }
        if (check_if_is_answer(*cu_node->down->val))
        {
            current_node = cu_node->down;

            std::cout << "yes"
                      << "down";

            disp();
            show_path(current_node);

            return 0;
        }
    }
    if (cu_node->right != nullptr)
    {

        if (all_record.contains(cu_node->right) == false)
        {
            all_record.insert(cu_node->right);
            search_queue.push(cu_node->right);
        }
        if (check_if_is_answer(*cu_node->right->val))
        {
            current_node = cu_node->right;

            std::cout << "yes"
                      << "right";
            disp();
            show_path(current_node);

            return 0;
        }
    }
    if (cu_node->left != nullptr)
    {
        if (all_record.contains(cu_node->left) == false)
        {
            all_record.insert(cu_node->left);
            search_queue.push(cu_node->left);
        }

        if (check_if_is_answer(*cu_node->left->val))
        {
            current_node = cu_node->left;

            std::cout << "yes"
                      << "left";
            disp();
            show_path(current_node);

            return 0;
        }
    }
    std::cout << search_queue.size() << std::endl;
    cu_node = search_queue.front();
    head = cu_node;
    if (search_queue.size() < 9000)
        search_for_answer(cu_node);
    return 0;
}
