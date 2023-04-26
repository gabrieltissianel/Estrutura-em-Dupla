#include "list.h"
#include <time.h>


//Descricao das funcoes===============================
void menu();
int gerarAleatorio(int min, int max);
void limparBuffer();
void alocarGrupos(int qtde_de_grupos, TLista *grupos);
void adicionarPessoa(TLista *list, TPessoa *pessoa);
void sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *lista);
int distanciaEuclidiana(TPessoa centroide, TPessoa pessoa);
TPessoa *criarPessoa();
void listarPessoas(TLista list);
void excluirPessoa(TLista *lista);
void listarGrupos(TLista *grupos); 


int main(){
    TLista lista;
    iniciar(&lista);
    TPessoa *pessoa;
    int opcao;
    TLista *grupos=NULL;
    
    do{
        menu();
        printf("\n\nOpcao: ");
        scanf("%d",&opcao);
        switch (opcao){
            case 1: pessoa = criarPessoa();
                    adicionarPessoa(&lista, pessoa);
                    break;
            case 2: listarPessoas(lista); break;
            case 3: excluirPessoa(&lista); break;
            //case 4: grupos=agrupar(lista); break;
            case 5: listarGrupos(grupos); break;
        }
    }while(opcao!=0);

    return 0;
}

//FUNCOES------------------------------------------------{{{
void menu(){
    system("clear");
    printf("\n0 - Sair (Encerrar Aplicação)");
    printf("\n1 - Inserir Dados de Nova Pessoa");
    printf("\n2 - Listar Dados de Pessoas");
    printf("\n3 - Excluir Pessoa");
    printf("\n4 - Agrupar Pessoas");
    printf("\n5 - Exibir grupos");
}


void limparBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
}


void alocarGrupos(int qtde_de_grupos, TLista *grupos){
    grupos = (TLista*)malloc(qtde_de_grupos * sizeof(TLista));

    for (int i = 0; i < qtde_de_grupos; i++){
        iniciar(&(grupos[i]));
    }
}

void adicionarPessoa(TLista *list, TPessoa *pessoa){
    inserirPessoa(list, pessoa);
}

int verificarSorteio(int *vetor, int tamanho_vetor, int valor){
    for (int i = 0; i < tamanho_vetor; i++){
        if (valor == vetor[i])
            return 0;   
    }
    return 1;
}

void sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *lista){
    alocarGrupos(qtde_de_grupos, grupos);
    int sorteado;
    TPessoa *centroide;
    int sorteados[qtde_de_grupos];
    int qtde_sorteados = 0;
    for (int i = 0; i < qtde_de_grupos; i++){
        do{
            sorteado = gerarAleatorio(0, qtde_de_grupos+1);
        } while (!verificarSorteio(sorteados, qtde_sorteados, sorteado));

        sorteados[qtde_sorteados++] = sorteado;

        centroide = lista->inicio;
        for (int j = 0; j < sorteado; j++){
            centroide = centroide->prox;
        }
        adicionarPessoa(&(grupos[i]), centroide);
    }
}


int distanciaEuclidiana(TPessoa centroide, TPessoa pessoa){
    return sqrt(pow(centroide.altura - pessoa.altura, 2) + pow(centroide.sexo - pessoa.sexo, 2) + pow(centroide.peso - centroide.peso, 2));
}


TPessoa *criarPessoa(){
    TPessoa *pessoa = (TPessoa*)malloc(sizeof(TPessoa));

    printf("Nome: ");
    scanf("%s[^\n]", pessoa->nome);

    limparBuffer();

    printf("Sexo: ");
    scanf("%c", &pessoa->sexo);
    
    printf("Peso: ");
    scanf("%f",&(pessoa->peso));
    
    printf("Altura: ");
    scanf("%f",&(pessoa->altura));

    system("clear");
    return pessoa;
}


void listarPessoas(TLista list){
    TPessoa *atual = list.inicio;
    
    if(!atual){
        printf("lista vazia!\n");
        return;
    }
    
    system("clear");
    printf("Nome\tSexo\tPeso\tAltura\n");
    while(atual){
        printf("%s\t",atual->nome);
        printf("%c\t",atual->sexo);
        printf("%0.2f\t",atual->peso);
        printf("%0.2f\n",atual->altura);
        atual = atual->prox;
    }
    limparBuffer();
    getchar();
}

int gerarAleatorio(int min, int max){
    int num = (rand()% (max-min)) + min;
    return num;
}

//----------------}}}
void excluirPessoa(TLista *lista){
    char nome[NOME]; //NOME DEFINIDO NO ARQUIVO list.h
    
    printf("\nNome da pessoa: ");
    scanf("%s[^\n]",nome);
   limparBuffer();

    int c = excluir(lista, nome);
    if(c==0){printf("\n\nNão existe niguem com esse nome!");}
    else{printf("\n\n%s Saiu da fila!",nome);}
    
    getchar();
}

void listarGrupos(TLista *grupos){ 
    limparBuffer();
    if(!grupos){
        printf("\n\nVoce tem que criar os grupos antes!");
        getchar();
        system("clear");
        return;
    }    
    
    system("clear");
    int tamanho, i;
    tamanho = sizeof(*grupos)/sizeof(TLista);
    printf("\n\nTamanho %d", tamanho);

    for(i=0;i<tamanho;i++){
        printf("\n\nGrupo: %d", tamanho);
        printf("\nNome\tSexo\tPeso\tAltura\n");
        TPessoa *atual = grupos[i].inicio;
        while(atual){
            printf("%s\t",atual->nome);
            printf("%c\t",atual->sexo);
            printf("%0.2f\t",atual->peso);
            printf("%0.2f\n",atual->altura);
            atual = atual->prox;
        }
    }
    getchar();
}
