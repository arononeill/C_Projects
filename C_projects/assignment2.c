/* Title: Assignment #2 Encrypting & Decrypting code
Author: Aron O'Neill
Date: 22/02/17
*/

#include <stdio.h>
#define SIZE 4

//Decloreing function prototypes by reference
void PIN (int*, int*, int*, int*);
void ENCRYPT (int*, int*, int*, int*, int*, int*);
void COMPARE (int*, int*, int*, int*, int*);
void DECRYPT (int*, int*, int*, int*);
void COUNT (int*, int*, int*);
void END ();

int main ()
{
    int pin[SIZE];
    int input = 0;
    int count_right = 0;
    int count_wrong = 0;
    int encrypt = 0;
    int encrypt_twice = 0;
    int pin_first = 0;
    int *code_p;
    int *correctly_entered;
    int *INcorrectly_entered;
    int *EncryptBeforeDecrypt;
    int *EncryptingTwice;
    int *EnterPinFirst;
    
    //Accessing variables using pointers
    code_p = pin;

    //Count how many times the user enters their code in correctly and incorrectly
    correctly_entered = &count_right;
    INcorrectly_entered = &count_wrong;
    
    //Ensures that the user encrypts before decrypting
    EncryptBeforeDecrypt = &encrypt;
    
    //Counter used to ensure the user cant encrypt the code twice
    EncryptingTwice = &encrypt_twice;
    
    //counter used so that the menu is firstly displayed the user can only choose option 1
    EnterPinFirst = &pin_first;
    
    //Display the following menu until the user enters 5 to exit the code
    do
    {
        
        printf("Please select any one of the following:\n\n");
        printf("1. Enter code\n");
        printf("2. Encrypt code and verify if correct\n");
        printf("3. Decrypt code\n");
        printf("4. Display the number of times the code was entered (i) Successfully (ii) Incorrectly\n");
        printf("5. Exit Program\n");
        scanf("%d", &input);
        
        switch (input)
        {
            case 1:
            {
                //call function PIN
                PIN (code_p, EncryptBeforeDecrypt, EncryptingTwice, EnterPinFirst);
                
                break;
                //end case 1
            }
            
            case 2:
            {
                //call function ENCRYPT
                ENCRYPT (code_p, correctly_entered, INcorrectly_entered, EncryptBeforeDecrypt, EncryptingTwice, EnterPinFirst);
                
                break;
                //end case 2
            }
            
            case 3:
            {
                //call function DECRYPT
                DECRYPT (code_p, EncryptBeforeDecrypt, EncryptingTwice, EnterPinFirst);
                
                break;
                //end case 3
            }
            
            case 4:
            {
                //call function COUNT
                COUNT (correctly_entered, INcorrectly_entered, EnterPinFirst);
                
                break;
                //end case 3
            }
        }
    }
    while (input != 5);
    
    //call function END
    END();
        
    getchar();
    getchar();
    
    return 0;
} // end main

//Implement function PIN
void PIN (int *code_p, int *EncryptBeforeDecrypt, int *EncryptingTwice, int *EnterPinFirst)
{  
    //Used so that if the user enters more than one digit then this loop starts again until they meet the requirements
    int condition2 = 0;
    
    while (condition2 == 0)
    {
        int i = 0;
        
        //Used to ensure the pin is only 4 digits long
        int condition = 0;
        
        //Counts how many digits are entered
        int FourDigits = 0;
        
        //Iniatialised to 0 so that the user can encrypt  their  code if the decide to re-enter a code
        *EncryptingTwice = 0;
        
        //Counter used so that the user may now decrypt their code
        *EncryptBeforeDecrypt = 0;
        
        printf("Enter your 4 digit PIN one digit at a time\n");
        
        while (condition == 0)
        {
            FourDigits++;
            
            scanf("%d", code_p+i);
            
            //Error checks so that each digit is less than 10
            if (*(code_p+i) > 9)
            {
                condition++;
            }
            
            else
            {
                if (FourDigits == SIZE)
                {
                    //Exits the first while loop as the requirements have been reached
                    condition2++;
                    condition++;
                }
            }
            i++;
        }
    }
    
    printf("\nYou have successfully entered your pin\nYour pin is: ");
    
    for (int i=0; i<SIZE; i++)
    {
        printf("%d", *(code_p+i));   
    }
    
    *EnterPinFirst = 1;
    
    printf("\n\n");
    
} //end function PIN

//Implement function ENCRYPT
void ENCRYPT (int *code_p, int *correctly_entered, int *INcorrectly_entered, int *EncryptBeforeDecrypt, int *EncryptingTwice, int *EnterPinFirst)
{   
    if (*EnterPinFirst == 1)
    {
        if (*EncryptingTwice == 0)
        {
            int tmp;
            
            //Algorithm to encrypt the user's pin
            tmp = *(code_p);
            *(code_p) = *(code_p+2);
            *(code_p+2) = tmp;
            
            tmp = *(code_p+1);
            *(code_p+1) = *(code_p+3);
            *(code_p+3) = tmp;
            
            //Increments each element
            for (int i=0; i<SIZE; i++)
            {
                (*(code_p+i))++;
                
                //sets any element that is now at 10 to 0
                if (*(code_p+i) == 10)
                {
                    *(code_p+i) = 0;
                }
                
            }
            
            printf("\nYour encyrpted pin is: ");
            
            for (int j=0;j<SIZE;j++)
            {
                printf("%d", *(code_p+j));   
            }
            
            printf("\n");
            
            //call function COMPARE
            COMPARE (code_p, correctly_entered, INcorrectly_entered, EncryptBeforeDecrypt, EncryptingTwice);
        }
        
        else
        {
            printf("\nSorry you have already encrypted this pin\n\n");
        }
    }
    
    else
    {
        printf("Please enter a pin first\n\n");
    }
    
} //end function ENCRYPT

//Implement function COMPARE
void COMPARE (int *code_p, int *correctly_entered, int *INcorrectly_entered, int *EncryptBeforeDecrypt, int *EncryptingTwice)
{  
    int access_code[] = {4, 5, 2, 3};
    bool flag = true;
    
    //Compares the encrypted user's pin with the access_code to see if they match
    for (int i = 0; i < SIZE; i++) {
        if (*(code_p + i) != *(access_code + i)) {
            flag = false;
            break;
        }
    }
    
    if (flag) {
        printf("\nCORRECT CODE!");
        (*correctly_entered)++;
    }
    
    else
    {
        printf("\nERROR CODE!");
        (*INcorrectly_entered)++; 
    }
    
    //Enables the user to now decrypt their encrypted code
    *EncryptBeforeDecrypt = 1;
    
    //stops the user from encrypting the code twice
    *EncryptingTwice = 1;
    
    printf("\n\n");
}  // end function COMPARE

//Implement function DECRYPT
void DECRYPT (int *code_p, int *EncryptBeforeDecrypt, int *EncryptingTwice, int *EnterPinFirst)
{   
    if (*EnterPinFirst == 1)
    {
        if (*EncryptBeforeDecrypt == 1)
        {
            int tmp;
            
            tmp = *(code_p+3);
            *(code_p+3) = *(code_p+1);
            *(code_p+1) = tmp;
            
            tmp = *(code_p);
            *(code_p) = *(code_p+2);
            *(code_p+2) = tmp;
            
            //Algorithm to decrypt the user's encrypted pin
            for (int i=0; i<SIZE; i++)
            {
                (*(code_p+i))--;
                
                if (*(code_p+i) == -1)
                {
                    *(code_p+i) = 9;
                }
            }
            
            printf("\nYour decyrpted pin is: ");
            
            for (int j=0;j<SIZE;j++)
            {
                printf("%d", *(code_p+j));   
            }
            
            
            (*EncryptBeforeDecrypt)++;
            
            //resets EncryptingTwice to 0 so that the code can now be encrypted
            *EncryptingTwice = 0;
            
            printf("\n\n");
        }
        
        else 
        {
            printf("\nsorry you must firstly encrypt this code in order to decrypt it\n\n");
        }
    }
    
    else
    {
        printf("Please enter a pin first\n\n");
    }
} //end function DECRYPT

//Implement function COUNT
void COUNT (int *correctly_entered, int *INcorrectly_entered, int *EnterPinFirst)
{
    if (*EnterPinFirst == 1)
    {
        //Displays the number of times the user's encrypted pin matches and doesn't match the access_code
        printf("\nYou entered your pin %d times correctly\n", *correctly_entered);
        printf("\nYou entered your pin %d times incorrectly\n", *INcorrectly_entered);
        
        printf("\n\n");
    }
    
    else
    {
        printf("Please enter a pin first\n\n");
    }
} //end function COUNT

//Implement function END
void END (void)
{
    printf("\n\n\t\t***Thank you for using this service***");
} //end function END