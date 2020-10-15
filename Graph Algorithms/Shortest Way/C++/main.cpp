#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "a_star.cpp"

static const char block_symbol = '#', start_symbol = 'S', target_symbol = 'T', path_symbol = '@';

void generate_grid(grid_t& grid, point_t& start, point_t& target, const char* filename)
{
    std::ifstream file(filename);
    if (!file.good())
    {
        throw std::runtime_error("Invalid file name, failed to open file.");
    }

    if (grid.empty())
    {
        grid.emplace_back();
    }
    
    char c;
    while (file.get(c))
    {
        if (c != '\n')
        {
            grid.back().push_back(node(c != block_symbol));
            // check if this is a special block
            if (c == start_symbol)
            {
                start = {grid.size() - 1, grid.back().size() - 1};
            }
            else if (c == target_symbol)
            {
                target = {grid.size() - 1, grid.back().size() - 1};
            }
        }
        else // c == \n
        {
            grid.emplace_back();
        }
    }
}

void write_board(std::vector<char>& board, const char* outname)
{
    std::ofstream file(outname);
    if (!file.good())
    {
        throw std::runtime_error("Invalid output name, failed to open file.");
    }
    for (auto c : board)
    {
        file << c;
    }
}
void generate_string(grid_t& grid, std::vector<point_t>& path, point_t& start, point_t& target, std::vector<char>& grid_string)
{
    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid.back().size(); ++j)
        {
            grid_string.push_back((grid[i][j].traversable ? '-' : '#'));
        }
        grid_string.push_back('\n');
    }

    for (auto& pnt : path)
    {
        grid_string[pnt.first * (grid.back().size() + (pnt.first > 0 ? 1 : 0)) + pnt.second ] = path_symbol;
    }

    grid_string[start.first * (grid.back().size() + (start.first > 0 ? 1 : 0)) + start.second] = start_symbol;
    grid_string[target.first * (grid.back().size() + (target.first > 0 ? 1 : 0)) + target.second] = target_symbol;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Invalid number of arguments, please include a grid file and an output file.");
    }

    grid_t grid;
    point_t start, target;
    std::vector<point_t> path;
    std::vector<char> grid_string;

    // generate th grid from the given file
    generate_grid(grid, start, target, argv[1]);

    // find the path and insert it into the path vector
    a_star(grid, start, target, path);

    // create the string to be inputted to the file
    generate_string(grid, path, start, target, grid_string);

    // write the string into the file 
    write_board(grid_string, argv[2]);
}
