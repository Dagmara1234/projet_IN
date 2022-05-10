#include <stdio.h>	
#include <stdlib.h>	
#include <stdint.h>		
#include <math.h>	
#include <gsl/gsl_fft_complex.h>
		
#define pi 3.141592654
		

		

		
struct wavfile //définit la structure de l entete d un wave
		
{
		
char id[4]; // doit contenir "RIFF"
		
int totallength; // taille totale du fichier moins 8 octets
		
char wavefmt[8]; // doit etre "WAVEfmt "
		
int format; // 16 pour le format PCM
		
short pcm; // 1 for PCM format
		
short channels; // nombre de channels
		
int frequency; // frequence d echantillonage (nombre d'échantillons par sec)
		
int bytes_per_second; // nombre de octets par secondes
		
short bytes_by_capture; // nombre de bytes par echantillon
		
short bits_per_sample; // nombre de bit par echantillon
		
char data[4]; // doit contenir "data"
		
int bytes_in_data; // nombre de bytes de la partie data
		
};
		

		

		

		
int main() {
		
	int puissance=0; // rajouté
		
	int i=0;
		
	int taille=1; //variable qui correspondra par la suite a la longueur du tableau(puissance de 2)
		
	int nbech=0; //nombre d echantillons extraits du fichier audio
		
	char fichieraudio[100];
		
	printf ("entrer le nom du fichier audio a analyser :\n");
		
	scanf("%s", fichieraudio);
		
	printf ("nom du fichier : %s\n", fichieraudio);
		
	FILE *wav = fopen(fichieraudio,"rb"); //ouverture du fichier wave
		
	struct wavfile header; //creation du header
		
	if ( wav == NULL ) {
		
		printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
		
		printf("ne pas oublier l'extention .wav\n");
		
		exit(1);}
		

		
//initialise le header par l'entete du fichier wave
		
//verifie que le fichier possede un entete compatible
		

		

		
	if ( fread(&header,sizeof(header),1,wav) < 1 ) {
		
		printf("\nne peut pas lire le header\n");
		
		exit(1); }
		
	if ( header.id[0] != 'R'|| header.id[1] != 'I'|| header.id[2] != 'F'|| header.id[3] != 'F' ){
		
		printf("\nerreur le fichier n'est pas un format wave valide\n");
		
		exit(1);}
		
	if (header.channels!=1) {
		
		printf("\nerreur : le fichier n'est pas mono\n");
		
		exit(1);
		
		}
		

		
	nbech=(header.bytes_in_data/header.bytes_by_capture);
		
	printf ("\nle fichier audio contient %d echantillons\n",nbech);
		
	while (nbech>taille) {
		
		taille=taille*2;
		
		puissance=puissance+1;
