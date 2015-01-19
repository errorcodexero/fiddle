//Adapted from: http://www.thelinuxdaily.com/2010/05/grab-raw-keyboard-input-from-event-device-node-devinputevent/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
 
void handler (int sig)
{
	printf("nexiting...(%d)n", sig);
	exit(0);
}
 
void perror_exit (const char *error)
{
	perror(error);
	handler(9);
}

//Reference for keyboard scan codes: http://flint.cs.yale.edu/cs422/doc/art-of-asm/pdf/APNDXC.PDF
 
int main (int argc, char *argv[])
{
	//Setup check
	if (argv[1] == NULL){
		printf("Please specify (on the command line) the path to the dev event interface devicen\n");
		exit(0);
	}
 
	if ((getuid ()) != 0)
		printf ("You are not root! This may not work...\n");
 
	char *device = NULL;
	if (argc > 1)
		device = argv[1];
 
	//Open Device
	int fd;
	if ((fd = open (device, O_RDONLY)) == -1)
		printf ("%s is not a vaild device.\n", device);
 
	//Print Device Name
	{
		char name[256] = "Unknown";
		ioctl(fd, EVIOCGNAME (sizeof (name)), name);
		printf("Reading From : %s (%s)\n", device, name);
 	}

	while(1){
		int rd;
		static const int SIZE = sizeof (struct input_event);
		static const int LEN=64;
		struct input_event ev[LEN];
		if((rd = read (fd, ev, SIZE*LEN)) < SIZE)
			perror_exit ("read()");     

		for(int i=0;i<rd/SIZE;i++){
			if(ev[i].value == 1 && ev[i].type == 1){ // Only read the key press event
				printf ("Code[%d]\n", (ev[1].code));
			}
		}
	}
	return 0;
}
