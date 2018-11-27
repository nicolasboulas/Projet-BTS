/**********************************************************************************************

Nom du projet : // A modifier
Nom du fichier : Fleche.h
Description :  Declaration de la classe Fleche permettant de fournir des instructions gcode permettant de r�aliser trois types de fl�ches ainsi qu'un retour � l'origine.
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



#pragma once
#include <cstdio>
#include "lrs232.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>



class Fleche
{


	//Attributs 
private :
	lrs232* lars; //Association � partir de la classe lrs232 

	//M�thodes
public :
//	Fleche(int l_port, int l_baudDebit, const char* l_mode); //Permet d'initialiser l'attribut lrs232

	Fleche(lrs232* l_lars);

	void TracerFleche(); //Permet de tracer une fl�che classique � partir de commandes gcode et en cela en utilisant la classe lrs232
	void TracerFlecheDroite(); //Permet de tracer une fl�che droite � partir de commandes gcode et en cela en utilisant la classe lrs232
	void TracerFlecheGauche(); //Permet de tracer une fl�che gauche � partir de commandes gcode et en cela en utilisant la classe lrs232

	void PositionDepart(); //Permet de revenir au point de depart pour tracer une nouvelle fl�che


	void TransmissionPlatineDeplacement(const char* l_texte);
	void TransmissionPlatineLeverDebut(const char* l_texte);
	void TransmissionPlatineLeverFin(const char* l_texte);
};



/*********************************************************************************************/
//Fin fichier Fleche.H