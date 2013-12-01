#include "menu.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

void menu()
{
   Table table;
   bool finished = false;
   string command;
   while (!finished)
   {
       cin >> command;
       std::transform(command.begin(), command.end(), command.begin(), ::toupper);
       if (command == "SHOW")
           table.output(cout);
       else if (command == "ADD_ROWS")
       {
           unsigned int t;
           cin >> t;
           table.addRows(t);
       }
       else if (command == "ADD_COLS")
       {
           unsigned int t;
           cin >> t;
           Table::CellType type = getType();
           table.addColumns(t, type);
       }
       else if (command == "EDIT")
       {
           unsigned int i;
           char j;
           cin >> i >> j;
           i--;
           j = toupper(j);
           if (j >= 'A' && j <= 'Z')
               j -= 'A';
           string data;
           cout << "Write new value" << endl << "<< ";
           cin >> data;
           table.editCell(i,j,data);
       }
       else if (command == "REMOVE_ROW")
       {
           unsigned int t;
           cin >> t;
           table.removeRow(t-1);
       }
       else if (command == "REMOVE_COLUMN")
       {
           char t;
           cin >> t;
           t = toupper(t);
           if (t >= 'A' && t <= 'Z')
               table.removeColumn(t - 'A');
           else
               table.removeColumn(t);
       }
       else if (command == "SAVE")
       {
           ofstream f("saved");
           table.save(f);
           f.close();
       }
       else if (command == "LOAD")
       {
           ifstream f("saved");
           table.load(f);
           f.close();
       }
       else if (command == "FINISH")
       {
           finished = true;
       }
       else if (command == "CHANGE_TYPE")
            {
                char j;
                cin >> j;
                j = toupper(j);
                if (j >= 'A' && j <= 'Z')
                    j -= 'A';
                table.setColumnType(j, getType());
       }
       else {
           cout << "Undefined command" << endl;
       }
   }
}

Table::CellType getType()
{
    cout << "Choose table:" << endl;
    cout << "0 - int" << endl << "1 - short" << endl << "2 - char" << endl
         << "3 - string" << endl << "4 - bool" << endl << "5 - double" << endl;
    cout << "<< ";
    int t;
    cin >> t;
    return Table::CellType(t);
}
