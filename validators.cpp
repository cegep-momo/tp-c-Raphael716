#include "validators.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool isValidISBN(const string& iRaw) 
{
    string s;
    for (char c : iRaw) {
        if (isdigit(static_cast<unsigned char>(c))) s.push_back(c);
    }
    return s.length() == 10 || s.length() == 13;
}

bool isValidName(const string& iName) 
{
    if (iName.empty()) return false;
    int letters = 0;
    for (unsigned char c : iName) {
        if (isalpha(c) || c >= 128) letters++;
        else if (c==' '||c=='-'||c=='\'') continue;
        else if ((unsigned)c < 32) return false;
    }
    return letters > 0;
}

bool isValidUserId(const string& iUserId) 
{
    if (iUserId.size() < 4) return false;
    string prefix = iUserId.substr(0,3);
    string digits = iUserId.substr(3);
    for (auto &c : prefix) c = toupper(static_cast<unsigned char>(c));
    if (prefix != "USR") return false;
    if (digits.empty()) return false;
    for (char c : digits) if (!isdigit(static_cast<unsigned char>(c))) return false;
    return true;
}

bool isNonEmptyTitle(const string& iTitle) 
{
    return !iTitle.empty();
}
