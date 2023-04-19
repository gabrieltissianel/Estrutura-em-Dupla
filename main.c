#include "list.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void inserir(TLista *f);

int main(){
    struct tipoLista ;
    
    TLista l;
    iniciar(&l);
    
}

void limparBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
}

void criarGrupos(int qtde_de_grupos, TLista *grupos){
    grupos = (TLista*)malloc(qtde_de_grupos * sizeof(TLista));

    for (int i = 0; i < qtde_de_grupos; i++){
        iniciar(&(grupos[i]));
    }
}

int distanciaEuclidiana(TPessoa centroide, TPessoa pessoa){
    return sqrt(pow(centroide.altura - pessoa.altura, 2) + pow(centroide.sexo - pessoa.sexo, 2) + pow(centroide.peso - centroide.peso, 2));
}

void inserir(TLista *f){
    criarPessoa(f);
    TPessoa *pessoa = f->fim;

    printf("nome: ");
    scanf("%s[^\n]", pessoa->nome);

    limparBuffer();

    printf("Sexo: ");
    scanf("%c", &pessoa->sexo);
    
    printf("Peso: ");
    scanf("%f",&(pessoa->peso));
    
    printf("Altura: ");
    scanf("%f",&(pessoa->altura));
}
