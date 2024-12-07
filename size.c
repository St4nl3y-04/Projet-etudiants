#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void test (int* b){
    (*b)=5;
}
int main(){
    int a=1;
    test(&a);
    printf("a= %d", a);
    return 0;
}