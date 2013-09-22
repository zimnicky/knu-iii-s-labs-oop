#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int uint;

class Matrix
{
private:

    vector<vector<double>> data;

public:
    Matrix(uint x = 0, uint y = 0);
    Matrix(const Matrix &other);
    Matrix(const vector<double> &vector);

    static Matrix E(uint size); // returns identity matrix size*size

    double at(uint x, uint y) const { return data[x][y]; } // returns value of element in [x][y]
    void setValue(uint x, uint y, double value){ data[x][y] = value;}

    void resize(pair<uint, uint> size);
    pair<uint, uint> size() const;

    void addRow(const vector<double> &row); // adds row to the matrix

    Matrix transpose() const; // returns transposed matrix
    Matrix inverse() const; // returns inversed matrix

    Matrix operator*(const Matrix &b) const;
    Matrix operator-(const Matrix &b) const;
};

#endif // MATRIX_H
