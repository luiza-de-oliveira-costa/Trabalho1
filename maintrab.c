#include "termip.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 4000
#define T 15
#define POS_X_TEXTO 10
#define POS_Y_TEXTO 10


FILE * arquivo;

int mb = 0; // matematica basica
int trig = 0; // trigonometria
int fun = 0; // funcao
int mod = 0; // modulo
int acertos = 0;

typedef struct{
	char * enunciado;
	char * q1;
	char * q2;
	char * q3;
	char * q4;
	char * gab;
	char resp[T];
	
} question;


int le_arquivo(question * x){

	char P[N];
	int i = -1;

	arquivo = fopen("banco_de_perguntas.txt", "r");
	if(arquivo == NULL) return -1;
	
	while(!feof(arquivo)){
		i++;
		fscanf(arquivo, "%[^\n]%*c" ,P);
		x[i].enunciado = (char *) malloc(N * sizeof(char));
		if(x[i].enunciado == NULL) return -1;
		strcpy(x[i].enunciado, P);

		fscanf(arquivo, "%[^\n]%*c" ,P);
		x[i].q1 = (char *) malloc(N * sizeof(char));
		if(x[i].q1 == NULL) return -1;
		strcpy(x[i].q1, P);

		fscanf(arquivo, "%[^\n]%*c" ,P);
		x[i].q2 = (char *) malloc(N * sizeof(char));
		if(x[i].q2 == NULL) return -1;
		strcpy(x[i].q2, P);
		
		fscanf(arquivo, "%[^\n]%*c" ,P);
		x[i].q3 = (char *) malloc(N * sizeof(char));
		if(x[i].q3 == NULL) return -1;
		strcpy(x[i].q3, P);

		fscanf(arquivo, "%[^\n]%*c" ,P);
		x[i].q4 = (char *) malloc(N * sizeof(char));
		if(x[i].q4 == NULL) return -1;
		strcpy(x[i].q4, P);

		fscanf(arquivo, "%[^\n]%*c" ,P);
		x[i].gab = (char *) malloc(T * sizeof(char));
		if(x[i].gab == NULL) return -1;
		strcpy(x[i].gab, P);

	}
	return 1;
}

void imprime_pergunta(question * x, int ia, int ju){

	int i = 0;

	draw_window(POS_Y_TEXTO-1, POS_X_TEXTO-3, 100, 12,  FG_CYAN, BG_DEFAULT, "|" ATTR_BLINK_ON ATTR_ITALIC_ON " info " ATTR_ITALIC_OFF ATTR_BLINK_OFF "|");

	gotoxy(POS_Y_TEXTO,POS_X_TEXTO);
	printf("Questão %d\n" , ju+1);
	gotoxy(POS_Y_TEXTO+1,POS_X_TEXTO);
	
	while(x[ia].enunciado[i] != '\0'){
		printf("%c" , x[ia].enunciado[i]);
		i++;
		if(i%100 == 0){
			printf(" \n\t");
		}
	}
	
	gotoxy(POS_Y_TEXTO+6,POS_X_TEXTO);
	printf("%s" , x[ia].q1);
	gotoxy(POS_Y_TEXTO+7,POS_X_TEXTO);
	printf("%s" , x[ia].q2);
	gotoxy(POS_Y_TEXTO+8,POS_X_TEXTO);
	printf("%s" , x[ia].q3);
	gotoxy(POS_Y_TEXTO+9,POS_X_TEXTO);
	printf("%s" , x[ia].q4);
	gotoxy(POS_Y_TEXTO+10,POS_X_TEXTO);
	printf("RESPOSTA: ");
	scanf("%s%*c" , x[ia].resp);
	
}

int confericao_da_resposta(question * var, int ia){

    if(strcmp(var[ia].resp,var[ia].gab)==0){
        acertos++;
    }
    else{
        if(ia == 0 || ia == 1 || ia == 2 || ia == 3 || ia == 4 || ia == 8 || ia == 9){
            mb++;
        }
        if(ia == 3 || ia == 5 || ia == 6 || ia == 7){
            fun++;
        }
        if(ia == 5 || ia == 6){
            trig++;
        }
        if(ia == 9){
            mod++;
        }
    }
}

void resultado(){
	
	int f = 0;
	draw_window(POS_Y_TEXTO-1, POS_X_TEXTO-1, 200, 12,  FG_CYAN, BG_DEFAULT, "|" ATTR_BLINK_ON ATTR_ITALIC_ON " info " ATTR_ITALIC_OFF ATTR_BLINK_OFF "|"); // Nova janela para mostrar o resultado do usuario

	if(acertos == 10 || (acertos == 9 && mb == 1)){
		gotoxy(POS_Y_TEXTO,POS_X_TEXTO);
		printf("Parabéns! Resultado %d/10 :D \n" ,acertos);
	}
	else{
		gotoxy(POS_Y_TEXTO,POS_X_TEXTO);
		printf("Você teve um total de %d/10 acertos\n" ,acertos);
		if(mb > 1 || trig > 0 || mod > 0 || fun > 0){
			gotoxy(POS_Y_TEXTO+1,POS_X_TEXTO);
			printf("Para ter um melhor desempenho em Cálculo I se concentre na(s) matéria(s): ");
			if(mb > 0){
				printf("matemática básica");	
				f++;
			}
			if(trig > 0){
				if(f > 0){
					printf(", ");
				}
				printf("trigonometria");
				f++;
			}
			if(mod > 0){
				if(f > 0){
					printf(", ");
				}
				printf("módulo");
				f++;
			}
			if(fun > 0){
				if(f > 0){
					printf(", ");
				}
				printf("função");
			}
		}
	}
	printf(".\n");
		
}

int main(){

	question * var = NULL;
	int i, ia, b = 0, k,h = 0,ju;
	int repete[N];
	var = (question *) calloc(N, sizeof(question));
	if(var == NULL){
		return 0;
	}

	set_bg(COLOR_CYAN,0);
	set_fg(COLOR_WHITE,1);
	clear();
	
	printf("Questionaŕio de pré-cálculo. Responda honestamente (︶^︶)\n");

	if(le_arquivo(var) == -1) return 0;
	
	srand(time(NULL)); // os passos seguintes utilizando rand são para imprimir as perguntas de forma aleatória 
	for(i=0;i<10;i++){
		h = 0;
		ju = i;
		ia = rand() % 10; 
		for(k=0;k<i;k++){
			if(ia == repete[k]){ // para não repetir os mesmos enunciados
				h = 2;
			}
		}
		if(h != 2)
		{	
			imprime_pergunta(var,ia,ju);
    		confericao_da_resposta(var, ia);			
    		repete[b] = ia;
			b++;
		}
		else
			i--;
	}
	
	resultado();

	//free(var);
	for(i=0;i<10;i++){
		free(var[i].enunciado);
		free(var[i].q1);
		free(var[i].q2);
		free(var[i].q3);
		free(var[i].q4);
		free(var[i].gab);
	}
	free(var);
	fclose(arquivo);

	//enquanto não achar "finish" não encerra o código.
	char end[T]; printf("\t\t");
	while(scanf("%s", end), strcmp(end, "finish") != 0) printf("\t\t");
	system("clear"); // Ao terminar,  

	return 0;
}
