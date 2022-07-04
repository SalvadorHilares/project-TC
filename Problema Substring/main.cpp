#include "forward.h"
#include "queue.h"
#include "double.h"
using namespace std;

struct linkedList{
    ForwardList<string>*  List;
    string transitions;
    linkedList(){
        List = new ForwardList<string>();
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
    ~AFN() = default;
};

struct AFD{
    string alphabet;
    DoubleList<string>*** transitions;
    DoubleList<DoubleList<string>*>* states_final;
    int filas;
    int columnas;
    AFD(){
        states_final = new DoubleList<DoubleList<string>*>();
    }
    AFD(string _alphabet){
        this->alphabet = _alphabet;
        states_final = new DoubleList<DoubleList<string>*>();
    }
    ~AFD() = default;
};

AFN* createAFN(){
    string alphabet= "", substring = "", state = "";
    int t = 0, z = 1;
    cin>>alphabet;
    cin>>t;
    AFN* afn = new AFN(alphabet);
    for(int i=0; i<t; i++){
        cin>>substring;
        for(int j=0; j<substring.size(); j++){
            linkedList* n = new linkedList();
            if (i > 0 && j==0){
                z = z + 1;
                afn->states->front()->List->push_back(to_string(z));
                afn->states->front()->transitions = afn->states->front()->transitions + substring[j];
                j += 1;
            }
            int b = z + 1;
            n->List->push_front(to_string(b));
            n->List->push_front(to_string(z));
            n->transitions = n->transitions + substring[j];
            afn->states->push_back(n);
            z++;
        }
    }
    return afn;
}

void display(AFN* afn){
    for(int i=0; i<afn->states->size(); i++){
        for(int j=0; j<afn->states[0][i]->List->size(); j++){
            cout<<afn->states[0][i]->List[0][j]<<" -> ";
        }
        cout<<"X";
        cout<<endl;
    }
}

void push_queue(AFN* afn, int position,char transition, Queue<string>* &queue){
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

string state_final_queue(AFN* afn, Queue<string>* queue){
    Queue<string>* temp = new Queue<string>(); // PUNTERO AL PUNTERO PARA NO CAMBIAR EL PUNTERO ORIGINAL
    for(int i=0; i<queue->size(); i++)
        temp->enqueue((*queue)[i]);
    while(!temp->is_empty()){
        bool cmp = true;
        string v = temp->dequeue();
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
    Queue<string>* queue = new Queue<string>();
    string answer = "NO";
    queue->enqueue(afn->states->front()->List->front()); // Inicializamos con el estado 1
    for(char z : s){
        Queue<string>* newQueue = new Queue<string>();
        while(!queue->is_empty()){
            string v = queue->dequeue();
            for(int i=0; i<afn->states->size(); i++) // n grupos de estados
                if(v == afn->states[0][i]->List[0][0]){
                    push_queue(afn,i,z,newQueue);
                    break;
                }
        }
        if(comprobate_alphabet(afn->alphabet,z))
            newQueue->enqueue(afn->states->front()->List->front());
        queue = newQueue;
        answer = state_final_queue(afn, queue);
        if(answer == "YES")
            return answer;
    }
    return answer;   
}

void transition_BFS(AFN* afn){
    int n = 0;
    string s = "";
    DoubleList<string>* answers = new DoubleList<string>();
    Queue<int>* queue = new Queue<int>();
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>s;
        answers->push_back(move_BFS(afn,s));
    }
    for(int i=0; i<answers->size(); i++)
        cout<<(*answers)[i]<<endl;
}

DoubleList<string>*** createMatriz(int n, int m){
    DoubleList<string>*** v = new DoubleList<string>**[n];
    for(int i=0; i<n; i++)
        v[i] = new DoubleList<string>*[m];
    return v;
}

DoubleList<string>* Union_matriz(DoubleList<string>*** matriz,int n, int m, DoubleList<string>* l){
    DoubleList<string>* res = new DoubleList<string>();
    for(int j=0; j<l->size(); j++)
        for(int i=0; i<n; i++)
            if(matriz[i][0][0][0] == (*l)[j])
                for(int z=0; z<matriz[i][m]->size(); z++)
                    res->push_back(matriz[i][m][0][z]);
    return res;
}

bool same(DoubleList<string>* n, DoubleList<string>* m){
    if(n->size() != m->size())
        return false;
    for(int i=0; i<n->size(); i++)
        if((*n)[i] != (*m)[i])
            return false;
    return true;
}

bool repeat_state(DoubleList<DoubleList<string>*>* n, DoubleList<string>* state){
    for(int i=0; i<n->size(); i++)
        if(same(n[0][i],state))
            return true;
    return false;
}

void final(AFN* afn,DoubleList<string>* c, DoubleList<DoubleList<string>*>*& f){
    for(int j=0; j<c->size(); j++){
        bool cmp = true;
        for(int i=0; i<afn->states->size(); i++)
            if(afn->states[0][i]->List[0][0] == (*c)[j]){
                cmp = false;
                break;
            }
        if(cmp)
            f->push_back(c);
    }
}

AFD* convert_AFN_to_AFD(AFN* afn){
    AFD* afd = new AFD(afn->alphabet);
    int f = afn->states->size(), c = afn->alphabet.size()+1;
    DoubleList<string>*** table_afnd = createMatriz(f,c);
    for(int i=0; i<afn->alphabet.size(); i++){
        for(int j=0; j<f; j++){
            DoubleList<string>* n = new DoubleList<string>();
            for(int z=0; z<afn->states[0][j]->transitions.size(); z++)
                if(afn->states[0][j]->transitions[z] == afn->alphabet[i])
                    n->push_back(afn->states[0][j]->List[0][z+1]);
            if(j==0)
                n->push_front("1");
            DoubleList<string>* r = new DoubleList<string>();
            r->push_back(afn->states[0][j]->List->front());
            table_afnd[j][0] = r;
            table_afnd[j][i+1] = n;
        }
    }
    DoubleList<DoubleList<string>*>* states = new DoubleList<DoubleList<string>*>();
    DoubleList<DoubleList<string>*>* finals = new DoubleList<DoubleList<string>*>();
    for(int i=1; i<c; i++){
        if(table_afnd[0][i]->size() > 1){
            DoubleList<string>* p = new DoubleList<string>();
            for(int j=0; j< table_afnd[0][i]->size(); j++)
                p->push_back(table_afnd[0][i][0][j]);
            states->push_back(p);
            final(afn,p, finals);
        }
    }
    DoubleList<DoubleList<string>*>* trans = new DoubleList<DoubleList<string>*>();
    for(int i=0; i<states->size(); i++){
        for(int z=1; z<c; z++){
            DoubleList<string>* n = new DoubleList<string>();
            n = Union_matriz(table_afnd,f, z, states[0][i]);
            if(!repeat_state(states,n) && n->size()>1){
                states->push_back(n);
                final(afn,n, finals);
            }
            trans->push_back(n);
        }
    }
    DoubleList<string>*** table_afd = createMatriz(states->size()+1,c);
    DoubleList<string>* b = new DoubleList<string>();
    b->push_back("1");
    table_afd[0][0] = b;
    for(int i=1; i<c; i++)
        table_afd[0][i] = table_afnd[0][i];
    int pos = 0;
    for(int i=1; i<states->size()+1; i++){
        table_afd[i][0] = (*states)[i-1]; // FUNCIONA
        for(int z=1; pos<trans->size(); z++){
            table_afd[i][z] = (*trans)[pos];
            pos++;
            if(z/afd->alphabet.size()==1)
                break;
        }
    }
    afd->transitions = table_afd;
    afd->states_final = finals;
    afd->filas = states->size()+1;
    afd->columnas = c;
    return afd;
}


void transiction_AFD(AFD* afd){
    int n = 0, posx = 0, posy = 0;
    string s = "";
    DoubleList<string>* answers = new DoubleList<string>();
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>s;
        DoubleList<string>* state = new DoubleList<string>();
        state->push_back("1");
        bool cmp = true;
        for(int j=0; j<=s.size(); j++){ // RECORREMOS LA CADENA
            if(repeat_state(afd->states_final, state)){ // ESTADO FINAL
                answers->push_back("YES");
                cmp = false;
                break;
            }
            for(int z=0; z<afd->filas; z++){ // BUSCAMOS EN QUE ESTADO SE ENCUENTRA
                if(same(state,afd->transitions[z][0])){
                    state = afd->transitions[z][0];
                    posx = z;
                    break;
                }
            }
            for(int k=0; k<afd->columnas; k++){ // UBICACION ALFABETO
                if(s[j] == afd->alphabet[k]){
                    posy = k+1;
                    break;
                }
            }
            state = afd->transitions[posx][posy];
        }
        if(cmp)
            answers->push_back("NO");
    }
    for(int i=0; i<answers->size(); i++)
        cout<<(*answers)[i]<<endl;
}

bool state_final(AFN* afn,string p){
    for(int i=0; i<afn->states->size(); i++)
        if(p == afn->states[0][i]->List[0][0])
            return false;
    return true;
}

int search_pos(AFN* afn,string state, int pos){
    for(int i=pos; i<afn->states->size(); i++)
        if(afn->states[0][i]->List[0][0] == state)
            return i;
    return -1;
}

void create_array_A(AFN* afn, string s, DoubleList<string>* A){
    string suffix = "", aux = "";
    int pos = 0;
    for(int i=s.size()-1; i>=0; i--){
        suffix = s[i] + suffix;
        for(int j=0; j<afn->states->front()->transitions.size(); j++){
            if(afn->states->front()->transitions[j] == suffix[0] && suffix.size() == 1){
                A->push_back(afn->states->front()->List[0][j+1]);
            }else if(afn->states->front()->transitions[j] == suffix[0]){
                aux = aux + afn->states->front()->transitions[j];
                pos = search_pos(afn, afn->states->front()->List[0][j+1], pos);
                while(true){
                    aux = aux + afn->states[0][pos]->transitions;
                    if(aux.size() == suffix.size() || pos==-1)
                        break;
                    pos = search_pos(afn, afn->states[0][pos]->List[0][1], pos);
                }
                if(aux == suffix)
                    A->push_back(afn->states[0][pos]->List[0][1]);
                aux.clear();
                pos = 0;
            }
        }
    }
}

int repeat_letter(DoubleList<char>* letters,  char s){
    for(int i=0; i<letters->size(); i++)
        if((*letters)[i] == s)
            return i;
    return -1;
}

int search_alphabet(string alphabet, char s){
    for (int i=0; i<alphabet.size(); i++)
        if(alphabet[i] == s)
            return i;
    return -1;
}

AFD* create_AFD_special(AFN* afn){
    // Estados
    DoubleList<DoubleList<string>*>* states = new DoubleList<DoubleList<string>*>();
    DoubleList<DoubleList<string>*>* finals = new DoubleList<DoubleList<string>*>();
    // Posicion y un comprobador
    int pos = 0;
    bool cmp = false;
    // Estado inicial q0
    const string initial_state = afn->states->front()->List->front();
    // Estado P
    string p = "";
    // Cadena S que puede llegar de q0 a p
    string s = "";
    // Creamos todos los estados junto a sus transiciones
    for(int i=0; i<afn->states->front()->transitions.size(); i++){
        s = s + afn->states->front()->transitions[i];
        while(pos < afn->states->size()){
            DoubleList<string>* A = new DoubleList<string>();
            if(!cmp) p = afn->states[0][pos]->List[0][1];
            else p = afn->states->front()->List[0][i+1];
            create_array_A(afn,s,A);
            A->push_front(initial_state);
            if(state_final(afn,p)){
                states->push_back(A);
                finals->push_back(A);
                pos++;
                cmp = true;
                break;
            }
            s = s + afn->states[0][pos+1 - (cmp==true ? 1 : 0)]->transitions;
            if(!repeat_state(states,A)) {
                states->push_back(A);
            }
            if(cmp) cmp = false;
            else pos++;
        }
        s.clear();
    }
    AFD* afd = new AFD(afn->alphabet);
    DoubleList<string>* b = new DoubleList<string>();
    b->push_back("1");
    states->push_front(b);
    DoubleList<string>*** table_afd = createMatriz(states->size(),afn->alphabet.size()+1);
    for(int i=0; i<states->size(); i++){
        table_afd[i][0] = (*states)[i];
        for(int j=1; j<afn->alphabet.size()+1; j++){
            DoubleList<string>* aux = new DoubleList<string>();
            aux->push_back("1");
            table_afd[i][j] = aux;
        }
        for(int k=0; k<(*states)[i]->size(); k++){
            for(int z=0; z<afn->states->size(); z++){
                if(afn->states[0][z]->List[0][0] == (*states)[i][0][k]){
                    for(int m=0; m<afn->states[0][z]->transitions.size(); m++){
                        pos = search_alphabet(afn->alphabet,afn->states[0][z]->transitions[m]);
                        if( pos != -1){
                            table_afd[i][pos+1]->push_back(afn->states[0][z]->List[0][m+1]);
                        }else throw("This character is not found in alphabet");
                    }
                    break;
                }
            }
        }
    }
    afd->columnas = afn->alphabet.size()+1;
    afd->filas = states->size();
    afd->states_final = finals;
    afd->transitions = table_afd;
    return afd;
}

int main(){
    AFN* afn = new AFN();
    afn = createAFN();
    //display(afn);
    //transition_BFS(afn);
    AFD* afd = new AFD();
    afd = convert_AFN_to_AFD(afn);
    //afd = create_AFD_special(afn);
    transiction_AFD(afd);
    delete afn;
    delete afd;
    return 0;
}