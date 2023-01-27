#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

void HJ3()
{
    set<int> numSet;
    int num;
    cin >> num;
    while (cin >> num) {
        numSet.insert(num);
    }
    for (const int n : numSet) {
        cout << n << endl;
    }
}