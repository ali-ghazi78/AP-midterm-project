#ifndef __color__
#define __color__

#include <string>
class Color
{
public:
    inline static std::string color_reset = "\033[0m";
    inline static std::string color_yellow = "\033[0m\033[33;1;2;3;5m";
    inline static std::string color_blue = "\033[0m\033[34;1;2;3;5m";
    inline static std::string color_red = "\033[0m\033[31;1;2;3;5m";
    inline static std::string color_green = "\033[0m\033[32;1;2;3;5m";
    inline static std::string color_yellow_b = "\033[0m\033[47;43;1;2;3;5m";
    inline static std::string color_blue_b = "\033[0m\033[47;44;1;2;3;5m";
    inline static std::string color_red_b = "\033[0m\033[47;41;1;2;3;5m";
    inline static std::string color_green_b = "\033[0m\033[47;42;1;2;3;5m";
    inline static std::string non_italic = "\033[23m";
    

};
#endif