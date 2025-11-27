#include <iostream>
using namespace std;

class Person{ 
    public: 
        string name; 
        string nationality; 
        
    void greet(){
        cout<<"Hello "<<name<<endl;
        cout<<"Nice to meet my "<<nationality<<" friend!"<<endl;
    } 
};


int main(){
    Person p; 
    
    p.name="Souvik"; 
    p.nationality="Bangladeshi"; 
    p.greet();

    return 0;
}
