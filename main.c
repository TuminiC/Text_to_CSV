#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"convert_to_csv.h"
#include"read_csv.h"

//Helper function to see if a name is present
int check_name(char *line, const char *name){
	const char separator[2]=",";
	char *tokenA=strtok(line,separator);
	if(!strcmp(tokenA,name)){
		return 1;
	} else{
		return 0;
	}
}

void find_name(const char *csv_filename, const char *name){
	FILE *input=fopen(csv_filename,"r");
	char line[1000];
	int count=0;
	int match[100]={0};
	for(int i=0;fgets(line,sizeof(line),input)!=NULL;i++){
		if(check_name(line, name)){
			count=1;
			match[i]=1;
		}
	}
	fclose(input);
	if(!count){
		printf("Name not found\n");
	} else{
		int j=0;
		FILE *input=fopen(csv_filename,"r");
		while(fgets(line,sizeof(line),input)!=NULL){
			if(match[j]){
				printf("%s",line);
			}
			j++;
		}
		fclose(input);
	}
}

void add_record(const char *csv_filename, const char *name, const int age, const char *city){
	FILE *output=fopen(csv_filename,"a");
	if(output==NULL) exit(-1);
	fprintf(output,"%s, %d, %s\n",name,age,city);
	fclose(output);
}

void delete_record(const char *csv_filename, const char *name){
	FILE *oldFile, *newFile;
	char a;
	char line[1000];
	int deleteLine, temp=1;
	oldFile=fopen(csv_filename,"r");
	for(deleteLine=1;fgets(line,sizeof(line),oldFile);deleteLine++){
		if(check_name(line,name)){
			break;
		}
	}
	newFile=fopen("replica.csv","w");
	rewind(oldFile);
	a='Z';
	while(a!=EOF){
		a=getc(oldFile);
		if(temp!=deleteLine) putc(a,newFile);
		if(a=='\n') temp++;
	}
	remove(csv_filename);
	rename("replica.csv",csv_filename);
	fclose(oldFile);
	fclose(newFile);
}

int main(){
	/*Question 1*/
	load_and_convert("input.txt");
	/*Question 2*/
	read_csv("output.csv");
	/*Question 3.1*/
	find_name("output.csv","Maria");
	find_name("output.csv","Jason");
	/*Question 3.2*/
	add_record("output.csv", "Jason", 36, "Skookmuchuk");
	read_csv("output.csv");	
	/*Question 3.3*/
	delete_record("output.csv","Maria");
	read_csv("output.csv");	//to print to the screen
	return 0;
}

