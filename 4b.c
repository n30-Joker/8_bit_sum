#include <stdio.h>
#include <string.h> //[1]
#include <stdlib.h> //[3]

/*
For question 4b the way I am approaching it is to check if the values entered
are binary or not, to which a message is given and the program ends whenever
there was an invalid input. The binary values are converted to decimal by taking
out the MSB and converting the rest of it into binary, and if the MSB was 1 then
the value was multiplied by -1 to become negative. The two denary values are
added together, followed by converting the result into unsigned binary.
If the value was positive, it was left as it was, otherwise the values were
swapped to get one's complement. Finally by adding 1, two's complement is
achieved.
*/

int checkbinary(int value)
//makes sure the inputs were in binary, if there is a non binary value it returns 0
{
	int temp = 0;
	while (value != 0) {
        temp = value % 10;
		//divding by 10 approach: binary consists of only 1s and 0s so through mod
		//the remainder must be either 1 or 0, otherwise it is not binary
        if ((temp == 0) || (temp == 1)) {
            value = value / 10;
            if (value == 0)
            {
                return 1;
            }
        }
        else {
            return 0;
			
        }
    }
	return 1;
	//in case the value entered had all 0
}

int signed2decimal(char value[])
{
	char *c = value;
	char *d = c + 1;
	//[4] removes the MSB which is the sign and used later
	int decimal,sign;
	sign = strtol(value, NULL, 10) / 10000000;
	//gets the most significant bit by seeing it as an integer in denary,
	//dividing it to remove all the values after it
	if (sign == 1)
	{
		decimal = -1 * strtol(d, NULL, 2);
		//the MSB had a 1 therefore the value is negative
	}
	else
	{
		decimal = strtol(d, NULL, 2);
		//converts to binary
	}
	return decimal;
}

int complement (int decimal)
//decimal converted into unsigned binary, to then 2s complement
{
	int a[9], b[9], c[9], i, j, k;
	//initialise some arrays and values
	int carry = 1;
	j = decimal;
	if (j < 0)
	{
		j = j * -1;
	}
	for(i = 0; i < 8; i++)
	//halving method, since binary values represent 2^N dividing by
	//2 is the fastest way to get 1s and 0s converting the denary
	//to binary
	{    
		a[i] = j % 2;
		//remainder becomes the binary value at that position
		j = j / 2;
		if (a[i] == 0 && decimal < 0)
		//swapping the binary values (one's complement) only when negative
		{
			b [i] = 1;
		}
		else if (a [i] == 1 && decimal < 0)
		{
			b [i] = 0;
		}
		else
		{
			b [i] = a[i];
			//no change when values are positive
		}
	}

	printf("Let a be unsigned binary, b be one's complement of a (if negative, otherwise the same): \n");
	for(k = 7; k >= 0; k--)    
	{
		printf("a %d , b %d \n", a[k], b[k]);
	}
	for(k = 0; k <= 7; k++)
	//add 1 to the one's complement to get the 2's complement
	{
		if(b[k] == 1 && carry == 1 && decimal < 0)
		//makes sure that it is for the negative value
		{
			c[k] = 0;
		}
		else if (b[k] == 0 && carry == 1 && decimal < 0)
		{
			c[k] = 1;
			carry = 0;
		}
		else
		{
			c[k] = b[k];
		}
	}

	printf("The two's complement of the sum of the binaries is %d%d%d%d%d%d%d%d", c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);
	//put it all in a statement
	return 0;
}

int main ()
{
	char a[9],b[9]; //[2] initialising strings
	int result;
	printf("Please enter two 8-bit binary values: \n");
	scanf("%s %s", a, b);
	if (strlen(a) != 8 && strlen(b) != 8)
	//checks if they entered 8 bits
	{
		printf("Must enter 8-bit binary values \n");
		return 0;
	}
	else
	{
		if (checkbinary(strtol(a, NULL, 10)) == 0 || checkbinary(strtol(b, NULL, 10)) == 0)
		//checks if the values are in binary
		{
			printf("Must enter binary values \n");
			return 0;
		}
		result = signed2decimal(a) + signed2decimal(b);
		//adding the denary values
		complement(result);
		//the function to convert the resulting denary into 2's complement
		//is called, to which will also output the value
	}
}

/*Sources:
[1] https://www.programiz.com/c-programming/library-function/string.h/strlen
[2] https://www.programiz.com/c-programming/c-strings
[3] https://en.cppreference.com/w/c/string/byte/strtol
[4] https://stackoverflow.com/questions/4319763/how-do-i-remove-the-first-number-from-an-integer
*/