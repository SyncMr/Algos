#include <iostream>
#include <iostream>
#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>        // std::fill_n, std::reverse, std::swap
#include <queue>            // Priority Queue
#include <typeinfo>         // typeid
#include <vector>
#include <cmath>            // ciel
#include <cstring>          // memset
#include <functional>       // std::function

using namespace std;

int main()
{
    cout << sizeof(int) << endl;
    cout << sizeof(char) << endl;

    int a = -1;
    if (a)
    {
        cout << "-1 is True" << endl;
    }
    else
    {
        cout << "-1 is False" << endl;
    }
    cout << endl;
    return 0;
}