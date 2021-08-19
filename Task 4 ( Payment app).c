/*
 ============================================================================
 Name        : Task.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Payment application
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef unsigned char uint8_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef struct ST_terminalData_t
{
	float transAmount;
    float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_transStat_t
{
	DECLINED,
	APPROVED
}EN_transStat_t;

typedef struct ST_transaction_t
{
ST_cardData_t cardHolderData;
ST_terminalData_t transData;
EN_transStat_t transStat;
}ST_transaction;

typedef struct ST_accountBalance_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountBalance_t;


ST_accountBalance_t db[10]={{100.00,"123456789"},{6000.00,"234567891"},{3250.25,"567891234"},{1500.12,"456789123"},{500.00,"258649173"},{2100.00,"654823719"},{0.00,"971362485"},{1.00,"793148625"},{10.12,"123123456"},{0.55,"456789321"}};


int transaction(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);

		uint8_t name[25];
		uint8_t pan[20];
		uint8_t expiry_date[6];
		float trans_Amount;
		uint8_t trans_Date[11];



		printf("Please Enter Card Data: \n");
		printf("Please Enter the Card Holder Name: \n");
		gets(name);
		printf("Please Enter the Primary Account Number: \n");
		gets(pan);
		printf("Please card Expiry Date: \n");
		gets(expiry_date);
		printf("Please Enter Terminal Data:\n Please Enter the transaction Amount: \n");
		scanf("%f",&trans_Amount);
		printf("Please Enter transaction Date: \n");
		scanf("%s",trans_Date);
		printf("Verifying Data from the server... \n");


		// compare PAN
		uint8_t value;
		int i;
		for( i=0;i<10;i++)
		{
			 value=strcmp(pan,db[i].primaryAccountNumber);
			if(value==0)
			{
				break;
			}

		}
		if(value!=0)
		{
			return 0;
		}

		// compare transaction amount with balance

		else if(trans_Amount>db[i].balance)
		{
			return 0;
		}

		// compare transaction amount with max account

		else if(trans_Amount>5000.0)
			{
				return 0;
			}

		// checking Expiry date
		uint8_t expiry_month[3];
		uint8_t expiry_year[3];
		memcpy(expiry_year,&expiry_date[3],2);
		expiry_year[2]='\0';
		uint8_t exp_year=atoi(expiry_year);

		memcpy(expiry_month,&expiry_date[0],2);
		expiry_month[2]='\0';
		uint8_t exp_month=atoi(expiry_month);


		uint8_t transaction_month[3];
		uint8_t transaction_year[3];
		memcpy(transaction_year,&trans_Date[8],2);
		transaction_year[2]='\0';
		uint8_t trans_year=atoi(transaction_year);

		memcpy(transaction_month,&trans_Date[3],2);
		transaction_month[2]='\0';
		uint8_t trans_month=atoi(transaction_month);

		if(trans_year>exp_year)
		{
			return 0;
		}
		else if((trans_year==exp_year)&&(trans_month>exp_month))
		{

			return 0;
		}



		return 1;



}


int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	uint8_t again=1;
	uint8_t yes_or_no;
	while(again==1)
{
	int trans;
	trans=transaction();
	if(trans==0)
	{
		printf("The Transaction is DECLINED \n");

	}
	else if(trans==1)
	{
		printf("The Transaction is APPROVED \n");

	}

	// check if user wants to continue

	again=0;
	printf("Do you want to continue (y/n)?: \n");
	scanf("%c",&yes_or_no);
	if(yes_or_no=='y')
	{
		again=1;
	}



}


}


