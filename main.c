#include "list.c"
#include <stdio.h>
#include <stdlib.h>

void inserir(TLista *f);

int main(){
    struct tipoLista ;
    
    TLista *l = iniciar();

    inserir(l);

    inserir(l);

    printf("%s\n", l->fim->nome);
    printf("%s\n", l->inicio->nome);

    excluir(l, "Joao");
    printf("%s\n", l->fim->nome);
    printf("%s\n", l->inicio->nome);
}

void limparBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
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
