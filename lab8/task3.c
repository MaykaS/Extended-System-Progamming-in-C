#include <stdio.h>


int digit_cnt(char* string){
    int counter=0;
    int num_count=0;
    char ans=string[0];
    while (ans!='\0'){
        if(ans>='0' && ans<='9')
            counter++;
        num_count++;
        ans=string[num_count];
    }
   
    return counter;
}

int main(int argc, char **argv){
  /*  
    void * p1 = ( void *)0x00000577; /*bad function */
    /*
    void * p2 = ( void *)0x0000054d;
    */
    /*
    int buf[103];
    FILE * goodFile;
    goodFile = fopen(argv[2],"r");
    fseek(goodFile,0x0000054d,SEEK_SET);
    fread(buf,sizeof(char),sizeof(buf),goodFile);
    
    FILE * badFile;
    badFile = fopen(argv[1], "r+"); 
    
    fseek(badFile, 0x00000577, SEEK_SET);
    fwrite(buf,sizeof(char),sizeof(buf),badFile);
    
    fclose(badFile);
    fclose(goodFile);
    */
    
    int counter=digit_cnt(argv[1]);
    printf("%d \n",counter);
    return 0;
}




