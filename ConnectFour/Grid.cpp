#include "Grid.hpp"

Grid::Grid(unsigned int rows, unsigned int columns) {
    this->rows = (rows > 4) ? rows : 4;
    cols = (columns > 4) ? columns : 4;

    for (unsigned int i=0; i<cols; i++) {
        this->columns.push_back(Column(this->rows));
    }
}

Grid::~Grid() {}

bool Grid::insertDisc(unsigned int column, Cell disc) {

    if (column >= cols || disc == GC_EMPTY) {
        return false;
    }

    for (unsigned int i=0; i<rows; i++) {
        if (columns[column].cells[i] == GC_EMPTY) {
            columns[column].cells[i] = disc;
            return true;
        }
    }

    return false;
}

Grid::Cell Grid::cellAt(unsigned int row, unsigned int column) const {

    if (column >= cols || row >= rows) {
        return GC_EMPTY;
    }

    return columns[column].cells[rows-row-1];
}

void Grid::reset() {
    for (unsigned int i=0; i<cols; i++) {
        for (unsigned int j=0; j<rows; j++) {
            columns[i].cells[j] = GC_EMPTY;
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
        columns[column].cells[i] = columns[column].cells[i+1];
    }
    columns[column].cells[rows-1] = GC_EMPTY;
}