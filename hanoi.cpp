/*
 * filename hanoi.cpp
 * hanoi
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int *top;
  int *base;
  int stacksize;
  char ch;
} stackHanoi;

void initStack(stackHanoi *s, int n) {
  s->base = (int*)malloc(n*sizeof(int));
  s->top = s->base;
  s->stacksize = n;
}

void pushStack(stackHanoi *s, int in) {
  *(s->top) = in;
  s->top++;
  return;
}

void popStack(stackHanoi *s, int *out) {
  s->top--;
  *out = *(s->top);
  return;
}

void clearStack(stackHanoi *s) {
  free(s->base);
  s->base = NULL;
  s->top = NULL;
  s->stacksize = 0;
}

void move(int n, stackHanoi *x, stackHanoi *y, stackHanoi *z) {
  int tmp = 0;
  if(n == 1) {
    popStack(x, &tmp);
    pushStack(z, tmp);
    printf("%c->%c\n", x->ch, z->ch);
  } else {
    move(n - 1, x, z, y);
    popStack(x, &tmp);
    pushStack(z, tmp);
    printf("%c->%c\n", x->ch, y->ch);
    move(n-1, y, x, z);
  }
}

void hanoiStack(int n) {
  stackHanoi a;
  stackHanoi b;
  stackHanoi c;
  a.ch = 'A';
  b.ch = 'B';
  c.ch = 'C';
  initStack(&a, n);
  initStack(&b, n);
  initStack(&c, n);
  for (int i = n; i > 0; i--) {
    pushStack(&a, i);
  }
  move(n, &a, &b, &c);
  clearStack(&a);
  clearStack(&b);
  clearStack(&c);
}

void hanoiRecursion(int n, char one = 'A', char two = 'B', char three = 'C') {
  if (n == 1) {
    printf("%c-->%c\n", one, three);
  } else {
    hanoiRecursion(n - 1, one, three, two);
    printf("%c-->%c\n", one, three);
    hanoiRecursion(n - 1, two, one, three);
  }
}

int main(int argc, char **argv) {

  int n;
  printf("please enter the num n:");
  fflush(stdin);
  scanf("%i", &n);

  printf("by stack:\nthe step:\n");
  hanoiStack(n);

  printf("by recursion:\nthe step:\n");
  hanoiRecursion(n);

  printf("Press enter to continue...");
  fflush(stdin);
  getchar();

  return 0;
}
