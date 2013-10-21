#include <fstream>
#include <iostream>
#include "matrix.h"

using namespace std;
void print(ofstream &out, Matrix &mat)
{
    for (uint i = 0; i < mat.rowsCount(); i++)
    {
        for (uint j = 0; j < mat.colsCount(); j++)
            out << mat.at(i,j) << " ";
        out << endl;
    }
}

void read(ifstream &in, Matrix &mat)
{
    int count;
    in >> count;
    for (int i = 0; i < count; i++)
    {
        uint r, c;
        int d;
        in >> r >> c >> d;
        mat.at(r,c) = d;

    }
}



int main()
{
    Matrix mat;
    ifstream in("input.txt");
    read(in, mat);
    in.close();
    int i, j;
    mat.getMax(i,j);

    ofstream out("output.txt");

    out << "max is:" << mat.at(i,j) << endl;
    print(out, mat);

    mat.removeRow(i);
    mat.removeColumn(j);


    out << "--------------------------" << endl;
    print(out, mat);
    out.close();
    return 0;
}

