#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "base.h"

int BinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, zbytek;
    while (n!=0)
    {
        zbytek = n%10;
        n /= 10;
        decimalNumber += zbytek*pow(2,i);
        ++i;
    }
    return decimalNumber;
}


int DecimalToOctal(int decimalNumber)
{
    int octal_num = 0, i = 1;	

    while (decimalNumber != 0)
    {
        octal_num += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octal_num;
}


// Function to convert hexadecimal to decimal 
int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
      
    // Extracting characters as digits from last character 
    for (int i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} 



int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
