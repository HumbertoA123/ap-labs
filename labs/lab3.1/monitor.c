#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include "logger.h"

#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

int main(int argc, char **argv)
{
	int length, i = 0;
	int fd;
	int wd;
	char buffer[EVENT_BUF_LEN];
	/*Handle number of arguments*/
	if(argc != 2) {
		printf("Invalid number of arguments.\n");
		return -1;
	}

	/*Creating the INOTIFY instance*/
	fd = inotify_init();

	/*Checking for error*/
	if ( fd < 0 ) {
		perror( "inotify_init" );
	}

	/*Adding the input directory into watch list.*/
	wd = inotify_add_watch( fd, argv[1], IN_CREATE | IN_DELETE );

	/*Read to determine the event change happens on the input directory. Actually this read blocks until the change event occurs*/ 
	length = read( fd, buffer, EVENT_BUF_LEN ); 

	/*Checking for error*/
	if ( length < 0 ) {
		perror( "read" );
	}
	/*Actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.*/
	while ( i < length) {
		struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
		if ( event->len ) {
			initLogger("stdout");
			if ( event->mask & IN_CREATE )
			{
			    if ( event->mask & IN_ISDIR )
			    {
			    	printf( "New directory %s created.\n", event->name );
			        infof("INFO", "New directory created.\n");
			    }
			    else
			    {
			    	printf( "New file %s created.\n", event->name );
			        infof("INFO", "New file created.\n");
			    }
			}
			else if ( event->mask & IN_DELETE )
			{
			    if ( event->mask & IN_ISDIR )
			    {
			    	printf( "Directory %s deleted.\n", event->name );
			        infof("INFO", "Directory deleted.\n");
			    }
			    else
			    {
			    	printf( "File %s deleted.\n", event->name );
			       	infof("INFO", "File deleted.\n");
			    }
			}
		}   
		i += EVENT_SIZE + event->len;
	}
	/*Removing the input directory from the watch list.*/
	inotify_rm_watch( fd, wd );

	/*Closing the INOTIFY instance*/
	close( fd );
	return 0;
}