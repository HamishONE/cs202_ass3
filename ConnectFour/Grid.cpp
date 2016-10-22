#include "Grid.hpp"

Grid::Grid(unsigned int rows, unsigned int columns) {

    // If the dimensions given are less than 4 make them equal to 4
    this->rows = (rows > 4) ? rows : 4;
    this->cols = (columns > 4) ? columns : 4;

    // Create a vector of vector the with the dimensions given
    cells = std::vector< std::vector<Cell> >(this->cols, std::vector<Cell>(this->rows, Grid::GC_EMPTY));
}

bool Grid::insertDisc(unsigned int column, Cell disc) {

    // If the column index or disc is invalid do nothing
    if (column >= cols || disc == GC_EMPTY) {
        return false;
    }

    // Loop upwards along the column
    for (unsigned int i=0; i<rows; i++) {

        // If an empty slot is found insert the disc here and exit
        if (cells[column][i] == GC_EMPTY) {
            cells[column][i] = disc;
            return true;
        }
    }

    // If the column is full already do nothing and return false
    return false;
}

Grid::Cell Grid::cellAt(unsigned int row, unsigned int column) const {

    // If either index is invalid return an empty cell
    if (column >= cols || row >= rows) {
        return GC_EMPTY;
    }

    // Otherwise return the cell at the position specified, adjusting for a vertically inverted coordinate system
    return cells[column][rows-row-1];
}

void Grid::reset() {

    // Loop through each cell and set it to empty
    for (unsigned int i=0; i<cols; i++) {
        for (unsigned int j=0; j<rows; j++) {
            cells[i][j] = GC_EMPTY;
        }
    }
}

unsigned int Grid::rowCount() const {
    return rows;
}

unsigned int Grid::columnCount() const {
    return cols;
}

void Grid::removeDisk(unsigned int row, unsigned int column) {

    // Loop through each cell above the one specified and drop them down one position
    for (unsigned int i=rows-row-1; i<rows-1; i++) {
        cells[column][i] = cells[column][i+1];
    }

    // Ensure the very top of the column is empty
    cells[column][rows-1] = GC_EMPTY;
}