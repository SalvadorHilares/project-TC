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
            if (i > 0 && j==0){
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

void push_queue(AFN* afn, int position,char transition, Queue<int>* &queue){
    for(int k=0; k<afn->states[0][position]->transitions.size(); k++)
        if(afn->states[0][position]->transitions[k] == transition)
            queue->enqueue(afn->states[0][position]->List[0][k+1]);
}

bool comprobate_alphabet(string aplhabet, char transition){
    for(char i : aplhabet)
        if (i == transition)
            return true;
    return false;
}

string state_final(AFN* afn, Queue<int>* queue){
    Queue<int>* temp = new Queue<int>(); // PUNTERO AL PUNTERO PARA NO CAMBIAR EL PUNTERO ORIGINAL
    for(int i=0; i<queue->size(); i++)
        temp->enqueue((*queue)[i]);
    while(!temp->is_empty()){
        bool cmp = true;
        int v = temp->dequeue();
        for(int i=0; i<afn->states->size(); i++){
            if(v == afn->states[0][i]->List[0][0]){
                cmp = false;
                break;
            }
        }
        if(cmp)
            return "YES";
    }
    return "NO";
}

string move_BFS(AFN* afn,string s){
    Queue<int>* queue = new Queue<int>();
    string answer = "NO";
    queue->enqueue(afn->states->front()->List->front()); // Inicializamos con el estado 1
    for(char z : s){
        Queue<int>* newQueue = new Queue<int>();
        while(!queue->is_empty()){
            int v = queue->dequeue();
            for(int i=0; i<afn->states->size(); i++) // n grupos de estados
                if(v == afn->states[0][i]->List[0][0]){
                    push_queue(afn,i,z,newQueue);
                    break;
                }
        }
        if(comprobate_alphabet(afn->alphabet,z))
            newQueue->enqueue(afn->states->front()->List->front());
        queue = newQueue;
        answer = state_final(afn, queue);
        if(answer == "YES")
            return answer;
    }
    return answer;   
}

void transition_BFS(AFN* afn){
    int n = 0;
    string s = "";
    ForwardList<string>* answers = new ForwardList<string>();
    Queue<int>* queue = new Queue<int>();
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>s;
        answers->push_back(move_BFS(afn,s));
    }
    for(int i=0; i<answers->size(); i++)
        cout<<(*answers)[i]<<endl;
}

int main(){
    AFN* afn = new AFN();
    afn = createAFN();
    transition_BFS(afn);
    delete afn;
    return 0;
}