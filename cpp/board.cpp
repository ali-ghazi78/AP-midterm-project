#include <board.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

Board::Board(const std::vector<int> &val)
{
    head = std::unique_ptr<Node>(val);
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);
    // head->disp(*(head->val));
}
Board::Node::Node(const std::vector<int> &initial_state)
{
    // disp(initial_state);
    val = std::make_unique<std::vector<int>>(initial_state);
    this->self = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->up = nullptr;
    this->down = nullptr;
    this->parent = nullptr;
}
auto set_parent = [](std::shared_ptr<Board::Node> n, Board *b) {
    if (n != nullptr)
        n->parent = b->current_node;
};
auto la = [](auto &vec1, int x, int y, int loc) {
    std::swap(vec1[loc], vec1[x + y * 3]);
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

    if (y_down != -1)
    {
        // std::cout<<"h_down"<<std::endl;

        std::vector<int> down = current_node;
        // std::cout<<"h_down1"<<std::endl;

        la(down, x_down, y_down, loc);
        std::cout << "h_down2" << std::endl;
        this->current_node->down = (y_down != -1) ? std::make_shared<Node>(down) : nullptr;
        std::cout << "h_down3" << std::endl;
        set_parent(this->current_node->down, this);
        // std::cout<<"h_down4"<<std::endl;
    }
    if (y_up != -1)
    {
        // std::cout<<"h_up"<<std::endl;
        std::vector<int> up = current_node;
        // std::cout<<"h_up2"<<std::endl;
        la(up, x_up, y_up, loc);
        std::cout << "h_up3" << std::endl;
        this->current_node->up = (y_up != -1) ? std::make_shared<Node>(up) : nullptr;
        std::cout << "h_up4" << std::endl;
        set_parent(this->current_node->up, this);
        // std::cout<<"h_up5"<<std::endl;
    }
    if (x_right != -1)
    {
        // std::cout<<"h_right1"<<std::endl;
        std::vector<int> right = current_node;
        // std::cout<<"h_right2"<<std::endl;
        la(right, x_right, y_right, loc);
        std::cout << "h_right3" << std::endl;
        this->current_node->right = (x_right != -1) ? std::make_shared<Node>(right) : nullptr;
        std::cout << "h_right4" << std::endl;
        set_parent(this->current_node->right, this);
        // std::cout<<"h_right5"<<std::endl;
    }
    if (x_left != -1)
    {
        // std::cout<<"h_left"<<std::endl;
        std::vector<int> left = current_node;
        // std::cout<<"h_left2"<<std::endl;
        la(left, x_left, y_left, loc);
        std::cout << "h_left3" << std::endl;
        this->current_node->left = (x_left != -1) ? std::make_shared<Node>(left) : nullptr;
        std::cout << "h_left4" << std::endl;
        set_parent(this->current_node->left, this);
        // std::cout<<"h_left5"<<std::endl;
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
void Board::disp(const std::vector<int> &v)
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
    // std::cout<<"here?1"<<std::endl;

    std::cout << "here?2" << std::endl;

    if (search_queue.size() >= 1)
        search_queue.pop();

    current_node = cu_node;
    std::cout << "here?3" << std::endl;

    make_adjacent_nodes(*(cu_node->val));
    std::cout << "here?4" << std::endl;

    if (cu_node != nullptr)
    {
        if (check_if_is_answer(*cu_node->val))
        {
            std::cout << "here?9" << std::endl;

            current_node = cu_node;

            std::cout << "yes"
                      << "khodesh" << std::endl;
            // disp();
            show_path(current_node);
            return 0;
        }
    }
    std::cout << "here?5" << std::endl;

    if (cu_node->up != nullptr)
    {
        std::cout << "here?55" << std::endl;
        if (all_record.contains(this->make_str(*cu_node->up->val)) == false)
        {
            std::cout << "here?9" << std::endl;

            search_queue.push(cu_node->up);
            all_record.insert(this->make_str(*cu_node->up->val));
        }
        else
        {
            std::cout << "here?9" << std::endl;

            // std::cout<<"already contain"<<std::endl;
            // current_node->up->parent = nullptr;
            cu_node->up = nullptr;
        }
        if (cu_node->up != nullptr)
            if (check_if_is_answer(*cu_node->up->val))
            {
                std::cout << "here?9" << std::endl;

                current_node = cu_node->up;

                std::cout << "yes"
                          << "up";
                // disp();
                show_path(current_node);

                return 0;
            }
    }
    std::cout << "here?6" << std::endl;

    if (cu_node->down != nullptr)
    {
        std::cout << "here?66" << std::endl;

        if (all_record.contains(this->make_str(*cu_node->down->val)) == false)
        {
            std::cout << "here?9" << std::endl;

            search_queue.push(cu_node->down);
            all_record.insert(this->make_str(*cu_node->down->val));
        }
        else
        {
            std::cout << "here?9" << std::endl;

            // current_node->down->parent = nullptr;
            cu_node->down = nullptr;
        }
        if (cu_node->down != nullptr)
            if (check_if_is_answer(*cu_node->down->val))
            {
                std::cout << "here?9" << std::endl;

                current_node = cu_node->down;

                std::cout << "yes"
                          << "down";

                // disp();
                show_path(current_node);

                return 0;
            }
    }
    std::cout << "here?7" << std::endl;

    if (cu_node->right != nullptr)
    {
        std::cout << "here?77" << std::endl;

        if (all_record.contains(this->make_str(*cu_node->right->val)) == false)
        {

            std::cout << "here?9" << std::endl;
            search_queue.push(cu_node->right);
            all_record.insert(this->make_str(*cu_node->right->val));
        }
        else
        {
            std::cout << "here?9" << std::endl;

            // current_node->right->parent = nullptr;
            cu_node->right = nullptr;
        }
        if (cu_node->right != nullptr)
            if (check_if_is_answer(*cu_node->right->val))
            {
                std::cout << "here?9" << std::endl;

                current_node = cu_node->right;

                std::cout << "yes"
                          << "right";
                // disp();
                show_path(current_node);

                return 0;
            }
    }
    std::cout << "here?8" << std::endl;

    if (cu_node->left != nullptr)
    {
        std::cout << "here?88" << std::endl;
        if (all_record.contains(this->make_str(*cu_node->left->val)) == false)
        {
            std::cout << "here?9" << std::endl;

            search_queue.push(cu_node->left);
            all_record.insert(this->make_str(*cu_node->left->val));
        }
        else
        {
            std::cout << "here?9" << std::endl;

            // current_node->left->parent = nullptr;
            cu_node->left = nullptr;
        }
        if (cu_node->left != nullptr)
            if (check_if_is_answer(*cu_node->left->val))
            {
                std::cout << "here?9" << std::endl;

                current_node = cu_node->left;

                std::cout << "yes"
                          << "left";
                // disp();
                show_path(current_node);

                return 0;
            }
    }
    std::cout << "here?9" << std::endl;
    std::cout << search_queue.size() << std::endl;
    cu_node = search_queue.front();
    // head = cu_node;
    // std::cout<<"here?10"<<std::endl;
    if (search_queue.size() < 180000)
    {
        search_for_answer(cu_node);
    }
    // std::cout<<"here?11"<<std::endl;
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
    std::string s;
    for (int i = 0; i < 9; i++)
    {
        s += std::to_string(v[i]);
    }
    return s;
}
