#ifndef __menu__
#define __menu__
#include <iostream>
#include <color.h>

void clear()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\033[0m\x1B[2J\x1B[H";
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