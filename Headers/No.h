#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

class No
{
    private:
        int id;
    public:
        No(int id);
        No();
        ~No();
        int getId();
        void setId(int id);
        bool ehIgualA(No *no);
};

#endif // NO_H_INCLUDED
