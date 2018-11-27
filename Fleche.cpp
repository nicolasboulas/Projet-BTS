/**********************************************************************************************

Nom du projet : // A modifier
Nom du fichier : Fleche.cpp
Description :  Definition des fonctions membres de la classe Fleche permettant de fournir des instructions gcode permettant de réaliser trois types de flèches ainsi qu'un retour à l'origine.
Auteur : Boulas Nicolas
Environnement : Microsoft Visual studio 2015
Version : 14.0.25123.00 Update 2

-----------------------------------------------------------------------------------------------

Historique :

10-04-2018  Creation de la classe Permettant de réaliser un type de flèche (flèche classqiue)

13-04-2018  Modification de la classe : Ajout de deux autres types de flèche (gauche et droite)

04-05-2018  Modification de la classe : Adaptation de la classe à la nouvelle classe rs232 (mise en place d'une composition, modification complète des méthodes utilisant maintenant la classe lrs232

11-05-2018  Modification de la classe : Ajout d'une méthode permettant de revenir au point de départ de la platine (à partir de l'instruction gcode "G28")

**********************************************************************************************/

#include "Fleche.h"


//----------------------------------------------------------------------------------------------
//Methode   : Sleep
//Role      : Permet d'effectuer un temps de pause entre certaines actions, utilisable par plusieurs classe et le main
//Parametre : Parametre 1 = Le temps en micro seconde
//Retour    : 0 
//----------------------------------------------------------------------------------------------
int Sleep(int ms)
{
	clock_t starting = clock();
	while (clock() - starting < ms) {}
	return 0;
}//Fin méthode Sleep






//---------------------------------------------------------------------------------------------
//Methode   : Fleche
//Role      : Constructeur (initialise les attributs)
//Parametre : Parametre 1 = le port (le port USB sur lequel est connectée la platine, 16 correspond au port TTYUSB0, 17 correspond au port TTYUSB1)
//            Parametre 2 = le debit en bauds
//            Parametre 3 = le nombre de bits, la parité, le nombre de bits de stop
//Retour    : Aucun
//---------------------------------------------------------------------------------------------
Fleche::Fleche(lrs232* l_lars)
{
if (l_lars != NULL)
{
lars = l_lars;
}
else
{
lars = NULL;
}
}//Fin constructeur



 //---------------------------------------------------------------------------------------------
 //Methode   : TracerFleche
 //Role      : Permet de tracer une flèche en utilisant les méthodes de déplacement de la classe lrs232
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::TracerFleche()
{

	if (lars != NULL)
	{
		TransmissionPlatineDeplacement("G1 X30 F2500\r\n"); //Cette méthode permet un déplacement classique, G1 indique un déplacement classique en abscisse, F corresponds  la vitesse de déplacement

		TransmissionPlatineDeplacement("G1 X-10 Y10 F2500\r\n"); //Deplacement en abscisse et ordonnée

		TransmissionPlatineLeverDebut("M1 80\r\n"); // Permet de lever le stylo

		TransmissionPlatineLeverFin("G1 X10 Y-10 F2500\r\n"); //Deplacement avec le stylo levé en abscisse et ordonnée

		TransmissionPlatineDeplacement("M1 140\r\n"); //Permet d'abaisser le stylo

		TransmissionPlatineDeplacement("G1 X-10 Y-10 F2500\r\n"); //Deplacement en abscisse et ordonnée

		TransmissionPlatineDeplacement("M1 80\r\n"); //Permet de lever le stylo


		PositionDepart();
	}//Retour à la position de départ (celle ou était le stylo avant toutes les instructions)
}//Fin méthode TracerFleche




 //---------------------------------------------------------------------------------------------
 //Methode   : TracerFlecheDroite
 //Role      : Permet de tracer une flèche droite en utilisant les méthodes de déplacement de la classe lrs232
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::TracerFlecheDroite()
{

	TransmissionPlatineDeplacement("G1 X30 F2500\r\n"); //Deplacement en abscisse 

	TransmissionPlatineDeplacement("G1 Y-20 F2500\r\n"); //Deplacement négatif en ordonnée

	TransmissionPlatineDeplacement("G1 X10 Y10 F2500\r\n"); //Deplacement en abscisse et ordonnée

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 X-10 Y-10 F2500\r\n"); //Deplacement avec le stylo levé en abscisse et ordonnée

	TransmissionPlatineDeplacement("M1 140\r\n"); //Permet d'abaisser le stylo

	TransmissionPlatineDeplacement("G1 X-10 Y10 F2500\r\n"); //Deplacement en abscisse et ordonnée

	TransmissionPlatineDeplacement("M1 80\r\n"); //Permet de lever le stylo


	PositionDepart(); //Retour à la position de départ
}//Fin méthode TracerFlecheDroite




 //---------------------------------------------------------------------------------------------
 //Methode   : TracerFlecheGauche
 //Role      : Permet de tracer une flèche gauche en utilisant les méthodes de déplacement de la classe lrs232
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::TracerFlecheGauche()
{

	TransmissionPlatineDeplacement("G1 X30 F2500\r\n"); //Deplacement en abscisse 

	TransmissionPlatineDeplacement("G1 Y20 F2500\r\n"); //Deplacement en ordonnée

	TransmissionPlatineDeplacement("G1 X10 Y-10 F2500\r\n"); //Deplacement en abscisse et ordonnée

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 X-10 Y10 F2500\r\n"); //Deplacement avec le stylo levé en abscisse et ordonnée

	TransmissionPlatineDeplacement("M1 140\r\n"); //Permet d'abaisser le stylo

	TransmissionPlatineDeplacement("G1 X-10 Y-10\r\n"); //Deplacement en abscisse et ordonnée

	TransmissionPlatineDeplacement("M1 80\r\n"); //Permet de lever le stylo


	PositionDepart();
}//Fin méthode TracerFlecheGauche




 //---------------------------------------------------------------------------------------------
 //Methode   : PositionDepart
 //Role      : Permet de revenir à la position de départ (celle ou était le stylo avant toutes les instructions)
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::PositionDepart()
{

	TransmissionPlatineDeplacement("G28\r\n"); //Retour à la position d'origine

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 Y70 F2500\r\n"); //Deplacement avec le stylo levé en ordonnée 

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 X60 F2500\r\n"); //Deplacement avec le stylo levé en abscisse
}//Fin méthode PositionDepart



 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineDeplacement
 //Role      : Permet de fournir une instruction à la platine permettant un déplacement en x ou y
 //Parametre : Parametre 1 = correspond à l'instruction gcode transmise à la platine
 //Retour    : Aucun
void Fleche::TransmissionPlatineDeplacement(const char* l_texte)
{
	if (lars != NULL)
	{
		lars->RS232_OpenComport(); //Ouverture du port

		Sleep(4000000); // Pause de 5 secondes
		lars->RS232_cputs(l_texte); // Envoie d'une commande Gcode
		Sleep(4000000); // Pause de 5 secondes

		lars->RS232_CloseComport(); // Fermeture du port

		Sleep(4000000); // Pause de 5 secondes
	}

}//Fin méthode TransmissionPlatineDeplacement




 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineLeverDebut
 //Role      : Permet de fournir une instruction à la platine permettant de lever le stylo
 //Parametre : Parametre 1 = correspond à l'instruction gcode transmise à la platine
 //Retour    : Aucun
void Fleche::TransmissionPlatineLeverDebut(const char* l_texte)
{
	if (lars != NULL)
	{
		lars->RS232_OpenComport(); //Ouverture du port

		Sleep(4000000); // Pause de 5 secondes
		lars->RS232_cputs(l_texte); // Envoie d'une commande Gcode
		Sleep(4000000); // Pause de 5 secondes
	}

}//Fin méthode TransmissionPlatineLeverDebut






 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineLeverFin
 //Role      : Permet de fournir une instruction à la platine permettant un déplacement en x ou y avec le stylo lever
 //Parametre : Parametre 1 = correspond à l'instruction gcode transmise à la platine
 //Retour    : Aucun
void Fleche::TransmissionPlatineLeverFin(const char* l_texte)
{
	if (lars != NULL)
	{
		Sleep(4000000); // Pause de 5 secondes
		lars->RS232_cputs(l_texte); // Envoi d'une commande gcode
		Sleep(4000000); // Pause de 5 secondes

		lars->RS232_CloseComport(); //Fermeture du port

		Sleep(4000000); // Pause de 5 secondes
	}



}//Fin méthode TransmissionPlatineLeverFin
