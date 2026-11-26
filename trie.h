#include<stdio.h>
#include<stdlib.h>
#include <dirent.h> //biblioteca para ler a pasta toda dos documentos facilitado


typedef struct NoTrie {
    struct NoTrie *filhos[26];
    int ehFimDePalavra;
    // Na Semana 2, voc� adicionar� aqui o ponteiro para a raiz da ABB:
    // struct NoABB *docs;
} NoTrie;


NoTrie* criarNoTrie();
void inserirPalavra(NoTrie* raiz, const char* palavra);
NoTrie* buscarPrefixo(NoTrie* raiz, const char* prefixo);
void liberarTrie(NoTrie *no);
void sugerirAutocomplete(NoTrie* noPrefixo, char* buffer, int nivel, int* contador);
void carregarPasta(NoTrie *raiz, const char *caminhoPasta);
void processarArquivo(NoTrie *raiz, const char *caminhoArquivo);
void paraMinusculo(char *str);
