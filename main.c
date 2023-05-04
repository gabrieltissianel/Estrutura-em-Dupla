#include "list.h"
#include <time.h>


//Descricao das funcoes===============================
void menu();
int gerarAleatorio(int min, int max);
void limparBuffer();
void iniciarGrupos(int qtde_de_grupos, TLista *grupos);
void adicionarPessoa(TLista *list, TPessoa *pessoa);
int *sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *lista);
float distanciaEuclidiana(TPessoa centroide, TPessoa pessoa);
TPessoa *alocarPessoa();
void adicionarPessoa(TLista *list, TPessoa *pessoa);
TPessoa *criarPessoa();
void listarPessoas(TLista list);
void excluirPessoa(TLista *lista);
int verificarCentroides(int *centroides, int quantidadeCentroides, int pessoa);
TLista *agrupar(TLista *lista, int *qtde_grupos);
void listarGrupos(TLista *grupos,int tamanho); 

int main(){
    TLista lista;
    iniciar(&lista);
    TPessoa *pessoa;
    int opcao, tamanho;
    TLista *grupos;
    
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
            case 4: grupos=agrupar(&lista, &tamanho); break;
            case 5: listarGrupos(grupos,tamanho); break;
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


void iniciarGrupos(int qtde_de_grupos, TLista *grupos){
    //grupos = (TLista*)malloc(qtde_de_grupos * sizeof(TLista));

    for (int i = 0; i < qtde_de_grupos; i++){
        iniciar(&(grupos[i]));
    }
}

void adicionarPessoa(TLista *list, TPessoa *pessoa){
    inserirPessoa(list, pessoa);
}

int gerarAleatorio(int min, int max){
    int num = (rand()% (max-min)) + min;
    return num;
}

int verificarSorteio(int *vetor, int tamanho_vetor, int valor){
    int i=0;
    while(i<tamanho_vetor && valor!=vetor[i]){i++;}
    
    if (i==tamanho_vetor)
        return 1;   
    else
        return 0;
}

int *sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *lista){
    iniciarGrupos(qtde_de_grupos, grupos);
    int sorteado, i;
    int *sorteados = (int*)malloc(qtde_de_grupos*sizeof(int));
    TPessoa *centroide, *pessoa;
    centroide = alocarPessoa();

    for (i = 0; i < qtde_de_grupos; i++){
        do{
            sorteado = gerarAleatorio(0, qtde_de_grupos);
        } while (!verificarSorteio(sorteados, i, sorteado));
        
        sorteados[i] = sorteado;
        pessoa = procurarPosicao(sorteado, lista);
        centroide = pessoacpy(pessoa); //ESSA FUNCAO RETORNA UM PONTEIRO PARA UMA COPIA DA PESSOA
        adicionarPessoa(&(grupos[i]), centroide);
    }
    return sorteados;
}

//VERIFICA SE A POSICAO DA PESSOA NÃO É A MESMA DE ALGUM CENTROIDE
//RETORNANDO 1 SE NAO TIVER E 0 SE TIVER
int verificarCentroides(int *centroides, int quantidadeCentroides, int pessoa){
    int i=0; 
    while(i<quantidadeCentroides && centroides[i]!=pessoa){i++;}
    if(i==quantidadeCentroides)
        return 1;
    else
        return 0;
}

TLista *agrupar(TLista *lista, int *qtde_grupos){
    int *sorteados, indiceCentroide, i, e, verificar;
    float menorDistancia, distancia;
    TLista *grupos;
    TPessoa *pessoa, *copiaPessoa;
    
    printf("Insira a quantidade de grupos: ");
    scanf("%d", qtde_grupos);
    grupos = (TLista*)malloc(*qtde_grupos * sizeof(TLista));

    sorteados = sortearCentroides(*qtde_grupos, grupos, lista);   
    
    for(i=0; i < lista->total; i++)
    {
        verificar = verificarCentroides(sorteados, *qtde_grupos, i);//VERIFICO SE A PESSOA NA POSICAO i NAO É UM CENTROIDE
        if(verificar)
        {//CONDICAO SE NAO ACHAR
            pessoa=procurarPosicao(i,lista);//REOTRNO UM PONTEIRO PARA A PESSOA DA RESPECTIVA POSICAO
            copiaPessoa = pessoacpy(pessoa);//RETORNA UM PONTEIRO PARA UMA COPIA DA PESSOA
            menorDistancia=9999;
            for(e=0; e<*qtde_grupos; e++)
            {
                distancia=distanciaEuclidiana(*grupos[e].inicio, *copiaPessoa);

                if(distancia<menorDistancia){
                    indiceCentroide=e;
                    menorDistancia=distancia;
                }
            }
            adicionarPessoa(&grupos[indiceCentroide], copiaPessoa);
        }
    }//for(if(for(if)))

    limparBuffer();
    printf("\nGrupos Criados!");
    getchar();
    return grupos;
}


float distanciaEuclidiana(TPessoa centroide, TPessoa pessoa){
    return sqrt(pow(centroide.altura - pessoa.altura, 2) + pow(centroide.sexo - pessoa.sexo, 2) + pow(centroide.peso - centroide.peso, 2));
}

TPessoa *alocarPessoa(){
    TPessoa *pessoa = (TPessoa*)malloc(sizeof(TPessoa));
    return pessoa; 
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


//----------------}}}
void excluirPessoa(TLista *lista){
    char nome[NOME]; //NOME DEFINIDO NO ARQUIVO list.h
    
    printf("\nNome da pessoa: ");
    scanf("%s[^\n]",nome);
    limparBuffer();

    int c = excluir(lista, nome);
    if(!c){printf("\n\nNão existe niguem com esse nome!");}
    else{printf("\n\n%s Saiu da fila!",nome);}
    
    getchar();
}

void listarGrupos(TLista *grupos, int tamanho){ 
    int i;
    limparBuffer();
    if(!grupos){
        printf("\n\nVoce tem que criar os grupos antes!");
        getchar();
        system("clear");
        return;
    }    
    
    system("clear");

    for(i=0;i<tamanho;i++){
        printf("\n\nGrupo: %d", i+1);
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
