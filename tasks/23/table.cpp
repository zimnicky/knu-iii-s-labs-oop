#include "table.h"
#include <iomanip>
#include <iostream>

Table::Table()
{
    cells.clear();
    columsTypes.clear();
}

void Table::output(ostream &out)
{
    out <<  setw(10)<< " ";
    for (unsigned int i = 0; i < columsTypes.size(); i++)
        out << setw(10) << char('A' + i);
    out << endl << setw(10) << " ";
    for (unsigned int i = 0; i < columsTypes.size(); i++)
        out << setw(10) << getTypeStr(columsTypes[i]);

    for (unsigned int i = 0; i < cells.size(); i++)
    {
        out << endl << setw(10) << (i + 1);
        for (unsigned int j = 0; j < columsTypes.size(); j++)
        {
            switch (columsTypes[j])
            {
            case CellType::BOOL: out << setw(10) << ((cells[i][j].boolData)?"true":"false"); break;
            case CellType::CHAR: out << setw(10) << cells[i][j].charData; break;
            case CellType::DOUBLE: out << setw(10) << cells[i][j].doubleData; break;
            case CellType::INT: out << setw(10) << cells[i][j].intData; break;
            case CellType::SHORT: out << setw(10) << cells[i][j].shortData; break;
            case CellType::STRING: out << setw(10) << cells[i][j].stringData; break;
            }
        }
    }
    out << endl;
}

string Table::getTypeStr(CellType type)
{
    string res;
    switch (type)
    {
    case CellType::BOOL: res = "bool"; break;
    case CellType::CHAR: res = "char"; break;
    case CellType::DOUBLE: res = "double"; break;
    case CellType::INT: res = "int"; break;
    case CellType::SHORT: res = "short"; break;
    case CellType::STRING: res = "string"; break;
    };

    return res;
}


void Table::addColumns(unsigned int count, CellType type)
{
    columsTypes.resize(columsTypes.size() + count, type);
    for (unsigned int i = 0; i < cells.size(); i++)
        cells[i].resize(columsTypes.size() + count);
}

void Table::addRows(unsigned int count)
{
    cells.resize(cells.size() + count, vector<Cell>(columsTypes.size()));
}

void Table::Cell::changeType(Table::CellType from, Table::CellType to)
{
    switch (from)
    {
    case CellType::BOOL:{
        switch (to)
        {
        case CellType::CHAR: charData = boolData; break;
        case CellType::DOUBLE: doubleData = boolData; break;
        case CellType::INT: intData = boolData; break;
        case CellType::SHORT: shortData = boolData; break;
        case CellType::STRING: stringData = (boolData)?"true":"false"; break;
        default:{};
        };
        break;
    }
    case CellType::CHAR:{
        switch (to)
        {
        case CellType::BOOL: boolData = charData; break;
        case CellType::DOUBLE: doubleData = charData; break;
        case CellType::INT: intData = charData; break;
        case CellType::SHORT: shortData = charData; break;
        case CellType::STRING: stringData = charData; break;
        default:{}
        };
        break;
    }
    case CellType::DOUBLE:{
        switch (to)
        {
        case CellType::CHAR: charData = 0; break;
        case CellType::BOOL: boolData = doubleData; break;
        case CellType::INT: intData = doubleData; break;
        case CellType::SHORT: shortData = doubleData; break;
        case CellType::STRING: stringData = to_string(doubleData); break;
        default:{}
        };
        break;
    }
    case CellType::INT:{
        switch (to)
        {
        case CellType::CHAR: charData = intData; break;
        case CellType::BOOL: boolData = intData; break;
        case CellType::DOUBLE: doubleData = intData; break;
        case CellType::SHORT: shortData = intData; break;
        case CellType::STRING: stringData = to_string(intData); break;
        default:{}
        };
        break;
    }
    case CellType::SHORT:{
        switch (to)
        {
        case CellType::CHAR: charData = shortData; break;
        case CellType::BOOL: boolData = shortData; break;
        case CellType::DOUBLE: doubleData = shortData; break;
        case CellType::INT: intData = shortData; break;
        case CellType::STRING: stringData = to_string(shortData); break;
        default:{}
        };
        break;
    }
    case CellType::STRING:{
        switch (to)
        {
        case CellType::CHAR: charData = (stringData.size() > 0)?stringData[0]:0; break;
        case CellType::BOOL: boolData = (stringData == "true"); break;
        case CellType::DOUBLE: doubleData = atof(stringData.c_str()); break;
        case CellType::INT: intData = atoi(stringData.c_str()); break;
        case CellType::SHORT: shortData =  atoi(stringData.c_str());break;
        default:{}
        };
        break;
    }
    };
}

Table::CellType Table::columnType(unsigned int num)
{
    return columsTypes[num];
}

void Table::setColumnType(unsigned int num, CellType type)
{
    for (unsigned int i = 0; i < cells.size(); i++)
        cells[i][num].changeType(columsTypes[num], type);

    columsTypes[num] = type;
}

void Table::editCell(unsigned int i, unsigned int j, const string &data)
{
    cells[i][j].stringData = data;
    cells[i][j].changeType(CellType::STRING, columsTypes[j]);
}


string Table::getCellData(unsigned int i, unsigned int j)
{
    string res;
    switch (columsTypes[j])
    {
    case CellType::CHAR: res = cells[i][j].charData; break;
    case CellType::BOOL: res = (cells[i][j].boolData)?"true":"false"; break;
    case CellType::DOUBLE: res = to_string(cells[i][j].doubleData); break;
    case CellType::INT: res = to_string(cells[i][j].intData); break;
    case CellType::SHORT: res = to_string(cells[i][j].shortData); break;
    case CellType::STRING: res = cells[i][j].stringData; break;
    default:{}
    };

    return res;
}


void Table::removeRow(unsigned int num)
{
   cells.erase(cells.begin() + num);
}

void Table::removeColumn(unsigned int num)
{
    columsTypes.erase(columsTypes.begin() + num);
    for (unsigned int i = 0; i < cells.size(); i++)
        cells[i].erase(cells[i].begin() + num);
}


void Table::save(ostream &out)
{
    out << cells.size() << " " << columsTypes.size() << endl;
    for (unsigned int i = 0; i < columsTypes.size(); i++)
        out << int(columsTypes[i]) << endl;

    for (unsigned int i = 0; i < cells.size(); i++)
        for (unsigned int j = 0; j < columsTypes.size(); j++)
            out << getCellData(i,j) << endl;
}

void Table::load(istream &in)
{
    int t1, t2;
    in >> t1 >> t2;
    columsTypes.resize(t2);
    cells.resize(t1, vector<Cell>(t2));

    string tmp;

    for (unsigned int i = 0; i < columsTypes.size(); i++)
    {
        int t;
        in >> t;
        columsTypes[i] = CellType(t);
    }

    for (unsigned int i = 0; i < cells.size(); i++)
        for (unsigned int j = 0; j < columsTypes.size(); j++)
        {
            in >> tmp;
            editCell(i, j, tmp);
        }
}
