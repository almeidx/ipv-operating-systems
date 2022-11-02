#include <stdlib.h>

/** Assume-se que já foi feito o srand. Devolve um inteiro entre 'de' e 'ate' */
int aleatorio(int de, int ate) { return de + (int)(((double)(ate - de + 1)) * rand() / (RAND_MAX + 1.0)); }
