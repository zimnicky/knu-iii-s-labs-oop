#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef unsigned int uint;

class Matrix
{
public:
    struct Node
    {
    friend class Matrix;
    private:
        uint row;
        uint col;
        int data;
        Node *right;
        Node *bottom;
    public:
        Node(uint r, uint c, uint value = 0):row(r),col(c),data(value),
            right(nullptr), bottom(nullptr){}
    };
private:
    friend class Node;
    vector<Node*> rows;
    vector<Node*> cols;

    /*inserts node to the column & returns it
     *if node = nullptr, creates it
     */
    Node* insertToColumn(uint row, uint col, Node* node = nullptr);

    /*inserts node to the row & returns it
     *if node = nullptr, creates it
     */
    Node* insertToRow(uint row, uint col, Node* node = nullptr);

    Node* getNode(uint r, uint c);  // returns node with indices r & c
public:
    Matrix();
    uint rowsCount() const { return rows.size();}
    uint colsCount() const {return cols.size();}
    int& at(uint row, uint col);
    void getMax(int &row, int &col); // returns maximum element's indices or (-1,-1) if matrix is empty
    void removeRow(uint row);
    void removeColumn(uint col);
};

#endif // MATRIX_H
