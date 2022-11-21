#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "terminal.h"
#include "card.h"
#define max_amount 8000

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    uint8_t currentday[3], currentmonth[3], currentyear[5];
    time_t rawtime = time(NULL);
    struct tm currentdate;
    localtime_s(&currentdate, &rawtime);
    sprintf(currentday, "%d", currentdate.tm_mday);
    sprintf(currentmonth, "%d", currentdate.tm_mon + 1);
    sprintf(currentyear, "%d", currentdate.tm_year + 1900);
    if (currentdate.tm_mday < 9) {
        (termData->transactionDate[0]) = 0;
        (termData->transactionDate[1]) = currentday[0];
    }
    else {
        (termData->transactionDate[0]) = currentday[0];
        (termData->transactionDate[1]) = currentday[1];
    }
    (termData->transactionDate[2]) = '/';
    
    if (currentdate.tm_mon < 9) {
        (termData->transactionDate[3]) = 0;
        (termData->transactionDate[4]) = currentmonth[0];
    }
    else {
        (termData->transactionDate[3]) = currentmonth[0];
        (termData->transactionDate[4]) = currentmonth[1];
    }
    (termData->transactionDate[5]) = '/';
    (termData->transactionDate[6]) = currentyear[0];
    (termData->transactionDate[7]) = currentyear[1];
    (termData->transactionDate[8]) = currentyear[2];
    (termData->transactionDate[9]) = currentyear[3];
    (termData->transactionDate[10]) = '\0';
   
    if ((termData->transactionDate) == NULL)
        return WRONG_DATE;
    
    else return ok;
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData , ST_terminalData_t termData)
{
   if ((cardData->cardExpirationDate[3]) < (termData.transactionDate[8])) {
        return EXPIRED_CARD;
    }
    if ((cardData->cardExpirationDate[3]) == (termData.transactionDate[8]))
    {
        if ((cardData->cardExpirationDate[4]) < (termData.transactionDate[9]))
            return EXPIRED_CARD;
        if ((cardData->cardExpirationDate[4]) == (termData.transactionDate[9]))
        {
            if ((cardData->cardExpirationDate[0]) < (termData.transactionDate[3]))
                return EXPIRED_CARD;
            if ((cardData->cardExpirationDate[0]) == (termData.transactionDate[3]))
            {
                if ((cardData->cardExpirationDate[1]) < (termData.transactionDate[4]))
                    return EXPIRED_CARD;
            }
        }
    }
    printf("Your Card is Not Expired\n");

    return ok;
}
    

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
    uint32_t digits_number = strlen(cardData->primaryAccountNumber), sum = 0;
    bool I_is_odd = false ;
    for (int32_t i = digits_number - 1 ; i >= 0; i--) {
        uint32_t current_number = cardData->primaryAccountNumber[i] - '0';
        if (I_is_odd == true)
            current_number *= 2;
        sum += current_number / 10;
        sum += current_number % 10;
        I_is_odd = !I_is_odd;      
    }
    if (sum % 10 != 0)
        return INVALID_CARD;
    else return ok;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Enter the transaction amount:");
    scanf_s("%f", &termData->transAmount);
    printf("your transaction amount = %0.1f\n", termData->transAmount);
    if ((termData->transAmount) <= 0)
        return INVALID_AMOUNT;
    else return ok;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    (termData->maxTransAmount) = max_amount;
    if ((termData->maxTransAmount) <= 0)
        return INVALID_MAX_AMOUNT;
    else return ok;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if ((termData->maxTransAmount) < (termData->transAmount))
        return EXCEED_MAX_AMOUNT;
    else return ok;
}


