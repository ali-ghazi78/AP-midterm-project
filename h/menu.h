#ifndef __menu__
#define __menu__
#include <iostream>
#include <color.h>

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
bool  show_costume()
{
    std::string s;
    bool done = false;
    std::vector<int> vec = std::vector<int>(9,-1);
    int j = 0;
    while (!done)
    {
        std::cout << Color::color_blue << "please enter a number between 0 to 8 " << std::endl;
        std::vector<int> init_vec = vec;
        Board t = Board(init_vec);
        t.disp_in_menu(init_vec, init_vec);
        std::cout << Color::color_blue << "enter  (b) to exit " << std::endl;
        std::cin >> s;
        clear();
        if (is_number(s) != -1 && s.size() == 1 && s!="9")
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
            if(s=="b"||s=="B")
                return 0;
            std::cout << Color::color_red << "invalid input" << std::endl;
        }
        if (done && !t.is_solvable(vec))
        {
            std::cout << Color::color_red << "sorry but your puzzle is not solvable enter sth else" << std::endl;
            vec =  std::vector<int>(9,-1);
            j = 0;
            done = false;
        }
    }
    clear();
    std::cout << Color::color_green << "please wait" << std::endl;
    Board a = Board(vec);
    a.loop();
    std::vector<std::vector<int>> result = a.final_val;
    for (int i = 0; i < result.size(); i++)
    {
        if (i + 1 < result.size())
            a.disp_in_menu(result[i], result[i + 1]);
        std::cout << Color::color_green << "press any key then enter continue" << std::endl;
        std::cin >> s;
    }
    std::cout << Color::color_green << "done" << std::endl;
    std::cout << Color::color_green << "press any key then enter continue" << std::endl;
    std::cin >> s;
}

void menu_loop()
{
    std::string s;
    clear();

    std::cout << Color::color_green << "please enter your desire option" << std::endl;
    std::cout << Color::color_green << "(1)" << Color::color_blue << "  solve random puzzle" << std::endl;
    std::cout << Color::color_green << "(2)" << Color::color_blue << "  solve costumized puzzle" << std::endl;
    std::cout << Color::color_green << "(3)" << Color::color_blue << "  exit" << std::endl;
    std::cin >> s;
    clear();
    if (s == "1")
    {
        std::vector<int> init_vec = {2, 4, 6, 5, 8, 3, 0, 1, 7};
        std::random_shuffle(init_vec.begin(), init_vec.end());

        Board t = Board(init_vec);
        while (!t.is_solvable(init_vec))
        {
            std::random_shuffle(init_vec.begin(), init_vec.end());
        }
        Board a = Board(init_vec);

        a.err_disp(init_vec);
        a.loop();
        std::vector<std::vector<int>> result = a.final_val;
        for (int i = 0; i < result.size(); i++)
        {
            if (i + 1 < result.size())
                a.disp_in_menu(result[i], result[i + 1]);
            std::cout << Color::color_green << "press any key then enter continue" << std::endl;
            std::cin >> s;
        }
        std::cout << Color::color_green << "done" << std::endl;
        std::cout << Color::color_green << "press any key then enter continue" << std::endl;
        std::cin >> s;
    }
    else if (s == "2")
    {
        show_costume();
    }
    else if (s == "3")
    {
        clear();
        exit(0);
    }
    else
    {
        std::cout << Color::color_red << "invalid input try again "
                  << "\033[0m" << std::endl;
    }
}

#endif