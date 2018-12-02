#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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


long long convertOctalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0)
    {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}

int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    int base = 1; 
      
    int dec_val = 0; 
      
    for (int i=len-1; i>=0; i--) 
    {    

        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
            base = base * 16; 
        } 
  
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
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