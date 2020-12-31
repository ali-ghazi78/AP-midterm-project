#include <color.h>
#include <bfs.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

int BFS::loop()
{
    bool done = false;
    while (!done)
    {
        done = search_for_answer(current_node);
    }
    return final_val.size();
}
BFS::~BFS()
{
    for (int i = 0; i < all_address_to_del.size(); i++)
    {
        delete all_address_to_del[i];
        all_address_to_del[i] = nullptr;
    }
}
BFS::BFS(std::vector<int> val)
{
    desire_final_state = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    randome_or_costume = true; //true means random
    head = new Node(move(val));
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);
    all_record.insert(make_str(val));
}
size_t BFS::Node::Node_no = 0;

BFS::Node::~Node()
{
    Node::Node_no--;
    up = nullptr;
    right = nullptr;
    down = nullptr;
    left = nullptr;
    parent = nullptr;
}
BFS::Node::Node(const std::vector<int> &initial_state)
{
    val = std::make_shared<std::vector<int>>(move(initial_state));
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;
    parent = nullptr;
    Node::Node_no++;
}

void BFS::move_zero(std::vector<int> &vec1, int x, int y, int loc)
{
    std::swap(vec1[loc], vec1[x + y * 3]);
}
void BFS::make_adjacent_nodes(const std::vector<int> &current_node)
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
bool BFS::check_if_is_answer(const std::vector<int> &v)
{

    if (randome_or_costume) //true means random
        return std::is_sorted(v.begin(), v.end() - 1) && v[v.size() - 1] == 0;
    else
    {
        for (int i = 0; i < 9; i++)
        {
            if (desire_final_state[i] != v[i])
                return 0;
        }
        return 1;
    }
}

size_t BFS::show_path(BFS::Node *n)
{
    size_t steps = 0;
    while (n != nullptr)
    {
        this->final_val.push_back(*n->val);
        steps++;
        n = n->parent;
    }
    std::reverse(final_val.begin(), final_val.end());
    std::cerr << "\n\033[32;4msteps : " << steps << "\033[0m" << std::endl;
    return steps - 1;
}
bool BFS::search_for_answer(Node *cu_node)
{

    current_node = cu_node;
    make_adjacent_nodes(*(cu_node->val));
    if (cu_node != nullptr)
    {
        if (check_if_is_answer(*cu_node->val))
        {
            current_node = cu_node;
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
        search_queue.push(cu_node->up);
        all_record.insert(this->make_str(*cu_node->up->val));
        if (check_if_is_answer(*cu_node->up->val))
        {
            current_node = current_node->up;
            show_path(current_node);
            return 1;
        }
    }

    if (cu_node->down != nullptr)
    {
        search_queue.push(cu_node->down);
        all_record.insert(this->make_str(*cu_node->down->val));

        if (check_if_is_answer(*cu_node->down->val))
        {
            current_node = current_node->down;

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
            current_node = current_node->right;

            show_path(current_node);

            return 1;
        }
    }

    if (cu_node->left != nullptr)
    {

        search_queue.push(cu_node->left);
        all_record.insert(this->make_str(*cu_node->left->val));
        if (check_if_is_answer(*cu_node->left->val))
        {
            current_node = cu_node->left;
            show_path(current_node);
            return 1;
        }
    }
    if (search_queue.size() >= 1)
        search_queue.pop();

    if (search_queue.size() >= 1)
        cu_node = search_queue.front();
    else
    {
        std::cerr << "no Node reamained" << BFS::Node::Node_no << std::endl;
        return 1;
    }
    current_node = cu_node;

    return 0;
}
bool BFS::is_solvable(const std::vector<int> &v)
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
std::string BFS::make_str(const std::vector<int> &v)
{
    std::string s = "";
    for (int i = 0; i < 9; i++)
    {
        s.append(std::to_string(v[i]));
    }
    return s;
}

void BFS::disp_in_menu(const std::vector<int> &v, const std::vector<int> &v2)
{
    auto it1 = std::find(v.begin(), v.end(), 0);
    auto it2 = std::find(v2.begin(), v2.end(), 0);
    size_t i1 = it1 - v.begin();
    size_t i2 = it2 - v2.begin();

    std::cout << Color::color_red << "\t  " << std::string(7, '-') << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << Color::color_red << Color::non_italic << "\t | ";

        for (size_t j = 0; j < 3; j++)
        {
            if (i1 == i2 && i2 == i * 3 + j)
            {
                std::cout << Color::color_reset << Color::color_red_b << " " << Color::color_reset << " ";
            }
            else if (v[i * 3 + j] == -1)
            {
                std::cout << Color::color_reset << Color::color_blue_b << " " << Color::color_reset << " ";
            }
            else if (i1 == i * 3 + j)
            {
                if (j != 2 && i2 == i1 + 1)
                    std::cout << Color::color_reset << Color::color_red_b << " "
                              << " " << Color::color_reset;
                else
                    std::cout << Color::color_reset << Color::color_red_b << " " << Color::color_reset << " ";
            }
            else if (i2 == i * 3 + j)
            {
                if (j != 2 && i2 + 1 == i1)
                    std::cout << Color::color_reset << Color::color_red_b << v[i * 3 + j] << " " << Color::color_reset;
                else
                    std::cout << Color::color_reset << Color::color_red_b << v[i * 3 + j] << Color::color_reset << " ";
            }
            else
                std::cout << Color::color_blue << v[i * 3 + j] << " ";
        }
        std::cout << Color::color_red << Color::non_italic << "|";

        std::cout << std::endl;
    }
    std::cout << Color::color_red << "\t  " << std::string(7, '-') << std::endl;
}
