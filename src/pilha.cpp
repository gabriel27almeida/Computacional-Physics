#include "pilha.h"
#include <iostream>

elemento::elemento(){;}

elemento::elemento(int n){
    value = n;
}

elemento::~elemento(){}

int elemento::GetValue() const{
    return value;
}

elemento* elemento::GetPrevious() const{
    return previous;
}

void elemento::SetPrevious(elemento* adr){
    previous = adr;
}


///////////////////////////
////////// PILHA


pilha::pilha(){
    tamanho = 0;
}

pilha::~pilha(){ 
    int n = tamanho;
	while(n--) this->pop();
}

int pilha::top() const{
    return Top->GetValue();
}

void pilha::pop(){
    if (tamanho == 0){
        std::cout << "[pilha::pop()] BAD REQUEST\n";
        return;
    }

    elemento* anterior = Top->GetPrevious();

	delete Top;
    
    Top = anterior;
    tamanho--;
}

void pilha::push(int n){
    elemento* e = new elemento(n);
    
    if (tamanho != 0) e->SetPrevious(Top);
    Top = e;
    tamanho++;
}

int pilha::size() const{
    return tamanho;
}

bool pilha::empty() const{
    return tamanho == 0;
}
