#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count(long);
int validating(long, int);
int get_start(long, int);
void flag_card(int, int);

int main(void)
{
    long card_number;
    int lenght;
    int sum;
    do
    {
        card_number = get_long("What's your credit card number?: ");

        lenght = count(card_number);
    }
    while (lenght < 8 || lenght > 16);

    sum = validating(card_number, lenght);

    if (sum % 10 != 0 || lenght < 13)
    {
        printf("INVALID\n");
    }
    else
    {
        int start = get_start(card_number, lenght);
        flag_card(start, lenght);
    }
}

void flag_card(int digit, int lenght)
{
    if ((digit / 10 == 4 && lenght == 13) || (digit / 10 == 4 && lenght == 16))
    {
        printf("VISA\n");
    }
    else if (digit >= 51 && digit <= 55 && lenght == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((digit == 34 && lenght == 15) || (digit == 37 && lenght == 15))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_start(long num, int lenght)
{
    while (num >= 100)
    {
        num /= 10;
    }
    return num;
}

int validating(long num, int lenght)
{
    int sum = 0;

    // looping in number to get last number and sum or multiply
    for (int i = 0; i < lenght; i++)
    {
        // digit is last number
        int digit = num % 10;

        if (i % 2 == 0)
        {
            sum += digit;
        }
        else if (digit >= 5)
        {
            sum += digit * 2 - 9;
        }
        else
        {
            sum += digit * 2;
        }
        num /= 10;
    }
    return sum;
}

int count(long num)
{
    int count = 0;
    while (num > 0)
    {
        num = round(num / 10);
        count++;
    }
    return count;
}