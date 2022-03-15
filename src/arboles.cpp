#include <iostream>
#include "../include/bintree.h"
#include <queue>
#include <list>
using namespace std;

int sumatoriaLvl(bintree<int>::node n){
    queue<bintree<int>::node> colaNodo;
    colaNodo.push(n);

    int sumatoria = 0;

    while(!colaNodo.empty()){
        bintree<int>::node temp = colaNodo.front();
        colaNodo.pop();
        sumatoria += *temp;

        if(!temp.left().null()){
            colaNodo.push(temp.left());
        }

        if(!temp.right().null()){
            colaNodo.push(temp.right());
        }
    }

    return sumatoria;
}

void pruneLevel(bintree<int> &A, int lvl){
    queue<pair<int, bintree<int>::node> > colaNodo;
    colaNodo.push(pair<int, bintree<int>::node>(0, A.root()));

    int lvlActual = 0;

    while(!colaNodo.empty()){

        pair<int, bintree<int>::node> temp = colaNodo.front();
        colaNodo.pop();

        if(temp.first == (lvl - 1)){
            bintree<int> Izq;
            bintree<int> Der;
            
            if(!temp.second.left().null()){
                A.prune_left(temp.second, Izq);
                int valueIzq = sumatoriaLvl(Izq.root());
                cout << valueIzq << endl;
                A.insert_left(temp.second, valueIzq);
            }

            if(!temp.second.right().null()){
                A.prune_right(temp.second, Der);
                int valueDer = sumatoriaLvl(Der.root());
                A.insert_right(temp.second, valueDer);
            }
            
        } 

        if(temp.first != lvlActual){
            lvlActual++;
        }

        if(!temp.second.left().null()){
            colaNodo.push(pair<int, bintree<int>::node>(lvlActual + 1, temp.second.left()));
        }

        if(!temp.second.right().null()){
            colaNodo.push(pair<int, bintree<int>::node>(lvlActual + 1, temp.second.right()));
        }
    }
}

bool compare(bintree<int>::node t, int &sumatoria, int k){
    if(t.left().null() && t.right().null()){
        return (sumatoria + *t) == k;
    } else {
        sumatoria += *t;

        if(sumatoria > k ){
            return false;
        }

        if(*t > *(t.left()) && *t > *(t.right())){
            return false;
        }

        return compare(t.left(), sumatoria, k) || compare(t.right(), sumatoria, k);
    
    }
}


void caminoSumaX(bintree<int> &T, int k){
    int sumatoria = 0;
    bool existe = compare(T.root(), sumatoria, k);
    if(existe){
        cout << "Hola si existe " << endl;
    } else {

        cout << "Hola no existe " << endl;
    }
}

void prom_nivel(bintree<int> &T, list<float> &P){
    queue<pair<int,bintree<int>::node> > colaNodo;
    colaNodo.push(pair<int, bintree<int>::node>(0, T.root()));

    int lvl = 0;
    float promedio = 0;
    float nodos = 0;

    while(!colaNodo.empty()){
        pair<int, bintree<int>::node> temp = colaNodo.front();
        colaNodo.pop();
        
        //cout << *(temp.second) << " " << temp.first << endl;
        if(lvl != temp.first){
            P.push_back(promedio / nodos);
            lvl++;
            promedio = 0;
            nodos = 0;
        }

        promedio += *(temp.second);
        nodos++;

        if(!temp.second.left().null()){
            colaNodo.push(pair<int, bintree<int>::node>(lvl + 1,temp.second.left()));
        }

        if(!temp.second.right().null()){
            colaNodo.push(pair<int, bintree<int>::node>(lvl + 1,temp.second.right()));
        }
    }

    P.push_back(promedio / nodos);

}



bool comprobarSiSonIguales(bintree<int>::node A, bintree<int>::node B){

    queue<bintree<int>::node> colaNodo;

    bool is_contenido = true;
    colaNodo.push(A);
    colaNodo.push(B);

    while(!colaNodo.empty() && is_contenido == true){
        bintree<int>::node a1 = colaNodo.front();
        colaNodo.pop();
        bintree<int>::node a2 = colaNodo.front();
        colaNodo.pop();

        if(*a1 != *a2){ 
            is_contenido = false;
        }

        if(!a1.left().null()){
            colaNodo.push(a1.left());
        }

        if(!a2.left().null()){
            colaNodo.push(a2.left());
        }

        if(!a1.right().null()){
            colaNodo.push(a1.right());
        }

        if(!a2.right().null()){
            colaNodo.push(a2.right());
        }
    }

    return is_contenido;
}

bool incluido(bintree<int> A, bintree<int> B){

    queue<bintree<int>::node> colaNodo;

    bool contenido = false;
    colaNodo.push(A.root());

    while(!colaNodo.empty() && contenido == false){

        bintree<int>::node temp = colaNodo.front();
        colaNodo.pop();

        contenido = comprobarSiSonIguales(temp, B.root());

        if(!temp.left().null()){
            colaNodo.push(temp.left());
        }

        if(!temp.right().null()){
            colaNodo.push(temp.right());
        }
    }

    return contenido;
}

bool is_recurrent_tree(bintree< int > A){
    queue<bintree<int>::node> colaNodo;

    bool recurrent = true;
    colaNodo.push(A.root());

    while(!colaNodo.empty()){
        bintree<int>::node temp = colaNodo.front();
        colaNodo.pop();

        if(!temp.left().null() && !temp.right().null()){
            if((*temp) != *(temp.left()) + *(temp.right())){
                recurrent = false;
            }
        }
        

        if(!temp.left().null()){
            colaNodo.push(temp.left());
        }

        if(!temp.right().null()){
            colaNodo.push(temp.right());
        }
    }

    return recurrent;
}

void sumadosarboles (bintree<int> A, bintree<int> B, bintree<int> &C){
    C = A;
    
    queue<bintree<int>::node> colaNodo;

    colaNodo.push(C.root());
    colaNodo.push(B.root());

    while(!colaNodo.empty()){
 
        bintree<int>::node a1 = colaNodo.front();
        colaNodo.pop();
        bintree<int>::node a2 = colaNodo.front();
        colaNodo.pop();

        *a1 += *a2;

        if(!a1.left().null()){
            colaNodo.push(a1.left());
        }

        if(!a2.left().null()){
            colaNodo.push(a2.left());
        }

        if(!a1.right().null()){
            colaNodo.push(a1.right());
        }

        if(!a2.right().null()){
            colaNodo.push(a2.right());
        }

        
    }
}

int main(){
    
    bintree<int> Arb(2);
    Arb.insert_left(Arb.root(), 3);
    Arb.insert_right(Arb.root(), 1);
    Arb.insert_right(Arb.root().left(), 8);
    Arb.insert_left(Arb.root().left(), 5);
    Arb.insert_left(Arb.root().left().left(), 8);
    //Arb.insert_left(Arb.root().right(), 5);
    //Arb.insert_right(Arb.root().right(),4);
    //Arb.insert_right(Arb.root().right().left(),4);
    
    
    // Ej 34
    /*for (bintree<int>::preorder_iterator i = Arb.begin_preorder(); i!=Arb.end_preorder(); ++i)
      cout << *i << " ";

    cout << endl;
    
    bintree<int> C;
    sumadosarboles(Arb, Arb, C);
    cout << "Preorden:";

    for (bintree<int>::preorder_iterator i = C.begin_preorder(); i!=C.end_preorder(); ++i)
      cout << *i << " ";

    cout << endl;*/

    /*
    for (bintree<int>::preorder_iterator i = Arb.begin_preorder(); i!=Arb.end_preorder(); ++i)
      cout << *i << " ";

    cout << "Hola" << endl;
    cout << is_recurrent_tree(Arb) << endl;
    */


    //Contenido
    /*for (bintree<int>::preorder_iterator i = Arb.begin_preorder(); i!=Arb.end_preorder(); ++i)
      cout << *i << " ";

    bintree<int> A1(2);
    A1.insert_right(A1.root(), 8);
    A1.insert_left(A1.root(), 1);

    cout << endl;
    cout << incluido(Arb, A1) << endl;*/


    /*cout << "OLA" << endl;

    list<float> P;

    prom_nivel(Arb, P);

    list<float>::iterator it;
    for(it = P.begin(); it != P.end(); ++it){
        cout <<  *it << " ";
    }*/

    //caminoSumaX(Arb, 10);
    
    for (bintree<int>::preorder_iterator i = Arb.begin_preorder(); i!=Arb.end_preorder(); ++i)
      cout << *i << " ";

    pruneLevel(Arb, 2);

    cout << endl;

    for (bintree<int>::preorder_iterator i = Arb.begin_preorder(); i!=Arb.end_preorder(); ++i)
      cout << *i << " ";


}
