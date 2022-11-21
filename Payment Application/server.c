#include "server.h"
#include <stdio.h>
#include <string.h>

ST_accountsDB_t Accounts[255] = { 
	{ 5000.0, "5405798921072756"},
	{ 83.0, "2221005176217006"},
	{ 1000.00, "3528418710439423754"},
	{2100.0,"6380976818716167"}
};
ST_transaction_t Transactions[255] = { 0 };
uint32_t Account_Number = 0, Transaction_Number = 1;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
		return DECLINED_STOLEN_CARD;
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
		return DECLINED_INSUFFECIENT_FUND;
	if (saveTransaction(transData) == SAVING_FAILED)
		return INTERNAL_SERVER_ERROR;
	printf("Your Balance Before Transaction was %0.1f\n", Accounts[Account_Number].balance);
	Accounts[Account_Number].balance = (Accounts[Account_Number].balance - transData->terminalData.transAmount);
	printf("Your Balance After Transaction is %0.1f\n", Accounts[Account_Number].balance);
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (; Account_Number < 255; Account_Number++) {
		if (strcmp(cardData->primaryAccountNumber, Accounts[Account_Number].primaryAccountNumber) == 0)
		{
			return Ok;
		}
	}
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	
	if (termData->transAmount > Accounts[Account_Number].balance) {
		return LOW_BALANCE;
	}
	return Ok;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber = Transaction_Number;
	if (transData->transactionSequenceNumber < 255) {
		Transactions[(transData->transactionSequenceNumber) - 1].cardHolderData = transData->cardHolderData;
		Transactions[(transData->transactionSequenceNumber) - 1].transState = transData->transState;
		Transactions[(transData->transactionSequenceNumber) - 1].terminalData = transData->terminalData;
		Transactions[(transData->transactionSequenceNumber) - 1].transactionSequenceNumber = transData->transactionSequenceNumber;
		Transaction_Number++;
		return Ok;
}
	return SAVING_FAILED;
}
