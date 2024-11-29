#include<stdio.h>
#include<stdlib.h>
#include<string.h>

size_t Taille_Tableau(int *P){
    size_t T= ((sizeof(P))/(sizeof P[0]));
    return T;
}
int main(){
    int P[]={1,2,2,2};
    printf("La taille du tableau est: %d", Taille_Tableau(P));
    return 0;
}