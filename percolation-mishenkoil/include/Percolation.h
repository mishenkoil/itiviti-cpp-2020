#pragma once
#include <stdio.h>
#include <vector>

struct Percolation
{
private:
    size_t dimension;
    size_t open_amount = 0;
    std::vector<std::vector<bool>> table_reachability;
    std::vector<std::vector<bool>> table_fullness;

    // checks board boundaries
    bool is_valid(int64_t row, int64_t column) const;

    // return is it available to full
    bool is_ready_to_full(size_t row, size_t column) const;

    // recursive function which full nearest opened & not fulled cells
    void full_around(size_t row, size_t column);

    // full selected cell
    void full(size_t row, size_t column);

    /**
     * Construct a new Percolation object
     * @param dimension dimension of percolation table
     */
public:
    Percolation(size_t dimension);

    /**
     * Opens the cell[row, column] if it's not opened already
     * @param row row index
     * @param column column index
     */
    void open(size_t row, size_t column);

    /**
     * Checks if cell[row, column] is open
     * @param row row index
     * @param column column index
     * @return true cell is open
     * @return false cell is blocked
     */
    bool is_open(size_t row, size_t column) const;

    /**
     * Checks if cell[row, column] is full
     * @param row row index
     * @param column column index
     * @return true cell is full
     * @return false cell is not full
     */
    bool is_full(size_t row, size_t column) const;

    /**
     * Gets number of open cells in table
     * @return number of open cells
     */
    size_t get_numbet_of_open_cells() const;

    /**
     * Checks if system percolates
     * @return true system percolates
     * @return false system doesn't percolate
     */
    bool has_percolation() const;
};