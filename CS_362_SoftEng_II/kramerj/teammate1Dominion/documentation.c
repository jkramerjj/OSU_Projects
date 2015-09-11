/**
 * The Smithy: Upon playing the Smithy, the current player draws three
 * additional cards that are added to his or her hand. The Smithy is then
 * discarded from the player's hand.
 **/

/**
 * The Adventurer: Upon playing the Adventurer, the current player begins
 * drawing cards from his or her deck. This will continue until the player
 * has drawn two treasure cards. During this process if the deck is empty
 * it is reshuffled and the player continues to draw and place cards into
 * his or her hand. If the card is a treasure card increase the number of 
 * treasure cards drawn and continue. If the card is not a treasure place
 * it into temphand and remove it from the players hand and increase z to 
 * reflect the new size of temphand. Once two treasures have been drawn
 * discard all cards in temphand (a.k.a. non treasure cards drawn) into
 * the current player's discard pile.
 **/

/**
 * discardCard(): The function is passed a handPos of card to discard,
 * the current player and gamestate, and a trashFlag. The flag is used
 * to tell the function whether or not a card should be trashed (removed
 * from the game) or just discarded. If the card is to be discarded it is 
 * removed from the players hand and added to the playedCards pile. The
 * function updates the number of cards in the player's hand while also 
 * ensuring that there are no gaps in the hand array.
 **/

/**
 * updateCoins(): There are many reasons why the number of coins needs
 * updating. When updateCoins() is called it is passed a player, a gameState
 * and a bonus number of coins to award. The bonus is added to whatever 
 * coins the player currently has in his or her hand. The function iterates
 * over the player's entire hand and counts up the number of coins present 
 * and then applies the bonus.
 **/
