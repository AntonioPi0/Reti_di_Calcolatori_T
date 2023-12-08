/*
* fattoreX.x
* defizione Input e strutture del talent
* definizione metodi e tipi richiesti/restituiti
*/

const MAX = 256;
const N = 5;
const GIUDICI = 4;

struct FattoreX{
    char candidato[MAX];
    char giudice[MAX];
    char categoria;
    char file[MAX];
    char fase;
    int voto;
};

struct Show{
    FattoreX fattoriX[N];
};

struct Giudice{
    char nome[MAX];
    int punteggio;
};

struct Giudici{
    Giudice giudice[GIUDICI];
};

struct Input{
    char nome[MAX];
    char op;
};

program FATTOREX {
	version FATTOREXVERS{
		Giudici CLASSIFICA_GIUDICI(void) = 1;
		void ESPRIMI_GIUDIZI(Input) = 2;
	} = 1;
} = 0x20000015;
