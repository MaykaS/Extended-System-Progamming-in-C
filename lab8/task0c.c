#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

    char *Map=NULL; /*the map-kernal choses the adress*/
    int descriptor=open(argv[1], O_RDWR);
    int length=lseek(descriptor,0,SEEK_END); /*file length*/
    lseek(descriptor,0,SEEK_SET); /*return to beginning*/
    
    /*creat new mapping */
    Map=mmap(Map,length,PROT_READ,MAP_SHARED,descriptor,0);
    Elf32_Ehdr *elfheader;
    elfheader= (Elf32_Ehdr*)Map;
    
    printf("Magic:\t\t\t\t %x,%x,%x\n",elfheader->e_ident[0],elfheader->e_ident[1],elfheader->e_ident[2]);
    printf("Data:\t\t\t\t %d's complement, little endian\n", elfheader->e_type);
    printf("Entry point address:\t\t 0x%x\n",elfheader->e_entry);
    printf("Start of section headers:\t %d\n",elfheader->e_shoff);
    printf("Num of section headers:\t\t %d\n",elfheader->e_shnum);
    printf("Size of section headers:\t %d\n",elfheader->e_shentsize);
    printf("Shatrtab index:\t\t\t %d\n",elfheader->e_shstrndx);
    
    munmap(Map,length); /* deletes Map*/
    close(descriptor);
    return 0;
}
