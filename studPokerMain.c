/* Status of main function execution */
#define EXECUTIONSTATUS 0
/* Functions from DeckOfCards.c */
#include "PokerTable.h"

/*
Function to validate the command-line input provided by the user. This program
requires two integers who's product is less than or equal to 52. The first
will be ignored and replaced by the integer CARDSPERHAND.

Input   = {int: argc, char * *: argv, int *: numOfHands}
Output  = {bool: valid}
*/
bool validateUserInput(int, const char * *, int *);

/*
Function to explain to the user the reasons for program termination, this
program requires two integers who's product is less than or equal to 52.

Input	= {void: null}
Output	= {void: null}
*/
void printReasonForTermination();

int main(int argc, const char * argv[])
{
  int handNum = NUM_INIT;
  int checkNumOfHands = NUM_INIT;
  char * message = NUM_INIT;
  if(validateUserInput(argc, argv, & checkNumOfHands) == TRUE)
  {
    pokerTable table;
    /* Use pointers to interact with poker table */
    card * deckPTR = table.deckOfCards;

    if(createDeck(deckPTR) == TRUE) /* validate deckPTR */
    {
      const int numOfHands = checkNumOfHands;
      /* Print original deck */
      message = "\n\nOriginal Ordered Deck:\n";
      printf("%s", message);
      printDeck(deckPTR);
      /* shuffle deck */
      modernFisherYatesShuffle(deckPTR);
      message = "Random Shuffled Deck:\n";
      printf("%s", message);
      printDeck(deckPTR);
      /* Deal cards to hands */

      if(dealHands(deckPTR, table.hands) == TRUE)
      {
        message = "Player Hands: (dealt from top/front of deck)\n";
        printf("%s", message);
        printHands(table.hands, numOfHands, 1);
        /* Sort Deck */

        message = "Player Hands: sorted\n";
        sortHands(table.hands);
        printf("%s", message);
        printHands(table.hands, numOfHands, 1);
        message = "Player Hands: ranked\n";
        printf("%s", message);
        printHands(table.hands, numOfHands, 2);
        message = "Player Hands: winner(s)\n";
        printf("%s", message);
        printHands(table.hands, numOfHands, 3);
        message = "Poker Hands: test\n";
        printf("%s", message);
        printHands(table.hands, numOfHands, 4);
      }
      else
      {
        message = "Unknown system error...\nExiting!\n";
        printf("%s", message);
      }
    }
  }
  else
  {
    printReasonForTermination();
  }
  return EXECUTIONSTATUS;
}

/*
Function to validate the command-line input provided by the user. This program
requires two integers who's product is less than or equal to 52. The first
will be ignored and replaced by the integer CARDSPERHAND.

Input   = {int: argc, char * *: argv, int *: numOfHands}
Output  = {bool: valid}
*/
bool validateUserInput(int argc, const char * argv[], int * checkNumOfHands)
{
  /* Verify arguments existence */
  if(argc == 3)
  {
    * checkNumOfHands = atoi(argv[argc - 1]);
    /* Determine if user input is valid. */
  	if((* checkNumOfHands < MIN_PLAYERS) || (* checkNumOfHands > MAX_PLAYERS))
  	{
      * checkNumOfHands = INVALID_INT;
  		return FALSE;
  	}
  	return TRUE;
  }
  else
  {
    * checkNumOfHands = INVALID_INT;
    return FALSE;
  }
}

/*
Function to explain to the user the reasons for program termination.

Input	= {void: null}
Output	= {void: null}
*/
void printReasonForTermination()
{
  /* Complete input requirements */
  const char statementOne[] =
  "This program requires two integers greater than zero.";
  const char statementTwo[] =
  "The first integer is the number of cards per hands.";
  const char statementThree[] =
  "In Stud Poker there is always 5 cards per hand.";
  const char statementFour[] =
  "The second integer is the number of hands.";
  const char statementFive[] =
  "The number of hands has to 1 through 13 inclusive.";

  /* Simple message for user. */
  printf("\n%s\n%s\n%s\n%s\n%s\n\n", statementOne, statementTwo, statementThree,
  statementFour, statementFive);
}
