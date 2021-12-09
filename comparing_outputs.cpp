#include<bits/stdc++.h>

using namespace std;

int main()
{
    string s1 = "P", s2 = "comp", s3 = ".txt", s10, s11;
    for(int i = 1; i <= 9; i++)
    {
        ifstream f1;
        char x = '0'+i;
        string s5 = "";
        s5 += x;
        string s4 = s1+s5;
        s4 = s4+s3;
        string s6 = s2+s5;
        s6 = s6+s3;
        f1.open(s4.c_str());
        ifstream f2;
        f2.open(s6.c_str());
        string s1, s2;
        while(f1>>s10)
        {
            f2>>s11;
            cout<<s10<<" "<<s11<<endl;
            if(s10.size() != s11.size())
            {
                cout<<"i is "<<i<<endl;
                cout<<s10<<" "<<s11<<endl;
                cout<<"diff"<<endl;
                return 0;
            }
            for(int i = 0; i < s10.size(); i++)
            {
                if(s10[i] != s11[i])
                {
                    cout<<"Diff"<<endl;
                    return 0;
                }
            }
        }
        cout<<"fine"<<endl;
    }
    return 0;
}