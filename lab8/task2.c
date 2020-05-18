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
    Map=mmap(Map,length,PROT_READ|PROT_WRITE,MAP_SHARED,descriptor,0);
    Elf32_Ehdr *elfheader;
    elfheader= (Elf32_Ehdr*)Map;
    
    /*check for 32bit*/
    if(elfheader->e_ident[EI_CLASS] != 1){
        perror("the file is not ELF 32 bit\n");
        munmap(Map ,length);
        close(descriptor);
        return 0;
    }
    
    /*section header offset*/
    Elf32_Shdr *sections =(Map+ elfheader->e_shoff);
    /*sh_offset section offset*/
    int s_offset=sections[elfheader->e_shstrndx].sh_offset;

    /*go over all sections in the sections table*/
    int i;
    for(i=0; i<elfheader->e_shnum; i++){
        Elf32_Shdr section=sections[i];
        /*SHT_SYMTAB = symbol table
        /*SHT_DYNSYM = minimal set of dynamic linking symbols*/
        if(section.sh_type==SHT_SYMTAB || section.sh_type==SHT_DYNSYM){
            Elf32_Sym *symbols=(Map+section.sh_offset);
            char *section_name=(Map +s_offset +section.sh_name);
            int symbol_offset=sections[section.sh_link].sh_offset;
            printf("Symbol table '%s' contains %d entries:\n", section_name,(section.sh_size / sizeof(Elf32_Sym)));
            printf("Num:\tValue\tsection_index\tsection_name\tsymbol_name\n");
            
            int index;
            for(index=0; index<(section.sh_size / sizeof(Elf32_Sym)); index++){
                Elf32_Sym symbol= symbols[index];
                char *symbol_name=(Map +symbol_offset+symbol.st_name);
                printf("%d:\t%08x\t%d\t%-12s\n",index,symbol.st_value,index,symbol_name);
            }
        }
    }
    printf("\n");
    munmap(Map,length);
    close(descriptor);
    return 0;
}
