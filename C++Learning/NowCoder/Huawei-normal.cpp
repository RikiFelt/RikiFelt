#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void HJ16()
{

}

bool HJ17_isNum(string str)
{
    int length = str.size();
    if (length > 2) return false;
    for (int i = 0; i < length; i++) {
        if ('0' <= str[i] && str[i] <= '9')continue;
        else return false;
    }
    return true;
}

void HJ17()
{
    string word;
    pair<int, int> pos(0, 0);
    while (getline(cin, word, ';')) {
        if (word.empty()) continue;
        string num = word.substr(1);

        if (HJ17_isNum(num)) {
            switch (word[0]) {
                case 'A':
                    pos.first -= stoi(num);
                    break;
                case 'D':
                    pos.first += stoi(num);
                    break;
                case 'W':
                    pos.second += stoi(num);
                    break;
                case 'S':
                    pos.second -= stoi(num);
                    break;
                default:
                    break;
            }
        }
    }
    cout << pos.first << "," << pos.second << endl;
}

bool HJ20_isValidLength(const string& password)
{
    if (password.length() < 8) return false;
    return true;
}

bool HJ20_isValidCategory(const string& password)
{
    int count[4] = { 0 };
    for (int i = 0; i < password.length(); i++) {
        if (isdigit(password[i]))
            count[0] = 1;
        else if (isupper(password[i]))
            count[1] = 1;
        else if (islower(password[i]))
            count[2] = 1;
        else
            count[3] = 1;
    }
    if (count[0] + count[1] + count[2] + count[3] < 3)
        return false;
    else
        return true;
}

bool HJ20_noRepeatedString(const string& password)
{
    int checkLength = password.length() - 3;
    for (int i = 0; i < checkLength; i++) {
        for (int j = i + 1; j < checkLength; j++) {
            if (password.substr(i, 3) == password.substr(j, 3)) {
                return false;
            }
        }
    }
    return true;
}

void HJ20()
{
    string password;
    while (cin >> password) {
        if (HJ20_isValidLength(password)) {
            if (HJ20_isValidCategory(password)) {
                if (HJ20_noRepeatedString(password)) {
                    cout << "OK" << endl;
                    continue;
                }
            }
        }
        cout << "NG" << endl;
    }
}

void HJ26()
{
    string input;
    while (getline(cin, input)) {
        string alphaStr;
        for (const char& c : input) {
            if (isalpha(c)) alphaStr += c;
        }

        stable_sort(alphaStr.begin(), alphaStr.end(),
            [](const char& c1, const char& c2) {return tolower(c1) < tolower(c2); });

        size_t idx = 0;
        for (const char& c : input) {
            if (isalpha(c)) {
                cout << alphaStr[idx++];
            } else {
                cout << c;
            }
        }
        cout << endl;
    }
}

void HJ27()
{

}

void HJ55()
{
    int num;
    while (cin >> num) {
        int count = 0;
        for (int i = 7; i <= num; i++)
            if (i % 7 == 0 || to_string(i).find('7', 0) != string::npos)
                count++;
        cout << count << endl;
    }
}