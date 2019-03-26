#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include <gmp.h>
using namespace std;
mpz_t p,q,p1,q1,n,phi,tmp1,tmp2,d,e,k,r_inv,l,msg,v;
mpz_in()
{

    mpz_init(p);
    mpz_init(q);
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(n);
    mpz_init(phi);
    mpz_init(tmp1);
    mpz_init(tmp2);
    mpz_init(d);
    mpz_init(e);
    mpz_init(k);
    mpz_init(r_inv);
    mpz_init(l);
    mpz_init(msg);
    mpz_init(v);
}
mpz_clr()
{
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(phi);
    mpz_clear(tmp1);
    mpz_clear(tmp2);
    mpz_clear(d);
    mpz_clear(e);
    mpz_clear(k);
    mpz_clear(r_inv);
    mpz_clear(l);
    mpz_clear(msg);
    mpz_clear(v);
}

int prime_num()
{
    mpz_in();
    int PRIMESIZE;
    cout<<"Enter No of bits for P and Q: ";
    cin>>PRIMESIZE;
    do
    {
        char* p_str = new char[PRIMESIZE+1];
        char* q_str = new char[PRIMESIZE+1];
        p_str[0] = '1';
        q_str[0] = '1';
        for(int i=1; i<PRIMESIZE; i++)
        {
            p_str[i] = char((rand()%2)+48);
            q_str[i] = char((rand()%2)+48);
        }
        p_str[PRIMESIZE] = '\0';
        q_str[PRIMESIZE] = '\0';

        mpz_set_str(p,p_str,2);
        mpz_set_str(q,q_str,2);

        mpz_nextprime(p,p);
        mpz_nextprime(q,q);
    }
    while(mpz_cmp(p, q) == 0);


    cout<<endl<<"p = ";
    mpz_out_str(stdout,10,p);

    cout<<endl<<endl<<"q = ";
    mpz_out_str(stdout,10,q);
    //// n=p*q
    mpz_mul(n, p, q);
    cout<<endl<<"n: ";
    mpz_out_str(stdout,10,n);

    //////////////// pi=(p-1)*(q-1)
    mpz_sub_ui(tmp1, p, 1);
    mpz_sub_ui(tmp2, q, 1);
    mpz_mul(phi, tmp1, tmp2);
    cout<<endl<<"phi: ";
    mpz_out_str(stdout,10,phi);
    cout<<endl;

    //////////////
    int cnt=1;
    mpz_set_ui(e,2);
    while(1)
    {
        mpz_gcd(tmp1,e,phi);
        //printf("gcd(e, phi) = [%s %s]=%s\n", mpz_get_str(NULL, 10, e),mpz_get_str(NULL, 10, phi),mpz_get_str(NULL, 10, tmp1));
        //mpz_out_str(stdout,10,tmp1);
        //cout<<endl;
        if (mpz_cmp_ui(tmp1,1)==0  )
            break;
        else
        {
            mpz_add_ui(e,e,1);
        }
    }
    printf("public key[e] = [%s]\n", mpz_get_str(NULL,10,e));
    /*
    mpz_set_ui(k,2);
    mpz_mul(tmp1,k,phi);
    mpz_add_ui(tmp1,tmp1,1);
    printf("(1+k*phi) = [%s]\n", mpz_get_str(NULL,10,tmp1));

    ///Division: l=s/r
    mpz_invert(r_inv,e,phi);

    mpz_mul(l,tmp1,r_inv);


    printf("l = [%s]\n", mpz_get_str(NULL,10,r_inv));
    */
    if(mpz_invert(d, e, phi) == 0)
    {
        mpz_gcd(tmp1, e, phi);
        printf("gcd(e, phi) = [%s]\n", mpz_get_str(NULL, 16, tmp1));
        printf("Invert failed\n");
    }
    printf("private key[d]= [%s]\n", mpz_get_str(NULL,10,d));
    mpz_set_ui(msg,34534785);


    mpz_powm(v,msg,e,n);//v=(l^e) mod n
    printf("Encrypt msg = [%s]\n", mpz_get_str(NULL,10,v));

    mpz_powm(tmp1,v,d,n);//v=(l^e) mod n
    printf("decrypt msg = [%s]\n", mpz_get_str(NULL,10,tmp1));

    mpz_clr();

}

int main()
{
    prime_num();




}
