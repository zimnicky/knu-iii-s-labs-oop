#include "matrix.h"
#include <iostream>

Matrix::Matrix()
{
}

Matrix::Node* Matrix::insertToColumn(uint row, uint col, Node* node)
{
    Node* currNode = cols[col];
    Node* prevNode = nullptr;

    while (currNode != nullptr && row < currNode->row)
    {
        prevNode = currNode;
        currNode = currNode->bottom;
    }

    if (currNode == nullptr || row > currNode->row) // element doesn't exists
    {
        if (node == nullptr)
            node = new Node(row, col);
        if (prevNode == nullptr) // element's row is less than first in the column
        {
            node->bottom = cols[col];
            cols[col] = node;
        }
        else
        {
            node->bottom = prevNode->bottom;
            prevNode->bottom = node;
        }
        return node;
    }

    return currNode;
}

Matrix::Node* Matrix::insertToRow(uint row, uint col, Node *node)
{
    Node* currNode = rows[row];
    Node* prevNode = nullptr;

    while (currNode != nullptr && col < currNode->col)
    {
        prevNode = currNode;
        currNode = currNode->right;
    }

    if (currNode == nullptr || col > currNode->col) // element doesn't exists
    {
        if (node == nullptr)
            node = new Node(row, col);
        if (prevNode == nullptr) // element's column is less than first in the row
        {
            node->right = rows[row];
            rows[row] = node;
        }
        else
        {
            node->right = prevNode->right;
            prevNode->right = node;
        }
        return node;
    }

    return currNode;
}

Matrix::Node* Matrix::getNode(uint r, uint c)
{
    if (rows.size() <= r)
        rows.resize(r+1);
    if (cols.size() <= c)
        cols.resize(c+1);

    Node* node = insertToRow(r,c); // if node doesn't exists, creates it
    insertToColumn(r, c, node);       // inserts new node, or do nothing, if it exists

    return node;
}

int& Matrix::at(uint row, uint col)
{
    return getNode(row, col)->data;
}


void Matrix::getMax(int &row, int &col)
{
    row = -1;
    col = -1;
    for (auto i = rows.begin(); i != rows.end(); i++)
    {
        Node* el = *i;
        while (el != nullptr)
        {
            if (row == -1 || at(row, col) < el->data)
            {
                row = el->row;
                col = el->col;
            }
            el = el->right;
        }
    }
}

void Matrix::removeRow(uint row)
{
    //remove links in columns
    for (uint i = 0; i < cols.size(); i++)
        if (cols[i] != nullptr)
        {
            Node* node = cols[i];
            Node* prev = nullptr;

            //find element
            while (node != nullptr && row < node->row)
            {
                prev = node;
                node = node->bottom;
            }

            //remove element
            if (node != nullptr && row == node->row)
            {
                if (prev == nullptr)
                    cols[i] = node->bottom;
                else
                    prev->bottom = node->bottom;
            }
        }

    //remove row
    Node* node = rows[row];
    Node* prev;
    while (node != nullptr)
    {
        prev = node;
        node = node->right;
        delete prev;
    }

    //replace pointers & indices
    for (uint i = row; i < rows.size() - 1; i++)
    {
        rows[i] = rows[i+1];
        node = rows[i];
        while (node != nullptr)
        {
            node->row = i;
            node = node->right;
        }
    }

    rows.resize(rows.size() - 1);
}

void Matrix::removeColumn(uint col)
{
    //remove links in rows
    for (uint i = 0; i < rows.size(); i++)
        if (rows[i] != nullptr)
        {
            Node* node = rows[i];
            Node* prev = nullptr;

            //find element
            while (node != nullptr && col < node->col)
            {
                prev = node;
                node = node->right;
            }

            //remove element
            if (node != nullptr && col == node->col)
            {
                if (prev == nullptr)
                    cols[i] = node->right;
                else
                    prev->right = node->right;
            }
        }

    //remove row
    Node* node = cols[col];
    Node* prev;
    while (node != nullptr)
    {
        prev = node;
        node = node->bottom;
        delete prev;
    }

    //replace pointers & indices
    for (uint i = col; i < cols.size() - 1; i++)
    {
        cols[i] = cols[i+1];
        node = cols[i];
        while (node != nullptr)
        {
            node->col = i;
            node = node->bottom;
        }
    }

    cols.resize(cols.size() - 1);
}




