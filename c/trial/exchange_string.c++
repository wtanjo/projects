#include <iostream>
#include <string>
using namespace std;
#define N 100

void exchange_string(string &r1, string &r2);

int main() {
    string s1 = "Shanghai";
    string s2 = "Beijing";
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    exchange_string(s1, s2);
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    return 0;
}

void exchange_string(string &r1, string &r2) {
    string temp = r1;
    r1 = r2;
    r2 = temp;
}