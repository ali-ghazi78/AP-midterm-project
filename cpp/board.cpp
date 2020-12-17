#include <board.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

Board::Board(std::vector<int> val)
{
    head = new Node(move(val));
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);
    all_record.insert(make_str(val));

    // head->disp(*(head->val));
}
size_t Board::Node::Node_no = 0;

Board::Node::~Node()
{
    if (Node::Node_no % 1000 == 0)
        std::cerr << "Node destructor:" << Node::Node_no << std::endl;

    Node::Node_no--;
    up = nullptr;
    right = nullptr;
    down = nullptr;
    left = nullptr;
    parent = nullptr;
}
Board::Node::Node(const std::vector<int> &initial_state)
{
    val = std::make_shared<std::vector<int>>(move(initial_state));
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;
    parent = nullptr;
    Node::Node_no++;
}

void Board::move_zero(std::vector<int> &vec1, int x, int y, int loc)
{
    std::cout << "h34" << std::endl;
    std::cout << x << y << loc << std::endl;

    std::swap(vec1[loc], vec1[x + y * 3]);
    std::cout << "h35" << std::endl;
}
void Board::make_adjacent_nodes(const std::vector<int> &current_node)
{
    std::cout << "h1" << std::endl;
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

    // std::cout << "h2" << std::endl;

    if (y_down != -1)
    {
        std::cout << (current_node[0]) << std::endl;
        std::vector<int> down = current_node;
        move_zero(down, x_down, y_down, loc);
        if (all_record.count(make_str(down)) == 0)
        {
            this->current_node->down = new Node(move(down));
            all_address_to_del.push_back(this->current_node->down);
            if (this->current_node->down != nullptr)
                this->current_node->down->parent = this->current_node;
        }
    }
    if (y_up != -1)
    {
        std::vector<int> up = current_node;
        move_zero(up, x_up, y_up, loc);
        if (all_record.count(make_str(up)) == 0)
        {
            this->current_node->up = new Node(move(up));
            all_address_to_del.push_back(this->current_node->up);
            if (this->current_node->up != nullptr)
                this->current_node->up->parent = this->current_node;
        }
    }
    if (x_right != -1)
    {
        std::vector<int> right = current_node;
        move_zero(right, x_right, y_right, loc);
        if (all_record.count(make_str(right)) == 0)
        {
            this->current_node->right = new Node(move(right));
            all_address_to_del.push_back(this->current_node->right);
            if (this->current_node->right != nullptr)
                this->current_node->right->parent = this->current_node;
        }
    }
    if (x_left != -1)
    {
        std::vector<int> left = current_node;
        move_zero(left, x_left, y_left, loc);
        if (all_record.count(make_str(left)) == 0)
        {
            this->current_node->left = new Node(move(left));
            all_address_to_del.push_back(this->current_node->left);
            if (this->current_node->left != nullptr)
                this->current_node->left->parent = this->current_node;
        }
    }
}
void Board::Node::disp(const std::vector<int> &v)
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
void Board::disp(std::vector<int> v)
{
    std::cout << "\033[2;35m" << std::string(12, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            std::cout << v[i * 3 + j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::string(12, '-') << "\033[0m" << std::endl;
}

bool Board::check_if_is_answer(const std::vector<int> &v)
{
    return std::is_sorted(v.begin(), v.end() - 1) && v[v.size() - 1] == 0;
}

auto show_path = [](Board::Node *n) {
    size_t steps = 0;
    while (n != nullptr)
    {
        // Board::err_disp(*n->val);
        steps++;
        n = n->parent;
    }
    std::cerr << "\n\033[32msteps : " << steps << "\033[0m" << std::endl;
    return steps;
};
bool Board::search_for_answer(Node *cu_node)
{

    disp(*cu_node->val);
    current_node = cu_node;

    std::cout << "here?3" << std::endl;

    make_adjacent_nodes(*(cu_node->val));

    std::cout << "here?3 out" << std::endl;

    if (cu_node != nullptr)
    {
        if (check_if_is_answer(*cu_node->val))
        {
            current_node = cu_node;
            std::cerr << "yes khodesh" << std::endl;
            show_path(current_node);
            return 1;
        }
    }
    else
    {
        std::cerr << "current node = 0 " << std::endl;
        return 1;
    }

    if (cu_node->up != nullptr)
    {
        std::cout << "here?909" << std::endl;
        search_queue.push(cu_node->up);
        all_record.insert(this->make_str(*cu_node->up->val));
        if (check_if_is_answer(*cu_node->up->val))
        {
            std::cerr << "yes up" << std::endl;
            current_node =  current_node->up;
            show_path(current_node);

            return 1;
        }
    }

    if (cu_node->down != nullptr)
    {
        std::cout << "here?66" << std::endl;

        search_queue.push(cu_node->down);
        all_record.insert(this->make_str(*cu_node->down->val));

        if (check_if_is_answer(*cu_node->down->val))
        {
            std::cerr << "yes down" << std::endl;
            current_node =  current_node->down;
            
            show_path(current_node);
            return 1;
        }
    }
    if (cu_node->right != nullptr)
    {
        search_queue.push(cu_node->right);
        all_record.insert(this->make_str(*cu_node->right->val));
        if (check_if_is_answer(*cu_node->right->val))
        {
            std::cout << "here?9" << std::endl;
            std::cerr << "yes right" << std::endl;
            current_node =  current_node->right;

            show_path(current_node);

            return 1;
        }
    }
    // std::cout << "here?8" << std::endl;

    if (cu_node->left != nullptr)
    {

        search_queue.push(cu_node->left);
        all_record.insert(this->make_str(*cu_node->left->val));
        if (check_if_is_answer(*cu_node->left->val))
        {
            std::cerr << "yes left" << std::endl;
            current_node = cu_node->left;
            show_path(current_node);
            return 1;
        }
    }
    if (search_queue.size() >= 1)
        search_queue.pop();

    // std::cerr << "sizeis: " << search_queue.size() << std::endl;
    // if (Board::Node::Node_no % 1000 == 0)
    //     std::cerr << "no of Nodes :" << Board::Node::Node_no << std::endl;

    if (search_queue.size() >= 1)
        cu_node = search_queue.front();
    else
    {
        std::cerr << "no Node reamained" << Board::Node::Node_no << std::endl;
        return 1;
    }
    current_node = cu_node;

    // if (search_queue.size() < 100000 && search_queue.size() != 0)
    // {
    //     search_for_answer(cu_node);
    // }
    // if (Board::Node::Node_no % 1000 == 0)
        // std::cerr << "Done" << Board::Node::Node_no << std::endl;
    
    return 0;
}
bool Board::is_solvable(const std::vector<int> &v)
{
    size_t inver = 0;
    for (int i = 0; i < v.size(); i++)
    {
        for (size_t j = i + 1; j < v.size(); j++)
        {
            if (v.at(i) > v.at(j) && v[i] && v[j])
            {
                inver++;
            }
        }
    }
    if (int(sqrt(v.size())) % 2 == 1)
        return (inver % 2 + 1) % 2;
    return inver % 2;
}
std::string Board::make_str(const std::vector<int> &v)
{
    std::string s = "";
    for (int i = 0; i < 9; i++)
    {
        s.append(std::to_string(v[i]));
    }
    return s;
}
void Board::err_disp(const std::vector<int> &v)
{
    std::cerr << "\033[2;35m" << std::string(12, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            std::cerr << v[i * 3 + j] << "\t";
        }
        std::cerr << std::endl;
    }
    std::cerr << std::string(12, '-') << "\033[0m" << std::endl;
}