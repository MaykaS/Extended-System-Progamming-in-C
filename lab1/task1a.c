#include <stdio.h>

int CtoA(){
    unsigned char c=getc(stdin);
    while((char)c!=EOF){
        if(c=='\n'){
            printf("\n");
        }
        else{
        printf("%d",c);
        }
        c=getc(stdin);
    }
    return 0;
}

int main(int argc, char **argv){
    CtoA();
    return 0;
}
