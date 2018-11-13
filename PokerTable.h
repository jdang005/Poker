#ifndef PokerTable_h
#define PokerTable_h

/* Macros for the simulated Poker Table. */
#define STD_DECK_SIZE 52
#define NUM_OF_SUITS 4
#define NUM_OF_RANKS 13
#define CARDS_PER_HAND 5
#define MIN_PLAYERS 1
#define MAX_PLAYERS 10
#define NUM_OF_HAND_RANKS 9
#define PAIR 2
#define TRIPLE 3
#define QUAD 4

/* Other used macros */
#define NUM_INIT 0
#define PRINT_MODES 4
#define INVALID_INT -1

/* stdio.h is included for standard input and output functionality. */
#include <stdio.h>

/*
  stdlib.h is included for the use of the srand(time_t) function. This function
*/
#include <stdlib.h>

/*
  time.h is included for the use of time(time_t * timer) function, necessary for
  srand(time_t) function to seed the generation random numbers using the rand()
  function.
*/
#include<time.h>


/* Simple boolean type */
typedef enum bool{FALSE, TRUE} bool;

/*
  Enumerated type for suit of a card
*/
typedef enum suit
{
  H, D, C, S
} suit;

/*
  Enumerated type for rank of a card
*/
typedef enum rank
{
  ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} rank;

/*
  Enumerated type for the rank of a hand
*/
typedef enum pokerRank
{
  HighCard, Pair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse,
  FourOfAKind, StraightFlush
} pokerRank;

/*
  Card structure

  A card is a structure with two members, a pointer to a string who's value is the
  suit of the card and an integer between 1 and 13, representing the rank of the
  card.
*/

typedef struct card
{
  rank cardRank;
  suit cardSuit;
} card;

/*
  Poker Table structure

  A PokerTable has an array of 52 cards, an array of integer representing the
  order that the deck is currently in, and a two dimensional array of
*/
typedef struct pokerTable
{
  /* Deck of cards is an array of 52 cards */
  card deckOfCards[STD_DECK_SIZE];
  /* The hands of cards */
  card hands[CARDS_PER_HAND][MAX_PLAYERS];
} pokerTable;

/*
  Function to create a card, given a pointer to a card, a rank, and a suit.

  Input   = {card *: newCard, rank: newRank, suit: newSuit}
  Output  = {bool: success}
*/
bool createCard(card [STD_DECK_SIZE], rank, suit);

/*
  Function to compare two cards for
*/

/*
  Function to print a card's rank and suit

  Input   = {card *: cardPTR}
  Output  = {void: NULL}
*/
void printCard(card [STD_DECK_SIZE]);

/*
  Function to populate an array of 52 cards with the standard ranks and suits.

  Input   = {card [STD_DECK_SIZE]: deck}
  Output  = {bool: success}
*/
bool createDeck(card [STD_DECK_SIZE]);

/*
  Function to print the deck of cards

  Input   = {card [STD_DECK_SIZE]: deck}
  Output  = {void: NULL}
*/
void printDeck(card [STD_DECK_SIZE]);

/*
  Function to shuffle the deck according to the modern interpretation of the
  Fisher-Yates algorithm. The algorithm selects a random card from an
  iteratively shrinking list of un-shuffled cards. As the list shrinks the
  selected cards are placed into a growing list of shuffled cards.

  Input   = {card [STD_DECK_SIZE]: deck}
  Output  = {void: NULL}
*/
void modernFisherYatesShuffle(card [STD_DECK_SIZE]);

/*
  Function to populate the poker table's hands two dimensional array.

  Input   = {card [STD_DECK_SIZE]: deck,
            card [CARDS_PER_HAND][MAX_PLAYERS]: hands}
  Output  = {bool: success}
*/
bool dealHands(card [STD_DECK_SIZE], card [CARDS_PER_HAND][MAX_PLAYERS]);

/*
  Function to print a hand of cards.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {void: NULL}
*/
void printHand(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to sort a hand of cards.

  Input   = {card [CARDS_PER_HAND]: hand}
  Output  = {void: NULL}
*/
void sortHand(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to sort the hands of the poker table.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands}
  Output  = {void: NULL}
*/
void sortHands(card [CARDS_PER_HAND][MAX_PLAYERS]);

/*
  Function to determine if a hand is a Straight Flush

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isStraightFlush};
*/
bool isStraightFlush(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand is a Four of a Kind

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isFourofAKind};
*/
bool isFourOfAKind(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand is a FullHouse

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isFullHouse};
*/
bool isFullHouse(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand is a Flush

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isFlush};
*/
bool isFlush(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand is a Straight

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isStraight};
*/
bool isStraight(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand is a ThreeOfAKind

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isThreeOfAKind};
*/
bool isThreeOfAKind(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand has a two pairs

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isTwoPair};
*/
bool isTwoPair(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine if a hand has a pair

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isPair};
*/
bool isPair(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine the rank of a hands.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {pokerRank: handRank}
*/
pokerRank assignRank(card [CARDS_PER_HAND][MAX_PLAYERS], int);

/*
  Function to determine a winner or winners;

  Input   = {int [numOfHands]: winners,
            card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: numOfhands}
  Output  = {int *: winners}
*/
int * determineWinner(int *,
  card [CARDS_PER_HAND][MAX_PLAYERS], int);


/*
  Function to print the poker table's hands two dimensional array up to the
  number of players at the table. Using the mode variable, the hands can be
  printed as is, with a rank assigned to each hand, or with a winner determined
  by the rank assigned to each hand.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: numOfHands,
            int: mode}
  Output  = {void: NULL}
*/
void printHands(card [CARDS_PER_HAND][MAX_PLAYERS], int, int);

#endif /* PokerTable_h */
