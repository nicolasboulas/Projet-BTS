#include <cstdio>
#include "lrs232.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include "Fleche.h"




#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct champbits
{
	//Unsigned char car cela va de 0 à 255 et correspond au type de protocole que nous avons choisi 
	unsigned char inferieur : 4; //bits de 0 à 3
	unsigned char superieur : 4; //bits de 4 à 7
}tst_champbits;


//Creation d'une union permettant de décomposer l'octet
typedef union lunion  
{
	tst_champbits octetdecomposable;
	unsigned char octetcomplet;
}tun_union;





//----------------------------------------------------------------------------------------------
//Fonction  : Error
//Role      : Permet d'afficher un message d'erreur
//Parametre : Parametre 1 = un message
//Retour    : Aucun
void error(char *msg) {
	perror(msg); //Affiche un message d'erreur
	exit(1);
}//Fin fonction error 



/*int func(int a) {
	return 2 * a;
}*/




//----------------------------------------------------------------------------------------------
//Fonction  : sendData
//Role      : Permet d'afficher un message d'erreur
//Parametre : Parametre 1 = le socket
//            Parametre 2 = un entier
//Retour    : Aucun
void sendData(int sockfd, int x) {
	int n;

	char buffer[32];
	sprintf(buffer, "%d\n", x);
	if ((n = write(sockfd, buffer, strlen(buffer))) < 0)
		error(const_cast<char *>("Erreur d'ecriture sur socket"));
	buffer[n] = '\0';
}//Fin fonction sendData



 //----------------------------------------------------------------------------------------------
 //Fonction  : getData
 //Role      : Permet d'afficher un message d'erreur
 //Parametre : Parametre 1 = le socket
 //Retour    : un entier, le buffer
int getData(int sockfd) {
	char buffer[32];
	int n;

	if ((n = read(sockfd, buffer, 31)) < 0)
		error(const_cast<char *>("Erreur de lecture sur socket"));
	buffer[n] = '\0';
	return atoi(buffer);
}//Fin fonction getData


int main()
{
	//Varaible representant les paramètres la liaison rs232
	int port = 16; //Le port est 16 ce qui correspond à ttyUSB0
	int baudDebit = 115200; //Le debit de 115200 bauds
	char mode[4] = { '8','N','1' }; //Le mode est 8 bits, pas de parité, 1 bits de stop

	lrs232 lars(port, baudDebit, mode);

//	Fleche lafleche(port,baudDebit,mode); //Creation d'un objet flèche avec les attributs précédents

	Fleche lafleche(&lars);


	tst_champbits champ; //Creation d'un champ de bits 
	tun_union lunion; //Creation d'une union


	int sockfd, newsockfd, portno = 51717, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	int data;

	printf("Utilisation du port :  #%d\n", portno);

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Initialisation du socket
	if (sockfd < 0) //Boucle si verifiant que l'initialisation du socket soit un succès.
		error(const_cast<char *>("Erreur d'ouverture du socket")); //Appel de la fonction affiachant un message d'erreur
	bzero((char *)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET; //AF_INET = adrress format, Internet = IP Addresses
	serv_addr.sin_addr.s_addr = INADDR_ANY; //Affecte la socket à toutes les interfaces locales
	serv_addr.sin_port = htons(portno); //Fonction permettant la conversion d'un entier depuis l'ordre des octets de l'hote vers celui du réseau 
	if (bind(sockfd, (struct sockaddr *) &serv_addr, 
		sizeof(serv_addr)) < 0)  //Bind fourni un nom à la socket
		error(const_cast<char *>("Erreur sur la liaison"));
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	//--- Attente infinie d'une connexion ---
	while (1) {
		printf("En attente d'un nouveau client...\n");
		if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen)) < 0) //Boucle permettant de verifier le succés de la connexion
			error(const_cast<char *>("Impossible d'accepter la nouvelle connexion"));
		printf("Ouverture d'une nouvelle connexion avec le client\n");
		while (1) {
			//---- Attendre un numéro du client ---
			data = getData(newsockfd);
			printf("Obtention de :  %d\n", data);
			if (data < 0)
				break;


			lunion.octetcomplet = (unsigned char)data;

			int donnee = lunion.octetdecomposable.inferieur;


			switch (donnee) //Boucle selon analysant la donnée envoyée par le client et réalisant un type de flèche selon cette donnée
			{
			case 1:
				lafleche.TracerFleche();
				break;
			case 2:
				lafleche.TracerFlecheDroite();
				break;
			case 3:
				lafleche.TracerFlecheGauche();

			default:
				printf("\n Erreur lors de la saisie");
				break;
			}

			printf("La donnee est :  %d\n", donnee);

			
		}
		close(newsockfd);

		//--- Si -2 envoyé par le client, le programme s'arrete ---
		if (data == -2)
			break;
	}











    return 0;
}




