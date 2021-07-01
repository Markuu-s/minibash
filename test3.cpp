#include <iostream>
#include <string>
using namespace std;

int main(){
    for(int i = 0; i <= 9999; ++i){
        long long x = (long long)i * i;
        string strX = to_string(x);
        while (strX.size() < 8){
            strX = "0" + strX;
        }
        if (stoi(strX.substr(2, 4)) == i){
            cout << i << '\n';
        }
    }
}