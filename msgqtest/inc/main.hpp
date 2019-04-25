#ifndef _MAIN_HPP_
#define _MAIN_HPP_


template <typename T> class A{
public:
    int a;
    int b;
    T c;

    void printval()
    {
        printf("a %d b %d c %d\n",a,b,(int)c);
    }

};


class DerivedA: public A<int>{


};






#endif
