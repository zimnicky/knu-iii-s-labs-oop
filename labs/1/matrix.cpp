#include "matrix.h"

Matrix::Matrix(uint x, uint y)
{
    data.resize(x);
    for (uint i = 0; i < x; i++)
        data[i].resize(y);
}

Matrix::Matrix(const Matrix &other)
{
    data.resize(other.data.size());
    for (uint i = 0; i < data.size(); i++)
    {
        data[i].resize(other.data[i].size());
        for (uint j = 0; j < data[i].size(); j++)
            data[i][j] = other.data[i][j];
    }
}

Matrix::Matrix(const vector<double> &vector)
{
    data.clear();
    data.push_back(vector);
}

void Matrix::resize(pair<uint, uint> size)
{
    data.resize(size.first);
    for (uint i = 0; i < size.first; i++)
        data[i].resize(size.second);
}

pair<uint, uint> Matrix::size() const
{
    int x = data.size();
    if (x == 0)
        return make_pair(0,0);
    return make_pair(x, data[0].size());
}

Matrix Matrix::operator*(const Matrix &b) const
{
    Matrix res(data.size(), b.size().second);

    uint max_inner = b.data.size();
    if (size().second > max_inner)
        max_inner = size().second;

    for (uint row = 0; row < data.size(); row++)
        for (uint col = 0; col < b.size().second; col++)
            for (uint inner = 0; inner < max_inner; inner++)
            {
                if (data[row].size() > inner && b.data.size() > inner)
                    res.data[row][col] += data[row][inner] * b.data[inner][col];
            }

    return res;
}

Matrix Matrix::E(uint size)
{
    Matrix res(size, size);

    for (uint i = 0; i < size; i++)
        res.data[i][i] = 1;

    return res;
}

Matrix Matrix::transpose() const
{
    Matrix res(size().second, data.size());
    for (uint i = 0; i < size().second; i++)
        for (uint j =0; j < data.size(); j++)
            res.data[i][j] = data[j][i];

    return res;
}


Matrix Matrix::inverse() const
{
    double tmp;

    Matrix E = Matrix::E(data.size());

    Matrix copy(*this);

    for (uint k = 0; k < copy.data.size(); k++) // select row
    {
        tmp = copy.data[k][k];
        for (uint j = 0; j < copy.data[k].size(); j++) // div row with selected element
        {
            copy.data[k][j] /= tmp;
            E.data[k][j] /= tmp;
        }

        for (uint i = k + 1; i < copy.data.size(); i++) // make zeros in another rows under selected element
        {
            tmp = copy.data[i][k];
            for (uint j = 0; j < copy.data[k].size(); j++)
            {
                copy.data[i][j] -= copy.data[k][j] * tmp;
                E.data[i][j] -= E.data[k][j] * tmp;
            }
        }
    }

    for (int k = copy.data.size() - 1; k > 0; k--) // select row
        for (int i = k - 1; i >= 0; i--)
        {
            tmp = copy.data[i][k];
            for (uint j = 0; j < copy.data[i].size(); j++) //subtract next row from the current
            {
                copy.data[i][j] -= copy.data[k][j] * tmp;
                E.data[i][j] -= E.data[k][j] * tmp;
            }
        }

    return E;
}


Matrix Matrix::operator-(const Matrix &b) const
{
    Matrix res(*this);
    for (uint i = 0; i < data.size(); i++)
        for (uint j = 0; j < size().second; j++)
            res.data[i][j] -= b.data[i][j];
    return res;
}


void Matrix::addRow(const vector<double> &row)
{
    data.push_back(row);
}
