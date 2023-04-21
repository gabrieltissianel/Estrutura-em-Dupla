#include "list.h"

//Descricao das funcoes===============================
void menu();
void limparBuffer();
void alocarGrupos(int qtde_de_grupos, TLista *grupos);
void sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *lista);
int distanciaEuclidiana(TPessoa centroide, TPessoa pessoa);
void adicionarPessoa(TLista *list, TPessoa *pessoa);
TPessoa *criarPessoa();
void listarPessoas(TLista list);


int main(){
    TLista lista;
    iniciar(&lista);
    TPessoa *pessoa;
    int opcao;
    
    do{
        menu();
        printf("\n\nOpcao: ");
        scanf("%d",&opcao);
        switch (opcao){
            case 1: pessoa = criarPessoa();
                    adicionarPessoa(&lista, pessoa);
                    break;
            case 2: listarPessoas(lista); break;
            //case 3: excluir(lista); break;
            //case 4: agrupar(lista); break;
            //case 5: listarGrupos(lista); break;
        }
    }while(opcao!=0);
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


void sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *lista){
    alocarGrupos(qtde_de_grupos, grupos);
    int sorteado;
    TPessoa *centroide;
    for (int i = 0; i < qtde_de_grupos; i++){
        //sorteado = gerarAleatorio(0, lista->total);
        centroide = lista->inicio;
        for (int j = 0; j < sorteado; j++){
            centroide = centroide->prox;
        }
        inserirPessoa(&(grupos[i]), centroide);
    }
}


int distanciaEuclidiana(TPessoa centroide, TPessoa pessoa){
    return sqrt(pow(centroide.altura - pessoa.altura, 2) + pow(centroide.sexo - pessoa.sexo, 2) + pow(centroide.peso - centroide.peso, 2));
}


void adicionarPessoa(TLista *list, TPessoa *pessoa){
    inserirPessoa(list, pessoa);
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
