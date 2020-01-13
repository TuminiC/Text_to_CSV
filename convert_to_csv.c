#include <stdio.h>
#include <stdlib.h>
#include "convert_to_csv.h"
#include "read_csv.h"

void load_and_convert(const char* filename){
    char names[1000];
    char places[1000];
    char ages[1000];
    //longest city name has 85 letters
    FILE *input= fopen(filename,"rt");
    if(input==NULL)exit(1);
    FILE *output= fopen("output.csv", "wt");
    if(output==NULL)exit(1);
    //write each line of the text file to the corresponding
    fgets(names, sizeof(names),input);
    fgets(ages, sizeof(ages), input);
    fgets(places, sizeof(places),input);
    char *nametok, *agetok,*placetok;
    char *namerem, *agerem, *placerem;
    //break up to the arrays into segments with space as a delimeter
    const char sep[2]=" ";
    nametok=strtok_r(names,sep,&namerem);
    agetok= strtok_r(ages,sep,&agerem);
    placetok=strtok_r(places,sep,&placerem);
    //if these pointers are not null, write them in the necessary format
    while(nametok!=NULL||agetok!=NULL||placetok!=NULL){
		if(strchr(nametok,'\n')!=NULL){
			nametok[strlen(nametok)-1]='\0';
		}
		if(strchr(agetok,'\n')!=NULL){
			agetok[strlen(agetok)-1]='\0';
		}
		if(strchr(placetok,'\n')!=NULL){
			placetok[strlen(placetok)-1]='\0';
		}
		fprintf(output,"%s, %s, %s\n",nametok,agetok,placetok);
		nametok=strtok_r(NULL,sep,&namerem);
		agetok=strtok_r(NULL,sep,&agerem);
		placetok=strtok_r(NULL,sep,&placerem);
	}
	fclose(input);
	fclose(output);

    
    }
