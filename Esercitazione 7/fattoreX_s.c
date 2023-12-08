/* fattoreX_s.c
 */

#include "fattoreX.h"
#include <fcntl.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX 256

/* STATO SERVER */
static Show fattoreX;
static Giudici judge;
static int inizializzato = 0;

void inizializza() {
    int i,randomjudge,randomcat,randomphase;

    if (inizializzato == 1) {
        return;
    }

    // inizializzazione struttura dati FattoreX
    char *candidati[] = {"Pino","Vittoria","Piero","Jhonatan","Guglielmo","Gianfranco"};
    char *giudici[] = {"Gianni","Loredana","J-AX","Manuel"};
    char categoria[] = {'U','D','O','B'};
    char fase[] = {'A','B','S'};
    char conc[MAX] = ".txt";
    char cand[MAX] = "";

    printf("%-13s %-13s %-13s %-13s %-13s %-13s\n","Candidato","Categoria","File","Giudice","Fase","Voto");
    
    for(i = 0; i < N; i++) {
      
        randomjudge = rand()%4;
        randomcat = rand()%4;
        randomphase= rand()%3;
        strcpy(cand,candidati[i]);
      
        strcpy(fattoreX.fattoriX[i].candidato,candidati[i]);
        fattoreX.fattoriX[i].categoria = categoria[randomcat];
        strcpy(fattoreX.fattoriX[i].file,strcat(cand,conc));
        strcpy(fattoreX.fattoriX[i].giudice,giudici[randomjudge]);
        fattoreX.fattoriX[i].fase = fase[randomphase];
        fattoreX.fattoriX[i].voto = 0;
      
        printf("%-13s %-13c %-13s %-13s %-13c %-13d\n", fattoreX.fattoriX[i].candidato, fattoreX.fattoriX[i].categoria,
        fattoreX.fattoriX[i].file,fattoreX.fattoriX[i].giudice,fattoreX.fattoriX[i].fase,fattoreX.fattoriX[i].voto);
     }

    // inizializzazione struttura dei giudici
    for(i = 0; i < GIUDICI; i++) {
        strcpy(judge.giudice[i].nome, giudici[i]);
        judge.giudice[i].punteggio = 0;
    }

    inizializzato = 1;
    printf("Terminata inizializzazione struttura dati!\n");
}

// algoritmo di ordinamento per i giudici
void bubbleSort(Giudici giudici, int n) {
    int i,j;

    Giudice temp;
    for(int i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(giudici.giudice[j].punteggio> giudici.giudice[j+1].punteggio) {
                temp = giudici.giudice[j];
                giudici.giudice[j] = giudici.giudice[j+1];
                giudici.giudice[j+1] = temp;
            }
        }
    }
}

Giudici *classifica_giudici_1_svc(void *in, struct svc_req *rqstp) {

    if(inizializzato == 0)
        inizializza();

    printf("Ricevuta richiesta di giudici ordinati per punteggio");
    bubbleSort(judge,GIUDICI);

    return (&judge);
} // classifica giudici

void *esprimi_giudizi_1_svc(Input *input, struct svc_req *rqstp) {
    
    if(inizializzato == 0)
        inizializza();
        
        int i;
        char giudice[256];
            for(i = 0; i < N; i++) {
                if(strcmp(input->nome,fattoreX.fattoriX[i].candidato) == 0) {
                    strcpy(giudice,fattoreX.fattoriX[i].giudice);
                    input->op == 'P' ? fattoreX.fattoriX[i].voto++ : fattoreX.fattoriX[i].voto--;
                     }    
                }
            for(i = 0; i< GIUDICI; i++){
                if(strcmp(giudice,judge.giudice[i].nome) == 0) {
                    input->op == 'P' ? judge.giudice[i].punteggio++ : judge.giudice[i].punteggio--;
                }
            }
}// esprimo giudizio
