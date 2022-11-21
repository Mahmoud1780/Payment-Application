#include <stdio.h>
#include <string.h>
#include "card.h"

#define card_holder_name_max 24
#define card_holder_name_min 20
#define card_expiry_date_len 5
#define card_pan_max_len 19
#define card_pan_min_len 16




EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Enter card holder name: ");
	scanf_s("%[^\n]s", &cardData->cardHolderName, card_holder_name_max + 1);
	if (strlen(cardData->cardHolderName) < card_holder_name_min || strlen(cardData->cardHolderName) > card_holder_name_max || (cardData->cardHolderName) == NULL)
		return WRONG_NAME;
	else return OK ;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)

{
	printf("Enter card Expiry Date in MM/YY format: ");
	scanf_s("%s", &cardData->cardExpirationDate, card_expiry_date_len + 1);
	
	if (strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate[2] != '/' || (cardData->cardExpirationDate) == NULL) 
	{
		return WRONG_EXP_DATE;
	}

	return OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter the Card PAN: ");

	scanf_s("%s", &cardData->primaryAccountNumber, card_holder_name_max + 1);
	if (strlen(cardData->primaryAccountNumber) < card_pan_min_len || strlen(cardData->primaryAccountNumber) > card_pan_max_len || (cardData->primaryAccountNumber) == NULL)
	{
		return WRONG_PAN;
	}
	printf("Your Card PAN is:%s\n", cardData->primaryAccountNumber);

	return OK;
}