// Copyright Militaru-Ionut-Marius

#include <stdio.h>
#include <stdlib.h>
#define mod 10007

void eliberare_matrice(int n, int **mat)
{
	for (int i = 0; i < n; i++)
		free(mat[i]); // eliberez linia i din matrice
	free(mat);		  // eliberez matricea
}

int modul(int p)
{
	// calculez modulul
	p %= mod;
	if (p < 0)
		p += mod;
	return p;
}

void alocare_matrice(int ***matrix, int n, int m)
{
	int **aux = (int **)malloc(n * sizeof(int *));
	if (!aux) { // daca nu pot aloca, opresc executia
		*matrix = NULL;
		return;
	}
	for (int i = 0; i < n; i++) {
		aux[i] = (int *)malloc(m * sizeof(int));
		// daca una din alocari a esuat, trebuie sa dezaloc tot ce am alocat
		if (!aux[i]) {
			for (int j = 0; j < i; j++)
				free(aux[j]);
			free(aux);
			*matrix = NULL;
			return;
		}
	}
	*matrix = aux;
}

void realocare(int ****mat, int **l, int **c, int *i, int *dim, int n, int m)
{
	(*i)++; // cresc indexul
	if (*i >= *dim) { // aloc memorie in plus daca nu mai am
		*mat = realloc(*mat, 2 * (*dim) * sizeof(int **));
		*l = realloc(*l, 2 * (*dim) * sizeof(int));
		*c = realloc(*c, 2 * (*dim) * sizeof(int));
		(*dim) *= 2;
	}
	(*l)[*i] = n;
	(*c)[*i] = m;
}

void citire_matrice(int ****mat, int **lin, int **col, int *index, int *dim)
{
	int n, m;
	scanf("%d%d", &n, &m);
	realocare(mat, lin, col, index, dim, n, m);
	int **aux;
	alocare_matrice(&aux, n, m);
	if (!aux) // in caz ca nu se poate aloca aux;
		return;
	(*mat)[*index] = aux;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &aux[i][j]);
}

void redimensionare(int ****mat, int **lin, int **col, int index)
{
	int nr, *l, *c, lenl, lenc;
	scanf("%d", &nr);
	scanf("%d", &lenl); // citesc numarul de linii
	l = (int *)malloc(lenl * sizeof(int));
	for (int i = 0; i < lenl; i++) // citesc parametrii de redimensionare
		scanf("%d", &l[i]);
	scanf("%d", &lenc); // citesc numarul de coloane
	c = (int *)malloc(lenc * sizeof(int));
	for (int i = 0; i < lenc; i++)
		scanf("%d", &c[i]); // citesc parametrii de redimensionare
	if (nr > index || nr < 0) {
		printf("No matrix with the given index\n");
		free(l);
		free(c);
		return;
	}
	int **aux;
	alocare_matrice(&aux, lenl, lenc);
	if (!aux) {
		// in caz ca nu se poate aloca aux;
		free(l);
		free(c);
		return;
	}
	for (int i = 0; i < lenl; i++)
		for (int j = 0; j < lenc; j++)
			aux[i][j] = (*mat)[nr][l[i]][c[j]];
	eliberare_matrice((*lin)[nr], (*mat)[nr]);
	// inlocuiesc matricea nou formata
	(*mat)[nr] = aux;
	(*lin)[nr] = lenl;
	(*col)[nr] = lenc;
	free(l);
	free(c);
}

int **inmultire_matrici(int **mat1, int **mat2, int n1, int n2, int m2)
{
	int **aux;
	alocare_matrice(&aux, n1, m2);
	if (!aux) {
		// in caz ca nu se poate aloca aux;
		return NULL;
	}
	// inmultesc matricile mat1 si mat 2
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			aux[i][j] = 0;
			for (int k = 0; k < n2; k++) {
				aux[i][j] += mat1[i][k] * mat2[k][j];
				aux[i][j] = modul(aux[i][j]);
			}
		}
	}
	return aux;
}

void inmultire(int ****mat, int **lin, int **col, int *index, int *dim)
{
	int i1, i2, m, n, p;
	scanf("%d%d", &i1, &i2);
	if (i1 > *index || i2 > *index || i1 < 0 || i2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if ((*col)[i1] != (*lin)[i2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	m = (*lin)[i1];
	n = (*lin)[i2];
	p = (*col)[i2];
	int **aux = inmultire_matrici((*mat)[i1], (*mat)[i2], m, n, p);
	if (!aux) {
		// in caz ca nu se poate aloca aux;
		return;
	}
	realocare(mat, lin, col, index, dim, (*lin)[i1], (*col)[i2]);
	// pun matrcea rezultat la finalul vectorului de matrici
	(*mat)[*index] = aux;
}

void elib_mat_vec(int ****mat, int **lin, int **col, int *index)
{
	int nr;
	scanf("%d", &nr);
	if (nr > *index || nr < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	// eliberez matricea cu indexul citit
	eliberare_matrice((*lin)[nr], (*mat)[nr]);
	for (int i = nr; i < *index; i++) {
		(*mat)[i] = (*mat)[i + 1];
		(*lin)[i] = (*lin)[i + 1];
		(*col)[i] = (*col)[i + 1];
	}
	(*index)--;// scad indexul
}

void transpusa(int ****mat, int **lin, int **col, int index)
{
	int nr;
	scanf("%d", &nr);
	if (nr > index || nr < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int **aux;
	alocare_matrice(&aux, (*col)[nr], (*lin)[nr]);
	if (!aux) {
		// in caz ca nu se poate aloca aux;
		return;
	}
	// calculez transpusa
	for (int i = 0; i < (*lin)[nr]; i++)
		for (int j = 0; j < (*col)[nr]; j++)
			aux[j][i] = (*mat)[nr][i][j];
	for (int i = 0; i < (*lin)[nr]; i++)
		free((*mat)[nr][i]);
	free((*mat)[nr]);
	//  inlocuiesc matricea noua
	(*mat)[nr] = aux;
	int aux2 = (*lin)[nr];
	(*lin)[nr] = (*col)[nr];
	(*col)[nr] = aux2;
}

void afisare_dimensiune(int *lin, int *col, int index)
{
	int nr;
	scanf("%d", &nr);
	if (nr > index || nr < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	printf("%d %d\n", lin[nr], col[nr]);
}

void afisare_matrice(int ***mat, int *lin, int *col, int index)
{	// afisez dimensiunile matricei cu indexul dat
	int nr;
	scanf("%d", &nr);
	if (nr > index || nr < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	for (int i = 0; i < lin[nr]; i++) {
		for (int j = 0; j < col[nr]; j++)
			printf("%d ", mat[nr][i][j]);
		printf("\n");
	}
}

int sum_mat(int **mat, int lin, int col)
{
	// calzulez suma elementelor matricei
	int s = 0;
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++)
			s += mat[i][j];
	}
	return modul(s);
}

void putere_log(int ****mat, int *lin, int *col, int index)
{
	int nr, putere, m;
	scanf("%d%d", &nr, &putere);
	if (nr > index || nr < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (putere < 0) {
		printf("Power should be positive\n");
		return;
	}
	m = lin[nr];
	if (m != col[nr]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	int **rez;
	alocare_matrice(&rez, m, m);
	// initializez matricea rez cu matricea identitate de dimensiune m
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			if (i == j)
				rez[i][j] = 1;
			else
				rez[i][j] = 0;
	while (putere > 0) {
		if (putere % 2 == 1) {
			int **aux;
			aux = inmultire_matrici(rez, (*mat)[nr], m, m, m);
			eliberare_matrice(m, rez);
			rez = aux;
		}
		int **aux = inmultire_matrici((*mat)[nr], (*mat)[nr], m, m, m);
		eliberare_matrice(m, (*mat)[nr]);
		(*mat)[nr] = aux;
		putere /= 2;
	}
	// pun matricea noua in locul celei vechi
	eliberare_matrice(lin[nr], (*mat)[nr]);
	(*mat)[nr] = rez;
}

void sortare(int ****mat, int **lin, int **col, int index)
{
	int **aux1, *sum, aux2;
	sum = (int *)malloc((index + 1) * sizeof(int));
	if (!sum) {
		// daca nu pot aloca
		return;
	}
	for (int i = 0; i <= index; i++)
		sum[i] = sum_mat((*mat)[i], (*lin)[i], (*col)[i]);
	// sortez dupa suma matricile si vectorii linie si coloana
	for (int i = 0; i < index; i++)
		for (int j = i + 1; j <= index; j++)
			if (sum[i] > sum[j]) {
				aux2 = sum[i];
				sum[i] = sum[j];
				sum[j] = aux2;
				aux1 = (*mat)[i];
				(*mat)[i] = (*mat)[j];
				(*mat)[j] = aux1;
				aux2 = (*lin)[i];
				(*lin)[i] = (*lin)[j];
				(*lin)[j] = aux2;
				aux2 = (*col)[i];
				(*col)[i] = (*col)[j];
				(*col)[j] = aux2;
			}

	free(sum);
}

void adunare_matrice(int n, int **a, int **b, int ***s)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			(*s)[i][j] = a[i][j] + b[i][j];
			(*s)[i][j] = modul((*s)[i][j]);
		}
}

void scadere_matrice(int n, int **a, int **b, int ***s)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			(*s)[i][j] = a[i][j] - b[i][j];
			(*s)[i][j] = modul((*s)[i][j]);
		}
}

void sterge_strassen(int n, int ****mat, int dim)
{
	for (int i = 0; i < dim; i++)
		eliberare_matrice(n, (*mat)[i]);
}

int **inmultire_strassen(int n, int **A, int **B)
{
	int **C;
	alocare_matrice(&C, n, n);
	if (n == 1) {
		C[0][0] = A[0][0] * B[0][0];
		C[0][0] = modul(C[0][0]);
		return C;
	}
	// declar submultimile pentru cele trei multimi
	int **A11, **A12, **A21, **A22, **B11, **B12, **B21, **B22;
	int **C11, **C12, **C21, **C22, dim_n = n / 2, **aux1, **aux2;
	// aloc memorie pentru noile matrici
	int ***mat[14] = {&A11, &A12, &A21, &A22, &B11, &B12,
	&B21, &B22, &C11, &C12, &C22, &C21, &aux1, &aux2};
	for (int i = 0; i < 14; i++)
		alocare_matrice(mat[i], dim_n, dim_n);
	// impart matricile A, B și C în submatrici
	for (int i = 0; i < dim_n; i++)
		for (int j = 0; j < dim_n; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + dim_n];
			A21[i][j] = A[i + dim_n][j];
			A22[i][j] = A[i + dim_n][j + dim_n];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + dim_n];
			B21[i][j] = B[i + dim_n][j];
			B22[i][j] = B[i + dim_n][j + dim_n];
		}
	int ***M = malloc(8 * sizeof(int **));
	// calculez M1
	adunare_matrice(dim_n, A11, A22, &aux1);
	adunare_matrice(dim_n, B11, B22, &aux2);
	M[1] = inmultire_strassen(dim_n, aux1, aux2);
	// calculez M2
	adunare_matrice(dim_n, A21, A22, &aux1);
	M[2] = inmultire_strassen(dim_n, aux1, B11);
	// calculez M3
	scadere_matrice(dim_n, B12, B22, &aux1);
	M[3] = inmultire_strassen(dim_n, A11, aux1);
	// calculez M4
	scadere_matrice(dim_n, B21, B11, &aux1);
	M[4] = inmultire_strassen(dim_n, A22, aux1);
	// calculez M5
	adunare_matrice(dim_n, A11, A12, &aux1);
	M[5] = inmultire_strassen(dim_n, aux1, B22);
	// calculez M6
	scadere_matrice(dim_n, A21, A11, &aux1);
	adunare_matrice(dim_n, B11, B12, &aux2);
	M[6] = inmultire_strassen(dim_n, aux1, aux2);
	// calculez M7
	scadere_matrice(dim_n, A12, A22, &aux1);
	adunare_matrice(dim_n, B21, B22, &aux2);
	M[7] = inmultire_strassen(dim_n, aux1, aux2);
	// calculez C11
	adunare_matrice(dim_n, M[1], M[4], &aux1);
	scadere_matrice(dim_n, aux1, M[5], &aux2);
	adunare_matrice(dim_n, aux2, M[7], &C11);
	// calculez C12
	adunare_matrice(dim_n, M[3], M[5], &C12);
	// calculez C21
	adunare_matrice(dim_n, M[2], M[4], &C21);
	// calculez C22
	scadere_matrice(dim_n, M[1], M[2], &aux1);
	adunare_matrice(dim_n, M[3], aux1, &aux2);
	adunare_matrice(dim_n, M[6], aux2, &C22);
	for (int i = 1; i <= 7; i++)
		eliberare_matrice(dim_n, M[i]);
	free(M);
	for (int i = 0; i < dim_n; i++)
		for (int j = 0; j < dim_n; j++) {
			C[i][j] = C11[i][j];
			C[i][j + dim_n] = C12[i][j];
			C[i + dim_n][j] = C21[i][j];
			C[i + dim_n][j + dim_n] = C22[i][j];
		}
	sterge_strassen(dim_n, mat, 14);
	return C;
}

void strassen(int ****mat, int **lin, int **col, int *index, int *dim)
{
	int i1, i2;
	scanf("%d%d", &i1, &i2);
	if (i1 > *index || i2 > *index || i1 < 0 || i2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if ((*col)[i1] != (*lin)[i2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	int **rez;
	// alocare_matrice(&rez,(*lin)[i1],(*lin)[i1]);
	rez = inmultire_strassen((*lin)[i1], (*mat)[i1], (*mat)[i2]);
	realocare(mat, lin, col, index, dim, (*lin)[i1], (*col)[i2]);
	// pun matricea rezultat in vectorul de matrici
	(*mat)[*index] = rez;
}

int main(void)
{
	int index, ***mat, *lin, *col, dim;
	char c, d;
	index = -1;
	// initializez cu -1 pentru a fi sigur ca citesc minim o matrice
	dim = 1;
	mat = (int ***)malloc(1 * sizeof(int **));
	lin = (int *)malloc(1 * sizeof(int));
	col = (int *)malloc(1 * sizeof(int));
	do {
		scanf("%c", &c);
		if (c == 'L')
			citire_matrice(&mat, &lin, &col, &index, &dim);
		else if (c == 'D')
			afisare_dimensiune(lin, col, index);
		else if (c == 'P')
			afisare_matrice(mat, lin, col, index);
		else if (c == 'C')
			redimensionare(&mat, &lin, &col, index);
		else if (c == 'M')
			inmultire(&mat, &lin, &col, &index, &dim);
		else if (c == 'O')
			sortare(&mat, &lin, &col, index);
		else if (c == 'T')
			transpusa(&mat, &lin, &col, index);
		else if (c == 'R')
			putere_log(&mat, lin, col, index);
		else if (c == 'F')
			elib_mat_vec(&mat, &lin, &col, &index);
		else if (c == 'S')
			strassen(&mat, &lin, &col, &index, &dim);
		else if (c != 'Q')
			printf("Unrecognized command\n");
		scanf("%c", &d); // citesc enterul dupa fiecare comanda
	} while (c != 'Q');
	// eliberez vectorul de matrici si vectorul linie si coloana
	for (int i = 0; i <= index; i++) {
		for (int j = 0; j < lin[i]; j++)
			free(mat[i][j]);
		free(mat[i]);
	}
	free(mat);
	free(lin);
	free(col);

	return 0;
}
