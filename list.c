#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa{
	char nome[25]; // identificador do filme
	char sexo;
	float peso;
    float altura; //ano de produção
	struct Pessoa *ante; //ponteiro para o filme anterior
	struct Pessoa *prox;
}TPessoa;

typedef struct tipoLista {
	TPessoa *inicio;
	TPessoa *fim;
	int total; //quantidade de filmes na lista
}TLista;

//=== Assinatura das Funções =======================================
TLista* iniciar();
void criarPessoa(TLista *L);
int excluir(TLista *L, char *nome);

//=== Funções ======================================================
TLista* iniciar(){
    //A VARIAVEL TEM QUE SER INICIADA 
    TLista *L = (TLista *)malloc(sizeof(TLista));
    L->inicio = NULL;
	L->fim = NULL;
	L->total = 0;

    return L;
}

//==================================================================
void criarPessoa(TLista *L){
   TPessoa *novo = (TPessoa *)malloc(sizeof(TPessoa));
   TPessoa *atual = L->fim;
   int inserido = 0;
   
   novo->ante = NULL;
   novo->prox = NULL;
   
   if(L->inicio == NULL){
   	   //Lista está vazia...
   	   L->inicio = novo;
   	   L->fim = novo;
   } else {
   	  novo->ante = atual;
      atual->prox = novo;
      L->fim = novo; 
   }//if...else
       
   L->total++;
}

//==================================================================
//RETORNA UM VALOR DE CONFIRMACAO, 1 SE EXCLUIU E 0 SE NÃO EXCLUIU
int excluir(TLista *L, char *nome){
   TPessoa *atual = L->inicio;
   TPessoa *anterior, *posterior;
   int excluido = 0;
   
   do{
   	   if(strcmp(nome, atual->nome) == 0){
   	   	  //Encontrado Registro a ser excluído...
   	   	  anterior = atual->ante;
   	   	  posterior = atual->prox;
   	   	  
   	   	  if(posterior != NULL){
   	   	    //O registro a ser excluído NÃO é o último da Lista.
   	   	    posterior->ante = anterior;
		  } else {
		    //O registro a ser excluído é o último da Lista.
		    L->fim = anterior;
		  }//if
		  
		  if(anterior != NULL){
		     //O registro a ser excluído NÃO é o primeiro da Lista.
			 anterior->prox = posterior;	
		  } else {
		  	 //O registro a ser excluído é o primeiro da Lista.
		     L->inicio = posterior;
		  }//if
		  
		  free(atual); //Excluído registro apontado por atual.
		  
		  excluido = 1;
	   }else
           atual = atual->prox;  //move atual para o próximo registro.
   }while((atual != NULL) && (excluido == 0));
   
   L->total--;
   return excluido;
}

//===================================================================
