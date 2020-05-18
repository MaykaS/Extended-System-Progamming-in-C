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
    
    if (descriptor == -1)
        perror("open");
    /*creat new mapping */
    Map=mmap(Map,length,PROT_READ,MAP_SHARED,descriptor,0);
    Elf32_Ehdr *elfheader;
    elfheader= (Elf32_Ehdr*)Map;
    
    if(elfheader->e_ident[EI_CLASS] != 1){
        perror("the file is not ELF 32 bit\n");
        munmap(Map ,length);
        close(descriptor);
        return 0;
    }
    
    /*section header offset*/
    Elf32_Shdr *sections =(Map+(elfheader->e_shoff));
    /*sh_offset section offset*/
    int s_offset=sections[elfheader->e_shstrndx].sh_offset;
    
    printf("Section Headers:\n");
    printf("[Nr]\tName\t\tAddr\t off\tSize\n");
    /*go over all sections in the sections table*/
    int i;
    for(i=0; i<elfheader->e_shnum; i++){
        Elf32_Shdr section=sections[i];
        char *name=(Map +s_offset +section.sh_name);
        printf("[%d]\t%-12s\t%08x %06x\t%06x\n",i,name,section.sh_addr,section.sh_offset,section.sh_size);
    }
    printf("\n");
    munmap(Map,length);
    close(descriptor);
    return 0;
}
