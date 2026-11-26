#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

int main() {
    NoTrie *raiz = criarNoTrie();
    int contadorMenu = 0;
    //Aqui coloque o destino que vai estar a pasta 'Cars'
    carregarPasta(raiz, "C:/Users/1645091/Documents/Trabalho-AED-II-main/Cars");

    char prefixo[100];

    printf("\n====================================\n");
    printf("\n||       Opnioes de Carros        ||\n");
    printf("\n====================================\n");

    do
    {
        printf("\n\n\n||DIGITE 1 PARA SAIR||\nDigite o prefixo para pesquisa: ");
        scanf("%99s", prefixo);

        for (int i = 0; prefixo[i]; i++) {
            prefixo[i] = tolower((unsigned char)prefixo[i]);
        }

        NoTrie *no = buscarPrefixo(raiz, prefixo);
        if (no != NULL) {
            char buffer[100];
            strcpy(buffer, prefixo);
            int contador = 0;
            sugerirAutocomplete(no, buffer, strlen(prefixo), &contador);
        }
        else
        {
            printf("Nenhum termo encontrado.\n");
            if(strcmp(prefixo, "1") == 0){
                liberarTrie(raiz);
                printf("\nSAINDO...\n");
                return 0;
            }
        }
    }while(contadorMenu != 1);
}
