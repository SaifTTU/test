//READ ME - to run the commands use the following: 
// ADDITIONALLY: do these: 
//	mkdir testdir
//	mkdir testdir2
//	touch testfile
//	//AND THESE 4 ONLY IF YOU WANT TO:
//		cd testdir
//		mkdir subdir
//		touch testfile2
//		cd ..
// //COMPILING
// gcc -o test hello.c
// RUNNING WITH ONLY THE DIRECTORY
// ./test testdir
//
// RUNNING WITH NAME
// ./test testdir -name testfile
//
// RUNNING WITH MMIN
// ./test testdir -mmin 5
// RUNNING WITH INUM
// ./test testdir -inum 5
//
// REMOVING A FILE
// CREATING A FILE TO REMOVE
// touch testfile
// REMOVING THAT FILE -- SO THAT WE DON'T ACCIDENTALLY DELETE A FILE WE WILL NEED LATER!
// ./test testdir -remove testfile
//
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char *argv[]) {
    struct dirent *pDirent;
    DIR *pDir;
    struct stat *buf;

    pDir = opendir (argv[1]);
    if (argc > 2) {
        if(argv[2]!=NULL){
            printf("argument: %s ", argv[2]);
        }
        if(strcmp(argv[2],"-name")==0){
            printf("name: %s \n",argv[3]);
        }
    }
    
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", argv[1]);
        return 1;
    }

    // Process each entry.

    while ((pDirent = readdir(pDir)) != NULL) {
        if (argc > 2) { //if there are 4 commands, we can get name, mmin, and innode, or delete
            if(strcmp(argv[2],"-name")==0){ //if that 3rd argument is name
                if(strcmp(argv[3],pDirent->d_name)==0){ //if the name of the fileis equivalent to the 4th argument
                    printf ("%s\n", pDirent->d_name); //print it
                }
            }
            if(strcmp(argv[2],"-mmin")==0){ //if the time modified for a file in the directory is less than the 3rd argument, which represents the less than time, then print those files onl7
                double temp = abs(atof(argv[3])); //absolute value to prevent negative number
                //printf("%lf\n", temp);

                struct stat attr;
                stat(pDirent->d_name, &attr);



                //if(atof(ctime(&attr.st_mtime))<temp){
                    printf("%s", pDirent->d_name);
                    printf(" %s ",ctime(&attr.st_mtime)); //also share the ammount of time ago that these were modified to ensure they were modified within this time
		   //with an argument like 0, we will get 0 prints
		   //it seems merely using this function registers it as recently modified though
                //}
            }
            if(strcmp(argv[2],"-inum")==0){ //similarly check all available options to see if the 3rd argument
                double temp = atof(argv[3]); //see if the 3rd argument

                struct stat attr;
                stat(pDirent->d_name, &attr);

                //&attr->ino = NULL;
                //printf (" %d", atoi(argv[3]));
                //if( atoi(argv[3]) == &attr.st_ino ){ //matches with the specified number, here it is commented out to see if numbers populate
                    printf (" %s", pDirent->d_name);
                    printf(" %lld \n",attr.st_ino);
                //}
            }
            if(strcmp(argv[2],"-remove")==0){
                if(strcmp(argv[3],pDirent->d_name)==0){
                    printf ("removed %s\n", pDirent->d_name);
                    remove(argv[3]);
                }
            }
        }
        else{ //however, if we only have 2 commands or 3 and such, just print all the files in the directory
            printf ("%s\n", pDirent->d_name);
        }
        
    }
    closedir (pDir); //close the directory once we're done with it
    return 0;
}
