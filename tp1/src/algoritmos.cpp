#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "../include/algoritmos.hpp"

void resetcounter(sortperf_t *s)
{
  // Descricao: inicializa estrutura
  // Entrada:
  // Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t *s, int num)
{
  // Descricao: incrementa o numero de comparacoes em num
  // Entrada: s, num
  // Saida: s
  s->cmp += num;
}

void incmove(sortperf_t *s, int num)
{
  // Descricao: incrementa o numero de movimentacoes de dados em num
  // Entrada: s, num
  // Saida: s
  s->move += num;
}

void inccalls(sortperf_t *s, int num)
{
  // Descricao: incrementa o numero de chamadas de função em num
  // Entrada: s, num
  // Saida: s
  s->calls += num;
}

char *printsortperf(sortperf_t *s, char *str, char *pref)
{
  // Descricao: gera string com valores de sortperf
  // Entrada: s, pref
  // Saida: str

  sprintf(str, "%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls);
  return str;
}

void initVector(int *vet, int size)
{
  // Descricao: inicializa vet com valores aleatorios
  // Entrada: vet
  // Saida: vet
  int i;
  // inicializa a parte alocada da vetor com valores aleatorios
  for (i = 0; i < size; i++)
  {
    vet[i] = (int)(drand48() * size);
  }
}

void printVector(int *vet, int size)
{
  // Descricao: inicializa vet com valores aleatorios
  // Entrada: vet
  // Saida: vet
  int i;
  for (i = 0; i < size; i++)
  {
    printf("%d ", vet[i]);
  }
  printf("\n");
}

void swap(int *xp, int *yp, sortperf_t *s)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  incmove(s, 3);
}

// shellsort
void shellSort(int *A, int n, sortperf_t *s)
{
  inccalls(s, 1);
  int h = n / 2;
  int j, chave;

  while (h > 0)
  {
    for (int i = h; i < n; i++)
    {
      int chave = A[i];
      incmove(s, 1);
      j = i - h;

      while (j >= 0 && A[j] > chave)
      {
        inccmp(s, 1);
        A[j + h] = A[j];
        incmove(s, 1);
        j -= h;
      }
      inccmp(s, 1);

      A[j + h] = chave;
      incmove(s, 1);
    }

    h /= 2;
  }
}

// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s)
{
  // find the minimum element in the unsorted subarray `[i…n-1]`
  // and swap it with `arr[i]`
  int min = l;
  inccalls(s, 1);
  for (int j = l + 1; j <= r; j++)
  {
    // if `arr[j]` is less, then it is the new minimum
    inccmp(s, 1);
    if (arr[j] < arr[min])
    {
      min = j; // update the index of minimum element
    }
  }

  // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
  if (min != l)
    swap(&arr[min], &arr[l], s);

  if (l + 1 < r)
  {
    recursiveSelectionSort(arr, l + 1, r, s);
  }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  int min;

  for (int i = 0; i < r; i++)
  {
    min = i;
    for (int j = i + 1; j < r + 1; j++)
    {
      inccmp(s, 1);
      if (arr[j] < arr[min])
      {
        min = j;
      }
    }
    if (min != i)
    {
      swap(&arr[i], &arr[min], s);
    }
  }
}

// insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  int j, chave;

  for (int i = l + 1; i <= r; i++)
  {
    chave = v[i];
    incmove(s, 1);
    j = i - 1;

    while (j >= l && chave < v[j])
    {
      inccmp(s, 1);
      incmove(s, 1);
      v[j + 1] = v[j];
      j--;
    }
    inccmp(s, 1);

    incmove(s, 1);
    v[j + 1] = chave;
  }
}

// median of 3 integers
int median(int a, int b, int c)
{
  if ((a <= b) && (b <= c))
    return b; // a b c
  if ((a <= c) && (c <= b))
    return c; // a c b
  if ((b <= a) && (a <= c))
    return a; // b a c
  if ((b <= c) && (c <= a))
    return c; // b c a
  if ((c <= a) && (a <= b))
    return a; // c a b
  return b;   // c b a
}

// quicksort partition using median of 3
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s)
{
  inccalls(s, 1);

  *i = l;
  *j = r;

  int pivo = median(A[l], A[(l + r) / 2], A[r]);

  while (*i <= *j)
  {
    while (A[*i] < pivo)
    {
      (*i)++;
      inccmp(s, 1);
    }

    while (A[*j] > pivo)
    {
      (*j)--;
      inccmp(s, 1);
    }

    inccmp(s, 1);
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }

    inccmp(s, 1);
  }
}

// standard quicksort partition
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s)
{
  inccalls(s, 1);

  int pivo = A[(*i + *j) / 2];

  *i = l;
  *j = r;

  do
  {
    inccmp(s, 1);
    while (A[*j] > pivo)
    {
      (*j)--;
      inccmp(s, 1);
    }

    while (A[*i] < pivo)
    {
      (*i)++;
      inccmp(s, 1);
    }

    inccmp(s, 1);
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }

  } while (*i <= *j);
}

// standard quicksort
void quickSort(int *A, int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  int i = l;
  int j = r;

  partition(A, l, r, &i, &j, s);

  if (l < j)
    quickSort(A, l, j, s);
  if (r > i)
    quickSort(A, i, r, s);
}

// quicksort with median of 3
void quickSort3(int *A, int l, int r, sortperf_t *s)
{
  inccalls(s, 1);

  int i = l;
  int j = r;

  partition3(A, l, r, &i, &j, s);

  if (l < j)
    quickSort3(A, l, j, s);
  if (r > i)
    quickSort3(A, i, r, s);
}

// quicksort with insertion for small partitions
void quickSortIns(int *A, int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  int i = l;
  int j = r;

  partition(A, l, r, &i, &j, s);

  int K = 50;

  if (j > l)
  {
    if (j - l <= K)
    {
      insertionSort(A, l, j, s);
    }
    else
    {
      quickSortIns(A, l, j, s);
    }
  }

  if (r > i)
  {
    if (r - i <= K)
    {
      insertionSort(A, i, r, s);
    }
    else
    {
      quickSortIns(A, i, r, s);
    }
  }
}

// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int *A, int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  int i = l;
  int j = r;

  partition3(A, l, r, &i, &j, s);

  int K = 50;

  if (j > l)
  {
    if (j - l <= K)
    {
      insertionSort(A, l, j, s);
    }
    else
    {
      quickSort3Ins(A, l, j, s);
    }
  }

  if (r > i)
  {
    if (r - i <= K)
    {
      insertionSort(A, i, r, s);
    }
    else
    {
      quickSort3Ins(A, i, r, s);
    }
  }
}