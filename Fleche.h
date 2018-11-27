/**********************************************************************************************

Nom du projet : // A modifier
Nom du fichier : Fleche.h
Description :  Declaration de la classe Fleche permettant de fournir des instructions gcode permettant de réaliser trois types de flèches ainsi qu'un retour à l'origine.
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
	lrs232* lars; //Association à partir de la classe lrs232 

	//Méthodes
public :
//	Fleche(int l_port, int l_baudDebit, const char* l_mode); //Permet d'initialiser l'attribut lrs232

	Fleche(lrs232* l_lars);

	void TracerFleche(); //Permet de tracer une flèche classique à partir de commandes gcode et en cela en utilisant la classe lrs232
	void TracerFlecheDroite(); //Permet de tracer une flèche droite à partir de commandes gcode et en cela en utilisant la classe lrs232
	void TracerFlecheGauche(); //Permet de tracer une flèche gauche à partir de commandes gcode et en cela en utilisant la classe lrs232

	void PositionDepart(); //Permet de revenir au point de depart pour tracer une nouvelle flèche


	void TransmissionPlatineDeplacement(const char* l_texte);
	void TransmissionPlatineLeverDebut(const char* l_texte);
	void TransmissionPlatineLeverFin(const char* l_texte);
};



/*********************************************************************************************/
//Fin fichier Fleche.H