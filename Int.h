#ifndef HIGH_H
#define HIGH_H
#define NUMMAXBIT 32768
#define endl putc('\n')

typedef struct Int{
    int len;
    int isNeg;
    char data[NUMMAXBIT];
}Int;

struct 
{



    Int (*Add)(Int a,Int b);
    Int (*Sub)(Int a,Int b);
    Int (*Mul)(Int a,Int b);
    Int (*Div)(Int a,Int b);
    Int (*Mod)(Int a,Int b);
    Int (*Pow)(Int a,Int b);
    
    Int (*FromInt32)(int n);
    Int (*FromInt64)(long long n);
    Int (*FromString)(char *s);
    
    int (*ToInt32)(Int a);
    long long (*ToInt64)(Int a);
    char* (*ToString)(Int a);

    int (*Compare)(Int a,Int b);

    void (*Print)(Int a);
}IntOperator;

Int _Zero();

Int _FromInt32(int n);

Int _FromInt64(long long n);

Int _FromString(char *s);

void _PrintInt(Int a);

int _ToInt32(Int a);

long long _ToInt64(Int a);

char* _ToString(Int a);

Int _Add(Int a,Int b);

Int _Sub(Int a,Int b);

int _Compare(Int a,Int b);

Int _Mul(Int a,Int b);

Int _Div(Int a,Int b);

Int _Mod(Int a,Int b);


Int _Pow(Int a,Int b);

#endif