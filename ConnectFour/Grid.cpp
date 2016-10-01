#include "Grid.hpp"

Grid::Grid(unsigned int rows, unsigned int columns) {

    this->rows = (rows > 4) ? rows : 4;
    cols = (columns > 4) ? columns : 4;
    cells = std::vector< std::vector<Cell> >(cols, std::vector<Cell>(this->rows, Grid::GC_EMPTY));
}

bool Grid::insertDisc(unsigned int column, Cell disc) {

    if (column >= cols || disc == GC_EMPTY) {
        return false;
    }

    for (unsigned int i=0; i<rows; i++) {
        if (cells[column][i] ==GC_EMPTY) {
            cells[column][i] = disc;
            return true;
        }
    }

    return false;
}

Grid::Cell Grid::cellAt(unsigned int row, unsigned int column) const {

    if (column >= cols || row >= rows) {
        return GC_EMPTY;
    }

    return cells[column][rows-row-1];
}

void Grid::reset() {

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

    for (unsigned int i=rows-row-1; i<rows-1; i++) {
        cells[column][i] = cells[column][i+1];
    }
    cells[column][rows-1] = GC_EMPTY;
}