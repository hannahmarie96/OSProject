#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int seatStatus[150];
int writingLock = 0;
int receiptLock =0;
char openName[150][30];
char openDOB[150][10];
char openGender[150][10];
char openID[150][10];
//stored receipt information
char receiptEmail[30];
char receiptPhone[12];
char receiptSeats[150];
char receiptName[150][30];
char receiptDOB[150][10];
char receiptGender[150][10];
char receiptID[150][10];
char receiptFlights[150][10];
int receiptCustomerNo;

//all printf change into send data from server->client
//Helper function to allow customer to view seat status
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
//Used to allow Customer to view receipt information.
//Complete DAP
void viewReceipt(int transactionNo){
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

//Used to open and store receipt data into memory for editing
//Complete DAP - Needs Testing, but similar format worked.
void openReceipt(int transactionNo){
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
				//doesnt need to store transactionID
				//Email Address
				fgets(data, 200, fptr);
				strcpy(receiptEmail, data);
				//Phone Number
				fgets(data, 200, fptr);
				strcpy(receiptPhone, data);
			}
			//Name
			fgets(data, 200, fptr);
			strcpy(receiptName[loop], data)
			//DoB
			fgets(data, 200, fptr);
			strcpy(receiptDOB[loop], data)
			//Gender
			fgets(data, 200, fptr);
			strcpy(receiptGender[loop], data);
			//Government ID
			fgets(data, 200, fptr);
			strcpy(receiptID[loop], data)
			//Flight Date
			fgets(data, 200, fptr);
			strcpy(receiptFlights[loop], data)
			//Seat Number
			fgets(data, 200, fptr);
			strcpy(receiptSeats[loop], data)
			//delimiter
			fgets(data, 200, fptr);
			loop++;
		}
		printf("--------------------------------------------\n");
		fclose(fptr);
		receiptCustomerNo = loop;
	}
}

//Used to create the initial receipt
//Mostly complete DAP --needs tested
void makeReceipt(int transactionNo, char* customerEmail, char* customerPhone, char* customerName, char* customerDOB, char* customerGender, char* customerID, char* flightDate, char* seatNumber){
	FILE *fptr;
	char s[20];
	sprintf(s, "%d", transactionNo);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
	fptr = fopen(filename, "w+");
	
	if(fptr == NULL){
		printf("Error Creating Receipt.");
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

//Used to add additional Customers to the receipt after primary contact
//mostly complete DAP -- needs testing
void appendReceipt(int transactionNo, char* customerName, char* customerDOB*, char* customerGender, char* customerID, char flightDate*, char* seatNumber){
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

//Creates a new flight file
//Complete DAP
void newFlight(int flightDate){
	FILE *fptr;
   
	char s[20];
	sprintf(s, "%d", flightDate);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
    fptr = fopen(filename, "wb+");
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

//Opens existing flight file into memory
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
		// Seat Number
		fgets(data, 200, fptr); 
		seatNumber = atoi(data)-1;
		// Customer Name - Empty if vacant
		fgets(data, 200, fptr);	//name
		strcpy(openName[seatNumber], data);
		if(strcmp(data, "\n")==0){seatStatus[seatNumber]=0;}
		else{seatStatus[seatNumber]=1;}
		// Date of Birth
		fgets(data, 200, fptr); //DoB
		strcpy(openDOB[seatNumber], data);
		// Customer Gender
		fgets(data, 200, fptr);	//Gender
		strcpy(openGender[seatNumber], data);
		// Customer Gov ID
		fgets(data, 200, fptr);	//ID
		strcpy(openID[seatNumber], data);
		// detect delimiter
		fgets(data, 200, fptr); //delimiter
	}
	fputs("\n", fptr);
	fclose(fptr);
}

//Writes updated flight data into file from memory.
//Complete DAP
void writeFlight(int flightDate){
	FILE *fptr;
   
	char s[20];
	sprintf(s, "%d", flightDate);
	char filename[] = "./";
	strcat(filename, s);
	strcat(filename, ".txt");
    fptr = fopen(filename, "wb+");
    for(int i=1; i<151; i++){
		fputs("&\n", fptr); 	//delimiter
		fprintf(fptr, "%d\n", i); //seat number
		fprintf(fptr, "%s\n", openName[i-1]); //Name
		fprintf(fptr, "%s\n", openDOB[i-1]); //DOB
		fprintf(fptr, "%s\n", openGender[i-1]); //Gender
		fprintf(fptr, "%s\n", openID[i-1]); //ID
	}
	fputs("\n", fptr);
	fclose(fptr);
}

//simple helper function to convert date string into int
//Complete DAP
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

//Process of creating the reservations
//Complete DAP
void makeReservation(int flightDate, char* customerName, char* customerDOB, char* customerGender, char* customerID, int seatNumber){
	while(writingLock==1){;}
	writingLock=1;
	openFlight(flightDate);
	strcpy(openName[seatNumber], customerName);
	strcpy(openDOB[seatNumber], customerDOB);
	strcpy(openGender[seatNumber], customerGender);
	strcpy(openID[seatNumber], customerID);
	writeFlight(flightDate);
	writingLock=0;
}

//Process to modify an existing reservation.
//might be unnessecary with how make reservation is created;
void modifyReservation(int transactionNo, int customerNo){
	while(receiptLock==1 || writingLock ==1){;}
	receiptLock = 1; 
	writingLock = 1;
	
	openRecipt(transactionNo);
	int flightDate = atoi(receiptFlights[customerNo]);
	int seatNumber = atoi(receiptSeats[customerNo])
	openFlight(flightDate);
	
	strcpy(openName[seatNumber], receiptName[customerNo]);
	strcpy(openDOB[seatNumber], receiptDOB[customerNo]);
	strcpy(openGender[seatNumber], receiptGender[customerNo]);
	strcpy(openID[seatNumber], receiptID[customerNo]);
	
	writeFlight(flightDate);
	receiptLock=0;
	WritingLock=0;

}

//Process to delete a reservation
//Complete DAP- Needs Testing
void cancelReservation(int transactionNo){
	while(receiptLock==1 || writingLock ==1){;}
	receiptLock = 1; 
	writingLock = 1;
	
	openRecipt(transactionNo);
	int flightDate = atoi(receiptFlights[customerNo]);
	int seatNumber;
	openFlight(flightDate);
	while(seatNumber>0){
		seatNumber = atoi(receiptSeats[i])
		//empties values of 
		strcpy(openName[seatNumber], "\n");
		strcpy(openDOB[seatNumber], "\n");
		strcpy(openGender[seatNumber], "\n");
		strcpy(openID[seatNumber], "\n");
	}
	writeFlight(flightDate);
	WritingLock=0;
	//possibly add a wipe function later
	//clearReceipt(transactionID);
	receiptLock=0;
}

//Used only for testing.
/*int main(){
	//flight number is based on 6 number date

    return EXIT_SUCCESS;
}*/
