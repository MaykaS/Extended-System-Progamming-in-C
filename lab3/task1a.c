#include <stdio.h>
#include <stdlib.h>

 
typedef struct diff {
    long offset; /* offset of the difference in file starting from zero*/
    unsigned char orig_value;     /* value of the byte in ORIG */
    unsigned char new_value;     /* value of the byte in NEW */
} diff;

typedef struct node node;
 
struct node {
    diff *diff_data; /* pointer to a struct containing the offset and the value of the bytes in each of the files*/
    node *next;
};

/* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. Each item followed by a newline character. */
void list_print(node *diff_list,FILE* output){
    
    node *current= diff_list; /*pointer to the beginning*/
    while(current){ /*as long as there is a current*/
        fprintf(output,"byte %li %02X %02X \n", current->diff_data->offset, current->diff_data->orig_value ,current->diff_data->new_value );
        current=current->next;
    }
}

/* Add a new node with the given data to the list,
and return a pointer to the list (i.e., the first node in the list).
If the list is null - create a new entry and return a pointer to the entry.*/ 
node* list_append(node* diff_list, diff* data){ /*add at the end*/
    
    struct node *new=malloc(sizeof(node)); /*creat the new node */
    new->diff_data = data;
    new->diff_data->offset = data->offset;
    new->diff_data->orig_value = data->orig_value;
    new->diff_data->new_value = data->new_value;
    new->next=NULL;
    
    if(diff_list==NULL){
        new->next = diff_list; 
        return new;
    }else{
        node * current=diff_list;
        while(current->next!=NULL)
            current=current->next;
        current->next=new;
        return diff_list;
    }
}
     
/* Free the memory allocated by and for the list. */
void list_free(node *diff_list){
     node *current=diff_list;
    node *tmp;
    while(current){
        tmp=current;
        current=current->next;
        free(tmp->diff_data);
        free(tmp);
    }
}



int main(int argc, char **argv){
    
    FILE * output = stdout;
    
    struct diff *first= malloc(sizeof(diff));
    struct diff *second= malloc(sizeof(diff));
    first->offset = 1;
    first->orig_value = 1;
    first->new_value = 1;
    second->offset = 2;
    second->orig_value = 2;
    second->new_value = 2;
    
    struct node *head=NULL; /*start*/
    
    head=list_append(head,first);
    head=list_append(head,second);
    
    list_print(head,output);

    list_free(head);
    return 0;
    
}
