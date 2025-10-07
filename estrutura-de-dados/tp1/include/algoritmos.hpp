#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

typedef struct sortperf
{
  long int cmp;
  long int move;
  long int calls;
} sortperf_t;

void resetcounter(sortperf_t *s);
void inccmp(sortperf_t *s, int num);
void incmove(sortperf_t *s, int num);
void inccalls(sortperf_t *s, int num);
void insertionSort(int v[], int l, int r, sortperf_t *s);
int median(int a, int b, int c);
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s);
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s);
void quickSort(int *A, int l, int r, sortperf_t *s);
void quickSort3(int *A, int l, int r, sortperf_t *s);
void quickSortIns(int *A, int l, int r, int K, sortperf_t *s);
void quickSort3Ins(int *A, int l, int r, int K, sortperf_t *s);

#endif