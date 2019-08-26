#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

void quickSort(dados vetor[], int inicio, int fim);
int particiona(dados vetor[], int inicio, int final);

void quickSort(dados vetor[], int inicio, int fim) {
    int pivo;
    if (fim > inicio) {
        pivo = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pivo-1);
        quickSort(vetor, pivo+1, fim);
    }
}

int particiona(dados vetor[], int inicio, int final) {
    int esq, dir;
    dados aux, pivo;
    esq = inicio;
    dir = final;
    pivo = vetor[inicio];
    while (esq < dir)
    {
        while (vetor[esq].cod <= pivo.cod)
            esq++;
        while (vetor[dir].cod > pivo.cod)
            dir--;
        if (esq < dir) {
            aux = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = aux;
        }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;
    return dir;
}

#endif