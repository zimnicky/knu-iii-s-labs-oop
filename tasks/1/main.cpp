#include <fstream>
#include "task.h"

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    Task task;
    task.read(in);
    in.close();
    out << task.solve() << endl;
    out.close();
    return 0;
}
