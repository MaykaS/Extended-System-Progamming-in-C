#include <stdio.h>
#include <string.h>
/*1a*/
int CtoA(FILE * output, FILE * inpute){
    unsigned char c=getc(inpute);
    while((char)c!=EOF){
        if(c=='\n'){
            printf("\n");
        }
        else{
        fprintf(output,"%d",c);
        }
        c=getc(inpute);
    }
    if(output!=stdout)
        fclose(output);
    if(inpute!=stdin)
        fclose(inpute);
    return 0;
}
/*1b*/
int ToBinary(char c,int *array, FILE * output){
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
            fprintf(output,"%d",array[k]);
        }
        return 0;
}


int CtoB(FILE * output, FILE * inpute){
    unsigned char c=getc(inpute);
    while((char)c!=EOF){
        if(c=='\n'){
            printf("\n");
        }
        else{
            int array[8];
            ToBinary(c,array,output);
        }
        c=getc(inpute);
    }
    if(output!=stdout)
        fclose(output);
    if(inpute!=stdin)
        fclose(inpute);
    return 0;
}

/*1c*/
int UandL(FILE * output, FILE * inpute){
     unsigned char c=getc(inpute);
    while((char)c!=EOF){
        if(c=='\n'){
            printf("\n");
        }
        else{
            int number = (int)c;
            if(number<=90 && number>=65)
                number=number+32;
            else if(number<=122 && number>=97)
                number=number-32;
        fprintf(output,"%c",number);
        }
        c=getc(inpute);
    }
    if(output!=stdout)
        fclose(output);
    if(inpute!=stdin)
        fclose(inpute);
    return 0;
}

int main(int argc, char **argv){
    FILE * inpute=stdin;
    FILE * output=stdout;
    int index;
    int a_flag=0;
    int b_flag=0;
    int c_flag=0;
    
    if(argc==1)
        a_flag=1;
    else{
        for(index=1; index<argc; index++){
            if(strcmp(argv[index], "-b")== 0)
                b_flag=1;
            if(strcmp(argv[index], "-c")== 0)
                c_flag=1;
            if(strcmp(argv[index], "-o")== 0){
                output=fopen(argv[index+1],"w");
            }
            if(strcmp(argv[index], "-i")== 0){
                inpute=fopen(argv[index+1],"r");
            }
        }
    }
    
    if(a_flag==1)
        CtoA(output,inpute);
    else if(b_flag==1)
        CtoB(output,inpute);
    else if(c_flag==1)
        UandL(output,inpute);
        
    
    return 0;
}
