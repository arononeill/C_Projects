/*Auhtor:Aron O'Neill
   Date:4/11/2017
   Programming assignment 1 - QUIZ */


#include <stdio.h>
int main ()
{
    //Initialising variables
    
    //used so that part 1 is executed first
    int startQuiz = 0;
    //used so that you cant check part 3 wihtout doing part 2
    int part2IsDone = 0;
    int counter = 1;
    int exit = 1;
	int num = 0;
	int option = 0;
    int answer1 = 0;
    int answer2 = 0;
    int answer3 = 0;
    int answer4 = 0;
    int answer5 = 0;
    int counterRight = 0;
    int counterWrong = 0;
	
    printf("\t\tMaths Quiz Game\n");
    
    while (option != 4)
    {
        //While loop running menu 
        printf("\nSelect which option you like:\n\n");
        printf("1. Enter the number of questions for this round (max 5)\n");
        printf("2. Start Quiz\n");
        printf("3. Display the number of questions that were answered (i) correctly (ii) incorrect\n");
        printf("4. Exit Program\n\n");
        scanf("%d", &option);
        
        if (option == 1)
        {
            //Menu screen input reading 
            printf(" 1.How many Questions would you like to answer? \n");
            scanf("%d",&num);
            printf("\nYou would like to answer %d questions \n", num );
            startQuiz = 1; // The user can now select part 2
        } //End if statement
        
        if (startQuiz == 1)
        {
            if (option == 2)
            {
                printf("\nFirst Question:\n");
                printf("What is 2 + 2\n");
                scanf("%d", &answer1);
                
                //checks whether the numbeer inputted is the right answer
                if (answer1 == 4)
                {
                    //Counts right answers
                    counterRight++;
                }
                
                else 
                {
                    //Counts left answers
                    counterWrong++;
                } //end if else 
                
                //checks if the number of questions the user asks is equal to the counter that records how many questions have been asked so far
                if (num != counter)
                {
                    printf("\nSecond Question:\n");
                    printf("What is 3 + 2\n");
                    scanf("%d", &answer2);
                    // counts number of questions displayed
                    counter = 2;
                    
                    if (answer2 == 5)
                    {
                        counterRight++;
                    }
                    
                    else 
                    {
                        counterWrong++;
                    } //end if else 
                }
                
                else
                {
                    //skips the rest of the questions
                    exit = 1;
                }
                
                //checks if the number of questions the user asks is equal to the counter that records how many questions have been asked so far
                if (exit != 1 || num != counter)
                {
                    printf("\nThird Question:\n");
                    printf("What is 4 + 2\n");
                    scanf("%d", &answer3);
                    // counts number of questions displayed
                    counter = 3;
                    
                    if (answer3 == 6)
                    {
                        counterRight++;
                    }
                    
                    else 
                    {
                        counterWrong++;
                    } //end if else 
                }
                
                else 
                {
                    //skips the rest of the questions
                    exit = 1;
                }
                
                //checks if the number of questions the user asks is equal to the counter that records how many questions have been asked so far
                if (exit != 1 || num != counter)
                {
                    printf("\nFourth Question:\n");
                    printf("What is 5 + 2\n");
                    scanf("%d", &answer4);
                    exit = 1;
                    if (answer4 == 7)
                    {
                        counterRight++;
                    }
                    
                    else 
                    {
                        counterWrong++;
                    } //end if else 
                }
                
                else 
                {
                    //skips the rest of the questions
                    exit = 1;
                }
                
                //checks if the number of questions the user asks is equal to the counter that records how many questions have been asked so far
                if (exit != 1 || num == 5)
                {
                    printf("\nFifth Question:\n");
                    printf("What is 6 + 2\n");
                    scanf("%d", &answer5);
                    
                    if (answer5 == 8)
                    {
                        counterRight++;
                    }
                    
                    else 
                    {
                        counterWrong++;
                    } //end if else 
                }
                
                part2IsDone = 1;
                
            } // end else if 
            
            else if (option == 3)
            {
                if ( part2IsDone == 1)
                {
                    printf("\n\t***You answered it right %d times***\n\n", counterRight);
                    printf("\t***You answered it wrong %d times\n\n***", counterWrong);
                }
                
                else
                {
                    printf("\n\n**Start Quiz before doing part 3**\n\n");
                }
            } //end if else if 
        }
        
        else 
        {
            printf("\n\n**You have to use part 1 before any other part**\n\n");
        }
    } //End while loop 
    
    printf("\n\n\t\t***Thank you for using this service***");
    
    getchar();
    getchar();
    
	
	return 0;
} //End main
