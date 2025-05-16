#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node *n) {
   int used[10]; // para números 1..9

       // Validar filas
      for(int i = 0; i < 3; i++){
           for(int k = 1; k <= 3; k++) used[k] = 0;
           for(int j = 0; j < 3; j++){
               int val = n->sudo[i][j];
               if(val != 0){
                   if(used[val]) return 0; // repetido
                   used[val] = 1;
               }
           }
       }

       // Validar columnas
       for(int j = 0; j < 9; j++){
           for(int k = 1; k <= 9; k++) used[k] = 0;
           for(int i = 0; i < 9; i++){
               int val = n->sudo[i][j];
               if(val != 0){
                   if(used[val]) return 0; // repetido
                   used[val] = 1;
               }
           }
       }

       // Validar submatrices 3x3
       for(int k = 0; k < 9; k++){
           for(int i = 1; i <= 9; i++) used[i] = 0;
           for(int p = 0; p < 9; p++){
               int i = 3*(k/3) + (p/3);
               int j = 3*(k%3) + (p%3);
               int val = n->sudo[i][j];
               if(val != 0){
                   if(used[val]) return 0; // repetido
                   used[val] = 1;
               }
           }
       }

   return 1; // válido
}


List* get_adj_nodes(Node* n){
   List* list = createList();
       int i, j;
       int found_empty = 0;
       int num; // Declarar fuera del for

       // Buscar la primera casilla vacía (0)
       for(i = 0; i < 9 && !found_empty; i++){
           for(j = 0; j < 9 && !found_empty; j++){
               if(n->sudo[i][j] == 0){
                   found_empty = 1;
                   // Para cada número del 1 al 9, crear un nuevo nodo con ese valor
                   for(num = 1; num <= 9; num++){
                       Node* copy_node = copy(n);
                       copy_node->sudo[i][j] = num;
                       pushBack(list, copy_node);
                   }
               }
           }
       }

   return list;
}


int is_final(Node* n) 
{
   for(int i=0; i<9; i++){
         for(int j=0; j<9; j++){
            if(n->sudo[i][j] == 0) return 0;
         }
      }
   return 1;
}


Node* DFS(Node* n, int* cont){
    Stack* S = createStack();
    push(S, n);

    while(!is_empty(S)){
        Node* current = (Node*) top(S);
        pop(S);
        (*cont)++;

        if(is_final(current)){
            clean(S);
            return current;
        }

        List* adj = get_adj_nodes(current);
        Node* aux = (Node*) first(adj);

        while(aux != NULL){
            push(S, aux);
            popFront(adj);
            aux = (Node*) first(adj);
        }

        clean(adj);
        free(current);
    }

    return NULL;
}





/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/