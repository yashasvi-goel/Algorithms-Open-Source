#include "node.cpp"
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

using grid_t = std::vector<std::vector<node>>;
using point_t = std::pair<int, int>;

void find_children(grid_t& grid, size_t parent_row, size_t parent_col, std::vector<point_t>& children)
{
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            // if this coordinate is not the parent itself, is valid and is traversable
            if (i | j != 0
                && parent_row + i >= 0 && parent_row + i < grid.size()
                && parent_col + j >= 0 && parent_col + j < grid.back().size()
                && grid[parent_row + i][parent_col + j].traversable)
            {
                children.push_back({parent_row + i, parent_col + j});
            }
        }
    }
}

int distance(point_t& lhs, point_t& rhs)
{
    int dx = abs(lhs.first - rhs.first), dy = abs(lhs.second - rhs.second);
    return abs(dx - dy) * 10 + std::min(dx, dy) * 14;
}

inline bool remaining_open(grid_t& grid)
{
    return std::any_of(grid.begin(), grid.end(), [](grid_t::value_type& row) {
        return std::any_of(row.begin(), row.end(), [](node& nd) {
            return nd.state == node::mode::OPENED;
        });
    });
}

/* find the node with the minimal f value out of the open nodes */
point_t cheapest_point(grid_t& grid)
{
    unsigned int min_fval = 0;
    point_t current;
    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid.back().size(); ++j)
        {
            if (grid[i][j].state == node::mode::OPENED && (min_fval == 0 || grid[i][j].f < min_fval))
            {
                min_fval = grid[i][j].f;
                current = {i, j};
            }
        }
    }
    return current;
}

void a_star(grid_t& grid, point_t& start, point_t& target, std::vector<point_t>& path)
{
    std::vector<point_t> children;
    point_t current;

    // add in the start node
    grid[start.first][start.second].state = node::mode::OPENED;

    while (remaining_open(grid))
    {
        current = cheapest_point(grid);

        // mark as closed
        grid[current.first][current.second].state = node::mode::CLOSED;

        // we've reached the target = end the algorithm
        if (current == target)
        {
            point_t path_point = target;
            while (path_point != start)
            {
                path.insert(path.begin(), path_point);

                // continue backtracking
                path_point = {grid[path_point.first][path_point.second].parent_row,
                            grid[path_point.first][path_point.second].parent_col};
            }
        }
        
        children.clear();
        find_children(grid, current.first, current.second, children);

        for (point_t& child_point : children)
        {
            node& child_node = grid[child_point.first][child_point.second];

            // if this node has yet to be evaluated
            if (child_node.state != node::mode::CLOSED)
            {
                // update g and f, distance is h
                auto new_g = grid[current.first][current.second].g + 10 + (current.first != child_point.first && current.second != child_point.second ? 4 : 0);

                // if this is the first time encountering this node, set it's heuristic value
                if (child_node.h == 0)
                {
                    child_node.h = distance(child_point, target);
                }

                // if throguh the current parent the way is shorter, update it
                if (child_node.g == 0 || child_node.g > new_g)
                {
                    child_node.g = new_g;

                    // set the childs parent for backtracking purporses
                    child_node.parent_row = current.first;
                    child_node.parent_col = current.second;
                    
                    // update the f value with the new g and h values
                    child_node.f = child_node.g + child_node.h;
                }
                // set the child to open, whether it was unreached or already open open
                child_node.state = node::mode::OPENED;
            }
        }
    }
}
