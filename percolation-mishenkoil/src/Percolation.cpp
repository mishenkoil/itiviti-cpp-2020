#include <cstdint>
#include "Percolation.h"

Percolation::Percolation(size_t dimension) : dimension(dimension)
{
    table_reachability.resize(dimension, std::vector<bool>(dimension, false));
    table_fullness.resize(dimension, std::vector<bool>(dimension, false));
}

bool Percolation::is_valid(int64_t row, int64_t column) const
{
    return (row >= 0) && (row < static_cast<int64_t> (dimension))
           && (column < static_cast<int64_t> (dimension)) && (column >= 0);
}

bool Percolation::is_ready_to_full(size_t row, size_t column) const
{
    if (row == 0)
    {
        return true;
    }
    if (is_valid(row - 1, column) && is_full(row - 1, column))
    {
        return true;
    }
    if (is_valid(row, column + 1) && is_full(row, column + 1))
    {
        return true;
    }
    if (is_valid(row + 1, column) && is_full(row + 1, column))
    {
        return true;
    }
    if (is_valid(row, column - 1) && is_full(row, column - 1))
    {
        return true;
    }
    return false;
}

void Percolation::full_around(size_t row, size_t column)
{
    full(row, column);
    if (is_valid(row - 1, column) && !is_full(row - 1, column) && is_open(row - 1, column))
    {
        full_around(row - 1, column);
    }
    if (is_valid(row, column + 1) && !is_full(row, column + 1) && is_open(row, column + 1))
    {
        full_around(row, column + 1);
    }
    if (is_valid(row + 1, column) && !is_full(row + 1, column) && is_open(row + 1, column))
    {
        full_around(row + 1, column);
    }
    if (is_valid(row, column - 1) && !is_full(row, column - 1) && is_open(row, column - 1))
    {
        full_around(row, column - 1);
    }
}

void Percolation::full(size_t row, size_t column)
{
    table_fullness[row][column] = true;
}

void Percolation::open(size_t row, size_t column)
{
    if (is_open(row, column))
    {
        return;
    }

    open_amount++;
    table_reachability[row][column] = true;

    if (is_ready_to_full(row, column))
    {
        full_around(row, column);
    }
}

bool Percolation::is_open(size_t row, size_t column) const
{
    return table_reachability[row][column];
}

bool Percolation::is_full(size_t row, size_t column) const
{
    return table_fullness[row][column];
}

size_t Percolation::get_numbet_of_open_cells() const
{
    return open_amount;
}

bool Percolation::has_percolation() const
{
    for (auto cell : table_fullness[table_fullness.size() - 1])
    {
        if (cell)
        {
            return true;
        }
    }
    return false;
}

