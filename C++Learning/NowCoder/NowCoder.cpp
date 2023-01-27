#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    return 0;
}

void test1()
{
    int first, next;
    while (cin >> first >> next) {
        cout << first + next << endl;
    }
}

#if 0
void test1_2()
{
    int first, next;
    while (scanf("%d %d", &first, &next) != EOF) {
        printf("%d\n", first + next);
    }
}
#endif

void text2()
{
    int count, first, next;
    cin >> count;
    while (cin >> first >> next) {
        cout << first + next << endl;
    }
}

void test3()
{
    int first, next;
    while (cin >> first >> next) {
        if (0 == first + next) break;
        cout << first + next << endl;
    }
}

void test4()
{
    int count, append, sum;
    cin >> count;
    while (0 != count) {
        sum = 0;
        for (int index = 0; index < count; index++) {
            cin >> append;
            sum += append;
        }
        cout << sum << endl;
        cin >> count;
    }
}

void test5()
{
    int row, count;
    int append, sum;
    cin >> row;
    while (0 < row) {
        cin >> count;
        sum = 0;
        for (int index = 0; index < count; index++) {
            cin >> append;
            sum += append;
        }
        cout << sum << endl;
        row--;
    }
}

void test6()
{
    int count, append, sum;
    while (cin >> count) {
        sum = 0;
        for (int index = 0; index < count; index++) {
            cin >> append;
            sum += append;
        }
        cout << sum << endl;
    }
}

void test7()
{
    int append, sum;
    sum = 0;
    while (cin >> append) {
        sum += append;
        if (cin.get() == '\n') {
            cout << sum << endl;
            sum = 0;
        }
    }
}

void test7_2()
{
    string line,append;
    int sum = 0;
    while (getline(cin, line)) {
        stringstream s(line);
        while (getline(s, append, ' ')) {
            sum += stoi(append);
        }
        cout << sum << endl;
    }
}

void test8()
{
    vector<string> words;
    int count;
    cin >> count;
    string word;
    while (cin >> word) {
        words.emplace_back(word);
    }
    sort(words.begin(), words.end());
    int idx = 1;
    int length = words.size();
    for (const string& w : words) {
        cout << w;
        if (idx != length) {
            idx++;
            cout << ' ';
        }
    }
}

void test9()
{
    vector<string> words;
    string line,word;
    while (getline(cin, line)) {
        stringstream s(line);
        while (getline(s, word, ' ')) {
            words.emplace_back(word);
        }
        sort(words.begin(), words.end());
        int idx = 1;
        int length = words.size();
        for (const string& w : words) {
            cout << w;
            if (idx != length) {
                idx++;
                cout << ' ';
            }
            else {
                cout << endl;
            }
        }
        words.clear();
    }
}


void test10()
{
    vector<string> words;
    string line,word;
    while (getline(cin, line)) {
        stringstream s(line);
        while (getline(s, word, ',')) {
            words.emplace_back(word);
        }
        sort(words.begin(), words.end());
        int idx = 1;
        int length = words.size();
        for (const string& w : words) {
            cout << w;
            if (idx != length) {
                idx++;
                cout << ',';
            } else {
                cout << endl;
            }
        }
        words.clear();
    }
}

