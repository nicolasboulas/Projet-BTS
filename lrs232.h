/**********************************************************************************************

Nom du projet : // A modifier
Nom du fichier : lrs232.h
Description :  Declaration de la classe lrs232 permettant d'etablir une communication rs232 (en communication multiplateforme)
Auteur : Boulas Nicolas
Environnement : Microsoft Visual studio 2015
Version : 14.0.25123.00 Update 2

-----------------------------------------------------------------------------------------------

Historique :

07-05-2018  Creation de la classe lsrs232 permettant d'établir une communication rs232

11-05-2018  Modification de la classe : Modification des attributs du constructeur


**********************************************************************************************/




#pragma once

#ifndef lrs232_INCLUDED
#define lrs232_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>




#if defined(__linux__) || defined(__FreeBSD__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/file.h>
#include <errno.h>


#else

#include <windows.h>

#endif


	class lrs232
	{
	
		//Attributs
	private :
		int leport;
		int baudDebit;
		const char* mode;

		//Méthodes
	public :

		lrs232();
		lrs232(int l_leport, int l_baudDebit,const char* l_mode);


	//	void TransmissionPlatineDeplacement(const char* l_texte);
	//	void TransmissionPlatineLeverDebut(const char* l_texte);
	//	void TransmissionPlatineLeverFin(const char* l_texte);

		int RS232_OpenComport();
		int RS232_PollComport(int comport_number, unsigned char *buf, int size);
		int RS232_SendByte(int comport_number, unsigned char byte);
		int RS232_SendBuf(int comport_number, unsigned char *buf, int size);
		void RS232_CloseComport();
		
		void RS232_cputs(const char *text);
		
		int RS232_IsDCDEnabled(int comport_number);
		int RS232_IsCTSEnabled(int comport_number);
		int RS232_IsDSREnabled(int comport_number);
		void RS232_enableDTR(int comport_number);
		void RS232_disableDTR(int comport_number);
		void RS232_enableRTS(int comport_number);
		void RS232_disableRTS(int comport_number);

		void RS232_flushRX(int comport_number);
		void RS232_flushTX(int comport_number);
		void RS232_flushRXTX(int comport_number);
		int RS232_GetPortnr(const char *devname);
	};



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/*************************************************************/
//Fin fichier lrs232.h