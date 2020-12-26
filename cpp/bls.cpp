#include <BLS.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

void BLS::loop()
{
    bool done = false;
    int c = 400000;
    while (!done && c--)
    {
        done = search_for_answer(current_node);
        disp_in_menu(*current_node->val, *current_node->val);
    }
}
BLS::BLS(std::vector<int> val)
{
    randome_or_costume = true; //true means random
    head = new Node(move(val));
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);
    all_record.insert(make_str(val));
}
size_t BLS::Node::Node_no = 0;

BLS::Node::~Node()
{
    Node::Node_no--;
    up = nullptr;
    right = nullptr;
    down = nullptr;
    left = nullptr;
    parent = nullptr;
}
BLS::Node::Node(const std::vector<int> &initial_state)
{
    val = std::make_shared<std::vector<int>>(move(initial_state));
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;
    parent = nullptr;
    Node::Node_no++;
}

void BLS::move_zero(std::vector<int> &vec1, int x, int y, int loc)
{
    std::swap(vec1[loc], vec1[x + y * 3]);
}
void BLS::make_adjacent_nodes(const std::vector<int> &current_node)
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
    bool resume = false;
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
        else
        {
            // this->current_node->up = nullptr;
            resume = true;
        }
    }
    if (y_down != -1)
    {
        std::vector<int> down = current_node;
        move_zero(down, x_down, y_down, loc);
        if (all_record.count(make_str(down)) == 0)
        {
            this->current_node->down = new Node(move(down));
            all_address_to_del.push_back(this->current_node->down);
            if (this->current_node->down != nullptr)
                this->current_node->down->parent = this->current_node;
        }
        else
        {
            // this->current_node->down = nullptr;
            resume = true;
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
        else
        {
            // this->current_node->right = nullptr;
            resume = true;
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
        else
        {
            // this->current_node->left = nullptr;
        }
    }
}

bool BLS::check_if_is_answer(const std::vector<int> &v)
{
    return std::is_sorted(v.begin(), v.end() - 1) && v[v.size() - 1] == 0;
}

size_t BLS::show_path(BLS::Node *n)
{
    size_t steps = 0;
    while (n != nullptr)
    {
        this->final_val.push_back(*n->val);
        // BLS::err_disp(*n->val);
        steps++;
        n = n->parent;
    }
    std::reverse(final_val.begin(), final_val.end());
    std::cerr << "\n\033[32;4msteps : " << steps << "\033[0m" << std::endl;
    return steps - 1;
}
bool BLS::search_for_answer(Node *cu_node)
{

    disp(*cu_node->val);
    current_node = cu_node;

    std::cout << "make adjacnet" << std::endl;

    make_adjacent_nodes(*(cu_node->val));

    std::cout << "adjacent done!" << std::endl;

    std::vector<int> s(4, 65535);
    int choose = -1;
    if (cu_node->up != nullptr)
        is_solvable(*cu_node->up->val, s[0]);
    if (cu_node->down != nullptr)
        is_solvable(*cu_node->down->val, s[1]);
    if (cu_node->right != nullptr)
        is_solvable(*cu_node->right->val, s[2]);
    if (cu_node->left != nullptr)
        is_solvable(*cu_node->left->val, s[3]);

    auto it = std::min_element(s.begin(), s.end());
    // std::cerr<<*it<<std::endl;
    if (*it != -1)
    {
        if (s[0] == *it)
            choose = 0;
        else if (s[1] == *it)
            choose = 1;
        else if (s[2] == *it)
            choose = 2;
        else if (s[3] == *it)
            choose = 3;
        // std::cerr<<choose<<std::endl;
    }

    if (cu_node != nullptr)
    {
        if (check_if_is_answer(*cu_node->val))
        {
            current_node = cu_node;
            // std::cerr << "yes khodesh" << std::endl;
            show_path(current_node);
            return 1;
        }
    }
    else
    {
        std::cerr << "current node = 0 " << std::endl;
        return 1;
    }

    choose = -1;
    if (cu_node->up != nullptr && 1)
    {
        if (all_record.count(make_str(*cu_node->up->val)) == 0)
        {
            std::cout << "up?" << std::endl;
            search_queue.push(cu_node->up);
            all_record.insert(this->make_str(*cu_node->up->val));
            choose = 0;
        }
        else
        {
            choose = -1;
        }
        
        if (check_if_is_answer(*cu_node->up->val))
        {
            // std::cerr << "yes up" << std::endl;
            current_node = current_node->up;
            show_path(current_node);

            return 1;
        }
    }
    if (cu_node->down != nullptr && choose==-1)
    {
        std::cout << "donw?" << std::endl;

        if (all_record.count(make_str(*cu_node->down->val)) == 0)
        {
            search_queue.push(cu_node->down);
            all_record.insert(this->make_str(*cu_node->down->val));
            choose = 0;
        }
        else 
            choose = -1;
        if (check_if_is_answer(*cu_node->down->val))
        {
            // std::cerr << "yes down" << std::endl;
            current_node = current_node->down;

            show_path(current_node);
            return 1;
        }
    }
     if (cu_node->right != nullptr && choose == -1)
    {
        std::cout << "right" << std::endl;
        if (all_record.count(make_str(*cu_node->right->val)) == 0)
        {
            search_queue.push(cu_node->right);
            all_record.insert(this->make_str(*cu_node->right->val));
            choose = 0;
        }
        else 
            choose = -1;
        if (check_if_is_answer(*cu_node->right->val))
        {
            // std::cout << "here?9" << std::endl;
            // std::cerr << "yes right" << std::endl;
            current_node = current_node->right;

            show_path(current_node);

            return 1;
        }
    }
    // std::cout << "here?8" << std::endl;

     if (cu_node->left != nullptr && choose==-1)
    {
        std::cout << "left" << std::endl;
        if (all_record.count(make_str(*cu_node->left->val)) == 0)
        {
            search_queue.push(cu_node->left);
            all_record.insert(this->make_str(*cu_node->left->val));
            choose = 0;
        }
        else 
            choose = -1;
        if (check_if_is_answer(*cu_node->left->val))
        {
            // std::cerr << "yes left" << std::endl;
            current_node = cu_node->left;
            show_path(current_node);
            return 1;
        }
    }
    if (search_queue.size() >= 1 && choose==-1)
        search_queue.pop();

    // std::cerr << "sizeis: " << search_queue.size() << std::endl;
    // if (BLS::Node::Node_no % 1000 == 0)
    //     std::cerr << "no of Nodes :" << BLS::Node::Node_no << std::endl;

    if (search_queue.size() >= 1)
        cu_node = search_queue.top();
    else
    {
        std::cerr << "no Node reamained" << BLS::Node::Node_no << std::endl;
        return 1;
    }
    current_node = cu_node;

    // if (search_queue.size() < 100000 && search_queue.size() != 0)
    // {
    //     search_for_answer(cu_node);
    // }
    // if (BLS::Node::Node_no % 1000 == 0)
    std::cerr << "node_no" << BLS::Node::Node_no << std::endl;

    return 0;
}
bool BLS::is_solvable(const std::vector<int> &v, int &inver)
{
    inver = 0;
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
std::string BLS::make_str(const std::vector<int> &v)
{
    std::string s = "";
    for (int i = 0; i < 9; i++)
    {
        s.append(std::to_string(v[i]));
    }
    return s;
}
void BLS::err_disp(const std::vector<int> &v)
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
#include <color.h>
void BLS::disp_in_menu(const std::vector<int> &v, const std::vector<int> &v2)
{
    auto it1 = std::find(v.begin(), v.end(), 0);
    auto it2 = std::find(v2.begin(), v2.end(), 0);
    size_t i1 = it1 - v.begin();
    size_t i2 = it2 - v2.begin();

    std::cerr << Color::color_red << "\t  " << std::string(7, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cerr << Color::color_red << Color::non_italic << "\t | ";

        for (size_t j = 0; j < 3; j++)
        {
            if (i1 == i2 && i2 == i * 3 + j)
            {
                std::cerr << Color::color_reset << Color::color_red_b << " " << Color::color_reset << " ";
            }
            else if (v[i * 3 + j] == -1)
            {
                std::cerr << Color::color_reset << Color::color_blue_b << " " << Color::color_reset << " ";
            }
            else if (i1 == i * 3 + j)
            {
                if (j != 2 && i2 == i1 + 1)
                    std::cerr << Color::color_reset << Color::color_red_b << " "
                              << " " << Color::color_reset;
                else
                    std::cerr << Color::color_reset << Color::color_red_b << " " << Color::color_reset << " ";
            }
            else if (i2 == i * 3 + j)
            {
                if (j != 2 && i2 + 1 == i1)
                    std::cerr << Color::color_reset << Color::color_red_b << v[i * 3 + j] << " " << Color::color_reset;
                else
                    std::cerr << Color::color_reset << Color::color_red_b << v[i * 3 + j] << Color::color_reset << " ";
            }
            else
                std::cerr << Color::color_blue << v[i * 3 + j] << " ";
        }
        std::cerr << Color::color_red << Color::non_italic << "|";

        std::cerr << std::endl;
    }
    std::cerr << Color::color_red << "\t  " << std::string(7, '-') << std::endl;
}

void BLS::Node::disp(const std::vector<int> &v)
{
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            // std::cout << v[i * 3 + j] << "\t";
        }
        // std::cout << std::endl;
    }
    // std::cout << std::string(20, '-') << "\033[0m" << std::endl;
}
void BLS::disp()
{
    // std::cout << "\033[2;33m" << std::string(12, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            // std::cout << (*current_node->val)[i * 3 + j] << "\t";
        }
        // std::cout << std::endl;
    }
    // std::cout << std::string(12, '-') << "\033[0m" << std::endl;
}
void BLS::disp(std::vector<int> v)
{
    // std::cout << "\033[2;35m" << std::string(12, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            // std::cout << v[i * 3 + j] << "\t";
        }
        // std::cout << std::endl;
    }
    // std::cout << std::string(12, '-') << "\033[0m" << std::endl;
}
