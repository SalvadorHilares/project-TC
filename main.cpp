#include <iostream>
#include "forward.h"
using namespace std;

bool comprobarSubcadena(string alfabeto,string substring){
    for(int i=0; i<substring.size(); i++)
        if(!alfabeto.find(substring[i]))
            return false;
    return true;
}

int main(){
    string alfabeto= "", substring = "";
    ForwardList<string>* T = new ForwardList<string>();
    int t = 0;
    cin>>alfabeto;
    cin>>t;
    for(int i=0; i<t; i++){
        cin>>substring;
        if(comprobarSubcadena(alfabeto,substring) == true)
            T->push_front(substring);
    }
    for(int i=0; i<T->size(); i++)
        cout<<"VALOR "<<i+1<<" DEL FORWARD LIST :"<<(*T)[i]<<endl;
    return 0;
}