#include <iostream>
#include "forward.h"
using namespace std;

struct linkedList{
    ForwardList<int>*  List;
    string transitions;
};

struct AFN{
    string alfabeto;
    ForwardList<linkedList*>* states;
    AFN(string _alfabeto){
        alfabeto = _alfabeto;
        states = new ForwardList<linkedList*>();
    }
};

int main(){
    string alfabeto= "", substring = "";
    AFN afn(alfabeto);
    int t = 0, z = 1;
    cin>>alfabeto;
    cin>>t;
    for(int i=0; i<t; i++){
        cin>>substring;
        for(int j=0; j<substring.size(); j++){
            linkedList* n = new linkedList();
            if (i > 0){
                afn.states->front()->List->push_back(z);
                afn.states->front()->transitions = afn.states->front()->transitions + substring[j];
                j += 1;
            }
            n->List->push_front(z+1);
            n->List->push_front(z);
            n->transitions = n->transitions + substring[j];
            afn.states->push_front(n);
        }
        z = substring.size()+1;
    }
    return 0;
}
