#include <BLS.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <regex>
#include <string>
#include <color.h>
bool BLS::loop()
{
    int done = 0;
    int c = 1000;
    while (done == 0 )
    {
    
        done = search_for_answer(current_node);
        // disp_in_menu(*current_node->val, *current_node->val);
        // std::cerr << make_str(current_node) << "^" <<current_node->number_of_parent<< std::endl
        //   << std::string(20, '-') << std::endl;
        // ;
    }
    // for(int i=0; i<all_record.size();i++)
    // {
    //     std::cerr<<all_record[i]<<" "<<all_grand_child[i]<<std::endl;
    // }

    return done % 2; //2 means not found also 0
}
BLS::BLS(std::vector<int> val)
{
    max_depth = 10;
    randome_or_costume = true; //true means random
    head = new Node(move(val));
    current_node = head;
    head->parent = nullptr;
    search_queue.push(head);

    all_grand_child.push_back(head->number_of_parent);
    std::string s = make_str(current_node);
    all_record.insert(s);
    all_map.insert(std::pair<std::string,int>(s,all_grand_child.back())) ;

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
    number_of_parent = 0;
}
void BLS::Node::set_parent_number()
{
    Node *n = this;
    number_of_parent = n->parent->number_of_parent;
    number_of_parent++;
}
void BLS::move_zero(std::vector<int> &vec1, int x, int y, int loc)
{
    std::swap(vec1[loc], vec1[x + y * 3]);
}
void BLS::make_adjacent_nodes(const std::vector<int> &current_node)
{
    this->current_node->up = nullptr;
    this->current_node->down = nullptr;
    this->current_node->right = nullptr;
    this->current_node->left = nullptr;

    // std::cout << "make adj" << std::endl;
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
    std::vector<int> up = current_node;
    std::vector<int> down = current_node;
    std::vector<int> right = current_node;
    std::vector<int> left = current_node;

    if (y_up != -1)
    {
        move_zero(up, x_up, y_up, loc);
    }
    if (y_down != -1)
    {
        move_zero(down, x_down, y_down, loc);
    }
    if (y_right != -1)
    {
        move_zero(right, x_right, y_right, loc);
    }
    if (y_left != -1)
    {
        move_zero(left, x_left, y_left, loc);
    }

    if (y_up != -1 && my_find(make_str(this->current_node, up)) == 0)
    {

        this->current_node->up = new Node(move(up));
        all_address_to_del.push_back(this->current_node->up);
        if (this->current_node->up != nullptr)
        {
            this->current_node->up->parent = this->current_node;
            this->current_node->up->set_parent_number();
        }
    }
    else if (y_down != -1 && my_find(make_str(this->current_node, down)) == 0)
    {
        this->current_node->down = new Node(move(down));
        all_address_to_del.push_back(this->current_node->down);
        if (this->current_node->down != nullptr)
        {
            this->current_node->down->parent = this->current_node;
            this->current_node->down->set_parent_number();
        }
    }
    else if (x_right != -1 && (my_find(make_str(this->current_node, right)) == 0))
    {
        this->current_node->right = new Node(move(right));
        all_address_to_del.push_back(this->current_node->right);
        if (this->current_node->right != nullptr)
        {
            this->current_node->right->parent = this->current_node;
            this->current_node->right->set_parent_number();
        }
    }
    else if (x_left != -1 && (my_find(make_str(this->current_node, left)) == 0))
    {

        this->current_node->left = new Node(move(left));
        all_address_to_del.push_back(this->current_node->left);
        if (this->current_node->left != nullptr)
        {
            this->current_node->left->parent = this->current_node;
            this->current_node->left->set_parent_number();
        }
    }
    // std::cout << "make adj done " << std::endl;
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
int BLS::search_for_answer(Node *cu_node)
{

    disp(*cu_node->val);
    current_node = cu_node;

    // std::cout << "search for answer start " << std::endl;

    make_adjacent_nodes(*(cu_node->val));

    // std::cout << "adjacent done!" << std::endl;

    int choose = -1;
    if (cu_node->up != nullptr)
    {

        if (my_find(make_str(cu_node->up)) == 0)
        {
            // disp_in_menu(*cu_node->up->val, *cu_node->val);
            std::cout << "up?" << std::endl;
            search_queue.push(cu_node->up);
            all_grand_child.push_back(cu_node->number_of_parent + 1);
            all_record.insert(this->make_str(cu_node->up));
            all_map.insert(std::pair<std::string,int>(this->make_str(cu_node->up),all_grand_child.back())) ;

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
    else if (cu_node->down != nullptr && choose == -1)
    {
        // std::cout << "down?" << std::endl;

        if (my_find(make_str(cu_node->down)) == 0)
        {
            // disp_in_menu(*cu_node->down->val, *cu_node->val);
            search_queue.push(cu_node->down);
            all_grand_child.push_back(cu_node->number_of_parent + 1);
            all_record.insert(this->make_str(cu_node->down));
            all_map.insert(std::pair<std::string,int>(this->make_str(cu_node->down),all_grand_child.back())) ;

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
    else if (cu_node->right != nullptr && choose == -1)
    {
        // std::cout << "right" << std::endl;
        if (my_find(make_str(cu_node->right)) == 0)
        {
            // disp_in_menu(*cu_node->right->val, *cu_node->val);
            search_queue.push(cu_node->right);
            all_grand_child.push_back(cu_node->number_of_parent + 1);
            all_record.insert(this->make_str(cu_node->right));
            all_map.insert(std::pair<std::string,int>(this->make_str(cu_node->right),all_grand_child.back())) ;

            choose = 0;
        }
        else
        {
            choose = -1;
        }
        if (check_if_is_answer(*cu_node->right->val))
        {
            // std::cout << "here?9" << std::endl;
            // std::cerr << "yes right" << std::endl;
            current_node = current_node->right;

            show_path(current_node);

            return 1;
        }
    }
    else if (cu_node->left != nullptr && choose == -1)
    {
        // std::cout << "left" << std::endl;
        if (my_find(make_str(cu_node->left)) == 0)
        {
            // disp_in_menu(*cu_node->left->val, *cu_node->val);
            search_queue.push(cu_node->left);
            all_grand_child.push_back(cu_node->number_of_parent + 1);
            all_record.insert(this->make_str(cu_node->left));
            all_map.insert(std::pair<std::string,int>(this->make_str(cu_node->left),all_grand_child.back())) ;

            choose = 0;
        }
        else
        {
            choose = -1;
        }
        if (check_if_is_answer(*cu_node->left->val))
        {
            // std::cerr << "yes left" << std::endl;
            current_node = cu_node->left;
            show_path(current_node);
            return 1;
        }
    }
    if ((search_queue.size() >= 1 && choose == -1) || search_queue.size() >= max_depth)
    {
        std::cout << "poping" << std::endl;
        search_queue.pop();
        std::cout << "searchque size " << search_queue.size() << " " << max_depth << std::endl;
    }

    if (search_queue.size() >= 1)
        cu_node = search_queue.top();
    else
    {
        std::cerr << "no Node reamained" << BLS::Node::Node_no << std::endl;
        return 2;
    }
    current_node = cu_node;

    if (BLS::Node::Node_no % 1000 == 0)
    {
        std::cerr << Color::color_blue << "node_no: " << BLS::Node::Node_no << "\tvisited:" << all_record.size() << "\tque_size: " << search_queue.size() << std::endl;
    
    }

    // std::cout << "search for answer done " << std::endl;

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

std::string BLS::make_str(Node *n, const std::vector<int> &vec)
{
    // std::cout<<Color::color_green<<"have val"<<std::endl;
    std::string s = "";
    if (vec[0] == -1)
    {
        for (int i = 0; i < 9; i++)
        {
            s.append(std::to_string((*n->val)[i]));
        }
    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            s.append(std::to_string(vec[i]));
        }
    }

    return s;
}
bool BLS::my_find(const std::string &my_str)
{
    auto it = all_record.find(my_str);

    // if (it != all_record.end())
    // {
    //     int index = all_grand_child.size() - 1 - (it - all_record.rbegin());
    //     int grand_current = this->current_node->number_of_parent +1;
    //     int grand_child = all_grand_child[index];
    //     return (grand_current < grand_child) ? 0 : 1;
    // }

    return (it == all_record.end()) ? 0 : 1;
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
}
void BLS::disp()
{
}
void BLS::disp(std::vector<int> v)
{
}
