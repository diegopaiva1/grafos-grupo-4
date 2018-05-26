#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>

class No
{
    private:
        int id;
        bool bipartiteFlag;
    public:
        No(int id);
        No();
        ~No();
        int getId();
        bool getBipartiteFlag();
        void setBipartiteFlag(bool bipartiteFlag);
        void setId(int id);
        bool ehIgualA(No *no);
        bool temBipartiteFlag();
};

#endif // NO_H_INCLUDED
