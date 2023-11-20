#include <cs50.h>
#include <stdio.h>

int calculate_years(int s, int e);

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int year = calculate_years(start, end);

    // TODO: Print number of years
    printf("Years: %i\n", year);
}

int calculate_years(int s, int e)
{
    int y = 0;
    while (s < e)
    {
        s += (s / 3 - s / 4);
        y++;
    }
    return y;
}
