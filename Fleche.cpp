/**********************************************************************************************

Nom du projet : // A modifier
Nom du fichier : Fleche.cpp
Description :  Definition des fonctions membres de la classe Fleche permettant de fournir des instructions gcode permettant de r�aliser trois types de fl�ches ainsi qu'un retour � l'origine.
Auteur : Boulas Nicolas
Environnement : Microsoft Visual studio 2015
Version : 14.0.25123.00 Update 2

-----------------------------------------------------------------------------------------------

Historique :

10-04-2018  Creation de la classe Permettant de r�aliser un type de fl�che (fl�che classqiue)

13-04-2018  Modification de la classe : Ajout de deux autres types de fl�che (gauche et droite)

04-05-2018  Modification de la classe : Adaptation de la classe � la nouvelle classe rs232 (mise en place d'une composition, modification compl�te des m�thodes utilisant maintenant la classe lrs232

11-05-2018  Modification de la classe : Ajout d'une m�thode permettant de revenir au point de d�part de la platine (� partir de l'instruction gcode "G28")

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
}//Fin m�thode Sleep






//---------------------------------------------------------------------------------------------
//Methode   : Fleche
//Role      : Constructeur (initialise les attributs)
//Parametre : Parametre 1 = le port (le port USB sur lequel est connect�e la platine, 16 correspond au port TTYUSB0, 17 correspond au port TTYUSB1)
//            Parametre 2 = le debit en bauds
//            Parametre 3 = le nombre de bits, la parit�, le nombre de bits de stop
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
 //Role      : Permet de tracer une fl�che en utilisant les m�thodes de d�placement de la classe lrs232
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::TracerFleche()
{

	if (lars != NULL)
	{
		TransmissionPlatineDeplacement("G1 X30 F2500\r\n"); //Cette m�thode permet un d�placement classique, G1 indique un d�placement classique en abscisse, F corresponds  la vitesse de d�placement

		TransmissionPlatineDeplacement("G1 X-10 Y10 F2500\r\n"); //Deplacement en abscisse et ordonn�e

		TransmissionPlatineLeverDebut("M1 80\r\n"); // Permet de lever le stylo

		TransmissionPlatineLeverFin("G1 X10 Y-10 F2500\r\n"); //Deplacement avec le stylo lev� en abscisse et ordonn�e

		TransmissionPlatineDeplacement("M1 140\r\n"); //Permet d'abaisser le stylo

		TransmissionPlatineDeplacement("G1 X-10 Y-10 F2500\r\n"); //Deplacement en abscisse et ordonn�e

		TransmissionPlatineDeplacement("M1 80\r\n"); //Permet de lever le stylo


		PositionDepart();
	}//Retour � la position de d�part (celle ou �tait le stylo avant toutes les instructions)
}//Fin m�thode TracerFleche




 //---------------------------------------------------------------------------------------------
 //Methode   : TracerFlecheDroite
 //Role      : Permet de tracer une fl�che droite en utilisant les m�thodes de d�placement de la classe lrs232
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::TracerFlecheDroite()
{

	TransmissionPlatineDeplacement("G1 X30 F2500\r\n"); //Deplacement en abscisse 

	TransmissionPlatineDeplacement("G1 Y-20 F2500\r\n"); //Deplacement n�gatif en ordonn�e

	TransmissionPlatineDeplacement("G1 X10 Y10 F2500\r\n"); //Deplacement en abscisse et ordonn�e

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 X-10 Y-10 F2500\r\n"); //Deplacement avec le stylo lev� en abscisse et ordonn�e

	TransmissionPlatineDeplacement("M1 140\r\n"); //Permet d'abaisser le stylo

	TransmissionPlatineDeplacement("G1 X-10 Y10 F2500\r\n"); //Deplacement en abscisse et ordonn�e

	TransmissionPlatineDeplacement("M1 80\r\n"); //Permet de lever le stylo


	PositionDepart(); //Retour � la position de d�part
}//Fin m�thode TracerFlecheDroite




 //---------------------------------------------------------------------------------------------
 //Methode   : TracerFlecheGauche
 //Role      : Permet de tracer une fl�che gauche en utilisant les m�thodes de d�placement de la classe lrs232
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::TracerFlecheGauche()
{

	TransmissionPlatineDeplacement("G1 X30 F2500\r\n"); //Deplacement en abscisse 

	TransmissionPlatineDeplacement("G1 Y20 F2500\r\n"); //Deplacement en ordonn�e

	TransmissionPlatineDeplacement("G1 X10 Y-10 F2500\r\n"); //Deplacement en abscisse et ordonn�e

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 X-10 Y10 F2500\r\n"); //Deplacement avec le stylo lev� en abscisse et ordonn�e

	TransmissionPlatineDeplacement("M1 140\r\n"); //Permet d'abaisser le stylo

	TransmissionPlatineDeplacement("G1 X-10 Y-10\r\n"); //Deplacement en abscisse et ordonn�e

	TransmissionPlatineDeplacement("M1 80\r\n"); //Permet de lever le stylo


	PositionDepart();
}//Fin m�thode TracerFlecheGauche




 //---------------------------------------------------------------------------------------------
 //Methode   : PositionDepart
 //Role      : Permet de revenir � la position de d�part (celle ou �tait le stylo avant toutes les instructions)
 //Parametre : Aucun
 //Retour    : Aucun
 //---------------------------------------------------------------------------------------------
void Fleche::PositionDepart()
{

	TransmissionPlatineDeplacement("G28\r\n"); //Retour � la position d'origine

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 Y70 F2500\r\n"); //Deplacement avec le stylo lev� en ordonn�e 

	TransmissionPlatineLeverDebut("M1 80\r\n"); //Permet de lever le stylo

	TransmissionPlatineLeverFin("G1 X60 F2500\r\n"); //Deplacement avec le stylo lev� en abscisse
}//Fin m�thode PositionDepart



 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineDeplacement
 //Role      : Permet de fournir une instruction � la platine permettant un d�placement en x ou y
 //Parametre : Parametre 1 = correspond � l'instruction gcode transmise � la platine
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

}//Fin m�thode TransmissionPlatineDeplacement




 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineLeverDebut
 //Role      : Permet de fournir une instruction � la platine permettant de lever le stylo
 //Parametre : Parametre 1 = correspond � l'instruction gcode transmise � la platine
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

}//Fin m�thode TransmissionPlatineLeverDebut






 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineLeverFin
 //Role      : Permet de fournir une instruction � la platine permettant un d�placement en x ou y avec le stylo lever
 //Parametre : Parametre 1 = correspond � l'instruction gcode transmise � la platine
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



}//Fin m�thode TransmissionPlatineLeverFin
