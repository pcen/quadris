#ifndef BOARDITERATOR_H
#define BOARDITERATOR_H

#include <vector>
#include <memory>

class Board;
class Cell;

class BoardIterator
{
	friend class Board;

public:
	// Only declared a single constructor as to override the default constructor
	BoardIterator(int x, int y, int row, int col, std::vector<std::vector<std::shared_ptr<Cell>>> board) :
		_y(y), _x(x), _rows(row), _cols(col), _cells(board) {};
        
        // No other SMFs need to be implemented as they will be defaulted by the compiler
        // We do not have any true pointer members allocated with memory for the iterator, only simple data members
        // constructor or assignment operators as we only really want shallow copy of data members

        std::shared_ptr<Cell> operator*();
        BoardIterator& operator++();
        bool operator!=(const BoardIterator& other);

private:
	int _y;		// current row index of iterator in board
	int _x;		// current column index of iterator in board
	int _rows;	// number of rows in board
	int _cols;	// number of columns in board
	std::vector<std::vector<std::shared_ptr<Cell>>> _cells;	// pointer to board object;
};

#endif // BOARDITERATOR_H