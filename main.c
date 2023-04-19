#include "list.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void menu();
void limparBuffer();
void inserir(TLista *f);

int main(){
    TLista *l = iniciar();
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
