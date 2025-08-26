#include "cube.h"
#include "data.h"


int main(int argc, char *argv[]) {
    clock_t start_time = clock();
    std::string scramble = argv[1];
    std::string temp_corner(3, ' ');
    std::string temp_edge(2, ' ');

    std::string corner_scramble = read_corner_scramble(scramble, temp_corner, corners_to_check, corner_data);
    std::string edge_scramble = read_edge_scramble(scramble, temp_edge, edges_to_check, edge_data);

    std::vector<char> unsolved_edges, unsolved_corners;
    initialize_unsolved(unsolved_edges, unsolved_corners);

    remove_solved_edges(edge_scramble, unsolved_edges, edge_pairs, edge_to_position_index);
    remove_solved_corners(corner_scramble, unsolved_corners, corner_pairs, corner_to_position_index);

    std::string edge_solve_string = solve_edges(edge_scramble, unsolved_edges, edge_pairs, edge_to_position_index);
    std::string corner_solve_string = solve_corners(corner_scramble, unsolved_corners, corner_pairs, corner_to_position_index);

    print_solve(edge_solve_string, corner_solve_string,
            edge_algorithms, reverse_edge_algorithms, edge_swap, r_perm,
            corner_algorithms, reverse_corner_algorithms, corner_swap);

    clock_t end_time = clock();
    double duration = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Time: " << duration << " seconds\n";
}

