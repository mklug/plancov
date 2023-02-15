#ifndef PERMS_H
#define PERMS_H

#include "perms.c"

perm* perm_initialize(int *array, int n);
perm* perm_mult(perm* g, perm* h);
bool perm_EQ(perm* g, perm* h);
perm* perm_inverse(perm* g);
perm* id_perm(int n);
int perm_action(perm* g, int k);
void print_perm(perm* g);
void free_perm(perm* g);
void print_cycle_decomposition(perm* g);
perm* random_perm (int n);

#endif
