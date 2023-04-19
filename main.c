#include "list.c"

void menu();
void limparBuffer();
TPessoa *criarPessoa();

int main(){
    TLista *l 
    iniciar(&l);
    int opcao;
    
    do{
        menu();
        printf("Opcao: ");
        scanf("%d",&opcao);
        switch (opcao){
            case 1: criarPessoa(); break;
            //case 2: listarPessoas(l); break;
            //case 3: excluir(l); break;
            //case 4: agrupar(l); break;
            //case 5: listarGrupos(l); break;
        }
    }while(opcao!=0);
}

void menu(){
    printf("0 - Sair (Encerrar Aplicação)");
    printf("1 - Inserir Dados de Nova Pessoa");
    printf("2 - Listar Dados de Pessoas");
    printf("3 - Excluir Pessoa");
    printf("4 - Agrupar Pessoas");
    printf("5 - Exibir grupos");
}

int gerarAleatorio(int min, int max){
    int num = (rand()% (max-min)) + min;
    return num;
}

int gerarAleatorio(int min, int max){
    int num = (rand()% (max-min)) + min;
    return num;
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

void sortearCentroides(int qtde_de_grupos, TLista *grupos, TLista *l){
    alocarGrupos(qtde_de_grupos, grupos);
    int sorteado;
    TPessoa *centroide;
    for (int i = 0; i < qtde_de_grupos; i++){
        sorteado = gerarAleatorio(0, l->total);
        centroide = l->inicio;
        for (int j = 0; j < sorteado; j++){
            centroide = centroide->prox;
        }
        inserirPessoa(&(grupos[i]), centroide);
    }
}

int distanciaEuclidiana(TPessoa centroide, TPessoa pessoa){
    return sqrt(pow(centroide.altura - pessoa.altura, 2) + pow(centroide.sexo - pessoa.sexo, 2) + pow(centroide.peso - centroide.peso, 2));
}

TPessoa *criarPessoa(){
    TPessoa *pessoa = (TPessoa*)malloc(sizeof(TPessoa));

    printf("nome: ");
    scanf("%s[^\n]", pessoa->nome);

    limparBuffer();

    printf("Sexo: ");
    scanf("%c", &pessoa->sexo);
    
    printf("Peso: ");
    scanf("%f",&(pessoa->peso));
    
    printf("Altura: ");
    scanf("%f",&(pessoa->altura));
     
    return pessoa;
}
