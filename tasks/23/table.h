#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <ostream>

using namespace std;


class Table
{
public:
    enum class CellType{INT, SHORT, CHAR, STRING, BOOL, DOUBLE};
private:
    struct Cell
    {
        int intData;
        short shortData;
        char charData;
        string stringData;
        double doubleData;
        bool boolData;
        void changeType(CellType from, CellType to);
    };
    vector<vector<Cell>> cells;
    vector<CellType> columsTypes;

public:
    Table();
    void output(ostream &out);
    void addColumns(unsigned int count, CellType type);
    void addRows(unsigned int count);

    CellType columnType(unsigned int num);
    void setColumnType(unsigned int num, CellType type);

    void editCell(unsigned int i, unsigned int j, const string &data);
    string getCellData(unsigned int i, unsigned int j);

    string getTypeStr(CellType type);   // cellType to string

    void removeRow(unsigned int num);
    void removeColumn(unsigned int num);

    void save(ostream &out);
    void load(istream &in);

};

#endif // TABLE_H
