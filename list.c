#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoFilme {
	int id; // identificador do filme
	char titulo[30];
	int  ano; //ano de produção
	struct tipoFilme *ante; //ponteiro para o filme anterior
	struct tipoFilme *prox;
}TFilme;

typedef struct tipoLista {
	TFilme *inicio;
	TFilme *fim;
	int total; //quantidade de filmes na lista
}TLista;

TLista lista;

//=== Assinatura das Funções =======================================
void inicializa(TLista *L);
int menu();
void inserir(TLista *L);
void exibirFilmes(TLista L);
int excluirFilme(TLista *L);
void alterarFilme(TLista *L);
void ordenarPorAno(TLista *L);

//=== Corpo Principal do Programa ==================================
int main(){
	int opcao, resposta;
	inicializa(&lista);
	
	do{
		opcao = menu();

		switch(opcao){
			case 1: inserir(&lista); break;
			case 2: exibirFilmes(lista); break;
			case 3: resposta = excluirFilme(&lista);
			        if(resposta == 0){
			        	printf("\n\nERRO: Exclusao Falhou!\n\n");
					} else {
						printf("\n\nExclusão bem sucedida!\n\n");
					}//if
					system("PAUSE");
					break;
			case 4: alterarFilme(&lista); break;
			case 5: ordenarPorAno(&lista); break;
		}//switch
		
	}while(opcao != 0);
	
}
//=== Funções ======================================================
void inicializa(TLista *L){
	L->inicio = NULL;
	L->fim = NULL;
	L->total = 0;
}
//==================================================================
int menu(){
	int opcao;
	system("CLS");
	printf("\n\n\t\t=====| MENU |=====\n\n");
	
	printf("\t0 - Sair (Encerrar).\n\n");
	printf("\t1 - Inserir Filme.\n");
	printf("\t2 - Listar Filmes.\n");
	printf("\t3 - Excluir Filmes.\n");
	printf("\t4 - Alterar Filme.\n");
	printf("\t5 - Ordenar Filme por ano de producao.\n\n");
	
	printf("\t\tInforme a opcao desejada:");
	scanf("%d", &opcao);
	
	if((opcao > 5) || (opcao < 0)){
		printf("\n\n\tERRO: opcao invalida.\n\tTente outra vez.\n\n");
		system("PAUSE");
	}//if
	return opcao;
}
//==================================================================
void inserir(TLista *L){
   TFilme *novo = (TFilme *)malloc(sizeof(TFilme));
   TFilme *atual = L->inicio;
   TFilme *anterior;
   int inserido = 0;
   
   printf("\n\n\t\t=====| INSERIR FILME |=====\n\n\n");
   printf("\tID: ");
   scanf("%d", &novo->id);
   
   printf("\n\tTITULO: ");
   fflush(stdin);
   gets(novo->titulo);
   
   printf("\n\tANO DE PRODUCAO: ");
   scanf("%d",&novo->ano);
   
   novo->ante = NULL;
   novo->prox = NULL;
   
   if(L->inicio == NULL){
   	   //Lista está vazia...
   	   L->inicio = novo;
   	   L->fim = novo;
   } else {
   	   
   	   while(atual != NULL){
   	       if(atual->id > novo->id)	{
   	          //Inserir novo antes de atual ...
		      inserido = 1;
			  novo->prox = atual;
			  anterior = atual->ante;
			  
			  if(anterior == NULL){
			  	 L->inicio = novo;
			  }else{
			     anterior->prox = novo; 	
			  }//if
			  
			  novo->ante = anterior;
			  atual->ante = novo;
			  break; //interrompe o while	
	       }//if
	       atual = atual->prox; //move atual para o próximo filme.
	   }//while
   	   
   	   if(!inserido){
   	   	  //Inserir Novo no Final da Lista...
   	   	  L->fim->prox = novo;
   	   	  novo->ante = L->fim;
   	   	  L->fim = novo;
	   }//if
   }//if
   
   L->total++;
}
//==================================================================
void exibirFilmes(TLista L){
	TFilme *atual = L.inicio;
	
	printf("\n\n\n\t\t=======| EXIBIR FILMES |=======\n\n\n");
	
	while(atual != NULL){
		printf("\t%d - %s (%d)\n", atual->id, atual->titulo, atual->ano);
		atual = atual->prox;
	}//while
	
	printf("\n\n");
	system("PAUSE");
}
//==================================================================
int excluirFilme(TLista *L){
   TFilme *atual = L->inicio;
   TFilme *anterior, *posterior;
   int id;
   int excluido = 0;
   
   printf("\n\n\n\t\t========| EXCLUIR FILME |========\n\n");
   printf("\tInforme ID: ");
   scanf("%d",&id);
   
   while(atual != NULL){
   	   if(id == atual->id){
   	   	  //Encontrado Registro a ser excluído...
   	   	  anterior = atual->ante;
   	   	  posterior = atual->prox;
   	   	  
   	   	  if(posterior != NULL){
   	   	    //O registro a ser excluído NÃO é o último da Lista.
   	   	    posterior->ante = anterior;
		  } else {
		    //O registro a ser excluído é o último da Lista.
		    L->fim = anterior;
		    if(anterior != NULL) anterior->prox = NULL;
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
		  break; //interrompe o while.
	   }//if
	   atual = atual->prox;  //move atual para o próximo registro.
   }//while
   L->total--;
   return excluido;
}
//==================================================================
void alterarFilme(TLista *L){
    TFilme *atual = L->inicio;
	int op, id;
	
	printf("\n\n\n\t\t=========| ALTERAR FILME |=========\n\n");
	printf("\tInforme ID: ");
	scanf("%d",&id);
	
	while(atual != NULL){
		if(atual->id == id){
			//Encontrado o registro a ser alterado...
		    printf("\n\t+----------------------------------------+");
		    printf("\n\t|  Clique em:                            |");
		    printf("\n\t|      1 - para alterar TITULO.          |");
		    printf("\n\t|      2 - para alterar ANO de PRODUCAO. |");
		    printf("\n\t|                                        |");
		    printf("\n\t+----------------------------------------+\n\n");
		    scanf("%d", &op);
		    
		    if(op == 1){
		    	printf("\n\nAntigo TITULO: %s.", atual->titulo);
		    	printf("\n\nNovo TITULO: ");
		    	fflush(stdin);
		    	gets(atual->titulo);
			} else if(op == 2){
				printf("\n\nAntigo ANO: %d.", atual->ano);
				printf("\n\nNovo ANO: ");
				scanf("%d",&atual->ano);
			}//if
			break;
		}//if
		atual = atual->prox;
	}//while
}
//===================================================================
void ordenarPorAno(TLista *L){
	TFilme *fixo, *movel, *aux;
	aux = (TFilme *)malloc(sizeof(TFilme));
	
	fixo = L->inicio;
	while(fixo != NULL){
		movel = fixo->prox;
		while(movel != NULL){
			if(movel->ano < fixo->ano){
				//fora de ordem: necessidade de troca.
				aux->id = movel->id;
				strcpy(aux->titulo, movel->titulo);
				aux->ano = movel->ano;
				
				movel->id = fixo->id;
				strcpy(movel->titulo, fixo->titulo);
				movel->ano = fixo->ano;
				
				fixo->id = aux->id;
				strcpy(fixo->titulo, aux->titulo);
				fixo->ano = aux->ano;
			}//if
			movel = movel->prox; //movimentação de movel
		}//while
		
		fixo = fixo->prox;
	}//while
	
	free(aux);
}
//===================================================================


