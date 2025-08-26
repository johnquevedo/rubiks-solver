#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::string read_corner_scramble(const std::string& scramble,
                                 std::string temp_corner,
                                 const std::array<std::array<int,3>,8>& corners_to_check,
                                 const std::unordered_map<std::string,std::string>& corner_data)
{
    std::string corner_scramble(54, ' ');
    for(int i {0}; i < 8; ++i) {
        for(int j {0}; j < 3; ++j)
            temp_corner[j] = scramble[corners_to_check[i][j]];
        temp_corner = corner_data.at(temp_corner);
        for(int j {0}; j < 3; ++j)
            corner_scramble[corners_to_check[i][j]] = temp_corner[j];
    }
    corner_scramble.erase(std::remove(corner_scramble.begin(), corner_scramble.end(), ' '), corner_scramble.end());
    return corner_scramble;
}


std::string read_edge_scramble(const std::string& scramble,
                               std::string temp_edge,
                               const std::array<std::array<int,2>,12>& edges_to_check,
                               const std::unordered_map<std::string,std::string>& edge_data)
{
    std::string edge_scramble(54, ' ');
    for(int i {0}; i < 12; ++i) {
        for(int j {0}; j < 2; ++j)
            temp_edge[j] = scramble[edges_to_check[i][j]];
        temp_edge = edge_data.at(temp_edge);
        for(int j {0}; j < 2; ++j)
            edge_scramble[edges_to_check[i][j]] = temp_edge[j];
    }
    edge_scramble.erase(std::remove(edge_scramble.begin(), edge_scramble.end(), ' '), edge_scramble.end());
    return edge_scramble;
}


void initialize_unsolved(std::vector<char>& unsolved_edges,
                         std::vector<char>& unsolved_corners)
{
    for(char c = 'a'; c <= 'x'; ++c) {
        if(c != 'b' && c != 'm') unsolved_edges.push_back(c);
        if(c != 'a' && c != 'e' && c != 'r') unsolved_corners.push_back(c);
    }
}


void remove_solved_edges(const std::string& edge_scramble,
                         std::vector<char>& unsolved_edges,
                         const std::unordered_map<char, char>& edge_pairs,
                         const std::unordered_map<char, size_t>& edge_to_position_index)
{
    for(int i {0}; i < edge_scramble.size(); ++i) {
        char c = edge_scramble[i];
        if(edge_to_position_index.at(c) == i) {
            auto it1 = std::find(unsolved_edges.begin(), unsolved_edges.end(), c);
            if(it1 != unsolved_edges.end()) unsolved_edges.erase(it1);

            char pair = edge_pairs.at(c);
            auto it2 = std::find(unsolved_edges.begin(), unsolved_edges.end(), pair);
            if(it2 != unsolved_edges.end()) unsolved_edges.erase(it2);
        }
    }
}


void remove_solved_corners(const std::string& corner_scramble,
                           std::vector<char>& unsolved_corners,
                           const std::unordered_map<char, std::pair<char,char>>& corner_pairs,
                           const std::unordered_map<char, size_t>& corner_to_position_index)
{
    for(int i {0}; i < corner_scramble.size(); ++i) {
        char c = corner_scramble[i];
        if(corner_to_position_index.at(c) == i) {
            auto it1 = std::find(unsolved_corners.begin(), unsolved_corners.end(), c);
            if(it1 != unsolved_corners.end()) unsolved_corners.erase(it1);

            auto it2 = std::find(unsolved_corners.begin(), unsolved_corners.end(), corner_pairs.at(c).first);
            if(it2 != unsolved_corners.end()) unsolved_corners.erase(it2);

            auto it3 = std::find(unsolved_corners.begin(), unsolved_corners.end(), corner_pairs.at(c).second);
            if(it3 != unsolved_corners.end()) unsolved_corners.erase(it3);
        }
    }
}


std::string solve_edges(std::string& edge_scramble,
                        std::vector<char>& unsolved_edges,
                        const std::unordered_map<char, char>& edge_pairs,
                        const std::unordered_map<char, size_t>& edge_to_position_index)
{
    std::string edge_solve_string;
    while(!unsolved_edges.empty()) {
        char last, last_pair;
        if(edge_scramble[2] == 'b' || edge_scramble[2] == 'm') {
            last = unsolved_edges.back();
            edge_solve_string += last;
            std::swap(edge_scramble[2], edge_scramble[edge_to_position_index.at(last)]);
        } else {
            last = edge_scramble[2];
            last_pair = edge_pairs.at(last);
            edge_solve_string += last;

            auto it1 = std::find(unsolved_edges.begin(), unsolved_edges.end(), last);
            if(it1 != unsolved_edges.end()) unsolved_edges.erase(it1);

            auto it2 = std::find(unsolved_edges.begin(), unsolved_edges.end(), last_pair);
            if(it2 != unsolved_edges.end()) unsolved_edges.erase(it2);

            std::swap(edge_scramble[2], edge_scramble[edge_to_position_index.at(last)]);
        }
    }
    return edge_solve_string;
}


std::string solve_corners(std::string& corner_scramble,
                          std::vector<char>& unsolved_corners,
                          const std::unordered_map<char,std::pair<char,char>>& corner_pairs,
                          const std::unordered_map<char,size_t>& corner_to_position_index)
{
    std::string corner_solve_string;
    while(!unsolved_corners.empty()) {
        char last, last_pair, last_other_pair;
        if(corner_scramble[4] == 'a' || corner_scramble[4] == 'e' || corner_scramble[4] == 'r') {
            last = unsolved_corners.back();
            corner_solve_string += last;
            std::swap(corner_scramble[4], corner_scramble[corner_to_position_index.at(last)]);
        } else {
            last = corner_scramble[4];
            last_pair = corner_pairs.at(last).first;
            last_other_pair = corner_pairs.at(last).second;
            corner_solve_string += last;

            auto it1 = std::find(unsolved_corners.begin(), unsolved_corners.end(), last);
            if(it1 != unsolved_corners.end()) unsolved_corners.erase(it1);
            auto it2 = std::find(unsolved_corners.begin(), unsolved_corners.end(), last_pair);
            if(it2 != unsolved_corners.end()) unsolved_corners.erase(it2);
            auto it3 = std::find(unsolved_corners.begin(), unsolved_corners.end(), last_other_pair);
            if(it3 != unsolved_corners.end()) unsolved_corners.erase(it3);

            std::swap(corner_scramble[4], corner_scramble[corner_to_position_index.at(last)]);
        }
    }
    return corner_solve_string;
}

void print_solve(const std::string& edge_solve_string,
                 const std::string& corner_solve_string,
                 const std::unordered_map<char, std::vector<std::string>>& edge_algorithms,
                 const std::unordered_map<char, std::vector<std::string>>& reverse_edge_algorithms,
                 const std::vector<std::string>& edge_swap,
                 const std::vector<std::string>& r_perm,
                 const std::unordered_map<char, std::vector<std::string>>& corner_algorithms,
                 const std::unordered_map<char, std::vector<std::string>>& reverse_corner_algorithms,
                 const std::vector<std::string>& corner_swap)
{

    for(auto e : edge_solve_string) {
        for(const auto& move : edge_algorithms.at(e))
            std::cout << move << " ";
        for(const auto& m : edge_swap)
            std::cout << m << " ";
        for(int i = reverse_edge_algorithms.at(e).size() - 1; i >= 0; --i)
            std::cout << reverse_edge_algorithms.at(e)[i] << " ";
        std::cout << "\n";
    }

    if(edge_solve_string.size() % 2 == 1) {
        for(const auto& m : r_perm)
            std::cout << m << " ";
        std::cout << "\n";
    }

    // Print corners
    for(auto c : corner_solve_string) {
        for(const auto& move : corner_algorithms.at(c))
            std::cout << move << " ";
        for(const auto& m : corner_swap)
            std::cout << m << " ";
        for(int i = reverse_corner_algorithms.at(c).size() - 1; i >= 0; --i)
            std::cout << reverse_corner_algorithms.at(c)[i] << " ";
        std::cout << "\n";
    }
}
