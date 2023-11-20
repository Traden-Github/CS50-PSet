#include <cs50.h>
#include <stdio.h>

string validate(long n);
bool luhn(long n);
string cardtype(long n);

int main(void)
{
    long number = get_long("Number: ");

    string card = validate(number);

    printf("%s", card);
}

string validate(long n)
{
    if (luhn(n))
    {
        return cardtype(n);
    }
    else
    {
        return "INVALID\n";
    }
}

bool luhn(long n)
{
    int counter = 0;
    int product_sum = 0;
    int sum = 0;
    while (n != 0)
    {
        int digit = n % 10;
        counter++;
        if (counter % 2 == 0)
        {
            int product;
            if (digit * 2 >= 10)
            {
                int left = digit * 2 / 10;
                int right = digit * 2 % 10;
                product = left + right;
            }
            else
            {
                product = digit * 2;
            }
            product_sum += product;
        }
        else
        {
            sum += digit;
        }
        n /= 10;
    }
    int total = product_sum + sum;
    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string cardtype(long n)
{
    int digit_count = 0;
    long n_clone = n;
    while (n_clone != 0)
    {
        n_clone /= 10;
        digit_count++;
    }
    while (n != 0)
    {
        n /= 10;
        if ((n == 34 || n == 37) && digit_count == 15)
        {
            return "AMEX\n";
        }
        if ((n == 51 || n == 52 || n == 53 || n == 54 || n == 55) && digit_count == 16)
        {
            return "MASTERCARD\n";
        }
        if (n == 4 && (digit_count == 13 || digit_count == 16))
        {
            return "VISA\n";
        }
    }
    return "INVALID\n";
}
