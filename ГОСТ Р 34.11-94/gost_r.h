#include <iostream>
#include <fstream>
#include <memory.h>

using namespace std;

class Gost_r
{
    typedef unsigned char Block[32];
    typedef unsigned char Block32[4];

    unsigned char *buf, result[32];

    unsigned int len;

    int fi(int arg);

    void E_f(unsigned char A[], unsigned char K[], unsigned char R[]);//Функция f в ГОСТ 28147-89
    void E(unsigned char D[], unsigned char K[], unsigned char R[]);
    void A_Y(unsigned char Y[], unsigned char R[]);
    void P_Y(unsigned char Y[], unsigned char R[]);
    void psi_Y(unsigned char arr[]);
    void psi_round(unsigned char arr[], int p);
    void f(unsigned char H[], unsigned char M[], unsigned char newH[]);
public:
    bool read_file(char *fileName);
    bool Show_hash();
    
    void gost_r();
};
