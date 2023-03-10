#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int time;
  double val;
  int ok;
  struct Node *next;
  struct Node *prev;
};

struct LR {
  int time1, time2, time3;
  double val1, val2, val3;
  struct LR *next;
  struct LR *prev;
};

struct Node *head = NULL, *tail = NULL, *head2 = NULL, *tail2 = NULL;
struct LR *l_head = NULL, *l_tail = NULL, *r_head = NULL, *r_tail = NULL;

void insereazaUltim(int ttime, double tval) {
  struct Node *temp_node = malloc(sizeof(struct Node));
  temp_node->time = ttime;
  temp_node->val = tval;
  temp_node->ok = 1;
  temp_node->next = NULL;
  temp_node->prev = NULL;
  if (head == NULL) {
    head = temp_node;
    head->prev = NULL;
    tail = temp_node;
  } else {
    tail->next = temp_node;
    temp_node->prev = tail;
    tail = temp_node;
  }
}

void insereazaUltim2(int ttime, double tval) {
  struct Node *temp_node = malloc(sizeof(struct Node));
  temp_node->time = ttime;
  temp_node->val = tval;
  temp_node->ok = 1;
  temp_node->next = NULL;
  temp_node->prev = NULL;
  if (head2 == NULL) {
    head2 = temp_node;
    head2->prev = NULL;
    tail2 = temp_node;
  } else {
    tail2->next = temp_node;
    temp_node->prev = tail2;
    tail2 = temp_node;
  }
}

void insereazaLeft(struct Node *node) {
  struct LR *temp_node = malloc(sizeof(struct LR));
  temp_node->time1 = node->prev->prev->time;
  temp_node->time2 = node->prev->time;
  temp_node->time3 = node->time;
  temp_node->val1 = node->prev->prev->val;
  temp_node->val2 = node->prev->val;
  temp_node->val3 = node->val;
  temp_node->next = NULL;
  temp_node->prev = NULL;
  if (l_head == NULL) {
    l_head = temp_node;
    l_head->prev = NULL;
    l_tail = temp_node;
  } else {
    l_tail->next = temp_node;
    temp_node->prev = l_tail;
    l_tail = temp_node;
  }
}

void insereazaRight(struct Node *node) {
  struct LR *temp_node = malloc(sizeof(struct LR));
  temp_node->time3 = node->next->next->time;
  temp_node->time2 = node->next->time;
  temp_node->time1 = node->time;
  temp_node->val3 = node->next->next->val;
  temp_node->val2 = node->next->val;
  temp_node->val1 = node->val;
  temp_node->next = NULL;
  temp_node->prev = NULL;
  if (r_head == NULL) {
    r_head = temp_node;
    r_head->prev = NULL;
    r_tail = temp_node;
  } else {
    r_tail->next = temp_node;
    temp_node->prev = r_tail;
    r_tail = temp_node;
  }
}

void insereazaDupa(int ttime, double tval, struct Node *node) {
  struct Node *temp_node = malloc(sizeof(struct Node));
  temp_node->val = tval;
  temp_node->time = ttime;
  temp_node->ok = 1;
  temp_node->next = node->next;
  temp_node->prev = node;
  node->next->prev = temp_node;
  node->next = temp_node;
}

void creazaLista(int nrperechi) {
  int ttime, i;
  double tval;
  for (i = 0; i < nrperechi; i++) {
    scanf("%d%lf", &ttime, &tval);
    insereazaUltim(ttime, tval);
  }
}

void printeazaLista(int nrperechi) {
  struct Node *temp_node;
  temp_node = head;
  printf("%d\n", nrperechi);
  while (temp_node != NULL) {
    printf("%d %.2lf\n", temp_node->time, temp_node->val);
    temp_node = temp_node->next;
  }
}

void freeLista() {
  struct Node *temp_node = head, *temp_next;
  while (temp_node != NULL) {
    temp_next = temp_node->next;
    free(temp_node);
    temp_node = temp_next;
    head = NULL;
  }
}

void freeLista2() {
  struct Node *temp_node = head2, *temp_next;
  while (temp_node != NULL) {
    temp_next = temp_node->next;
    free(temp_node);
    temp_node = temp_next;
    head2 = NULL;
  }
}

void freeListaLR(struct LR *node) {
  struct LR *temp_node = node, *temp_next;
  while (temp_node != NULL) {
    temp_next = temp_node->next;
    free(temp_node);
    temp_node = temp_next;
    node = NULL;
  }
}

double mediaVal(struct Node *node, int k) {
  struct Node *temp_node = node;
  double val = 0;
  int i;
  for (i = 0; i < k; i++) {
    val = val + temp_node->val;
    temp_node = temp_node->next;
  }
  val = val / k;
  return val;
}

double deviatiaVal(struct Node *node, int k) {
  struct Node *temp_node = node;
  double val = 0;
  double media = mediaVal(temp_node, k);
  int i;
  for (i = 0; i < k; i++) {
    val = val + pow(temp_node->val - media, 2);
    temp_node = temp_node->next;
  }
  val = val / k;
  val = sqrt(val);
  return val;
}

void removeNotOk(int *nrperechi) {
  struct Node *temp_node = head, *temp_del;
  while (temp_node != NULL) {
    if (temp_node->ok == 0) {
      temp_del = temp_node;
      temp_node = temp_node->next;
      temp_del->prev->next = temp_del->next;
      temp_del->next->prev = temp_del->prev;
      free(temp_del);
      (*nrperechi)--;
    } else
      temp_node = temp_node->next;
  }
}

void valoareMediana(struct Node *node, int k) {
  double max1, max2, max3;
  int i;
  struct Node *temp_node = node;
  max1 = max2 = max3 = LONG_MIN;
  for (i = 0; i < k; i++) {
    if (temp_node->val > max1) {
      max3 = max2;
      max2 = max1;
      max1 = temp_node->val;
    } else if (temp_node->val > max2) {
      max3 = max2;
      max2 = temp_node->val;
    } else if (temp_node->val > max3) {
      max3 = temp_node->val;
    }
    temp_node = temp_node->next;
  }
  temp_node = node;
  for (i = 0; i < k; i++) {
    if (temp_node->val == max3)
      insereazaUltim2(node->next->next->time, temp_node->val);
    temp_node = temp_node->next;
  }
}

void medieAritmetica(struct Node *node, int k) {
  int i;
  struct Node *temp_node = node;
  float medie = 0;
  for (i = 0; i < k; i++) {
    medie = medie + temp_node->val;
    temp_node = temp_node->next;
  }
  medie = medie / 5;
  insereazaUltim2(node->next->next->time, medie);
}

double C(int timestamp, struct LR *left, struct LR *right) {
  double C = (double)(timestamp - left->time3) / (right->time1 - left->time3);
  return C;
}

double w(int i) {
  double numitor = 0;
  int j;
  for (j = 0; j <= 2; j++)
    numitor = numitor + pow((double)j / 2, 2) * 0.9 + 0.1;
  return (pow((double)i / 2, 2) * 0.9 + 0.1) / numitor;
}

double f(struct LR *left, struct LR *right, int timestamp) {
  double leftSum, rightSum, f;
  f = 1 - C(timestamp, left, right);
  leftSum = left->val1 * w(0) + left->val2 * w(1) + left->val3 * w(2);
  rightSum = right->val3 * w(0) + right->val2 * w(1) + right->val1 * w(2);
  return f * leftSum + C(timestamp, left, right) * rightSum;
}

void intervale(int st) {
  struct Node *temp_node = head;
  double minVal, maxVal;
  int interval = st, contor;
  minVal = temp_node->val;
  maxVal = temp_node->val;
  temp_node = temp_node->next;
  while (temp_node != NULL) {
    if (temp_node->val < minVal)
      minVal = temp_node->val;
    if (temp_node->val > maxVal)
      maxVal = temp_node->val;
    temp_node = temp_node->next;
  }
  while (interval > minVal)
    interval = interval - st;
  while (interval < maxVal) {
    temp_node = head;
    contor = 0;
    while (temp_node != NULL) {
      if (temp_node->val > interval && temp_node->val < interval + st)
        contor++;
      temp_node = temp_node->next;
    }
    if (contor > 0)
      printf("[%d, %d] %d\n", interval, interval + st, contor);
    interval = interval + st;
  }
}
int main(int argc, char **argv) {

  int i, nrperechi, k = 5, j;
  scanf("%d", &nrperechi);
  creazaLista(nrperechi);
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--e1") == 0) {
      double media, dev;
      struct Node *temp_node = head;
      for (j = 0; j <= nrperechi - 5; j++) {
        media = mediaVal(temp_node, k);
        dev = deviatiaVal(temp_node, k);
        if ((temp_node->next->next->val < media - dev) ||
            (temp_node->next->next->val > media + dev))
          temp_node->next->next->ok = 0;
        temp_node = temp_node->next;
      }
      removeNotOk(&nrperechi);
    } else if (strcmp(argv[i], "--e2") == 0) {
      struct Node *temp_node = head, *temp_head, *temp_tail;
      for (j = 0; j <= nrperechi - 5; j++) {
        valoareMediana(temp_node, k);
        temp_node = temp_node->next;
      }
      nrperechi = nrperechi - 4;
      temp_head = head;
      head = head2;
      head2 = temp_head;
      temp_tail = tail;
      tail = tail2;
      tail = tail2;
      tail2 = temp_tail;
      freeLista2();
    } else if (strcmp(argv[i], "--e3") == 0) {
      struct Node *temp_node = head, *temp_head, *temp_tail;
      for (j = 0; j <= nrperechi - 5; j++) {
        medieAritmetica(temp_node, k);
        temp_node = temp_node->next;
      }
      nrperechi = nrperechi - 4;
      temp_head = head;
      head = head2;
      head2 = temp_head;
      temp_tail = tail;
      tail = tail2;
      tail = tail2;
      tail2 = temp_tail;
      freeLista2();
    } else if (strcmp(argv[i], "--u") == 0) {
      struct Node *temp_node = head->next;
      for (j = 1; j < nrperechi; j++) {
        if ((temp_node->time - temp_node->prev->time >= 100) &&
            (temp_node->time - temp_node->prev->time <= 1000)) {
          temp_node->time = (temp_node->prev->time + temp_node->time) / 2;
          temp_node->val = (temp_node->prev->val + temp_node->val) / 2;
        }
        temp_node = temp_node->next;
      }
    } else if (strcmp(argv[i], "--c") == 0) {
      struct Node *temp_node = head;
      while (temp_node != NULL) {
        if ((temp_node->prev != NULL) && (temp_node->next != NULL))
          if ((temp_node->prev->prev != NULL) &&
              (temp_node->next->next != NULL)) {
            insereazaLeft(temp_node);
            insereazaRight(temp_node);
          }
        temp_node = temp_node->next;
      }
      temp_node = head->next->next;
      struct LR *temp_l = l_head, *temp_r = r_head;
      while (temp_node->next->next != NULL) {
        if (temp_node->next->time - temp_node->time > 1000) {
          int timestamp = temp_node->time + 200;
          while (timestamp < temp_node->next->time) {
            insereazaDupa(timestamp, f(temp_l, temp_r->next, timestamp),
                          temp_node);
            timestamp = timestamp + 200;
            temp_node = temp_node->next;
            nrperechi++;
          }
          freeListaLR(l_head);
          freeListaLR(r_head);
          l_head = NULL;
          r_head = NULL;
          l_tail = NULL;
          r_tail = NULL;
          struct Node *temp_node2 = head;
          while (temp_node2 != NULL) {
            if ((temp_node2->prev != NULL) && (temp_node2->next != NULL))
              if ((temp_node2->prev->prev != NULL) &&
                  (temp_node2->next->next != NULL)) {
                insereazaLeft(temp_node2);
                insereazaRight(temp_node2);
              }
            temp_node2 = temp_node2->next;
          }
          temp_l = l_head;
          temp_r = r_head;
          while (temp_l->time3 != temp_node->time) {
            temp_l = temp_l->next;
            temp_r = temp_r->next;
          }
        }
        temp_node = temp_node->next;
        temp_l = temp_l->next;
        temp_r = temp_r->next;
      }
    } else if (strstr(argv[i], "--st") != 0) {
      int st = atoi(argv[i] + 4);
      intervale(st);
    }
  }
  if (strstr(argv[argc - 1], "--st") == 0)
    printeazaLista(nrperechi);
  freeLista();
  freeListaLR(l_head);
  freeListaLR(r_head);
  return 0;
}