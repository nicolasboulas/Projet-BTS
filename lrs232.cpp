#include "lrs232.h"







#if defined(__linux__) || defined(__FreeBSD__)   /* Linux & FreeBSD */

#define RS232_PORTNR  38


int Cport[RS232_PORTNR],
error;

struct termios new_port_settings,
	old_port_settings[RS232_PORTNR];

char *comports[RS232_PORTNR] = { "/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
"/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
"/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
"/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5",
"/dev/ttyAMA0","/dev/ttyAMA1","/dev/ttyACM0","/dev/ttyACM1",
"/dev/rfcomm0","/dev/rfcomm1","/dev/ircomm0","/dev/ircomm1",
"/dev/cuau0","/dev/cuau1","/dev/cuau2","/dev/cuau3",
"/dev/cuaU0","/dev/cuaU1","/dev/cuaU2","/dev/cuaU3" };




//----------------------------------------------------------------------------------------------
//Methode   : lrs232
//Role      : Constructeur par défaut
//Parametre : Aucun
//Retour    : Aucun
//----------------------------------------------------------------------------------------------
lrs232::lrs232()
{

	leport = 16; //Le port par défaut est 16, cela correspond à ttyUSB0
	baudDebit = 112500; //Débit en baud

}//Fin constructeur





//----------------------------------------------------------------------------------------------
//Methode   : lrs232
//Role      : Constructeur par défaut
//Parametre : Parametre 1 = Parametre 1 = le port (le port USB sur lequel est connectée la platine, 16 correspond au port TTYUSB0, 17 correspond au port TTYUSB1)
//            Parametre 2 = le debit en bauds
//            Parametre 3 = le nombre de bits, la parité, le nombre de bits de stop
//Retour    : Aucun
lrs232::lrs232(int l_leport, int l_baudDebit,const char* l_mode):mode(l_mode)
{

	leport = l_leport; //L'attribut recoit la valeur placée en paramètre, le port est alors connu

	baudDebit = l_baudDebit; //L'attribut recoit la valeur placée en paramètre, le debit est alors spécifié.

}//Fin constructeur



/*
 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineDeplacement
 //Role      : Permet de fournir une instruction à la platine permettant un déplacement en x ou y
 //Parametre : Parametre 1 = correspond à l'instruction gcode transmise à la platine
 //Retour    : Aucun
void lrs232::TransmissionPlatineDeplacement(const char* l_texte)
{

	RS232_OpenComport(); //Ouverture du port

	Sleep(4000000); // Pause de 5 secondes
	RS232_cputs(l_texte); // Envoie d'une commande Gcode
	Sleep(4000000); // Pause de 5 secondes

	RS232_CloseComport(); // Fermeture du port

	Sleep(4000000); // Pause de 5 secondes

}//Fin méthode TransmissionPlatineDeplacement*/


/*
 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineLeverDebut
 //Role      : Permet de fournir une instruction à la platine permettant de lever le stylo
 //Parametre : Parametre 1 = correspond à l'instruction gcode transmise à la platine
 //Retour    : Aucun
void lrs232::TransmissionPlatineLeverDebut(const char* l_texte)
{
	RS232_OpenComport(); //Ouverture du port

	Sleep(4000000); // Pause de 5 secondes
	RS232_cputs(l_texte); // Envoie d'une commande Gcode
	Sleep(4000000); // Pause de 5 secondes
}//Fin méthode TransmissionPlatineLeverDebut*/


/*
 //----------------------------------------------------------------------------------------------
 //Methode   : TransmissionPlatineLeverFin
 //Role      : Permet de fournir une instruction à la platine permettant un déplacement en x ou y avec le stylo lever
 //Parametre : Parametre 1 = correspond à l'instruction gcode transmise à la platine
 //Retour    : Aucun
void lrs232::TransmissionPlatineLeverFin(const char* l_texte)
{
	Sleep(4000000); // Pause de 5 secondes
	RS232_cputs(l_texte); // Envoie d'une commande Gcode
	Sleep(4000000); // Pause de 5 secondes

	RS232_CloseComport(); // Fermeture du port

	Sleep(4000000); // Pause de 5 secondes
}//Fin méthode TransmissionPlatineLeverFin*/




 //----------------------------------------------------------------------------------------------
 //Methode   : RS232_OpenComport
 //Role      : Permet d'ouvrir le port et ainsi d'établir une connexion 
 //Parametre : Aucun
 //Retour    : 0 si réussi, 1 si erreur
int lrs232::RS232_OpenComport()
{
	//Variables locales
	int baudr,
		status;

	if ((leport >= RS232_PORTNR) || (leport<0)) //Boucle si permettant de verifier si le numéro de port est légal, pour cela il doit etre supérieur à 0 et compris ou égal RS232_PORTNR (38)
	{
		printf("numéro de port illegal\n");
		return(1); //Sortie de la méthode et retour = 1 signifiant une erreur
	}

	switch (baudDebit) //Boucle selon affectant une valeur à la variable locale baudr selon une valeur contenue dans l'attribut baudDebit
	{
	case      50: baudr = B50;
		break;
	case      75: baudr = B75;
		break;
	case     110: baudr = B110;
		break;
	case     134: baudr = B134;
		break;
	case     150: baudr = B150;
		break;
	case     200: baudr = B200;
		break;
	case     300: baudr = B300;
		break;
	case     600: baudr = B600;
		break;
	case    1200: baudr = B1200;
		break;
	case    1800: baudr = B1800;
		break;
	case    2400: baudr = B2400;
		break;
	case    4800: baudr = B4800;
		break;
	case    9600: baudr = B9600;
		break;
	case   19200: baudr = B19200;
		break;
	case   38400: baudr = B38400;
		break;
	case   57600: baudr = B57600;
		break;
	case  115200: baudr = B115200;
		break;
	case  230400: baudr = B230400;
		break;
	case  460800: baudr = B460800;
		break;
	case  500000: baudr = B500000;
		break;
	case  576000: baudr = B576000;
		break;
	case  921600: baudr = B921600;
		break;
	case 1000000: baudr = B1000000;
		break;
	case 1152000: baudr = B1152000;
		break;
	case 1500000: baudr = B1500000;
		break;
	case 2000000: baudr = B2000000;
		break;
	case 2500000: baudr = B2500000;
		break;
	case 3000000: baudr = B3000000;
		break;
	case 3500000: baudr = B3500000;
		break;
	case 4000000: baudr = B4000000;
		break;
	default: printf("Debit en bauds invalide\n");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur 
		break;
	}


	//Variables locales
	int cbits = CS8, //Nombre de bits
		cpar = 0,
		ipar = IGNPAR,
		bstop = 0; //Bits de stop

	if (strlen(mode) != 3) //Boucle si permettant de de vérifier que mode ne soit pas différent de 3
	{
		printf("le mode est invalide \"%s\"\n", mode);
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}

	switch (mode[0]) //Boucle selon permettant d'affecter la valeur de la case 0 de l'attribut mode à la variable locale cbits (correspondant au nombre de bits)
	{
	case '8': cbits = CS8;
		break;
	case '7': cbits = CS7;
		break;
	case '6': cbits = CS6;
		break;
	case '5': cbits = CS5;
		break;
	default: printf("nombre invalide de bits '%c'\n", mode[0]);
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
		break;
	}

	switch (mode[1]) //Boucle selon permettant d'affecter la valeur de la case 1 de l'attribut mode à la variable locale ipar (correspondant à la parité)
	{
	case 'N':
	case 'n': cpar = 0;
		ipar = IGNPAR;
		break;
	case 'E':
	case 'e': cpar = PARENB;
		ipar = INPCK;
		break;
	case 'O':
	case 'o': cpar = (PARENB | PARODD);
		ipar = INPCK;
		break;
	default: printf("la parité est invalide '%c'\n", mode[1]);
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
		break;
	}

	switch (mode[2]) //Boucle selon permettant d'affecter la valeur de la case 2 de l'attribut mode à la varibale locale bstop (correspondant au bit de stop)
	{
	case '1': bstop = 0;
		break;
	case '2': bstop = CSTOPB;
		break;
	default: printf("nombre de bits de stop invalide '%c'\n", mode[2]);
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
		break;
	}

	/*
	http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html

	http://man7.org/linux/man-pages/man3/termios.3.html
	*/

	Cport[leport] = open(comports[leport], O_RDWR | O_NOCTTY | O_NDELAY);  //Ouverture d'un port avec comme paramètre l'attribut leport.

	if (Cport[leport] == -1) //Boucle si permettant de vérifier si il y a eu une erreur lors de l'ouverture du port
	{
		perror("impossible d'ouvrir le port ");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}

	/* Verrouiller l'acces afin qu'un autre processus ne puisse utiliser le port */
	if (flock(Cport[leport], LOCK_EX | LOCK_NB) != 0) //Fonction de verrouillage du port avec comme paramètre l'attribut leport
	{
		close(Cport[leport]); //fermeture du port avec comme paramètre l'attribut leport
		perror("Un autre processus à verrouillé le port.");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}


	error = tcgetattr(Cport[leport], old_port_settings + leport);
	if (error == -1)
	{
		close(Cport[leport]); 
		flock(Cport[leport], LOCK_UN);  /* libérer le port afin que d'autres puissent l'utiliser */
		perror("impossible de lire les paramètres du port ");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}
	memset(&new_port_settings, 0, sizeof(new_port_settings));  /* Effacer la nouvelle structure */


	new_port_settings.c_cflag = cbits | cpar | bstop | CLOCAL | CREAD;
	new_port_settings.c_iflag = ipar;
	new_port_settings.c_oflag = 0;
	new_port_settings.c_lflag = 0;
	new_port_settings.c_cc[VMIN] = 0;      /* Bloquer jusqu'a ce que n octets soient reçus */
	new_port_settings.c_cc[VTIME] = 0;     /* Bloquer jusqu'a l'expiration d'une minuterie (n * 100 mSec.) */

	cfsetispeed(&new_port_settings, baudr);
	cfsetospeed(&new_port_settings, baudr);

	error = tcsetattr(Cport[leport], TCSANOW, &new_port_settings);
	if (error == -1)
	{
		tcsetattr(Cport[leport], TCSANOW, old_port_settings + leport);
		close(Cport[leport]);
		flock(Cport[leport], LOCK_UN);  /* libérer le port afin que d'autres puissent l'utiliser */
		perror("Impossible d'ajuster les paramètres du port ");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}

	/* http://man7.org/linux/man-pages/man4/tty_ioctl.4.html */

	if (ioctl(Cport[leport], TIOCMGET, &status) == -1)
	{
		tcsetattr(Cport[leport], TCSANOW, old_port_settings + leport);
		flock(Cport[leport], LOCK_UN);  /* libérer le port afin que d'autres puissent l'utiliser */
		perror("Impossible d'obtenir le statut du port");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}

	status |= TIOCM_DTR;    /* Activer DTR */
	status |= TIOCM_RTS;    /* Activer RTS */

	if (ioctl(Cport[leport], TIOCMSET, &status) == -1)
	{
		tcsetattr(Cport[leport], TCSANOW, old_port_settings + leport);
		flock(Cport[leport], LOCK_UN);  /* libérer le port afin que d'autres puissent l'utiliser */
		perror("Impossible de mettre en place le statut du port");
		return(1); //Sortie de la fonction et retour = 1 signifiant une erreur
	}

	return(0);
}//Fin Methode RS232_OpenComport





int lrs232::RS232_PollComport(int comport_number, unsigned char *buf, int size)
{
	int n;

	n = read(Cport[comport_number], buf, size);

	if (n < 0)
	{
		if (errno == EAGAIN)  return 0;
	}

	return(n);
}






int lrs232::RS232_SendByte(int comport_number, unsigned char byte)
{
	int n = write(Cport[comport_number], &byte, 1);
	if (n < 0)
	{
		if (errno == EAGAIN)
		{
			return 0;
		}
		else
		{
			return 1;
		}
}

	return(0);
}

int lrs232::RS232_SendBuf(int comport_number, unsigned char *buf, int size)
{
	int n = write(Cport[comport_number], buf, size);
	if (n < 0)
	{
		if (errno == EAGAIN)
		{
			return 0;
		}
		else
		{
			return -1;
		}
}

	return(n);
}



//----------------------------------------------------------------------------------------------
//Methode   : RS232_CloseComport
//Role      : Permet de fermer le port et ainsi de mettre fin à une connexion 
//Parametre : Aucun
//Retour    : Aucun
void lrs232::RS232_CloseComport()
{
	int status;

	if (ioctl(Cport[leport], TIOCMGET, &status) == -1)
	{
		perror("impossible d'obtenir le statut du port");
	}

	status &= ~TIOCM_DTR;    /* Desactive DTR */
	status &= ~TIOCM_RTS;    /* Desactive RTS */

	if (ioctl(Cport[leport], TIOCMSET, &status) == -1)
	{
		perror("Impossible de mettre en place le statut du port");
	}

	tcsetattr(Cport[leport], TCSANOW, old_port_settings + leport);
	close(Cport[leport]);

	flock(Cport[leport], LOCK_UN);  /* libérer le port afin que d'autres puissent l'utiliser */
}//RS232_CloseComport



/*
Constant  Description
TIOCM_LE        DSR (data set ready/line enable)
TIOCM_DTR       DTR (data terminal ready)
TIOCM_RTS       RTS (request to send)
TIOCM_ST        Secondary TXD (transmit)
TIOCM_SR        Secondary RXD (receive)
TIOCM_CTS       CTS (clear to send)
TIOCM_CAR       DCD (data carrier detect)
TIOCM_CD        see TIOCM_CAR
TIOCM_RNG       RNG (ring)
TIOCM_RI        see TIOCM_RNG
TIOCM_DSR       DSR (data set ready)

http://man7.org/linux/man-pages/man4/tty_ioctl.4.html
*/


int lrs232::RS232_IsDCDEnabled(int comport_number)
{
	int status;

	ioctl(Cport[comport_number], TIOCMGET, &status);

	if (status&TIOCM_CAR) return(1);
	else return(0);
}


int lrs232::RS232_IsCTSEnabled(int comport_number)
{
	int status;

	ioctl(Cport[comport_number], TIOCMGET, &status);

	if (status&TIOCM_CTS) return(1);
	else return(0);
}

int lrs232::RS232_IsDSREnabled(int comport_number)
{
	int status;

	ioctl(Cport[comport_number], TIOCMGET, &status);

	if (status&TIOCM_DSR) return(1);
	else return(0);
}

void lrs232::RS232_enableDTR(int comport_number)
{
	int status;

	if (ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
	{
		perror("unable to get portstatus");
	}

	status |= TIOCM_DTR;    /* turn on DTR */

	if (ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
	{
		perror("unable to set portstatus");
	}
}



void lrs232::RS232_disableDTR(int comport_number)
{
	int status;

	if (ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
	{
		perror("unable to get portstatus");
	}

	status &= ~TIOCM_DTR;    /* turn off DTR */

	if (ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
	{
		perror("unable to set portstatus");
	}
}

void lrs232::RS232_enableRTS(int comport_number)
{
	int status;

	if (ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
	{
		perror("unable to get portstatus");
	}

	status |= TIOCM_RTS;    /* turn on RTS */

	if (ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
	{
		perror("unable to set portstatus");
	}
}

void lrs232::RS232_disableRTS(int comport_number)
{
	int status;

	if (ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
	{
		perror("unable to get portstatus");
	}

	status &= ~TIOCM_RTS;    /* turn off RTS */

	if (ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
	{
		perror("unable to set portstatus");
	}
}


void lrs232::RS232_flushRX(int comport_number)
{
	tcflush(Cport[comport_number], TCIFLUSH);
}


void lrs232::RS232_flushTX(int comport_number)
{
	tcflush(Cport[comport_number], TCOFLUSH);
}

void lrs232::RS232_flushRXTX(int comport_number)
{
	tcflush(Cport[comport_number], TCIOFLUSH);
}

#else /* windows */

#define RS232_PORTNR  16

HANDLE Cport[RS232_PORTNR];


char *comports[RS232_PORTNR] = { "\\\\.\\COM1",  "\\\\.\\COM2",  "\\\\.\\COM3",  "\\\\.\\COM4",
"\\\\.\\COM5",  "\\\\.\\COM6",  "\\\\.\\COM7",  "\\\\.\\COM8",
"\\\\.\\COM9",  "\\\\.\\COM10", "\\\\.\\COM11", "\\\\.\\COM12",
"\\\\.\\COM13", "\\\\.\\COM14", "\\\\.\\COM15", "\\\\.\\COM16" };

char mode_str[128];

int lrs232::RS232_OpenComport(int comport_number, int baudrate, const char *mode)
{
	if ((comport_number >= RS232_PORTNR) || (comport_number<0))
	{
		printf("illegal comport number\n");
		return(1);
	}

	switch (baudrate)
	{
	case     110: strcpy(mode_str, "baud=110");
		break;
	case     300: strcpy(mode_str, "baud=300");
		break;
	case     600: strcpy(mode_str, "baud=600");
		break;
	case    1200: strcpy(mode_str, "baud=1200");
		break;
	case    2400: strcpy(mode_str, "baud=2400");
		break;
	case    4800: strcpy(mode_str, "baud=4800");
		break;
	case    9600: strcpy(mode_str, "baud=9600");
		break;
	case   19200: strcpy(mode_str, "baud=19200");
		break;
	case   38400: strcpy(mode_str, "baud=38400");
		break;
	case   57600: strcpy(mode_str, "baud=57600");
		break;
	case  115200: strcpy(mode_str, "baud=115200");
		break;
	case  128000: strcpy(mode_str, "baud=128000");
		break;
	case  256000: strcpy(mode_str, "baud=256000");
		break;
	case  500000: strcpy(mode_str, "baud=500000");
		break;
	case 1000000: strcpy(mode_str, "baud=1000000");
		break;
	default: printf("invalid baudrate\n");
		return(1);
		break;
	}

	if (strlen(mode) != 3)
	{
		printf("invalid mode \"%s\"\n", mode);
		return(1);
	}

	switch (mode[0])
	{
	case '8': strcat(mode_str, " data=8");
		break;
	case '7': strcat(mode_str, " data=7");
		break;
	case '6': strcat(mode_str, " data=6");
		break;
	case '5': strcat(mode_str, " data=5");
		break;
	default: printf("invalid number of data-bits '%c'\n", mode[0]);
		return(1);
		break;
	}

	switch (mode[1])
	{
	case 'N':
	case 'n': strcat(mode_str, " parity=n");
		break;
	case 'E':
	case 'e': strcat(mode_str, " parity=e");
		break;
	case 'O':
	case 'o': strcat(mode_str, " parity=o");
		break;
	default: printf("invalid parity '%c'\n", mode[1]);
		return(1);
		break;
	}

	switch (mode[2])
	{
	case '1': strcat(mode_str, " stop=1");
		break;
	case '2': strcat(mode_str, " stop=2");
		break;
	default: printf("invalid number of stop bits '%c'\n", mode[2]);
		return(1);
		break;
	}

	strcat(mode_str, " dtr=on rts=on");

	/*
	http://msdn.microsoft.com/en-us/library/windows/desktop/aa363145%28v=vs.85%29.aspx

	http://technet.microsoft.com/en-us/library/cc732236.aspx
	*/

	Cport[comport_number] = CreateFileA(comports[comport_number],
		GENERIC_READ | GENERIC_WRITE,
		0,                          /* no share  */
		NULL,                       /* no security */
		OPEN_EXISTING,
		0,                          /* no threads */
		NULL);                      /* no templates */

	if (Cport[comport_number] == INVALID_HANDLE_VALUE)
	{
		printf("unable to open comport\n");
		return(1);
	}

	DCB port_settings;
	memset(&port_settings, 0, sizeof(port_settings));  /* clear the new struct  */
	port_settings.DCBlength = sizeof(port_settings);

	if (!BuildCommDCBA(mode_str, &port_settings))
	{
		printf("unable to set comport dcb settings\n");
		CloseHandle(Cport[comport_number]);
		return(1);
	}

	if (!SetCommState(Cport[comport_number], &port_settings))
	{
		printf("unable to set comport cfg settings\n");
		CloseHandle(Cport[comport_number]);
		return(1);
	}

	COMMTIMEOUTS Cptimeouts;

	Cptimeouts.ReadIntervalTimeout = MAXDWORD;
	Cptimeouts.ReadTotalTimeoutMultiplier = 0;
	Cptimeouts.ReadTotalTimeoutConstant = 0;
	Cptimeouts.WriteTotalTimeoutMultiplier = 0;
	Cptimeouts.WriteTotalTimeoutConstant = 0;

	if (!SetCommTimeouts(Cport[comport_number], &Cptimeouts))
	{
		printf("unable to set comport time-out settings\n");
		CloseHandle(Cport[comport_number]);
		return(1);
	}

	return(0);
}

int lrs232::RS232_PollComport(int comport_number, unsigned char *buf, int size)
{
	int n;

	/* added the void pointer cast, otherwise gcc will complain about */
	/* "warning: dereferencing type-punned pointer will break strict aliasing rules" */

	ReadFile(Cport[comport_number], buf, size, (LPDWORD)((void *)&n), NULL);

	return(n);
}


int lrs232::RS232_SendByte(int comport_number, unsigned char byte)
{
	int n;

	WriteFile(Cport[comport_number], &byte, 1, (LPDWORD)((void *)&n), NULL);

	if (n<0)  return(1);

	return(0);
}

int lrs232::RS232_SendBuf(int comport_number, unsigned char *buf, int size)
{
	int n;

	if (WriteFile(Cport[comport_number], buf, size, (LPDWORD)((void *)&n), NULL))
	{
		return(n);
	}

	return(-1);
}


void lrs232::RS232_CloseComport(int comport_number)
{
	CloseHandle(Cport[comport_number]);
}

/*
http://msdn.microsoft.com/en-us/library/windows/desktop/aa363258%28v=vs.85%29.aspx
*/


int lrs232::RS232_IsDCDEnabled(int comport_number)
{
	int status;

	GetCommModemStatus(Cport[comport_number], (LPDWORD)((void *)&status));

	if (status&MS_RLSD_ON) return(1);
	else return(0);
}

int lrs232::RS232_IsCTSEnabled(int comport_number)
{
	int status;

	GetCommModemStatus(Cport[comport_number], (LPDWORD)((void *)&status));

	if (status&MS_CTS_ON) return(1);
	else return(0);
}


int lrs232::RS232_IsDSREnabled(int comport_number)
{
	int status;

	GetCommModemStatus(Cport[comport_number], (LPDWORD)((void *)&status));

	if (status&MS_DSR_ON) return(1);
	else return(0);
}

void lrs232::RS232_enableDTR(int comport_number)
{
	EscapeCommFunction(Cport[comport_number], SETDTR);
}


void lrs232::RS232_disableDTR(int comport_number)
{
	EscapeCommFunction(Cport[comport_number], CLRDTR);
}


void lrs232::RS232_enableRTS(int comport_number)
{
	EscapeCommFunction(Cport[comport_number], SETRTS);
}

void lrs232::RS232_disableRTS(int comport_number)
{
	EscapeCommFunction(Cport[comport_number], CLRRTS);
}


/*
https://msdn.microsoft.com/en-us/library/windows/desktop/aa363428%28v=vs.85%29.aspx
*/

void lrs232::RS232_flushRX(int comport_number)
{
	PurgeComm(Cport[comport_number], PURGE_RXCLEAR | PURGE_RXABORT);
}


void lrs232::RS232_flushTX(int comport_number)
{
	PurgeComm(Cport[comport_number], PURGE_TXCLEAR | PURGE_TXABORT);
}

void lrs232::RS232_flushRXTX(int comport_number)
{
	PurgeComm(Cport[comport_number], PURGE_RXCLEAR | PURGE_RXABORT);
	PurgeComm(Cport[comport_number], PURGE_TXCLEAR | PURGE_TXABORT);
}


#endif

void lrs232::RS232_cputs(const char *text)  /* sends a string to serial port */
{
	while (*text != 0)   RS232_SendByte(leport, *(text++));
}

/* return index in comports matching to device name or -1 if not found */
int lrs232::RS232_GetPortnr(const char *devname)
{
	int i;

	char str[32];

#if defined(__linux__) || defined(__FreeBSD__)   /* Linux & FreeBSD */
	strcpy(str, "/dev/");
#else  /* windows */
	strcpy(str, "\\\\.\\");
#endif
	strncat(str, devname, 16);
	str[31] = 0;

	for (i = 0; i<RS232_PORTNR; i++)
	{
		if (!strcmp(comports[i], str))
		{
			return i;
		}
	}

	return -1;  /* device not found */
}
