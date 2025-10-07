#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "../include/algoritmos.hpp"

void resetcounter(sortperf_t *s) {
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t *s, int num) {
  s->cmp += num;
}

void incmove(sortperf_t *s, int num) {
  s->move += num;
}

void inccalls(sortperf_t *s, int num) {
  s->calls += num;
}

void swap(int *xp, int *yp, sortperf_t *s) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  incmove(s, 3);
}

// insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s) {
  inccalls(s, 1);
  int j, chave;

  for (int i = l + 1; i <= r; i++) {
    chave = v[i];
    incmove(s, 1);
    j = i - 1;

    while (j >= l && chave < v[j]) {
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
int median(int a, int b, int c) {
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
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
  inccalls(s, 1);

  *i = l;
  *j = r;

  int pivo = median(A[l], A[(l + r) / 2], A[r]);

  while (*i <= *j) {
    while (A[*i] < pivo) {
      (*i)++;
      inccmp(s, 1);
    }

    while (A[*j] > pivo) {
      (*j)--;
      inccmp(s, 1);
    }

    inccmp(s, 1);
    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }

    inccmp(s, 1);
  }
}

// standard quicksort partition
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
  inccalls(s, 1);

  int pivo = A[(*i + *j) / 2];

  *i = l;
  *j = r;

  do {
    inccmp(s, 1);
    while (A[*j] > pivo) {
      (*j)--;
      inccmp(s, 1);
    }

    while (A[*i] < pivo) {
      (*i)++;
      inccmp(s, 1);
    }

    inccmp(s, 1);
    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }

  } while (*i <= *j);
}

// standard quicksort
void quickSort(int *A, int l, int r, sortperf_t *s) {
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
void quickSort3(int *A, int l, int r, sortperf_t *s) {
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
void quickSortIns(int *A, int l, int r, int K, sortperf_t *s)
{
  inccalls(s, 1);
  int i = l;
  int j = r;

  partition(A, l, r, &i, &j, s);

  if (j > l) {
    if (j - l <= K) {
      insertionSort(A, l, j, s);
    } else {
      quickSortIns(A, l, j, K, s);
    }
  }

  if (r > i) {
    if (r - i <= K) {
      insertionSort(A, i, r, s);
    } else {
      quickSortIns(A, i, r, K, s);
    }
  }
}

// quicksort com mediana de 3 e insertion para partições pequenas
void quickSort3Ins(int *A, int l, int r, int K, sortperf_t *s) {
  inccalls(s, 1);
  int i = l;
  int j = r;

  partition3(A, l, r, &i, &j, s);

  if (j > l) {
    if (j - l < K) {
      insertionSort(A, l, j, s);
    } else{
      quickSort3Ins(A, l, j, K, s);
    }
  }

  if (r > i) {
    if (r - i < K) {
      insertionSort(A, i, r, s);
    } else {
      quickSort3Ins(A, i, r, K,s);
    }
  }
}