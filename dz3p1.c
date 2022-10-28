#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct graf {
	int n;
	int e;
	int* gph;
	int* edg;
	int* wgh;
} grafStruct;

grafStruct* noviGraf(n) {
	grafStruct* graf = (grafStruct*)malloc(sizeof(grafStruct));
	graf->e = 0;
	graf->n = n;
	graf->n++;
	graf->gph = (int*)malloc(graf->n * sizeof(int));
	memset(graf->gph, 0, (graf->n) * sizeof(int));
	graf->edg = NULL;
	graf->wgh = NULL;
	return graf;
}

void noviCvor(grafStruct* graf) {
	graf->n++;
	graf->gph = (int*) realloc(graf->gph, (graf->n)*sizeof(int));
	(graf->gph)[(graf->n) - 1] = (graf->gph)[(graf->n) - 2];
}

void ispisGrafa(grafStruct* graf) {
	for (int i = 0; i < graf->n; i++) {
		printf("%d ", graf->gph[i]);
	}
	putchar('\n');
	for (int i = 0; i < graf->e; i++) {
		printf("%d ", graf->edg[i]);
	}
	putchar('\n');
	for (int i = 0; i < graf->e; i++) {
		printf("%d ", graf->wgh[i]);
	}
	printf("\n-----------------------\n");
}

void ispis(grafStruct* graf) {
	for (int i = 0; i < graf->n - 1; i++) {
		printf("\n%d\n", i + 1);
		for (int j = graf->gph[i]; j < graf->gph[i + 1]; j++) {
			printf("%d [%d] | ", graf->edg[j], graf->wgh[j]);
		}
	}
	printf("\n\n%d %d\n", graf->n, graf->e);
	printf("-----------------------\n");
}

void brisanjeCvora(int a, grafStruct* graf) {
	if (a > graf->n) {
		printf("Nepostojeci cvor");
		return;
	}
	int g = 0, f = 0, i = 0, j=1;
	for (; i + g < graf->e; i++) {
		if (j >= a)
			f = 1;
		if (i + g == (graf->gph)[j+f]) {
			(graf->gph)[j] = (graf->gph)[j + f] - g;
			j++;
		}
		(graf->edg)[i] = (graf->edg)[i + g];
		(graf->wgh)[i] = (graf->wgh)[i + g];
		if ((graf->edg)[i + g] == a || i + g >= (graf->gph)[a - 1] && i + g < (graf->gph)[a]) {
			g++;
			i--;
		}
		else if ((graf->edg)[i] > a)
			(graf->edg)[i]--;
	}
	for(; j< graf->n; j++)
		(graf->gph)[j] = (graf->gph)[j + f] - g;
	graf->gph = (int*) realloc(graf->gph, (--(graf->n)) * sizeof(int));
	graf->edg = (int*) realloc(graf->edg, (graf->e - g) * sizeof(int));
	graf->wgh = (int*) realloc(graf->wgh, (graf->e - g) * sizeof(int));
	graf->e -= g;
}

void novaGrana(int a, int b, int w, grafStruct* graf) {
	graf->e++;
	graf->edg = (int*) realloc(graf->edg, (graf->e) * sizeof(int));
	graf->wgh = (int*) realloc(graf->wgh, (graf->e) * sizeof(int));
	int i;
	for (i = graf->e-1; i > (graf->gph)[a]; i--) {
		(graf->edg)[i] = (graf->edg)[i - 1];
		(graf->wgh)[i] = (graf->wgh)[i - 1];
	}
	(graf->edg)[i] = b;
	(graf->wgh)[i] = w;
	for (i = a; i < graf->n; i++) {
		(graf->gph)[i]++;
	}
	//ispisGrafa(*n, graf->gph, *e, graf->edg);
}

void brisanjeGrane(int i, /*int a, int b, */ grafStruct* graf) {
	//int i;
	/*for (i = (*gph)[a - 1]; i < (*gph)[a]; i++) {
		if ((*edg)[i] == b)
			break;
	}
	if (i == (*gph)[a]) {
		printf("Nepostojeca grana");
		return;
	}*/
	int a;
	for (a = 0; a < graf->n; a++) {
		if (i < (graf->gph)[a + 1])
			break;
	}
	a++;
	for (; i < (graf->e) - 1; i++) {
		(graf->edg)[i] = (graf->edg)[i + 1];
		(graf->wgh)[i] = (graf->wgh)[i + 1];
	}
	for (i = a; i < (graf->n); i++) {
		(graf->gph)[i]--;
	}
	(graf->e)--;
	graf->edg = (int*) realloc(graf->edg, (graf->e) * sizeof(int));
	graf->wgh = (int*) realloc(graf->wgh, (graf->e) * sizeof(int));
}

void brisanjeGrafa(grafStruct* graf) {
	free(graf->gph);
	free(graf->edg);
	free(graf->wgh);
	graf->e = 0;
	graf->n = 0;
	free(graf);
}

grafStruct* grafDatoteka() {
	FILE* matrica = fopen("graf3.txt", "r");
	if (!matrica) {
		printf("nepostojeca datoteka");
		return 0;
	}
	int n;
	fscanf(matrica, "%d", &n);
	grafStruct* graf = noviGraf(n);
	for (int i = 0; i < graf->n - 1; i++) {
		for (int j = 0; j < graf->n - 1; j++) {
			int w;
			fscanf(matrica, "%d", &w);
			if (w) {
				novaGrana(i + 1, j + 1, w, graf);
			}
		}
	}
	fclose(matrica);
	return graf;
}

void ciklusi(grafStruct* graf) {
	int* pos = (int*) malloc((graf->n-1)*sizeof(int));
	//int* pos = (int*) malloc(30 * sizeof(int));
	for (int i = 0; i < graf->n - 1; i++) {
		pos[i] = (graf->gph)[i] - 1;
	}
	int cv = 0;
	int* stk = (int*) malloc((graf->n - 1) * sizeof(int));
	stk[0] = 0;
	//printf("%d ", stk[cv] + 1);
	while (1) {
		while (cv >= 0) {
			int tCvor = stk[cv];
			if (++pos[tCvor] < (graf->gph)[tCvor + 1]) {
				int grana = pos[tCvor];
				if ((graf->wgh)[grana] > 0) {
					int prvi = (graf->edg)[grana] - 1;
					if (pos[prvi] >= (graf->gph)[prvi] && pos[prvi] < (graf->gph)[prvi + 1]) {
						printf("%d ", prvi + 1);
						int clan = pos[prvi];
						int min = (graf->wgh)[clan];
						while (clan != grana) {
							printf("%d ", (graf->edg)[clan]);
							clan = pos[(graf->edg)[clan] - 1];
							if ((graf->wgh)[clan] < min) {
								min = (graf->wgh)[clan];
							}
							cv--;
						}
						printf("%d [%d]\n", prvi + 1, min);
						(graf->wgh)[clan] -= min;
						clan = pos[prvi];
						while (clan != grana) {
							pos[prvi] = (graf->gph)[prvi]-1;
							(graf->wgh)[clan] -= min;
							prvi = (graf->edg)[clan] - 1;
							clan = pos[(graf->edg)[clan] - 1];
						}
						pos[tCvor]--;
					}
					else {
						cv++;
						stk[cv] = (graf->edg)[pos[tCvor]] - 1;
						//printf("%d ", stk[cv] + 1);
					}
				}
			}
			else {
				cv--;
			}
		}
		int i;
		for (i = 0; i < graf->n - 1; i++) {
			if (pos[i] == (graf->gph)[i] - 1) {
				stk[0] = i;
				cv = 0;
				break;
			}
		}
		if (i == graf->n - 1)
			break;
	}
	for (int i = 0; i < graf->e; i++) {
		if ((graf->wgh)[i] == 0) {
			brisanjeGrane(i, graf);
			i--;
		}
	}
	printf("-----------------------\n");
}

void ciklusiR(grafStruct* graf) {
	int* pos = (int*)malloc((graf->n - 1) * sizeof(int));
	//int* pos = (int*) malloc(30 * sizeof(int));
	for (int i = 0; i < graf->n - 1; i++) {
		pos[i] = (graf->gph)[i] - 1;
	}
	int cv = 0;
	int* stk = (int*)malloc((graf->n - 1) * sizeof(int));
	stk[0] = 0;
	//printf("%d ", stk[cv] + 1);
	while (1) {
		while (cv >= 0) {
			int tCvor = stk[cv];
			if (++pos[tCvor] < (graf->gph)[tCvor + 1]) {
				int grana = pos[tCvor];
				int prvi = (graf->edg)[grana] - 1;
				if (pos[prvi] >= (graf->gph)[prvi] && pos[prvi] < (graf->gph)[prvi + 1]) {
					printf("%d ", prvi + 1);
					int clan = pos[prvi];
					int min = (graf->wgh)[clan];
					while (clan != grana) {
						printf("%d ", (graf->edg)[clan]);
						clan = pos[(graf->edg)[clan] - 1];
						if ((graf->wgh)[clan] < min) {
							min = (graf->wgh)[clan];
						}
						//cv--;
					}
					printf("%d [%d]\n", prvi + 1, min);
					/*(graf->wgh)[clan] -= min;
					clan = pos[prvi];
					while (clan != grana) {
						pos[prvi] = (graf->gph)[prvi] - 1;
						(graf->wgh)[clan] -= min;
						prvi = (graf->edg)[clan] - 1;
						clan = pos[(graf->edg)[clan] - 1];
					}*/
					cv--;
					//pos[tCvor]--;
				}
				else {
					cv++;
					stk[cv] = (graf->edg)[pos[tCvor]] - 1;
					//printf("%d ", stk[cv] + 1);
				}
			}
			else {
				cv--;
			}
		}
		int i;
		for (i = 0; i < graf->n - 1; i++) {
			if (pos[i] == (graf->gph)[i] - 1) {
				stk[0] = i;
				cv = 0;
				break;
			}
		}
		if (i == graf->n - 1)
			break;
	}
	for (int i = 0; i < graf->e; i++) {
		if ((graf->wgh)[i] == 0) {
			brisanjeGrane(i, graf);
			i--;
		}
	}
	printf("-----------------------\n");
}

// 0 1 2 2 3 4 5
// 0 1 2 3 4 5

// 0 2 4 5 6 7
// 2 5 3 4 4 5 2

int main()
{
	grafStruct* graf = NULL;
	/*graf = noviGraf(4);
	novaGrana(1, 2, 8, graf);
	novaGrana(2, 3, 1, graf);
	novaGrana(3, 4, 2, graf);
	novaGrana(2, 4, 3, graf);
	noviCvor(graf);
	novaGrana(1, 5, 4, graf);
	novaGrana(5, 2, 6, graf);
	novaGrana(4, 1, 7, graf);*/
	////ispis(graf);
	//ciklusiR(graf);
	//ispisGrafa(graf);
	////brisanjeCvora(1, graf);
	////ispisGrafa(graf);
	/*graf = grafDatoteka();
	ispisGrafa(graf);
	ciklusi(graf);
	ispis(graf);*/
	while (1) {
		int t;
		int n;
		int a, b, w;
		if (!graf) {
			printf("1. pravljenje praznog grafa\n2. dodavanje grafa iz datoteke\n");
			scanf("%d", &t);
			switch (t) {
			case 1:
				scanf("%d", &n);
				if (n > 0) {
					graf = noviGraf(n);
				}
				else {
					printf("broj cvorova mora biti veci od 0");
				}
				break;
			case 2:
				graf = grafDatoteka();
				break;
			}
		}
		else {
			printf("1. dodavanje cvora\n2. brisanje cvora\n3. dodavanje grane\n4. brisanje grane\n5. ispis grafa\n6. brisanje grafa\n7. kompenzacija ciklusa\n8. izlazak\n");
			scanf("%d", &t);
			switch (t) {
			case 1:
				noviCvor(graf);
				break;
			case 2:
				scanf("%d", &n);
				if (n > 0 && n < graf->n) {
					brisanjeCvora(n, graf);
				}
				else {
					printf("nepostojeci cvor\n");
				}
				break;
			case 3:
				scanf("%d %d %d", &a, &b, &w);
				if (a > 0 && a < graf->n && b > 0 && b < graf->n) {
					novaGrana(a, b, w, graf);
				}
				else {
					printf("nepostojeci cvorovi\n");
				}
				break;
			case 4:
				scanf("%d %d", &a, &b);
				int i;
				for (i = graf->gph[a - 1]; i < graf->gph[a]; i++) {
					if (graf->edg[i] == b)
						break;
				}
				if (i == graf->gph[a]) {
					printf("nepostojeca grana\n");
					break;
				}
				else {
					brisanjeGrane(i, graf);
				}
				break;
			case 5:
				ispisGrafa(graf);
				break;
			case 6:
				brisanjeGrafa(graf);
				graf = NULL;
				break;
			case 7:
				ciklusi(graf);
				break;
			case 8:
				return 0;
			}

		}
	}
	return 0;
}

/*10
0 2 0 0 5 0 0 0 0 0
0 0 1 5 0 0 0 0 0 0 
0 0 0 5 0 0 0 0 0 0
5 0 0 0 0 0 0 0 0 0
0 5 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 5 0 0 0
0 0 0 0 0 0 0 1 0 2
0 0 0 0 0 0 0 0 5 0
0 0 0 0 0 0 0 0 0 5
0 0 0 0 0 5 0 0 0 0*/