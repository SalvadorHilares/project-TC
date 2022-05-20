#include "forward.h"
#include "queue.h"
using namespace std;

struct linkedList{
    ForwardList<int>*  List;
    string transitions;
    linkedList(){
        List = new ForwardList<int>();
    }
};

struct AFN{
    string alphabet;
    ForwardList<linkedList*>* states;
    AFN(string _alphabet){
        alphabet = _alphabet;
        states = new ForwardList<linkedList*>();
    }
    AFN(){
        states = new ForwardList<linkedList*>();
    }
};

AFN* createAFN(){
    string alphabet= "", substring = "";
    int t = 0, z = 1;
    cin>>alphabet;
    cin>>t;
    AFN* afn = new AFN(alphabet);
    for(int i=0; i<t; i++){
        cin>>substring;
        for(int j=0; j<substring.size(); j++){
            linkedList* n = new linkedList();
            if (i > 0){
                afn->states->front()->List->push_back(++z);
                afn->states->front()->transitions = afn->states->front()->transitions + substring[j];
                j += 1;
            }
            n->List->push_front(z+1);
            n->List->push_front(z);
            n->transitions = n->transitions + substring[j];
            afn->states->push_back(n);
            z++;
        }
    }
    return afn;
}

// queue -> enqueue(afn->states[0][i]);

bool comprobate_alphabet(string aplhabet, char transition){
    for(char i : aplhabet)
        if (i == transition)
            return true;
    return false;
}

void createQueue(AFN* afn){
    Queue<int>* eliminated = new Queue<int>(); // cola de eliminados
    for(int i=0; i<afn->states->size(); i++) // 3 grupos de estados
        for(int j=0; j<afn->states[0][i]->List->size(); j++)
            if(!comprobate_alphabet(afn->alphabet,afn->states[0][i]->transitions[j])){
                eliminated->enqueue(afn->states[0][i]->List[0][j]);
            }
}

int main(){
    AFN* afn = new AFN();
    afn = createAFN();
    createQueue(afn);
    delete afn;
    return 0;
}