#include "htree.h"
#include <queue>
#include <memory.h>


using namespace std;

HTree::HTree(const string &str)
{
    int counter[256];
    memset(counter, 0, sizeof counter);

    // count numbers of symbols in string
    for (unsigned int i = 0; i < str.size(); i++)
        counter[str[i]]++;

    priority_queue<pair<int, Node*>> queue;

    //add symbols to the priority queue
    for (int i = 0; i < 255; i++)
        if (counter[i] > 0)
            queue.push(make_pair(-counter[i], new Node(i)));

    // pop two the biggest elements from the queue and merge them
    Node *biggest = queue.top().second;
    int biggestFreq = queue.top().first;
    queue.pop();
    while (!queue.empty())
    {
        Node* biggest2 = queue.top().second;
        int biggestFreq2 = queue.top().first;
        queue.pop();

        Node* parent = new Node();
        parent->left = biggest;
        parent->right = biggest2;

        queue.push(make_pair(biggestFreq + biggestFreq2, parent));

        biggest = queue.top().second;
        biggestFreq = queue.top().first;
        queue.pop();
    }

    root = biggest;
}


bool HTree::getCode(Node* node, char target, string &code)
{
    if (node == nullptr)
        return false;

    if (target == node->symbol)
        return true;

    if (getCode(node->left, target, code))
        code.push_back('0');
    else if (getCode(node->right, target, code))
            code.push_back('1');
    else return false;

    return true;

}

string HTree::getCode(char c)
{
    string res;
    getCode(root, c, res);

    for (unsigned int i = 0; i < res.size() / 2; i++)
        swap(res[i], res[res.size() - i - 1]);

    return res;
}


char HTree::getChar(const string &code) throw(const char *)
{
    Node* node = root;
    for (unsigned int i = 0; i < code.size(); i++)
    {
        if (node == nullptr) throw "There are no symbols with this code";

        if (code[i] == '0')
            node = node->left;
        else if (code[i] == '1')
            node = node->right;
        else
            throw "Wrong character";
    }

    if (node == nullptr) throw "There are no symbols with this code";

    return node->symbol;
}
