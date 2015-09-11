//Refactored Cards

/**
 * Smithy
 **/

/**
 * Adventurer
 **/

/**
 * Great_Hall
 **/

/**
 * Tribute
 **/

/**
 * Minion
 **/

//Introduced Bugs

/**
 * Smithy: This card is supposed to be added to the player's discard pile.
 * I have changed the flag in the call to discardCard to trash the card
 * instead. "discardCard(handPos, currentPlayer, state, 1)" instead of 0.
 **/

/**
 * Adventurer: This card is supposed to draw cards from the deck until
 * two treasures are found. The deck is supposed to be resuffled with the
 * discard pile once the deck is empty. I have changed the function to 
 * shuffle when the number of cards in the deck is <= 1 instead of < 1.
 * "if(state->deckCount[currentPlayer] <= 1)"
 **/

/**
 * Great_Hall: This card is supposed to award one additional action. I have
 * changed it to add two additional actions. "state->numActions += 2"
 **/

/**
 * Tribute: This card is supposed to affect the player on the left of the
 * current player. I changed it to be the player on the right.
 * "int nextPlayer = currentPlayer - 1" instead of +1
 * NOTE: This function does not check for the validity of nextPlayer
 * because the original code in cardEffect() didn't check either.
 **/

/**
 * Minion: No bugs introduced.
 **/

/**
 * Village: No bugs introduced.
 **/

