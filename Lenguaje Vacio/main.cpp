#include "forward.h"
#include "queue.h"
#include <string.h>
using namespace std;

struct GIC{
    string terminales;
    string variables;
    ForwardList<string>* derecha;
    ForwardList<char>* izquierda;
    GIC(){
        derecha = new ForwardList<string>();
        izquierda = new ForwardList<char>();
    }
    ~GIC() = default;
};

GIC* create_GIC(){
    GIC* gic = new GIC();
    string terminales = "";
    cin>>terminales;
    gic->terminales = terminales;
    string variables = "";
    cin>>variables;
    gic->variables = variables;
    int r = 0;
    cin>>r;
    for(int a=0; a<r; a++){
        char i = '\0';
        string d = "";
        cin>>i>>d;
        gic->derecha->push_back(d);
        gic->izquierda->push_back(i);
    }
    return gic;
}

bool comprobate(string generator, string s){
    int n = 0;
    for(int i=0; i<s.size(); i++)
        for(int j=0; j<generator.size(); j++)
            if(s[i] == generator[j])
                n++;
        if(n == s.size())
            return true;
    return false;
}

bool same(string generator, char s){
    for(int i=0; i<generator.size(); i++)
        if(generator[i] == s)
            return true;
    return false;
}

string language_empty(GIC* gic){
    string generator = gic->terminales;
    ForwardList<string>* derecha = gic->derecha;
    while(true){
        int n = generator.size();
        for(int j=0; j<derecha->size(); j++){
            if(comprobate(generator,(*derecha)[j]) && !same(generator,gic->izquierda[0][j]))
                generator = generator + gic->izquierda[0][j];
        }
        if (n == generator.size())
            break;
    }
    if(same(generator,gic->variables[0]))
        return "SI";
    return "NO";
}

char** create_matriz(GIC* gic){
    char** matriz = new char*[gic->variables.size()];
    for(int i=0; i<gic->variables.size(); i++)
        matriz[i] = new char[2];
    return matriz;
}

char** insert_matriz(GIC* gic){
    char** matriz = create_matriz(gic);
    for(int i=0; i<gic->variables.size(); i++){
        matriz[i][0] = gic->variables[i];
        matriz[i][1] = 'N';
    }
    return matriz;
}

Queue<char>* insert_queue(GIC* gic, char** matriz){
    Queue<char>* queue = new Queue<char>();
    string generator = gic->terminales;
    ForwardList<string>* derecha = gic->derecha;
    for(int j=0; j<derecha->size(); j++)
        if(comprobate(generator,(*derecha)[j]) && !same(generator,gic->izquierda[0][j])){
            queue->enqueue(gic->izquierda[0][j]);
            for(int k=0; k<gic->variables.size(); k++)
                if(gic->izquierda[0][j] == matriz[k][0])
                    matriz[k][1] = 'S';
        }
    return queue;
}

ForwardList<int>* insert_quantity(GIC* gic){
    ForwardList<int>* quantitys = new ForwardList<int>();
    for(int i=0; i<gic->derecha->size(); i++){
        int n = 0;
        for(int j=0; j<gic->variables.size(); j++){
            for(int k=0; k<gic->derecha[0][i].size(); k++){
                if(gic->derecha[0][i][k] == gic->variables[j])
                    n++;
            }
        }
        quantitys->push_back(n);
        n=0;
    }
    return quantitys;
}

string language_empty_queue(GIC* gic, char** matriz, Queue<char>* queue, ForwardList<int>* quantity){
    ForwardList<string>* derecha = gic->derecha;
    while (!queue->is_empty()){
        char s = queue->dequeue();
        const char* aux = &s;
        for(int i=0; i<derecha->size(); i++){
            const char* r = (*derecha)[i].c_str();
            if (strstr(r,aux))
                (*quantity)[i]--;
            if((*quantity)[i] == 0){
                for(int j=0; j<gic->variables.size(); j++)
                    if(gic->variables[j] == gic->izquierda[0][i] && matriz[j][1] != 'S'){
                        matriz[j][1] = 'S';
                        queue->enqueue(gic->izquierda[0][i]);
                    }
            }
        }
        if(matriz[0][1] == 'S')
            return "SI";
    }
    return "NO";
}

int main(){
    GIC* gic = new GIC();
    gic = create_GIC();
    //cout<<language_empty(gic)<<endl;
    char** matriz = insert_matriz(gic);
    Queue<char>* queue = insert_queue(gic,matriz);
    ForwardList<int>* quantity = insert_quantity(gic);
    cout<<language_empty_queue(gic,matriz,queue, quantity);
    delete gic;
    return 0;
}