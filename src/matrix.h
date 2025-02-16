#ifndef MATRIX_H
#define MATRIX_H

#include <QLIst>

class SquareCell;

class Matrix
{
private:
    int m_rows;
    int m_cols;
    QList<QList<SquareCell *>> m_matrix;
public:
    Matrix(int rows, int columns);
    ~Matrix();

    SquareCell* at(int i, int j);
};

#endif // MATRIX_H
