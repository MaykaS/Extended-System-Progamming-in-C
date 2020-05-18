#include <stdio.h>
#include <string.h>
 
 
/* TODO: 2a functions here */
void echo_printer(char c){
    printf("%c",c);
    printf(" ");
}
void ascii_printer(char c){
    if(c=='\n'){
        printf("\n");
    }
    else{
        printf("%d ",c);
    } 
}

/*helper to binary_printer*/
int ToBinary(char c,int *array){
    int i=1;
    int number=c;
    int ans=0;
    int remainder;
      
      while (number > 0) {
          remainder = number %2;
          ans = ans + (i*remainder);
          number = number/2;
          i = i*10;
        }
        int j;
        for(j=0;j<8;j++){
            array[j]=ans%10;
            ans=ans/10;
        }
        int k;
        for(k=0;k<8;k++){
            printf("%d",array[k]);
        }
        printf(" ");
        return 0;
}

void binary_printer(char c){
    if(c=='\n'){
        printf("\n");
    }
    else{
        int array[8];
        ToBinary(c,array);
    } 
}
void upper_to_lower_to_upper_printer(char c){
    if(c=='\n'){
            printf("\n");
        }
        else{
            int number = (int)c;
            if(number<=90 && number>=65)
                number=number+32;
            else if(number<=122 && number>=97)
                number=number-32;
            printf("%c ",number);
        } 
}
 
void string_printer(char* str, void (*f) (char)){
    int i;
    for(i=0;i<strlen(str)-1; i++){
        f(str[i]);
        printf(" ");
    }
    printf("\n");
}
 
void string_reader(char* s){
  /* TODO: Complete during task 2c*/
}
 
void bitwise_xor(char* s){
  /*TODO: Complete during task2c */
}
 
int main(int argc, char **argv){

}
