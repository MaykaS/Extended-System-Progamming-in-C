#include <stdio.h>
#include <string.h>

struct fun_desc {
  char *name;
  void (*fun)(char);
};
 
/* 2a functions here */
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
    fgets(s,11,stdin);
}
 
void bitwise_xor(char* s){
    char result=s[0];
    int i;
    for(i=1;i<strlen(s)-1;i++){
        result=result^s[i];
    }
    binary_printer(result);
}
 
int main(int argc, char **argv){
     char str_input[11];
     int p_type;
     struct fun_desc menu[]={
    {"echo_printer", echo_printer},
    {"ascii_printer", ascii_printer},
    {"binary_printer", binary_printer},
    {"upper to lower and lower to upper case", upper_to_lower_to_upper_printer}};
    
     printf("Please enter a string (0<size<=10):\n");
     string_reader(str_input);
     
     printf("Please choose printer type:\n");
     int i;
     for(i=0;i<4;i++){
            printf("%d) %s\n",i,menu[i].name);
    }
    printf("4) bitwise_xor \n");
    
    while(scanf("%d",&p_type)!=EOF){ /*the printer type*/
        printf("Option: ");
        if(p_type<4 && p_type>-1){ /*if type is OK*/
            printf("%d \n",p_type);
            string_printer(str_input, menu[p_type].fun); /*call the func*/
        }
        else if(p_type==4){ /*if xor*/
            printf("4 \n");
            bitwise_xor(str_input); 
            printf("\n");
        }
        else
            break;
    }
    printf("DONE. \n");
    return 0;
     
}
