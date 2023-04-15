#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa{
	char nome[25]; // identificador do filme
	char sexo;
	float peso;
    float altura; //ano de produ��o
	struct Pessoa *ante; //ponteiro para o filme anterior
	struct Pessoa *prox;
}TPessoa;

typedef struct tipoLista {
	TPessoa *inicio;
	TPessoa *fim;
	int total; //quantidade de filmes na lista
}TLista;

//=== Assinatura das Fun��es =======================================
TLista iniciar(TLista *L);
void criarPessoa(TLista *L);
int excluir(TLista *L, char *nome);

//=== Fun��es ======================================================
TLista iniciar(TLista *L){
    //A VARIAVEL TEM QUE SER INICIADA
    /*TLista i;
     * iniciar(&i)*/
    L->inicio = NULL;
	L->fim = NULL;
	L->total = 0;
}

//==================================================================
void criarPessoa(TLista *L){
   TPessoa *novo = (TPessoa *)malloc(sizeof(TPessoa));
   TPessoa *atual = L->fim;
   int inserido = 0;
   
   //VALORES PADROES
   //TEM QUE SER ALTERADO NO ARQUIVO PRINICIPAL
   novo->nome[0] = 's';
   novo->sexo = 's';
   novo->peso = -1;
   novo->altura = -1;
   
   novo->ante = NULL;
   novo->prox = NULL;
   
   if(L->inicio == NULL){
   	   //Lista est� vazia...
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
//RETORNA UM VALOR DE CONFIRMACAO, 1 SE EXCLUIU E 0 SE N�O EXCLUIU
int excluir(TLista *L, char *nome){
   TPessoa *atual = L->inicio;
   TPessoa *anterior, *posterior;
   int excluido = 0;
   
   do{
   	   if(strcmp(nome, atual->nome) == 0){
   	   	  //Encontrado Registro a ser exclu�do...
   	   	  anterior = atual->ante;
   	   	  posterior = atual->prox;
   	   	  
   	   	  if(posterior != NULL){
   	   	    //O registro a ser exclu�do N�O � o �ltimo da Lista.
   	   	    posterior->ante = anterior;
		  } else {
		    //O registro a ser exclu�do � o �ltimo da Lista.
		    L->fim = anterior;
		  }//if
		  
		  if(anterior != NULL){
		     //O registro a ser exclu�do N�O � o primeiro da Lista.
			 anterior->prox = posterior;	
		  } else {
		  	 //O registro a ser exclu�do � o primeiro da Lista.
		     L->inicio = posterior;
		  }//if
		  
		  free(atual); //Exclu�do registro apontado por atual.
		  
		  excluido = 1;
	   }else
           atual = atual->prox;  //move atual para o pr�ximo registro.
   }while((atual != NULL) && (excluido == 0));
   
   L->total--;
   return excluido;
}

//===================================================================