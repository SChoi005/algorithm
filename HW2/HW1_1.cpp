#include <iostream>
#include <string>

using namespace std;

int main()
{
    string t, s;
    int check = 0;
    getline(cin, t);
    getline(cin, s);

    for (int i = 0; i < t.length(); i++)
        t[i] = tolower(t[i]);
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);

    for (int i = 0; i < s.length(); i++)
    {
        int n = t.find(s[i], check);
        if (n < 0)
        {
            cout << "No" << endl;
            return 0;
        }
        check = n + 1;
    }
    cout << "Yes";
}