#include <string> 
#include <unordered_map> 
#include <array>
#include <algorithm>
#include <vector>

std::unordered_map<std::string, std::string> corner_data = { 
    {"wob", "aer"}, {"wbo", "are"}, {"owb", "ear"}, {"obw", "era"}, {"bwo", "rae"}, {"bow", "rea"}, 
    {"wrb", "bnq"}, {"wbr", "bqn"}, {"rbw", "nqb"}, {"rwb", "nbq"}, {"brw", "qnb"}, {"bwr", "qbn"}, 
    {"wog", "dfi"}, {"wgo", "dif"}, {"gow", "ifd"}, {"gwo", "idf"}, {"ogw", "fid"}, {"owg", "fdi"}, 
    {"wrg", "cmj"}, {"wgr", "cjm"}, {"grw", "jmc"}, {"gwr", "jcm"}, {"rwg", "mcj"}, {"rgw", "mjc"}, 
    {"yob", "xhs"}, {"ybo", "xsh"}, {"oby", "hsx"}, {"oyb", "hxs"}, {"boy", "shx"}, {"byo", "sxh"}, 
    {"yrb", "wot"}, {"ybr", "wto"}, {"rby", "otw"}, {"ryb", "owt"}, {"bry", "tow"}, {"byr", "two"}, 
    {"yog", "ugl"}, {"ygo", "ulg"}, {"ogy", "glu"}, {"oyg", "gul"}, {"gyo", "lug"}, {"goy", "lgu"}, 
    {"yrg", "vpk"}, {"ygr", "vkp"}, {"rgy", "pkv"}, {"ryg", "pvk"}, {"gry", "kpv"}, {"gyr", "kvp"}, 
}; 

std::unordered_map<std::string, std::string> edge_data = { 
    {"wb", "aq"}, {"bw", "qa"}, 
    {"wr", "bm"}, {"rw", "mb"}, 
    {"wg", "ci"}, {"gw", "ic"}, 
    {"wo", "de"}, {"ow", "ed"}, 
    {"yb", "ws"}, {"by", "sw"}, 
    {"yr", "vo"}, {"ry", "ov"}, 
    {"yg", "uk"}, {"gy", "ku"}, 
    {"yo", "xg"}, {"oy", "gx"}, 
    {"gr", "jp"}, {"rg", "pj"}, 
    {"rb", "nt"}, {"br", "tn"}, 
    {"go", "lf"}, {"og", "fl"}, 
    {"ob", "hr"}, {"bo", "rh"} 
}; 

std::unordered_map<char, char> edge_pairs = { 
    {'a', 'q'}, {'q', 'a'}, 
    {'b', 'm'}, {'m', 'b'}, 
    {'c', 'i'}, {'i', 'c'}, 
    {'d', 'e'}, {'e', 'd'}, 
    {'k', 'u'}, {'u', 'k'}, 
    {'o', 'v'}, {'v', 'o'}, 
    {'s', 'w'}, {'w', 's'}, 
    {'g', 'x'}, {'x', 'g'}, 
    {'j', 'p'}, {'p', 'j'}, 
    {'n', 't'}, {'t', 'n'}, 
    {'r', 'h'}, {'h', 'r'}, 
    {'l', 'f'}, {'f', 'l'} 
}; 

std::unordered_map<char, std::pair<char, char>> corner_pairs = { 
    {'a', {'e', 'r'}}, {'e', {'a', 'r'}}, {'r', {'e', 'a'}}, 
    {'b', {'n', 'q'}}, {'n', {'b', 'q'}}, {'q', {'n', 'b'}}, 
    {'c', {'j', 'm'}}, {'j', {'c', 'm'}}, {'m', {'j', 'c'}}, 
    {'d', {'i', 'f'}}, {'i', {'d', 'f'}}, {'f', {'i', 'd'}}, 
    {'h', {'s', 'x'}}, {'s', {'h', 'x'}}, {'x', {'s', 'h'}}, 
    {'g', {'l', 'u'}}, {'l', {'g', 'u'}}, {'u', {'l', 'g'}}, 
    {'k', {'v', 'p'}}, {'v', {'k', 'p'}}, {'p', {'v', 'k'}}, 
    {'o', {'w', 't'}}, {'w', {'o', 't'}}, {'t', {'w', 'o'}} 
}; 
    
std::array<std::array<int, 3>, 8> corners_to_check = {{ 
    {0, 9, 38}, 
    {2, 29, 36}, 
    {8, 20, 27}, 
    {6, 11, 18}, 
    {17, 24, 45}, 
    {26, 33, 47}, 
    {35, 42, 53}, 
    {15, 44, 51} 
}};

std::array<std::array<int, 2>, 12> edges_to_check = {{ 
    {1, 37}, 
    {3, 10}, 
    {5, 28}, 
    {7, 19}, 
    {12, 41}, 
    {14, 21}, 
    {23, 30}, 
    {32, 39}, 
    {25, 46}, 
    {16, 48}, 
    {34, 50}, 
    {43, 52} 
}}; 

std::unordered_map<char, size_t> edge_to_position_index = { 
    {'a', 0}, 
    {'d', 1}, 
    {'b', 2}, 
    {'c', 3}, 
    {'e', 4}, 
    {'h', 5}, 
    {'f', 6}, 
    {'g', 7}, 
    {'i', 8}, 
    {'l', 9}, 
    {'j', 10}, 
    {'k', 11}, 
    {'m', 12}, 
    {'p', 13}, 
    {'n', 14}, 
    {'o', 15}, 
    {'q', 16}, 
    {'t', 17}, 
    {'r', 18}, 
    {'s', 19}, 
    {'u', 20}, 
    {'x', 21}, 
    {'v', 22}, 
    {'w', 23}, 
}; 

std::unordered_map<char, size_t> corner_to_position_index = { 
    {'a', 0}, 
    {'b', 1}, 
    {'d', 2}, 
    {'c', 3}, 
    {'e', 4}, 
    {'f', 5}, 
    {'h', 6}, 
    {'g', 7}, 
    {'i', 8}, 
    {'j', 9}, 
    {'l', 10}, 
    {'k', 11}, 
    {'m', 12}, 
    {'n', 13}, 
    {'p', 14}, 
    {'o', 15}, 
    {'q', 16}, 
    {'r', 17}, 
    {'t', 18}, 
    {'s', 19}, 
    {'u', 20}, 
    {'v', 21}, 
    {'x', 22}, 
    {'w', 23}
}; 

std::unordered_map<char, std::vector<std::string>> edge_algorithms = { 
    {'a', {"l2", "D'", "L2"}}, 
    {'c', {"l2", "D", "L2"}}, 
    {'d', {""}}, {'e', {"L'", "d", "L'"}}, 
    {'f', {"d'", "L"}}, 
    {'g', {"L", "d", "L'"}}, 
    {'h', {"d", "L'"}}, 
    {'i', {"l", "D'", "L2"}}, 
    {'j', {"d2", "L"}}, 
    {'k', {"D'", "L", "d", "L'"}}, 
    {'l', {"L'"}}, {'n', {"d", "L"}}, 
    {'o', {"D2", "L", "d", "L'"}}, 
    {'p', {"d'", "L'"}}, 
    {'q', {"l'", "D", "L2"}}, 
    {'r', {"L"}}, 
    {'s', {"D", "L", "d", "L'"}}, 
    {'t', {"d2", "L'"}}, 
    {'u', {"D'", "L2"}}, 
    {'v', {"D2", "L2"}}, 
    {'w', {"D", "L2"}}, 
    {'x', {"L2"}} 
}; 

std::unordered_map<char, std::vector<std::string>> reverse_edge_algorithms = { 
    {'a', {"l2", "D", "L2"}}, 
    {'c', {"l2", "D'", "L2"}}, 
    {'d', {""}}, 
    {'e', {"L", "d'", "L"}}, 
    {'f', {"d", "L'"}}, 
    {'g', {"L'", "d'", "L"}}, 
    {'h', {"d'", "L"}}, 
    {'i', {"l'", "D", "L2"}}, 
    {'j', {"d2", "L'"}}, 
    {'k', {"D''", "L'", "d'", "L"}}, 
    {'l', {"L"}}, {'n', {"d'", "L'"}}, 
    {'o', {"D2", "L'", "d'", "L"}}, 
    {'p', {"d", "L"}}, 
    {'q', {"l", "D'", "L2"}},   
    {'r', {"L'"}}, 
    {'s', {"D'", "L'", "d'", "L"}}, 
    {'t', {"d2", "L"}}, {'u', {"D", "L2"}}, 
    {'v', {"D2", "L2"}}, 
    {'w', {"D'", "L2"}}, 
    {'x', {"L2"}} 
}; 

std::unordered_map<char, std::vector<std::string>> corner_algorithms = { 
    {'b', {"R2"}}, 
    {'c', {"F2", "D"}}, 
    {'d', {"F2"}}, 
    {'m', {"F"}}, 
    {'f', {"F'", "D"}}, 
    {'g', {"F'"}}, 
    {'h', {"D'", "R"}}, 
    {'i', {"F", "R'"}}, 
    {'j', {"R'"}}, 
    {'k', {"F", "R'"}}, 
    {'l', {"F2", "R'"}}, 
    {'n', {"R'", "F"}}, 
    {'o', {"R2", "F"}}, 
    {'p', {"R", "F"}}, 
    {'q', {"R", "D'"}}, 
    {'s', {"D2", "F'", "R'"}}, 
    {'t', {"R"}}, 
    {'u', {"D"}}, 
    {'v', {""}}, 
    {'w', {"D'"}}, 
    {'x', {"D2"}} 
}; 
            
std::unordered_map<char, std::vector<std::string>> reverse_corner_algorithms = { 
    {'b', {"R2"}}, 
    {'c', {"F2", "D'"}}, 
    {'d', {"F2"}}, 
    {'m', {"F'"}}, 
    {'f', {"F", "D'"}}, 
    {'g', {"F"}}, 
    {'h', {"D", "R'"}}, 
    {'i', {"F'", "R"}}, 
    {'j', {"R"}}, 
    {'k', {"F'", "R"}}, 
    {'l', {"F2", "R"}}, 
    {'n', {"R", "F'"}}, 
    {'o', {"R2", "F'"}}, 
    {'p', {"R'", "F'"}}, 
    {'q', {"R'", "D"}}, 
    {'s', {"D2", "F", "R"}}, 
    {'t', {"R'"}}, 
    {'u', {"D'"}}, 
    {'v', {""}}, 
    {'w', {"D"}}, 
    {'x', {"D2"}} 
}; 

std::vector<std::string> edge_swap = {"R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'"}; 
std::vector<std::string> corner_swap = {"R", "U'", "R'", "U'", "R", "U", "R'", "F'", "R", "U", "R'", "U'", "R'", "F", "R"}; 
std::vector<std::string> r_perm = {"R", "U", "R'", "F'", "R", "U2", "R'", "U2", "R'", "F", "R", "U", "R", "U2", "R'", "U'"}; 