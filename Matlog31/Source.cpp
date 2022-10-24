#include<iostream>
#include<string>

using namespace std;

string Operation(string str);
string Parsing(string str);

int main()
{
    string l;
    getline(cin, l);
    cout << Operation(l);
    return 0;
}

string brackkiller(string str) {
    string s = "";
    for (char i : str)
    {
        if ((i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9') || i == '\'')
            s += i;
    }
    return s;
}
string Operation(string str) {
    int process = 0;
    string l = str;
    for (int i = 0; i < str.size() - 1; i++) {
        if (str[i] == '-' && str[i + 1] == '>' || str[i] == '|' || str[i] == '&' || str[i] == '!')
            process = 1;
    }
    if (process == 1)
    {
        l = '(' + Parsing(str) + ')';
        return l;
    }
    else return brackkiller(str);
}

string Parsing(string str) {
    if (str[0] == '(' && str[str.size() - 1] == ')')
    {
        str.erase(str.size() - 1, 1);
        str.erase(0, 1);
    }
    int ind = -1, brack = 0, max = 100000;
    for (int i = 0; i < str.size() - 1; i++) {
        if (str[i] == '-' && str[i + 1] == '>') {
            if (brack < max) {
                max = brack;
                ind = i;
            }
        }
        if (str[i] == '|') {
            if (brack + 1 <= max) {
                max = brack + 1;
                ind = i;
            }
        }
        if (str[i] == '&') {
            if (brack + 2 <= max) {
                max = brack + 2;
                ind = i;
            }
        }
        if (str[i] == '!') {
            if (brack + 3 < max) {
                max = brack + 3;
                ind = i;
            }
        }
        if (str[i] == '(')
            brack += 4;
        if (str[i] == ')')
            brack -= 4;
    }
    string answ = "", interim = "", interim2 = "";
    if (str[ind] == '-' && str[ind + 1] == '>')
    {
        interim = str.substr(0, ind);
        interim2 = str.substr(ind + 2);
        answ = "->," + Operation(interim) + "," + Operation(interim2);
    }
    if (str[ind] == '|')
    {
        interim = str.substr(0, ind);
        interim2 = str.substr(ind + 1);
        answ = "|," + Operation(interim) + "," + Operation(interim2);
    }
    if (str[ind] == '&')
    {
        interim = str.substr(0, ind);
        interim2 = str.substr(ind + 1);
        answ = "&," + Operation(interim) + "," + Operation(interim2);
    }
    if (str[ind] == '!')
    {
        interim = str.substr(ind + 1);
        answ = "!" + Operation(interim);
    }
    string l = "";

    for (int i = 0; i < answ.size(); i++)
    {
        if (answ[i] != ' ' && answ[i] != '\r' && answ[i] != '\t')
            l += answ[i];
    }
    return l;
}