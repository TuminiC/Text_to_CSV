#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"read_csv.h"

void read_csv(const char *csv_filename){
	FILE *input=fopen(csv_filename,"r");
	char line[1000];
	while(fgets(line,sizeof(line),input)!=NULL){
		printf("%s",line);
	}
	fclose(input);
}
