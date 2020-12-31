#ifndef __menu__
#define __menu__
#include <iostream>
#include <color.h>
#include <cstdlib>
#include <dls.h>
#include <ctime>
#include <bfs.h>

std::vector<int> how_many_shuffle(size_t steps);

std::string my_cin()
{
    std::string myString;
    std::getline(std::cin, myString);
    return myString;
}
void clear()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\033[0m\x1B[2J\x1B[H";
}

int is_number(const std::string &s)
{
    bool ok = !s.empty() && std::find_if(s.begin(),
                                         s.end(), [](unsigned char c) { return (!std::isdigit(c)); }) == s.end();
    if (ok)
        return std::stoi(s);
    else
        return -1;
}
bool solve_dfs(std::vector<int> init_vec)
{
    clear();
    DLS t = DLS(init_vec);
    BFS b(init_vec);
    std::cout << Color::color_green << "please be patient we are solving the following puzzle ... " << std::endl;
    b.disp_in_menu(init_vec, init_vec);
    int bfs_min_dep = b.loop();
    std::cout << Color::color_blue << "minimum depth that is requierd to solve the puzzel is: " << Color::color_red << bfs_min_dep << std::endl;
    std::cout << Color::color_green << "but u can choose ur desire depth" << std::endl;
    std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
    std::cout << Color::color_green << "please enter ur depth :" << std::endl;
    int depth = 0;
    while (depth <= 0)
    {
        std::string ss = my_cin();
        if (ss == "b" || ss == "B")
        {
            clear();
            return 0;
        }
        depth = is_number(ss);
        if (depth < 0)
        {
            std::cout << Color::color_red << "invalid input try again" << std::endl;
            std::cout << Color::color_green << "please enter ur depth :" << std::endl;
            std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        }
    }
    if (bfs_min_dep > depth)
    {
        clear();
        std::cout << Color::color_red << "you entered :" << depth << std::endl;
        std::cout << Color::color_red << "but minimum depth that is requierd to solve the puzzel is :" << bfs_min_dep << std::endl;
        std::cout << Color::color_red << "we are sorry but it is impossible to solve the puzzle using given input " << std::endl;

        return 0;
    }

    std::string s = "";
    DLS a = DLS(init_vec);
    a.max_depth = depth;
    a.loop();
    // clear();
    std::vector<std::vector<int>> result = a.final_val;
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i << "/" << result.size() - 1 << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
        std::cout << Color::color_green << "press enter to continue" << std::endl;
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        s = my_cin();
        clear();

        if (s == "b" || s == "B")
            return 0;
    }
    std::cout<<Color::color_yellow<<std::string(40,'-')<<std::endl;
    std::cout<<Color::color_yellow<<"showing all steps"<<std::endl;

    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i << "/" << result.size() - 1 << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
    }
    if (result.size() == 0)
        std::cout << Color::color_red << "we are sorry but it is not solvable with specified depth" << std::endl;

    std::cout << Color::color_green << "done" << std::endl;
    std::cout << Color::color_green << "press enter to continue" << std::endl;
    s = my_cin();
    clear();
    return 0;
}
bool solve_bfs(std::vector<int> init_vec)
{
    clear();
    std::cout << Color::color_green << "please wait. we are solving puzzle be patient ..." << std::endl;
    std::string s = "";
    BFS a = BFS(init_vec);

    a.loop();
    clear();
    std::vector<std::vector<int>> result = a.final_val;
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i << "/" << result.size() - 1 << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
        std::cout << Color::color_green << "press enter to continue" << std::endl;
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        s = my_cin();
        clear();

        if (s == "b" || s == "B")
            return 0;
    }
    std::cout<<Color::color_yellow<<std::string(40,'-')<<std::endl;
    std::cout<<Color::color_yellow<<"showing all steps"<<std::endl;

    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i << "/" << result.size() - 1 << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
    }
    std::cout << Color::color_green << "done" << std::endl;
    std::cout << Color::color_green << "press enter to continue" << std::endl;
    s = my_cin();
    clear();
    return 0;
}
bool show_random()
{
    clear();
    std::cout << Color::color_green << "please wait. creating best puzzle in the world just for u" << std::endl;
    clear();

    std::srand(std::time(0));

    std::string s;
    std::vector<int> init_vec = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::cout << Color::color_red << "how many move to shuffle the puzzle?" << std::endl;
    bool go2 = false;
    int shuffle;
    while (!go2)
    {
        s = my_cin();
        shuffle = is_number(s);
        if (is_number(s) == -1)
        {
            clear();
            std::cout << Color::color_red << "invalid input try again" << std::endl;
        }
        else
            go2 = true;
        std::cout << Color::color_red << "how many move to shuffle the puzzle?" << std::endl;
    }
    clear();

    init_vec = how_many_shuffle(shuffle);
    BFS t = BFS(init_vec);
    while (!t.is_solvable(init_vec))
    {
        init_vec = how_many_shuffle(10);
    }
    // while(1);
    s = "";
    bool go = false;
    while (!go)
    {
        clear();
        if (s != "1" && s != "2" && s != "")
            std::cout << Color::color_red << "invalid input try again" << std::endl;
        std::cout << Color::color_green << "enter  (1)  if u want to use BFS" << std::endl;
        std::cout << Color::color_green << "enter  (2)  if u want to use DFS" << std::endl;
        std::cout << Color::color_blue << "enter  (b)  to exit " << std::endl;
        s = my_cin();
        if (s == "b" || s == "B")
            return 0;
        else if (s == "1" || s == "2")
            go = true;
    }
    clear();
    if (s == "1")
        return solve_bfs(init_vec);
    else
    {
        return solve_dfs(init_vec);
    }
}
bool show_costume_with_costume()
{
    std::string s;
    bool done = false;
    std::vector<int> vec = std::vector<int>(9, -1);
    std::vector<int> vec_goal = std::vector<int>(9, -1);
    int j = 0;
    bool inver = true;

    while (!done)
    {
        std::cout << Color::color_green << "please enter a number between 0 to 8  " << Color::color_red << "this is your initial state" << std::endl;
        std::vector<int> init_vec = vec;
        BFS t = BFS(init_vec);
        t.disp_in_menu(init_vec, init_vec);
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        s = my_cin();
        clear();
        if (is_number(s) != -1 && s.size() == 1 && s != "9")
        {
            int num = std::stoi(s);
            if (std::find(vec.begin(), vec.end(), num) == vec.end())
            {
                vec[j] = num;
                j++;
            }
            else
            {
                std::cout << Color::color_red << "this number entered before" << std::endl;
            }

            done = (j >= 9) ? true : false;
        }
        else
        {
            if (s == "b" || s == "B")
                return 0;
            std::cout << Color::color_red << "invalid input" << std::endl;
        }
        if (done)
        {
            inver = t.is_solvable(vec);
        }
    }

    done = false;
    j = 0;

    while (!done)
    {
        std::cout << Color::color_green << "please enter a number between 0 to 8  " << Color::color_red << "this is your goal state" << std::endl;
        std::vector<int> init_vec = vec_goal;
        BFS t = BFS(init_vec);
        t.disp_in_menu(init_vec, init_vec);
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        s = my_cin();
        clear();
        if (is_number(s) != -1 && s.size() == 1 && s != "9")
        {
            int num = std::stoi(s);
            if (std::find(vec_goal.begin(), vec_goal.end(), num) == vec_goal.end())
            {
                vec_goal[j] = num;
                j++;
            }
            else
            {
                std::cout << Color::color_red << "this number entered before" << std::endl;
            }

            done = (j >= 9) ? true : false;
        }
        else
        {
            if (s == "b" || s == "B")
                return 0;
            std::cout << Color::color_red << "invalid input" << std::endl;
        }
        if (done && t.is_solvable(vec_goal) != inver)
        {
            std::cout << Color::color_red << "sorry but your puzzle is not solvable inversion of initial and goal state doesn't match enter sth else" << std::endl;
            vec_goal = std::vector<int>(9, -1);
            j = 0;
            done = false;
        }
    }
    clear();
    std::cout << Color::color_green << "please wait" << std::endl;
    BFS a = BFS(vec);
    a.desire_final_state = vec_goal;
    a.randome_or_costume = false;
    a.loop();
    std::vector<std::vector<int>> result = a.final_val;
    std::cout<<Color::color_yellow<<std::string(40,'-')<<std::endl;
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i + 1 << "/" << result.size() << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
        std::cout << Color::color_green << "press enter to continue" << std::endl;
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;

        s = my_cin();
        clear();
        if (s == "b" || s == "B")
            return true;
    }
    std::cout<<Color::color_yellow<<std::string(40,'-')<<std::endl;
    std::cout<<Color::color_yellow<<"showing all steps"<<std::endl;
    
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i << "/" << result.size() - 1 << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
    }
    std::cout << Color::color_green << "done" << std::endl;
    std::cout << Color::color_green << "press enter to continue" << std::endl;
    std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
    s = my_cin();
    clear();
    if (s == "b" || s == "B")
    {
        return true;
    }
    return false;
}

bool show_costume()
{
    std::string s;
    bool done = false;
    std::vector<int> vec = std::vector<int>(9, -1);
    int j = 0;
    while (!done)
    {
        std::cout << Color::color_green << "please enter a number between 0 to 8 " << std::endl;
        std::vector<int> init_vec = vec;
        BFS t = BFS(init_vec);
        t.disp_in_menu(init_vec, init_vec);
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        s = my_cin();
        clear();
        if (is_number(s) != -1 && s.size() == 1 && s != "9")
        {
            int num = std::stoi(s);
            if (std::find(vec.begin(), vec.end(), num) == vec.end())
            {
                vec[j] = num;
                j++;
            }
            else
            {
                std::cout << Color::color_red << "this number entered before" << std::endl;
            }

            done = (j >= 9) ? true : false;
        }
        else
        {
            if (s == "b" || s == "B")
                return 0;
            std::cout << Color::color_red << "invalid input" << std::endl;
        }
        if (done && !t.is_solvable(vec))
        {
            std::cout << Color::color_red << "sorry but your puzzle is not solvable enter sth else" << std::endl;
            vec = std::vector<int>(9, -1);
            j = 0;
            done = false;
        }
    }
    clear();
    std::cout << Color::color_green << "please wait" << std::endl;
    BFS a = BFS(vec);
    a.loop();
    std::vector<std::vector<int>> result = a.final_val;
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i + 1 << "/" << result.size() << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
        std::cout << Color::color_green << "press enter to continue" << std::endl;
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;

        s = my_cin();
        clear();
        if (s == "b" || s == "B")
            return true;
    }
    std::cout<<Color::color_yellow<<std::string(40,'-')<<std::endl;
    std::cout<<Color::color_yellow<<"showing all steps"<<std::endl;
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << Color::color_green << "step:" << i << "/" << result.size() - 1 << std::endl;
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
    }
    std::cout << Color::color_green << "done" << std::endl;
    std::cout << Color::color_green << "press enter to continue" << std::endl;
    std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
    s = my_cin();
    clear();
    if (s == "b" || s == "B")
    {
        return true;
    }
    return false;

}

void menu_loop()
{
    std::string s;

    std::cout << Color::color_green << "please enter your desire option" << std::endl;
    std::cout << Color::color_green << "(1)" << Color::color_blue << "  solve random puzzle" << std::endl;
    std::cout << Color::color_green << "(2)" << Color::color_blue << "  solve costumized puzzle" << std::endl;
    std::cout << Color::color_green << "(3)" << Color::color_blue << "  solve costumized puzzle with costume goal node" << std::endl;
    std::cout << Color::color_green << "(4)" << Color::color_blue << "  exit" << std::endl;
    s = my_cin();
    clear();
    if (s == "1")
    {
        show_random();
    }
    else if (s == "2")
    {
        show_costume();
    }
    else if (s == "3")
    {
        show_costume_with_costume();
    }

    else if (s == "4")
    {
        clear();
        exit(0);
    }
    else
    {
        std::cout << Color::color_red << "invalid input try again "
                  << "\"" << s << "\""
                  << "\033[0m" << std::endl;
    }
}
void move_zero(std::vector<int> &vec1, int x, int y, int loc)
{
    std::swap(vec1[loc], vec1[x + y * 3]);
}

std::vector<int> how_many_shuffle(size_t steps)
{
    std::vector<int> init_vec{1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::vector<int> random_move{1, 2, 3, 4};
    int pre_move = 0;
    while (steps--)
    {
        auto p = std::find(init_vec.begin(), init_vec.end(), 0);
        int loc = p - init_vec.begin();
        int x = p - init_vec.begin();
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
        std::srand(std::time(0));
        std::random_shuffle(random_move.begin(), random_move.end());
        bool done = false;
        int i = 0;
        while (!done)
        {
            std::random_shuffle(random_move.begin(), random_move.end());

            if (y_up != -1 && random_move[0] == 1 && pre_move != 2)
            {
                done = true;
                move_zero(init_vec, x_up, y_up, loc);
                pre_move = 1;
            }
            else if (y_down != -1 && random_move[0] == 2 && pre_move != 1)
            {
                done = true;
                move_zero(init_vec, x_down, y_down, loc);
                pre_move = 2;
            }
            else if (x_right != -1 && random_move[0] == 3 && pre_move != 4)
            {
                done = true;
                move_zero(init_vec, x_right, y_right, loc);
                pre_move = 3;
            }
            else if (x_left != -1 && random_move[0] == 4 && pre_move != 3)
            {
                done = true;
                move_zero(init_vec, x_left, y_left, loc);
                pre_move = 4;
            }
        }
    }
    return init_vec;
}

#endif