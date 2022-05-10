#ifndef __PILHA_H__
#define __PILHA_H__

class elemento {
    public:
        elemento();
        elemento(int);
        ~elemento();

        int GetValue() const;

        elemento* GetPrevious() const;
        void SetPrevious(elemento*);

    private:
        int value;
        elemento* previous;
};

class pilha {
    public:
        pilha();
        ~pilha();

        int top() const;
        void pop();
        void push(int);
        int size() const;
        bool empty() const;

    private:
        int tamanho;
        elemento* Top;
};

#endif