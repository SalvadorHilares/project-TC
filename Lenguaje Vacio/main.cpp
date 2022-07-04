#include "forward.h"
#include "queue.h"
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

bool comprobate_terminal(string generator, string s){
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
            if(comprobate_terminal(generator,(*derecha)[j]) && !same(generator,gic->izquierda[0][j]))
                generator = generator + gic->izquierda[0][j];
        }
        if (n == generator.size())
            break;
    }
    if(same(generator,gic->variables[0]))
        return "SI";
    return "NO";
}

string language_empty_queue(GIC* gic){
    
}

int main(){
    GIC* gic = new GIC();
    gic = create_GIC();
    cout<<language_empty(gic)<<endl;
    delete gic;
    return 0;
}