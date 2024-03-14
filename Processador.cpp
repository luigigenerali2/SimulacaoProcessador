#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<conio2.h>
#include "tad.h"

void exibe_moldura()
{
	int CI=1,CF=120,LI=2,LF=27,i;
	textcolor(WHITE);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,6);
		printf("%c",205);
	}
	gotoxy(CI,6);
	printf("%c",204);
	gotoxy(CF,6);
	printf("%c",185);
	textcolor(BLUE);
	gotoxy(12,4);
	printf("** Processador 1 **");
	gotoxy(38,4);
	printf("** Processador 2 **");
	gotoxy(64,4);
	printf("** Processador 3 **");
	gotoxy(90,4);
	printf("** Processador 4 **");
	LI=8;LF=12;CI=8;CF=32;
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	for(int j=0; j<4;j++){
		for(i=CI+1;i<CF;i++)
		{
			gotoxy(i,LI);
			printf("%c",205);
			gotoxy(i,LF);
			printf("%c",205);
		}
		for(i=LI+1;i<LF;i++)
		{
			gotoxy(CI,i);
			printf("%c",186);
			gotoxy(CF,i);
			printf("%c",186);
		}
		CI=CF+3;
		CF+=28;
	}
}

int LerProcesso(tpReg &registro, FILE *processos) {
	if(!feof(processos)) {
		fscanf(processos ,"%d;%[^;];%[^;];%d", &registro.processador, &registro.nome, &registro.processo, &registro.ut);
		
		if(stricmp(registro.processo, "Gravar em dispostivo interno") == 0) {
			registro.prioridade = 1;	
		}
		else if(stricmp(registro.processo, "Gravar em dispostivo externo") == 0) {
			registro.prioridade = 2;
		}
		else if(stricmp(registro.processo, "Deletar") == 0) {
			registro.prioridade = 3;
		}
		else if(stricmp(registro.processo, "Ler") == 0) {
			registro.prioridade = 4;
		}
		else {
			registro.prioridade = 5;
		}
		return 1;
	}
	return 0;
}

void inicializaProcessador(tpDescProcessador &listaProcessador, int quant) {
	
	inicializarListaProcessador(listaProcessador);
	for(int i = 0; i < quant; i++) {
		inserirProcessador(listaProcessador);
	}
}

void insereProcessoProcessador(tpProcessador *processador, tpReg registro) {
	inserirOrdenadoProcesso(processador->listaProcesso, registro);
}

char iniciaProcesso(tpProcessador &processador) {
	if(!vaziaListaProcesso(processador.listaProcesso)) {
		processador.processando = retirarInicioListaProcesso(processador.listaProcesso);
		return 1;
	}
	return 0;
}

char processando(tpProcessador *processador) {
	if(processador->processando.ut == 0) return 0;
	return 1;
}

char processaOperacao(tpProcessador *processador) {
	processador->processando.ut--;
	if(processador->processando.ut == 0)
		return 1;
	return 0;
}

FILE *novoArquivoLer(char nomeArquivo[100]) {
	FILE *arquivo;
	arquivo = fopen(nomeArquivo, "w");
	fclose(arquivo);
	
	arquivo = fopen(nomeArquivo, "r+");
	
	return arquivo;
}

FILE *arqtemp() {
	FILE *novoArquivo;
	novoArquivo = novoArquivoLer("temp.txt");
	
	return novoArquivo;
}

void processaOperacaoDoProcessador(tpProcessador *processador, char encerra) {
	
	if(!processando(processador) && encerra == 0) {
		if(!vaziaListaProcesso(processador->listaProcesso)) {
			processador->processando = retirarInicioListaProcesso(processador->listaProcesso);
		}
	} else if(processando(processador)){
		processaOperacao(processador);		
	}
}

void processaListaProcessador(tpDescProcessador &listaProcessador, char encerra) {
	tpProcessador *processador = listaProcessador.inicio;
	while(processador) {
		processaOperacaoDoProcessador(processador, encerra);
		processador = processador->prox;
	}
}

void exibeItem(tpProcessador *processador) {
	int j;
	while(processador !=NULL){
		if(processando(processador)){
			if(processador->processando.processador==1){
				gotoxy(9,9);
				if(strlen(processador->processando.nome)>17){
					for(j=0; j<15; j ++)
						printf("%c",processador->processando.nome[j]);
					printf("...");
				}
				else
					printf("%s",processador->processando.nome);
				gotoxy(9,10);
				printf("UT: %d",processador->processando.ut);
				gotoxy(9,11);
				printf("Tipo: %s",processador->processando.processo);
			}
			if(processador->processando.processador==2){
				gotoxy(37,9);
				if(strlen(processador->processando.nome)>17){
					for(j=0; j<15; j ++)
						printf("%c",processador->processando.nome[j]);
					printf("...");
				}
				else
					printf("%s",processador->processando.nome);
				gotoxy(37,10);
				printf("UT: %d",processador->processando.ut);
				gotoxy(37,11);
				printf("Tipo: %s",processador->processando.processo);
			}
			if(processador->processando.processador==3)
			{
				gotoxy(67,9);
				if(strlen(processador->processando.nome)>17){
					for(j=0; j<15; j ++)
						printf("%c",processador->processando.nome[j]);
					printf("...");
				}
				else
					printf("%s",processador->processando.nome);
				gotoxy(67,10);
				printf("UT: %d",processador->processando.ut);
				gotoxy(67,11);
				printf("Tipo: %s",processador->processando.processo);
			}
			if(processador->processando.processador==4){
				gotoxy(93,9);
				if(strlen(processador->processando.nome)>17){
					for(j=0; j<15; j ++)
						printf("%c",processador->processando.nome[j]);
					printf("...");
				}
				else
					printf("%s",processador->processando.nome);
				gotoxy(93,10);
				printf("UT: %d",processador->processando.ut);
				gotoxy(93,11);
				printf("Tipo: %s",processador->processando.processo);
			}
		} else {
			if(processador->processando.processador==1){
				gotoxy(9,9);
				printf("Nenhum Processo");
			}
			if(processador->processando.processador==2){
				gotoxy(37,9);
				printf("Nenhum Processo");
			}
			if(processador->processando.processador==3){
				gotoxy(67,9);
				printf("Nenhum Processo");
			}
			if(processador->processando.processador==4){
				gotoxy(93,9);
				printf("Nenhum Processo");
			}
		}
		processador=processador->prox;
	}
}

char listaProcessando(tpDescProcessador listaProcessador) {
	tpProcessador *processador;
	processador = listaProcessador.inicio;
	
	while(processador != NULL && processador->processando.ut == 0) {
		processador = processador->prox;
	}
	
	return processador != NULL;
}

void iniciaProcessamento(FILE *arquivo, int &ut, tpDescProcessador &listaProcessador) {
	char tecla = 0, encerra = 0;
	tpReg registro;
	tpProcessador *Proc;
	int verifica, processador,numprocessador,cont=1,quantproc1=0,quantproc2=0,quantproc3=0,quantproc4=0;
	exibe_moldura();
	while((tecla != 27 && !feof(arquivo)) || listaProcessando(listaProcessador)) {
		system("cls");
		exibe_moldura();
		processaListaProcessador(listaProcessador, encerra);
		if(kbhit() && encerra == 0) {
			tecla = getch();
		} 
		if(tecla == 27) 
			encerra = 1;
		verifica = LerProcesso(registro, arquivo);
		if(verifica == 1) {
			if(encerra == 0){
				insereProcessoProcessador(retornaProcessador(listaProcessador, registro.processador), registro);
				numprocessador=registro.processador;
				if(numprocessador==1)
					quantproc1++;
				else if(numprocessador==2)
					quantproc2++;
				else if(numprocessador==3)
					quantproc3++;
				else
					quantproc4++;
			}
			exibeItem(retornaProcessador(listaProcessador, 1));
			exibeLista(retornaProcessador(listaProcessador, 1)->listaProcesso.inicio,cont);
			exibeItem(retornaProcessador(listaProcessador, 2));
			exibeLista(retornaProcessador(listaProcessador, 2)->listaProcesso.inicio,cont);
			exibeItem(retornaProcessador(listaProcessador, 3));
			exibeLista(retornaProcessador(listaProcessador, 3)->listaProcesso.inicio,cont);
			exibeItem(retornaProcessador(listaProcessador, 4));
			exibeLista(retornaProcessador(listaProcessador, 4)->listaProcesso.inicio,cont);
		}
		ut++;
		Sleep(2000);
		cont=1;
	}
	system("cls");
	exibe_moldura();
	gotoxy(9,9);
	printf("Tarefas executadas: %d",quantproc1);
	gotoxy(37,9);
	printf("Tarefas executadas: %d",quantproc2);
	gotoxy(67,9);
	printf("Tarefas executadas: %d",quantproc3);
	gotoxy(93,9);
	printf("Tarefas executadas: %d",quantproc4);
	gotoxy(53,16);
	printf("Tarefas executadas total(sessao): %d",quantproc1+quantproc2+quantproc3+quantproc4);
	
}

char listaEmExecucao(tpDescProcessador listaProcessador) {
	tpProcessador *processador;
	processador = listaProcessador.inicio;
	
	while(processador != NULL && processador->listaProcesso.inicio == NULL)
		processador = processador->prox;
		
	return processador != NULL;
}

void gravaResto(FILE *arquivo, tpDescProcessador &listaProcessador) {
	tpProcessador *processador;
	tpReg registro;
	
	while(listaEmExecucao(listaProcessador)) {
		processador = listaProcessador.inicio;
			
		while(processador) {
			if(!vaziaListaProcesso(processador->listaProcesso)) {
				registro = retirarInicioListaProcesso(processador->listaProcesso);
				fprintf(arquivo, "%d;%s;%s;%d\n", registro.processador, registro.nome, registro.processo, registro.ut);	
			}
			processador = processador->prox;
		}
	}
}

void gravaRestoArquivo(FILE *arquivo, FILE *arquivoAntigo) {
	tpReg registro;
	LerProcesso(registro, arquivoAntigo);
	while(!feof(arquivoAntigo)) {
		fprintf(arquivo, "%d;%s;%s;%d\n", registro.processador, registro.nome, registro.processo, registro.ut);
		LerProcesso(registro, arquivoAntigo);
	}
}

FILE *renomear(FILE *arquivo, char nome[100]) {
	fclose(arquivo);
	remove(nome);
	rename("temp.txt", nome);

	arquivo = fopen(nome, "r+");
	return arquivo;
}

FILE *gravarProcessoNovoArquivo(FILE *processos, tpDescProcessador &listaProcessador) {
	FILE *arquivoRetomada;
	arquivoRetomada = arqtemp();
	
	gravaResto(arquivoRetomada, listaProcessador);
	gravaRestoArquivo(arquivoRetomada, processos);
	fclose(processos);
	arquivoRetomada = renomear(arquivoRetomada, "retomarProcessos.txt");
	
	return arquivoRetomada;
}

int main(void) {
	tpDescProcessador listaProcessador;
	inicializaProcessador(listaProcessador, 4);
	int ut = 0;
	FILE *processosArq;
	processosArq = fopen("retomarProcessos.txt", "r+");
	if (processosArq == NULL) {
		fclose(processosArq);
		processosArq = fopen("processos.txt", "r+");
	}
	iniciaProcessamento(processosArq, ut, listaProcessador);
	processosArq = gravarProcessoNovoArquivo(processosArq, listaProcessador);
	fclose(processosArq);
	
	return 0;
}
