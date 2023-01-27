#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;
void HJ1()
{
    string word;
    while (cin >> word) {}
    cout << word.length();
}

void HJ2()
{
    unordered_map<char, int> charCountMap;
    string sentence;
    getline(cin, sentence);
    char checkChar;
    cin >> checkChar;
    checkChar = tolower(checkChar);
    for (const char& s : sentence) {
        charCountMap[tolower(s)]++;
    }
    cout << charCountMap[checkChar];
}

void HJ4()
{
    string word;
    string output;
    cin >> word;
    size_t cut = 8;
    while (word.length() > cut) {
        output = word.substr(0, cut);
        cout << output << endl;
        if (word.length() == cut) {
            word.clear();
        }
        else {
            word = word.substr(cut);
        }
    }
    if (word.length()>0) {
        cout << word;
        for ( size_t end = cut - word.length(); end > 0; end--) {
            cout << '0';
        }
    }
}

void HJ4_2()
{
    string word;
    cin >> word;
    word.append( "00000000" );
    size_t rate = 1;
    size_t cut = 8;
    size_t length = word.length();
    while (rate * cut < length) {
        cout << word.substr((rate - 1) * cut, cut) << endl;
        rate++;
    }
}

void HJ5()
{
    int ans = 0;
    string hex;
    cin >> hex;
    reverse(hex.begin(), hex.end());
    for (int idx = 0; idx < hex.size(); idx++) {
        if (hex[idx] >= '0' && hex[idx] <= '9') {
            ans += (hex[idx] - '0') * pow(16, idx);
        } else if (hex[idx] >= 'A' && hex[idx] <= 'F') {
            ans += (hex[idx] - 'A' + 10) * pow(16, idx);
        }
    }
    cout << ans;
}

void HJ6()
{
    int num;
    cin >> num;
    int factor = 2;
    while (factor * factor <= num) {
        if (num % factor == 0) {
            cout << factor << ' ';
            num /= factor;
        } else {
            factor++;
        }
    }
    cout << num;
}

void HJ8()
{
    int count, index, value;
    map<int, int, less<int>> idxMap;
    cin >> count;
    while (count--) {
        cin >> index >> value;
        idxMap[index] += value;
    }
    for (const auto& i : idxMap) {
        cout << i.first << ' ' << i.second << endl;
    }
}

void HJ10()
{
    char singleChar;
    unordered_set<char> charSet;
    while (cin >> singleChar) {
        charSet.insert(singleChar);
    }
    cout << charSet.size();
}

void HJ11_12()
{
    string number;
    cin >> number;
    reverse(number.begin(), number.end());
    cout << number;
}

void HJ13()
{
    string word;
    stack<string> words;
    while (cin >> word) {
        words.push(word);
    }
    while (!words.empty()) {
        cout << words.top() << ' ';
        words.pop();
    }
}

void HJ14()
{
    string word;
    vector<string> words;
    cin >> word;
    while (cin >> word) {
        words.emplace_back(word);
    }
    sort(words.begin(), words.end());
    for (const string& w : words) {
        cout << w << endl;
    }
}

void HJ15()
{
    int num, count = 0;
    cin >> num;
    while (num) {
        if (num & 1) {
            count++;
        }
        num >>= 1;
    }
    cout << count << endl;
}

void HJ21()
{
    string word;
    string original = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" };
    string transformation = { "bcdefghijklmnopqrstuvwxyza222333444555666777788899990123456789" };
    cin >> word;
    int length = word.length();
    for (int idx = 0; idx < length; idx++) {
        cout << transformation[original.find(word[idx])];
    }
}

void HJ22()
{
    int count = 0;
    while (cin >> count && 0 != count) {
        cout << count / 2 << endl;
    }
}

void HJ23()
{

}

void HJ31()
{

}

void HJ34()
{
    string word;
    cin >> word;
    sort(word.begin(), word.end());
    cout << word;
}

void HJ35()
{
    int totalRow = 0;
    int head = 1;
    int next = 1;
    cin >> totalRow;
    for (int row = 1; row <= totalRow; row++) {
        head = head + row - 1;
        cout << head << ' ';
        next = head;
        for (int col = 1; col <= totalRow - row; col++) {
            next = next + col + row;
            cout << next << ' ';
        }
        cout << endl;
    }
}

void HJ53()
{
    int num;
    while (cin >> num) {
        if (num == 1 || num == 2) {
            num = -1;
        } else {
            switch (num % 4) {
                case 3: num = 2; break;
                case 0: num = 3; break;
                case 2: num = 4; break;
                case 1: num = 2; break;
            }
        }
        cout << num << endl;
    }
}

void HJ62()
{
    int num, count = 0;
    while (cin >> num) {
        while (num) {
            if (num & 1) {
                count++;
            }
            num >>= 1;
        }
        cout << count << endl;
        count = 0;
    }
}

void HJ73()
{
    int year, month, date;
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    cin >> year >> month >> date;
    int totalDay = 0;
    if (((year % 100 == 0) && (year % 400 == 0)) ||
            ((year % 100 != 0) && (year % 4 == 0))) {
        days[1] = 29;
    }
    int monthIdx;
    for (monthIdx = 0; monthIdx < month - 1; monthIdx++) {
        totalDay += days[monthIdx];
    }
    totalDay += date;
    days[1] = 28;
    cout << totalDay << endl;
}

void HJ76()
{
    int num;
    cin >> num;
    int first = num * num - (num - 1);
    cout << first;
    for (int idx = 1; idx < num; idx++)
        cout << '+' << first + 2 * idx;
    cout << endl;
}

void HJ81()
{
    string shortS, longS;
    bool res;
    while (cin >> shortS >> longS) {
        unordered_set<char> set;
        for (char c : longS) {
            set.insert(c);
        }
        res = true;
        for (char c : shortS) {
            if (!set.count(c)) {
                res = false;
                break;
            }
        }

        //boolalpha操纵符改变布尔值格式
        cout << boolalpha << res << endl;
    }
}

void HJ86()
{
    int num, count = 0, maxCount = 0;
    while (cin >> num) {
        while (num) {
            if (num & 1) {
                count++;
                maxCount = max(count, maxCount);
            } else {
                count = 0;
            }
            num >>= 1;
        }
        cout << maxCount << endl;
        count = 0;
        maxCount = 0;
    }
}

void HJ99()
{
    int num = 0, count = 0;
    string origin, square;
    cin >> num;
    for (int i = 0; i <= num; i++) {
        //仅对个位数符合条件的数执行自守数的判断
        if ((i % 10 == 0) || (i % 10 == 1) || (i % 10 == 5) || (i % 10 == 6)) {
            origin = to_string(i);
            square = to_string(i * i);
            if (square.substr(square.length() - origin.length()) == origin)
                count++;
        }
    }
    cout << count << endl;
}

void HJ100()
{
    int count;
    cin >> count;
    int sum = 2 * count + 3 * count * (count - 1) / 2;
    cout << sum << endl;
}