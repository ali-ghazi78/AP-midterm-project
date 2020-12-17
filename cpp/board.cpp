#include <board.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

Board::Board(std::vector<int> val)
{
    head = std::make_shared<Node>(move(val));
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);
    // head->disp(*(head->val));
}
Board::Node::Node(const std::vector<int> &initial_state)
{
    // disp(initial_state);
    // std::cout << "here is probemic?" << std::endl;
    // std::shared_ptr<std::vector<int>> fake_test;
    // disp(initial_state);
    // fake_test = std::make_shared<std::vector<int>>(move(initial_state));
    std::cout << "here is probemic029" << std::endl;
    std::cout << "val1 loc" << val << std::endl;
    val = std::make_shared<std::vector<int>>();
    std::cout << "val2 loc" << val << std::endl;
    *val = move(initial_state);
    std::cout << "val3 loc" << val << std::endl;
    std::cout << "here is probemic2?" << std::endl;
    // this->self = nullptr;
    // this->right = nullptr;
    // this->left = nullptr;
    // this->up = nullptr;
    // this->down = nullptr;
    // this->parent = nullptr;
    std::cout << "val4 loc" << val << std::endl;
}
auto set_parent = [](std::shared_ptr<Board::Node> n, std::shared_ptr<Board::Node> b) {
    if (n != nullptr)
        n->parent = b;
    else
    {
        std::cout << "fucckckkk no memeory is available " << std::endl;
    }
};
auto la = [](std::vector<int> &vec1, int x, int y, int loc) {
    std::cout << "h34" << std::endl;
    std::cout << x << y << loc << std::endl;

    std::swap(vec1[loc], vec1[x + y * 3]);
    std::cout << "h35" << std::endl;
};
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
        la(down, x_down, y_down, loc);
        this->current_node->down = std::make_shared<Node>(move(down));
        set_parent(this->current_node->down, this->current_node);
    }
    if (y_up != -1)
    {
        std::vector<int> up = current_node;
        la(up, x_up, y_up, loc);
        this->current_node->up = std::make_shared<Node>(move(up));
        set_parent(this->current_node->up, this->current_node);
    }
    if (x_right != -1)
    {
        std::vector<int> right = current_node;
        la(right, x_right, y_right, loc);
        this->current_node->right = std::make_shared<Node>(move(right));
        set_parent(this->current_node->right, this->current_node);
    }
    if (x_left != -1)
    {
        std::vector<int> left = current_node;
        la(left, x_left, y_left, loc);
        this->current_node->left = std::make_shared<Node>(move(left));
        set_parent(this->current_node->left, this->current_node);
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

auto show_path = [](std::shared_ptr<Board::Node> n) {
    size_t steps = 0;
    while (n != nullptr)
    {
        steps++;
        n = n->parent;
    }
    std::cout << "\n\033[32msteps : " << steps << "\033[0m" << std::endl;
    return steps;
};
bool Board::search_for_answer(std::shared_ptr<Node> cu_node)
{

    //10095
    // std::cout<<"\n\033[32msteps : " <<sizeof( *search_queue.front()) <<"\033[0m"<<std::endl;
    // std::cout << "here?1" << std::endl;

    // std::cout << "here?2" << std::endl;
    disp(*cu_node->val);

    current_node = cu_node;
    std::cout << "here?3" << std::endl;

    make_adjacent_nodes(*(cu_node->val));
    // std::cout << "here?4" << std::endl;
    std::cout << "here?3 out" << std::endl;

    if (cu_node != nullptr)
    {
        if (check_if_is_answer(*cu_node->val))
        {
            // std::cout << "here?9" << std::endl;

            current_node = cu_node;

            std::cout << "yes"
                      << "khodesh" << std::endl;
            // disp();
            show_path(current_node);
            return 0;
        }
    }
    // std::cout << "here?5" << std::endl;

    if (cu_node->up != nullptr)
    {
        // std::cout << "here?55" << std::endl;
        if (!all_record.count(this->make_str(*cu_node->up->val)))
        {
            std::cout << "here?909" << std::endl;

            search_queue.push(cu_node->up);
            all_record.insert(this->make_str(*cu_node->up->val));
        }
        else
        {
            // std::cout << "here?9" << std::endl;

            std::cout << "up already contain" << std::endl;
            // current_node->up->parent = nullptr;
            // current_node->up->down = nullptr;
            // current_node->up->right = nullptr;
            // current_node->up->left = nullptr;
            // current_node->up->up = nullptr;
            // current_node->up->val = nullptr;
            // cu_node->up = nullptr;
        }
        if (cu_node->up != nullptr)
            if (check_if_is_answer(*cu_node->up->val))
            {
                std::cout << "here?09" << std::endl;

                // current_node = cu_node->up;

                std::cout << "yes"
                          << "up";
                // disp();
                show_path(current_node);

                return 0;
            }
    }
    // std::cout << "here?6" << std::endl;

    if (cu_node->down != nullptr)
    {
        std::cout << "here?66" << std::endl;

        if (!all_record.count(this->make_str(*cu_node->down->val)))
        {
            std::cout << "here?9" << std::endl;

            search_queue.push(cu_node->down);
            all_record.insert(this->make_str(*cu_node->down->val));
        }
        else
        {
            std::cout << "here?9" << std::endl;

            // current_node->down->up = nullptr;
            // current_node->down->parent = nullptr;
            // current_node->down->down = nullptr;
            // current_node->down->right = nullptr;
            // current_node->down->left = nullptr;
            // current_node->down->val = nullptr;

            // current_node->down->parent = nullptr;
            // cu_node->down = nullptr;
        }
        std::cout << "here?67" << std::endl;

        if (cu_node->down != nullptr)
            if (check_if_is_answer(*cu_node->down->val))
            {

                // current_node = cu_node->down;

                std::cout << "yes"
                          << "down";

                // disp();
                show_path(current_node);

                return 0;
            }
    }
    // std::cout << "here?7" << std::endl;

    if (cu_node->right != nullptr)
    {
        std::cout << "here?77" << std::endl;

        if (!all_record.count(this->make_str(*cu_node->right->val)))
        {

            // std::cout << "here?9" << std::endl;
            search_queue.push(cu_node->right);
            all_record.insert(this->make_str(*cu_node->right->val));
        }
        else
        {
            // std::cout << "here?9" << std::endl;

            // current_node->right->up = nullptr;
            // current_node->right->parent = nullptr;
            // current_node->right->down = nullptr;
            // current_node->right->right = nullptr;
            // current_node->right->left = nullptr;
            // current_node->right->val = nullptr;

            // current_node->right->parent = nullptr;
            // cu_node->right = nullptr;
        }
        if (cu_node->right != nullptr)
            if (check_if_is_answer(*cu_node->right->val))
            {
                std::cout << "here?9" << std::endl;

                // current_node = cu_node->right;

                std::cout << "yes"
                          << "right";
                // disp();
                show_path(current_node);

                return 0;
            }
    }
    // std::cout << "here?8" << std::endl;

    if (cu_node->left != nullptr)
    {
        // std::cout << "here?88" << std::endl;
        if (!all_record.count(this->make_str(*cu_node->left->val)))
        {
            // std::cout << "here?9" << std::endl;

            search_queue.push(cu_node->left);
            all_record.insert(this->make_str(*cu_node->left->val));
        }
        else
        {
            // std::cout << "here?9" << std::endl;
            // current_node->left->up = nullptr;
            // current_node->left->parent = nullptr;
            // current_node->left->down = nullptr;
            // current_node->left->right = nullptr;
            // current_node->left->left = nullptr;
            // current_node->left->val = nullptr;

            // current_node->left->parent = nullptr;
            // cu_node->left = nullptr;
        }
        if (cu_node->left != nullptr)
            if (check_if_is_answer(*cu_node->left->val))
            {
                std::cout << "here?9" << std::endl;

                // current_node = cu_node->left;

                std::cout << "yes"
                          << "left";
                // disp();
                show_path(current_node);

                return 0;
            }
    }
    if (search_queue.size() >= 1)
        search_queue.pop();

    std::cout << "here?9" << std::endl;
    std::cout << "sizeis: " << search_queue.size() << std::endl;
    if (search_queue.size() >= 1)
        cu_node = search_queue.front();
    else
    {
        return 0;
    }

    // head = cu_node;
    // std::cout << "here?10" << std::endl;
    if (search_queue.size() < 8000)
    {
        search_for_answer(cu_node);
    }
    // std::cout << "here?11" << std::endl;
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
    std::cout << "start str making" << std::endl;

    if (v.size() == 0)
    {
        std::cout << "real funked up?" << std::endl;
        return std::string("000000000");
    }
    std::string s = "";
    std::cout<<"size of vecotr:"<<v.size()<<std::endl;
    disp(v);
    for (int i = 0; i < 9; i++)
    {
        std::cout<<"val of vec"<<i<<":"<<v[i]<<std::endl;
        s.append(std::to_string(v[i]));
    }

    std::cout << "done str making" << std::endl;
    return s;
}
