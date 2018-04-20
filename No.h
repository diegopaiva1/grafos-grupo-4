#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

class No
{
    private:
        int id;
        No *proximoNo;
    public:
        No(int id);
        No();
        ~No();
        int getId();
        void setId(int id);
        void setProximoNo(No *no);
        No* getProximoNo();
};

#endif // NO_H_INCLUDED
