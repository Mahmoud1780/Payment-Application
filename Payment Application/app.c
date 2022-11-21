#include<stdio.h>
#include <string.h>
#include "card.h"
#include "server.h"
#include "app.h"
#include "types.h"
#define appStart main

void appStart(void)
{

	ST_cardData_t cardHolderData;
	ST_cardData_t* cardData = &cardHolderData;

	ST_terminalData_t terminalData;
	ST_terminalData_t* termData = &terminalData;

	ST_transaction_t transactonData;
	ST_transaction_t* transData = &transactonData;

	if (getCardHolderName(cardData) == WRONG_NAME)
	{
		printf("Wrong Name");
		return 0;
	}
	if (getCardPAN(cardData) == WRONG_PAN)
	{
		printf("Wrong PAN");
		return 0;
	}
	if (getCardExpiryDate(cardData) == WRONG_EXP_DATE)
	{
		printf("Wrong Expiry Date");
		return 0;
	}
	
	if (isValidCardPAN(cardData) == INVALID_CARD)
	{
		printf("Invalid card");
		return 0;
	}
	if (getTransactionDate(termData) == WRONG_DATE)
	{
		printf("Wrong Date");
		return 0;
	}
	if (isCardExpired(cardData, terminalData) == EXPIRED_CARD)
	{
		printf("Expired Card");
		return 0;
	}
	if (getTransactionAmount(termData) == INVALID_AMOUNT)
	{
		printf("Invalid Amount");
		return 0;
	}
	if (setMaxAmount(termData) == INVALID_MAX_AMOUNT)
	{
		printf("Invalid Max Amount");
		return 0;
	}
	if (isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
	{
		printf("Exceeded Max Amount");
		return 0;
	}
	transData->cardHolderData = cardHolderData;
	transData->terminalData = terminalData;
	switch (recieveTransactionData(transData))
	{
	case DECLINED_INSUFFECIENT_FUND:
		printf("Declined Insuffecient Fund");
		saveTransaction(transData);
		break;
	case DECLINED_STOLEN_CARD:
		printf("Declined Stolen Card");
		saveTransaction(transData);
		break;
	case INTERNAL_SERVER_ERROR:
		printf("Internal Server Error");
		break;
	case APPROVED:
		printf("Approved Transaction");
		break;
	default:
		break;
	}

}