#include "list.c"

TPessoa *criarPessoa();

int main(){
    struct tipoLista ;
    
    TLista l;
    iniciar(&l);
    
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
