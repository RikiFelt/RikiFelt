#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

void HJ7()
{
    float input;
    int output;
    cin >> input;
    output = input + 0.5;
    cout << output << endl;
}

void HJ9()
{
    string input;
    cin >> input;
    unordered_set<char> set;
    for (auto iter = input.rbegin(); iter != input.rend(); iter++) {
        if (set.count(*iter))continue;
        set.insert(*iter);
        cout << *iter;
    }
}

void HJ46()
{
    string input;
    cin >> input;
    int count;
    cin >> count;
    for (int idx = 0; idx < count; idx++) {
        cout << input[idx];
    }
}

void HJ58()
{
    int length, count, num;
    cin >> length >> count;
    vector<int> nums;
    while (cin >> num) {
        nums.emplace_back(num);
    }
    sort(nums.begin(), nums.end());
    for (int idx = 0; idx < count; idx++) {
        cout << nums[idx] << ' ';
    }
}

void HJ101()
{
    int length, num, sortType;
    vector<int> nums;
    cin >> length;
    while (0 < length--) {
        cin >> num;
        nums.emplace_back(num);
    }
    sortType = 0;
    cin >> sortType;
    if (0 == sortType) {
        sort(nums.begin(), nums.end());
    } else {
        sort(nums.rbegin(), nums.rend());
    }
    for (const int output : nums) {
        cout << output << ' ';
    }
}