#include "trie.h"
#include <string.h>
#include <ctype.h>

int palavrasInseridas = -1;

NoTrie* criarNoTrie() {
    NoTrie *no = (NoTrie *)malloc(sizeof(NoTrie));
    if (no == NULL) {
        return NULL;
    }
    no->ehFimDePalavra = 0;
    for (int i = 0; i < 26; i++) {
        no->filhos[i] = NULL;
    }
    return no;
}

void inserirPalavra(NoTrie* raiz, const char* palavra) {
    if (raiz == NULL || palavra == NULL) return;
    NoTrie *atual = raiz;
    for (size_t i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';
        if (indice < 0 || indice >= 26) {
            continue;
        }
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNoTrie();
        }
        atual = atual->filhos[indice];
    }
    if (atual != raiz) {
        palavrasInseridas++;
        printf("\rTOTAL DE CARROS INSERIDOS: %d", palavrasInseridas);
        atual->ehFimDePalavra = 1;
    }
}


NoTrie* buscarPrefixo(NoTrie* raiz, const char* prefixo) {
    if (raiz == NULL) return NULL;

    NoTrie *atual = raiz;
    for (size_t i = 0; prefixo[i] != '\0'; i++) {
        int indice = prefixo[i] - 'a';
        if (indice < 0 || indice >= 26 || atual->filhos[indice] == NULL) {
            return NULL;
        }
        atual = atual->filhos[indice];
    }
    return atual;
}

void liberarTrie(NoTrie *no) {
    if (no == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        liberarTrie(no->filhos[i]);
    }
    free(no);
}

void sugerirAutocomplete(NoTrie* noPrefixo, char* buffer, int nivel, int* contador) {
    if (noPrefixo == NULL) return;

    if (noPrefixo->ehFimDePalavra) {
        buffer[nivel] = '\0';
        printf(">> %s\n", buffer);
        if (contador != NULL) (*contador)++;
    }

    for (int i = 0; i < 26; i++) {
        if (noPrefixo->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            sugerirAutocomplete(noPrefixo->filhos[i], buffer, nivel + 1, contador);
        }
    }
}

void paraMinusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void processarArquivo(NoTrie *raiz, const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", caminhoArquivo);
        return;
    }

    char linha[1024];
    const char *delimitadores = " \t\n\r,.;:!?\"'()[]{}";

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *palavra = strtok(linha, delimitadores);
        while (palavra != NULL) {
            paraMinusculo(palavra);

            if (strlen(palavra) > 1) {
                inserirPalavra(raiz, palavra);
            }

            palavra = strtok(NULL, delimitadores);
        }
    }

    fclose(arquivo);
}

void carregarPasta(NoTrie *raiz, const char *caminhoPasta) {
    DIR *dir = opendir(caminhoPasta);
    if (dir == NULL) {
        printf("Nao foi possivel abrir a pasta: %s\n", caminhoPasta);
        return;
    }

    struct dirent *entrada;
    char caminhoCompleto[512];

    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        if (strstr(entrada->d_name, ".csv") != NULL || strstr(entrada->d_name, ".txt") != NULL) {
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", caminhoPasta, entrada->d_name);
            processarArquivo(raiz, caminhoCompleto);
        }
    }

    closedir(dir);
}
