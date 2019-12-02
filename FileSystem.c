#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int seatStatus[150];
int writingLock = 0;
char openName[150][30];
char openDOB[1500];
char openGender[1500];
char openID[1500];

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
//IN PROGRESS
void openFlight(int flightDate){
	FILE *fptr;
   
	char s[20];
	sprintf(s, "%d", flightDate);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
    fptr = fopen("102020.txt", "rb+");
	char delimiter[200];
	fgets(delimiter,200,fptr);
	char data[200];
	int seatNumber=0;
	stpcpy(data, delimiter);
    while(strcmp(data, delimiter) == 0){
		fgets(data, 200, fptr); //seat number
		seatNumber = atoi(data)-1;
		fgets(data, 200, fptr);	//name
		//*(openName+(seatNumber-1)*20) = *data;
		
		if(strcmp(data, "\n")==0){seatStatus[seatNumber]=0;}
		else{seatStatus[seatNumber]=1;}
		
		fgets(data, 200, fptr); //DoB
		//*(openDOB+seatNumber*8) = *data;
		
		fgets(data, 200, fptr);	//Gender
		//*(openGender+seatNumber*8) = *data;
		
		fgets(data, 200, fptr);	//ID
		//*(openID+seatNumber*8) = *data;
		
		fgets(data, 200, fptr); //delimiter
	}
	fputs("\n", fptr);
	fclose(fptr);
}


void makeReservation(int flightDate, char* customerName, char* customerDoB, char customerGender, int customerIDno){

}


void modifyReservation(int transactionNo){
	
	
}


void cancelReservation(){
	
}

//Used only for testing.
int main()
{
    openFlight(102020);
	
	printSeats();
	
	//printf("\n%s ", openName[0][0]);
	
    return EXIT_SUCCESS;
}
