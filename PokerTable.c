#include "PokerTable.h"

/* Strings for suits. */
char * namedSuits[NUM_OF_SUITS] =
{
  "H\0", "D\0", "C\0", "S\0"
};

/* Strings for ranks and suits. */
char * namedRanks[NUM_OF_RANKS] =
{
  "A\0", "2\0", "3\0", "4\0", "5\0", "6\0", "7\0", "8\0", "9\0", "T\0" ,"J\0",
  "Q\0", "K\0"
};

char * handRanks[NUM_OF_HAND_RANKS] =
{
  "High Card\0", "One Pair\0", "Two Pairs\0", "Three of a Kind\0", "Straight\0",
  "Flush\0", "Full House\0", "Four of a Kind\0", "Straight Flush\0",
};

/*
  Function to create a card, given a pointer to a card, a rank, and a suit.

  Input   = {card *: newCard, rank: newRank, suit: newSuit}
  Output  = {bool: success}
*/
bool createCard(card * newCard, rank newRank, suit newSuit)
{
  /*
    Defensive Programming!
    Validate the cards existance and members
  */
  /* Reject undefined cards */
  if(newCard == NULL)
  {
    return FALSE;
  }
  newCard->cardRank = newRank;
  newCard->cardSuit = newSuit;
  return TRUE;
}

/*
  Function to print a card's rank and suit

  Input   = {card *: cardPTR}
  Output  = {void: NULL}
*/
void printCard(card * cardPTR)
{
  /*
    Defensive Programming!
    Validate the cards existance and members
  */
  /* Reject undefined cards */
  if(cardPTR == NULL)
  {
    return;
  }

  /* Variables used to print card in a standard format */
  char * suitPTR = NULL;
  char * rankPTR = NULL;
  const char * const RIGHTBRACE = "[ \0";
  const char * const LEFTBRACE = " ]\0";
  const char * const SEPERATOR = "-\0";

  suitPTR = namedSuits[cardPTR->cardSuit];
  rankPTR = namedRanks[cardPTR->cardRank];

  /* Print rank and suit */
  printf("%s%s%s%s%s", RIGHTBRACE, rankPTR, SEPERATOR, suitPTR, LEFTBRACE);
}

/*
  Function to populate an array of 52 cards with the standard ranks and suits.

  Input   = {card [STD_DECK_SIZE]: deck}
  Output  = {bool: success}
*/
bool createDeck(card deck[STD_DECK_SIZE])
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int suitNum = NUM_INIT;

  for(rankNum = NUM_INIT; rankNum < NUM_OF_RANKS; rankNum ++)
  {
    for(suitNum = NUM_INIT; suitNum < NUM_OF_SUITS; suitNum ++)
    {
      if(createCard(& deck[cardNum], rankNum, suitNum) == TRUE)
      {
        cardNum ++;
      }
      else
      {
        return FALSE;
      }
    }
  }
  return TRUE;
}

/*
  Function to print the deck of cards

  Input   = {card [STD_DECK_SIZE]: deck}
  Output  = {void: NULL}
*/
void printDeck(card deck[STD_DECK_SIZE])
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int suitNum = NUM_INIT;
  card * cardPTR = deck;
  const char * SEPERATOR = "  ";

  for(suitNum = NUM_INIT; suitNum < NUM_OF_SUITS; suitNum ++)
  {
    for(rankNum = NUM_INIT; rankNum < NUM_OF_RANKS; rankNum ++)
    {
      printCard(& cardPTR[cardNum ++]);
      printf("%s", SEPERATOR);
    }
    puts("\n");
  }
}

/*
  Function to swap the locations of two card in memory.

  Input   = {card *: firstLoc, card *: secondLoc}
  Output  = {void: NULL}
*/
void swap(card * firstLoc, card * secondLoc)
{
  /* Temporary storage for first value */
  card tempCard;
  tempCard.cardRank = NUM_INIT;
  tempCard.cardSuit = NUM_INIT;
  createCard(& tempCard, firstLoc->cardRank, firstLoc->cardSuit);
  createCard(firstLoc, secondLoc->cardRank, secondLoc->cardSuit);
  createCard(secondLoc, tempCard.cardRank, tempCard.cardSuit);
}

/*
  Function to shuffle the deck according to the modern interpretation of the
  Fisher-Yates algorithm. The algorithm selects a random card from an
  iteratively shrinking list of un-shuffled cards. As the list shrinks the
  selected cards are placed into a growing list of shuffled cards.

  Input   = {card [STD_DECK_SIZE]: deck}
  Output  = {void: NULL}
*/
void modernFisherYatesShuffle(card deck[STD_DECK_SIZE])
{
  /* Seed random number generator. */
  srand(time(NUM_INIT));
  /* Create minimum and maximum variables. */
  int MIN = NUM_INIT;
  int max = NUM_INIT;
  /* Variables to perform card value swap. */
  int selectedCardIndex = NUM_INIT;

  /* Loop through deck, randomly selecting cards. */
  int cardNum = NUM_INIT;
  for(cardNum = NUM_INIT; cardNum < STD_DECK_SIZE; cardNum ++)
  {
    /* Every time the loop completes the range of random selection shrinks. */
    /* Range = max - min + 1. */
    max = STD_DECK_SIZE - cardNum;

    /* Random number within range = rand() % range + min. */
    selectedCardIndex = rand() % max + MIN;
    swap(& deck[selectedCardIndex], & deck[max - 1]);
  }
}

/*
  Function to populate the poker table's hands two dimensional array using the
  poker table's deck array.

  Input   = {card [STD_DECK_SIZE]: deck,
            card [CARDS_PER_HAND][MAX_PLAYERS]: hands}
  Output  = {bool: success}
*/
bool dealHands(card deck[STD_DECK_SIZE],
  card hands[CARDS_PER_HAND][MAX_PLAYERS])
{
  int cardNum = NUM_INIT;
  int deckIndex = NUM_INIT;
  int playrNum = NUM_INIT;

  /* Every player gets 5 cards in their hand */
  for(playrNum = NUM_INIT; playrNum < MAX_PLAYERS; playrNum ++)
  {
    for(cardNum = NUM_INIT; cardNum < CARDS_PER_HAND; cardNum ++)
    {
      if
      (
        createCard(& hands[cardNum][playrNum], deck[deckIndex].cardRank,
        deck[deckIndex].cardSuit) == TRUE
      )
      {
        /* Card created in hand */
        deckIndex ++;
      }
      else
      {
        return FALSE;
      }
    }
    /* Hand created */
  }
  return TRUE;
}

/*
  Function to print a hand of cards.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {void: NULL}
*/
void printHand(card hands[CARDS_PER_HAND][MAX_PLAYERS], int hand)
{
  int cardNum = NUM_INIT;
  char * SEPERATOR = "  \0";
  /* Standard formating */
  for(cardNum = NUM_INIT; cardNum < CARDS_PER_HAND - 1; cardNum ++)
  {
    printCard(& hands[cardNum][hand]);
    printf("%s", SEPERATOR);
  }
  /* Print the last card with no SEPERATOR string after */
  printCard(& hands[cardNum][hand]);
}

/*
  Function to sort a hand of cards using simple bubble sort

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {void: NULL}
*/
void sortHand(card hands[CARDS_PER_HAND][MAX_PLAYERS], int hand)
{
   int leftIndex = NUM_INIT;
   int rightIndex = NUM_INIT;

   /* Compare adjacent cards in a hand */
   for(leftIndex = 0; leftIndex < CARDS_PER_HAND-1; leftIndex++)
   {
     for(rightIndex = 0; rightIndex < CARDS_PER_HAND-leftIndex-1; rightIndex++)
     {
       /* If adjacent cards are in the wrong order, swap the two */
       if(hands[rightIndex][hand].cardRank > hands[rightIndex+1][hand].cardRank)
       {
         swap(& hands[rightIndex][hand], & hands[rightIndex+1][hand]);
       }
     }
   }
}

/*
  Function to sort the hands of the poker table.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands}
  Output  = {void: NULL}
*/
void sortHands(card hands[CARDS_PER_HAND][MAX_PLAYERS])
{
  int handNum = NUM_INIT;
  /* Sort every hand */
  for(handNum = NUM_INIT; handNum < MAX_PLAYERS; handNum ++)
  {
    sortHand(hands, handNum);
  }
}

/*
  Function to determine is a hand is a Straight Flush, a straight flush has all
  cards of the same suit with every card's rank only one greater than the last
  card viewed.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: handNum}
  Output  = {bool: isStraightFlush};
*/
bool isStraightFlush(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int suitNum = NUM_INIT;
  sortHands(hands);

  rankNum = hands[NUM_INIT][handNum].cardRank;
  suitNum = hands[NUM_INIT][handNum].cardSuit;

  /*
    Special Case of a Royal Flush
    Royal Flushes start on a Ten and end on an Ace
  */
  if(rankNum == ACE)
  {
    /* Determine the conditions of a Royal Flush */
    if(hands[cardNum + 1][handNum].cardRank == TEN)
    {
      /* Exclude the ACE */
      cardNum ++;
      rankNum = hands[cardNum][handNum].cardRank;
      /* Treat the rest of the hand normally */
      for(; cardNum < CARDS_PER_HAND - 1; cardNum ++)
      {
        if
        (
          ((hands[cardNum + 1][handNum].cardRank -
          hands[cardNum][handNum].cardRank) != 1) ||
          (hands[cardNum][handNum].cardSuit != suitNum)
        )
        {
          return FALSE;
        }
      }
    }
    else
    {
      /* Check for Straight Flush */
      for(; cardNum < CARDS_PER_HAND - 1; cardNum ++)
      {
        if
        (
          ((hands[cardNum + 1][handNum].cardRank -
          hands[cardNum][handNum].cardRank) != 1) ||
          (hands[cardNum][handNum].cardSuit != suitNum)
        )
        {
          return FALSE;
        }
      }
    }
    return TRUE;
  }
  else
  {
    /* Check for Straight Flush */
    for(; cardNum < CARDS_PER_HAND - 1; cardNum ++)
    {
      if
      (
        ((hands[cardNum + 1][handNum].cardRank -
        hands[cardNum][handNum].cardRank) != 1) ||
        (hands[cardNum][handNum].cardSuit != suitNum)
      )
      {
        return FALSE;
      }
    }
  }
  return TRUE;
}

/*
  Function to determine is a hand is a Four of a Kind.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isFourofAKind};
*/
bool isFourOfAKind(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int suitNum = NUM_INIT;
  int kindNum = NUM_INIT;
  sortHands(hands);

  /* Take the first card as the starting value of comparison */
  rankNum = hands[cardNum][handNum].cardRank;
  kindNum ++;
  /* Check for FourOfAKind in any space of the array */
  for(cardNum = NUM_INIT + 1; cardNum < CARDS_PER_HAND; cardNum ++)
  {
    if(hands[cardNum][handNum].cardRank == rankNum)
    {
      kindNum ++;
      /* 4 matching kinds yields a FourOfAKind hand rank */
      if(kindNum == QUAD)
      {
        return TRUE;
      }
    }
    else
    {
      if(cardNum == CARDS_PER_HAND - 1)
      {
        return FALSE;
      }
      cardNum = cardNum + 1;
      kindNum = NUM_INIT + 1;
    }
  }
  /* 4 matching kinds yields a FourOfAKind hand rank */
  if(kindNum == QUAD)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*
  Function to determine is a hand is a FullHouse, three ranks of a kind and a
  pair.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isFullHouse};
*/
bool isFullHouse(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int suitNum = NUM_INIT;
  int kindNum = NUM_INIT;
  bool pair = FALSE;
  bool threeOfAKind = FALSE;
  sortHands(hands);

  /* Take the first card as the starting value of comparison */
  rankNum = hands[cardNum][handNum].cardRank;
  /* Check for a triple and a pair */
  if
  (
    (hands[cardNum + 1][handNum].cardRank == rankNum) &&
    (hands[cardNum + 2][handNum].cardRank == rankNum)
  )
  {
    threeOfAKind = TRUE;
    if
    (
      hands[cardNum + 3][handNum].cardRank ==
      hands[cardNum + 4][handNum].cardRank
    )
    {
      pair = TRUE;
    }
  }
  /* Or a pair and a triple */
  else if(hands[cardNum + 1][handNum].cardRank == rankNum)
  {
    pair = TRUE;
    if
    (
      (hands[cardNum + 2][handNum].cardRank ==
      hands[cardNum + 3][handNum].cardRank) &&
      (hands[cardNum + 3][handNum].cardRank ==
      hands[cardNum + 4][handNum].cardRank)
    )
    {
      threeOfAKind = TRUE;
    }
  }

  if(pair == TRUE && threeOfAKind == TRUE)
  {
    return TRUE;
  }
  return FALSE;

}

/*
  Function to determine is a hand is a Flush.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isFlush};
*/
bool isFlush(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  /* All cards must be of the same suit */
  int cardNum = NUM_INIT;
  int suitNum = hands[NUM_INIT][handNum].cardSuit;
  for(cardNum = NUM_INIT + 1; cardNum < CARDS_PER_HAND; cardNum ++)
  {
    if(hands[cardNum][handNum].cardSuit != suitNum)
    {
      return FALSE;
    }
  }
  return TRUE;
}

/*
  Function to determine is a hand is a Straight.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: isStraight};
*/
bool isStraight(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  sortHands(hands);
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  /* After sorting ranks must be in increasing order */
  rankNum = hands[cardNum][handNum].cardRank;
  for(cardNum = NUM_INIT + 1; cardNum < CARDS_PER_HAND; cardNum ++)
  {
    if(hands[cardNum][handNum].cardRank != (rankNum + cardNum))
    {
      return FALSE;
    }
  }
  return TRUE;
}

/*
  Function to determine is a hand has three of a kind. Assumes the hands are
  sorted.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: ThreeOfAKind};
*/
bool isThreeOfAKind(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  sortHands(hands);
  /* Check at the beginning */
  if
  (
    (hands[cardNum][handNum].cardRank ==
    hands[cardNum + 1][handNum].cardRank) &&
    (hands[cardNum + 1][handNum].cardRank ==
    hands[cardNum + 2][handNum].cardRank)
  )
  {
    return TRUE;
  }
  /* Check in the middle */
  else if
  (
    (hands[cardNum + 1][handNum].cardRank ==
    hands[cardNum + 2][handNum].cardRank) &&
    (hands[cardNum + 2][handNum].cardRank ==
    hands[cardNum + 3][handNum].cardRank)
  )
  {
    return TRUE;
  }
  /* Check the end */
  else if
  (
    (hands[cardNum + 2][handNum].cardRank ==
    hands[cardNum + 3][handNum].cardRank) &&
    (hands[cardNum + 3][handNum].cardRank ==
    hands[cardNum + 4][handNum].cardRank)
  )
  {
    return TRUE;
  }
  return FALSE;
}

/*
  Function to determine is a hand has two pairs

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: TwoPair};
*/
bool isTwoPair(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int pairs = NUM_INIT;
  sortHands(hands);
  /* Check at the beginning */
  if
  (
    hands[cardNum][handNum].cardRank ==
    hands[cardNum + 1][handNum].cardRank
  )
  {
    pairs ++;
  }
  /* Check in the mid-left */
  if
  (
    hands[cardNum + 1][handNum].cardRank ==
    hands[cardNum + 2][handNum].cardRank
  )
  {
    pairs ++;
  }
  /* Check the mid-right */
  if
  (
    hands[cardNum + 2][handNum].cardRank ==
    hands[cardNum + 3][handNum].cardRank
  )
  {
    pairs ++;
  }
  /* Check the left */
  if
  (
    hands[cardNum + 3][handNum].cardRank ==
    hands[cardNum + 4][handNum].cardRank
  )
  {
    pairs ++;
  }

  if (pairs == 2)
  {
    return TRUE;
  }
  return FALSE;
}

/*
  Function to determine if hand has a pair

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {bool: Pair};

*/
bool isPair(card hands[CARDS_PER_HAND][MAX_PLAYERS], int handNum)
{
  int cardNum = NUM_INIT;
  int rankNum = NUM_INIT;
  int pairs = NUM_INIT;
  sortHands(hands);
  /* Check at the beginning */
  if
  (
    hands[cardNum][handNum].cardRank ==
    hands[cardNum + 1][handNum].cardRank
  )
  {
    pairs ++;
  }
  /* Check in the mid-left */
  if
  (
    hands[cardNum + 1][handNum].cardRank ==
    hands[cardNum + 2][handNum].cardRank
  )
  {
    pairs ++;
  }
  /* Check the mid-right */
  if
  (
    hands[cardNum + 2][handNum].cardRank ==
    hands[cardNum + 3][handNum].cardRank
  )
  {
    pairs ++;
  }
  /* Check the left */
  if
  (
    hands[cardNum + 3][handNum].cardRank ==
    hands[cardNum + 4][handNum].cardRank
  )
  {
    pairs ++;
  }

  if (pairs > 0)
  {
    return TRUE;
  }
  return FALSE;
}

/*
  Function to determine the rank of a hands.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: hand}
  Output  = {pokerRank: handRank}
*/
pokerRank assignRank(card hands[CARDS_PER_HAND][MAX_PLAYERS], int hand)
{
  pokerRank rank;
  if(isStraightFlush(hands, hand) == TRUE)
  {
    rank = StraightFlush;
    return rank;
  }
  else if(isFourOfAKind(hands, hand) == TRUE)
  {
    rank = FourOfAKind;
    return rank;
  }
  else if(isFullHouse(hands, hand) == TRUE)
  {
    rank = FullHouse;
    return rank;
  }
  else if(isFlush(hands, hand) == TRUE)
  {
    rank = Flush;
    return rank;
  }
  else if(isStraight(hands, hand) == TRUE)
  {
    rank = Straight;
    return rank;
  }
  else if(isThreeOfAKind(hands, hand) == TRUE)
  {
    rank = ThreeOfAKind;
    return rank;
  }
  else if(isTwoPair(hands, hand) == TRUE)
  {
    rank = TwoPair;
    return rank;
  }
  else if(isPair(hands, hand) == TRUE)
  {
    rank = Pair;
    return rank;
  }
  else
  {
    rank = HighCard;
    return rank;
  }
}

/*
  Function to determine a winner or winners;

  Input   = {pokerRank [numOfHands]: winners,
            card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: numOfhands}
  Output  = {int *: winners}
*/
int * determineWinner(int winners[],
  card hands[CARDS_PER_HAND][MAX_PLAYERS], int numOfHands)
{
  int playrNum = NUM_INIT;
  pokerRank handRank = NUM_INIT;
  pokerRank maxRank = NUM_INIT;
  /* Ranks are ordered least to greatest,the max rank is the winning rank */
  for(playrNum = NUM_INIT; playrNum < numOfHands; playrNum ++)
  {
    handRank = assignRank(hands, playrNum);
    if(handRank > maxRank)
    {
      maxRank = handRank;
    }
  }
  /* Determine all winners */
  for(playrNum = NUM_INIT; playrNum < numOfHands; playrNum ++)
  {
    /* Winners are marked by the number one, all other are negative one */
    if(assignRank(hands, playrNum) == maxRank)
    {
      winners[playrNum] = 1;
    }
    else
    {
      winners[playrNum] = -1;
    }
  }
  return winners;
}

/*
  Function to print the poker table's hands two dimensional array up to the
  number of players at the table. Using the mode variable, the hands can be
  printed as is, with a rank assigned to each hand, with a winner determined
  by the rank assigned to each hand, or in test mode, where the hand ranks are
  demonstrated.

  Input   = {card [CARDS_PER_HAND][MAX_PLAYERS]: hands, int: numOfHands,
            int: mode}
  Output  = {void: NULL}
*/
void printHands(card hands[CARDS_PER_HAND][MAX_PLAYERS], int numOfHands,
  int mode)
{
  /* Reject invalid input */
  if
  (
    (numOfHands < 1) || (numOfHands > MAX_PLAYERS) || (mode < 1) ||
    (mode > PRINT_MODES)
  )
  {
    return;
  }

  int deckNum = NUM_INIT;
  int cardNum = NUM_INIT;
  int playrNum = NUM_INIT;
  char * message = NUM_INIT;

  if(mode == 1) /* Print each players hands as is */
  {
    for(playrNum = NUM_INIT; playrNum < numOfHands; playrNum ++)
    {
      message = "Player ";
      /*
        The number 10 will be replaced with the character T to preserve
        formatting.
      */
      if(playrNum == 9)
      {
        printf("%sT", message);
      }
      else
      {
        printf("%s%d", message, playrNum + 1);
      }
      message = "] - ";
      printf("%s", message);
      printHand(hands, playrNum);
      puts("\n");
    }
  }
  else if(mode == 2) /* Print each players hands with an assigned ranking */
  {
    for(playrNum = NUM_INIT; playrNum < numOfHands; playrNum ++)
    {
      message = "Player ";
      /*
        The number 10 will be replaced with the character T to preserve
        formatting.
      */
      if(playrNum == 9)
      {
        printf("%sT", message);
      }
      else
      {
        printf("%s%d", message, playrNum + 1);
      }
      message = "] - ";
      printf("%s", message);
      printHand(hands, playrNum);
      message = " - ";
      printf("%s", message);
      message = handRanks[assignRank(hands, playrNum)];
      printf("%s", message);
      puts("\n\0");
    }
  }
  else if(mode == 3) /* Print each players hands with winner determined */
  {
    int winners[numOfHands];
    determineWinner(winners, hands, numOfHands);
    for(playrNum = NUM_INIT; playrNum < numOfHands; playrNum ++)
    {
      message = "Player ";
      /*
        The number 10 will be replaced with the character T to preserve
        formatting.
      */
      if(playrNum == 9)
      {
        printf("%sT", message);
      }
      else
      {
        printf("%s%d", message, playrNum + 1);
      }
      message = "] - ";
      printf("%s", message);
      printHand(hands, playrNum);
      message = " - ";
      printf("%s", message);
      message = handRanks[assignRank(hands, playrNum)];
      printf("%s", message);
      if(winners[playrNum] > 0)
      {
        message = " - Winner";
        printf("%s", message);
      }
      puts("\n\0");
    }
  }
  else /* Print each players hands with winner determined */
  {
    card presentationHand[CARDS_PER_HAND][MAX_PLAYERS];
    card testHands[CARDS_PER_HAND][MAX_PLAYERS];
    rank testRanks[CARDS_PER_HAND * NUM_OF_HAND_RANKS] =
    {
      TWO, THREE, FOUR, SIX, QUEEN,
      FOUR, FIVE, FIVE, SEVEN, TEN,
      THREE, THREE, TEN, TEN, QUEEN,
      THREE, THREE, THREE, TEN, QUEEN,
      ACE, TWO, THREE, FOUR, FIVE,
      TWO, THREE, FOUR, FIVE, QUEEN,
      THREE, THREE, THREE, TEN, TEN,
      THREE, THREE, THREE, THREE, QUEEN,
      TEN, JACK, QUEEN, KING, ACE
    };
    suit testSuits[CARDS_PER_HAND * NUM_OF_HAND_RANKS] =
    {
      D, C, D, S, H,
      H, H, D, H, S,
      D, H, C, D, C,
      D, H, S, D, C,
      S, D, C, D, D,
      C, C, C, C, C,
      D, H, S, D, C,
      D, H, S, C, C,
      D, D, D, D, D
    };

    for(playrNum = NUM_INIT; playrNum < NUM_OF_HAND_RANKS; playrNum ++)
    {
      for(cardNum = NUM_INIT; cardNum < CARDS_PER_HAND; cardNum ++)
      {
        if
        (
          (createCard(& testHands[cardNum][playrNum],
          testRanks[deckNum], testSuits[deckNum]) == TRUE) &&
          (createCard(& presentationHand[cardNum][playrNum],
          testRanks[deckNum], testSuits[deckNum]) == TRUE)

        )
        {
          deckNum ++;
        }
      }
    }
    for(playrNum = NUM_INIT; playrNum < NUM_OF_HAND_RANKS; playrNum ++)
    {
      message = "Player ";
      /*
        The number 10 will be replaced with the character T to preserve
        formatting.
      */
      if(playrNum == 9)
      {
        printf("%sT", message);
      }
      else
      {
        printf("%s%d", message, playrNum + 1);
      }
      message = "] - ";
      printf("%s", message);
      printHand(presentationHand, playrNum);
      message = " - ";
      printf("%s", message);
      message = handRanks[assignRank(testHands, playrNum)];
      printf("%s", message);
      puts("\n\0");
    }
  }
}
