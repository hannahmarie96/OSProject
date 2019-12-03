#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int seatStatus[150];
int writingLock = 0;
int reciptLock =0;
char openName[150][30];
char openDOB[150][10];
char openGender[150][10];
char openID[1500][10];

//Complete DAP
void printSeats(){
	printf(ANSI_COLOR_RED "Red indicates a seat is unavaliable.\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN "Green indicates a seat is avaliable.\n" ANSI_COLOR_RESET);
	for(int i=0; i < 150; i++){
		//Print Seat Status
		if(seatStatus[i]==0){printf(ANSI_COLOR_GREEN "%d " ANSI_COLOR_RESET, i+1);} //seat is avaliable
		else{printf(ANSI_COLOR_RED "%d " ANSI_COLOR_RESET, i+1);} //seat is filled
		if(i%5 ==4) {printf("\n");}
	}
}
//all printf change into send data from server->client
//Complete DAP
void viewRecipt(int transactionNo){
	FILE *fptr;
	char s[20];
	sprintf(s, "%d", transactionNo);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
	fptr = fopen(filename, "r");
	
	if(fptr == NULL){
		printf("Transaction not Found.");
	}
	else{
		int loop =0;
		char delimiter[200];
		fgets(delimiter,200,fptr);
		char data[200];
		while(strcmp(data, delimiter) == 0){
			if(loop==0){	
				printf("---------Transaction Information------------\n");
				//TransactionID
				fgets(data, 200, fptr);
				printf("Transaction ID: %s", data);
				//Email Address
				fgets(data, 200, fptr);
				printf("Contact Email: %s", data);
				//Phone Number
				fgets(data, 200, fptr);
				printf("Contact Number: %s", data);
				loop=1;
			}
			printf("---------------Customer %d-------------------\n", loop);
			//Name
			fgets(data, 200, fptr);
			printf("Customer Name: %s", data);
			//DoB
			fgets(data, 200, fptr);
			printf("Customer DoB: %s", data);
			//Gender
			fgets(data, 200, fptr);
			printf("Gender: %s", data);
			//Government ID
			fgets(data, 200, fptr);
			printf("Government ID: %s", data);
			//Flight Date
			fgets(data, 200, fptr);
			printf("Flight Date: %s", data);
			//Seat Number
			fgets(data, 200, fptr);
			printf("Seat Number: %s", data);
			//delimiter
			fgets(data, 200, fptr);
			loop++;
		}
		printf("--------------------------------------------\n");
		fclose(fptr);
	}
}
//Complete DAP
void newFlight(int flightDate){
	FILE *fptr;
   
	char s[20];
	sprintf(s, "%d", flightDate);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
    fptr = fopen("102020.txt", "wb+");
    for(int i=1; i<151; i++){
		fputs("&\n", fptr); 	//delimiter
		fprintf(fptr, "%d\n", i); //seat number
		fputs("\n", fptr);		//name
		fputs("\n", fptr); 		//DoB
		fputs("\n", fptr);		//Gender
		fputs("\n", fptr);		//ID
	}
	fputs("\n", fptr);
	fclose(fptr);
}
//Complete DAP
void openFlight(int flightDate){
	FILE *fptr;
   
	char s[20];
	sprintf(s, "%d", flightDate);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
    fptr = fopen("102020.txt", "r");
	char delimiter[200];
	fgets(delimiter,200,fptr);
	char data[200];
	int seatNumber=0;
	stpcpy(data, delimiter);
    while(strcmp(data, delimiter) == 0){
		fgets(data, 200, fptr); //seat number
		seatNumber = atoi(data)-1;
		fgets(data, 200, fptr);	//name
		strcpy(openName[seatNumber], data);
		if(strcmp(data, "\n")==0){seatStatus[seatNumber]=0;}
		else{seatStatus[seatNumber]=1;}
		
		fgets(data, 200, fptr); //DoB
		strcpy(openDOB[seatNumber], data);
		
		fgets(data, 200, fptr);	//Gender
		strcpy(openGender[seatNumber], data);
		
		fgets(data, 200, fptr);	//ID
		strcpy(openID[seatNumber], data);
		
		fgets(data, 200, fptr); //delimiter
	}
	fputs("\n", fptr);
	fclose(fptr);
}

//Complete DAP
//simple helper function to convert date string into int
int date2int(char date[15]){
	char *buffer = NULL; 
	buffer = strtok(date, "/");
	int month = atoi(buffer);
	buffer = strtok(NULL, "/");
	int day = atoi(buffer);
	buffer = strtok(NULL, "\0");
	int year = atoi(buffer)%100;
	int output = month * 10000 + day * 100 + year;
	return output;
}
//Inprogress
void makeReservation(int flightDate, int reservations){
	while(writingLock==1){;}
	writingLock=1;
	openFlight(flightDate);
	
	writingLock=0;
	
	while(reciptLock==1){;}
	reciptLock =1;
	makeRecipt(transactionNo,);
}


//Mostly complete DAP --needs tested
void makeRecipt(int transactionNo, char customerEmail[30], char customerPhone[15], char customerName[30], char customerDOB[15], char customerGender[10], char customerID[10], char flightDate[15], char seatNumber[5]){
	FILE *fptr;
	char s[20];
	sprintf(s, "%d", transactionNo);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
	fptr = fopen(filename, "w+");
	
	if(fptr == NULL){
		printf("Error Creating Recipt.");
	}
	else{
	fputs("&\n", fptr);
	fprintf(fptr, "%d\n", transactionNo);
	fprintf(fptr, "%s\n", customerEmail);
	fprintf(fptr, "%s\n", customerPhone);
	fprintf(fptr, "%s\n", customerName);
	fprintf(fptr, "%s\n", customerDOB);
	fprintf(fptr, "%s\n", customerGender);
	fprintf(fptr, "%s\n", customerID);
	fprintf(fptr, "%s\n", flightDate);
	fprintf(fptr, "%s\n", seatNumber);
	fclose(fptr);
	}
}


//mostly complete DAP -- needs testing
void appendRecipt(int transactionNo, char customerName[30], char customerDOB[15], char customerGender[10], char customerID[10], char flightDate[15], char seatNumber[5]){
	FILE *fptr;
	char s[20];
	sprintf(s, "%d", transactionNo);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
	fptr = fopen(filename, "a");
	fprintf(fptr, "%s\n", customerName);
	fprintf(fptr, "%s\n", customerDOB);
	fprintf(fptr, "%s\n", customerGender);
	fprintf(fptr, "%s\n", customerID);
	fprintf(fptr, "%s\n", flightDate);
	fprintf(fptr, "%s\n", seatNumber);
	fputs("&\n", fptr);
}


void modifyReservation(int transactionNo){
	
}


void cancelReservation(int transactionNo){
	
}

//Used only for testing.
int main(){
	//flight number is based on 6 number date

    return EXIT_SUCCESS;
}
