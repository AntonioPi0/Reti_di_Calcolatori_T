/* sala_c.c
 *
 */

#include "fattoreX.h"
#include <rpc/rpc.h>
#include <stdio.h>

#define N 5
#define GIUDICI 4
#define MAX_L 256

int main(int argc, char *argv[]) {
    char   *host;
    CLIENT *cl;
    int    *ris, *start_ok;
    void   *in;
    Giudici   *giudici;
    char    str[5];
    Input input;
    char candidato[MAX_L];
    int     i, j;
    char    c, ok[MAX_L];

    if (argc != 2) {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];

    cl = clnt_create(host, FATTOREX, FATTOREXVERS, "udp");
    if (cl == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    printf("Inserire:\nC) per visualizzare la classifica dei giudici\tE) per esprimere un giudizio\t^D per terminare: ");
    while (gets(ok)) {

        if (strcmp(ok, "E") == 0) {
            printf("Tipologia di operazione (P, M): \n");
            gets(ok);
            // Leggo il tipo di operazione
            while ((strcmp(ok, "P") != 0) && (strcmp(ok, "M") != 0)) {
                printf("Lettera sbagliata! Inserisci P, M: \n");
                gets(ok);
            }
            input.op = ok[0];
           

            // Leggo il nome del candidato
            
            printf("Inserisci il nome del candidato\n");
            while (scanf("%s", &candidato) != 1) {
                    /* Ricorda problema scanf...*/
                    do {
                        c = getchar();
                        printf("%c ", c);
                    } while (c != '\n');
                    printf("Candidato: ");
                }
            
            // consumo il fine linea
            gets(ok);
            strcpy(input.nome, candidato);
         
            // Invocazione remota
            esprimi_giudizi_1(&input, cl);
        } // if 
        else if (strcmp(ok, "C") == 0)
        {
            giudici = classifica_giudici_1(in, cl);
            if (giudici == NULL) {
                clnt_perror(cl, host);
                exit(1);
            }

            printf("Classifica giudici:\n");
            for (i = 0; i < GIUDICI; i++) {
                    printf("Giudice:%-10s\t punteggio: %-10d\n", giudici->giudice[i].nome, giudici->giudice[i].punteggio);
                printf("\n");
            }
        } // if something else
        else
        {
            printf("Argomento di ingresso errato!!\n");
        }
         printf("Inserire:\nC) per visualizzare la classifica dei giudici\nE) per esprimere un giudizio\t^D per terminare: ");
    } // while

    // Libero le risorse, distruggendo il gestore di trasporto
    clnt_destroy(cl);
    exit(0);
}
