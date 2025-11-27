#include <fstream>
#include <iostream>
using namespace std;

int main(){
    ofstream out("data.txt"); out<<"Hello, World! I am Souvik and I am learning C++.\n"; out.close();
    ifstream in("data.txt"); string line; getline(in,line);
    cout<<line<<endl; in.close(); return 0;
}
