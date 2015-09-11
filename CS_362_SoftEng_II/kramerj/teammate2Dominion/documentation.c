	smithy card: Draw three cards.

	adventurer card: Whenever the deck is empty, shuffle discard and add to deck. Draw one card each time, if the most recently draw card is Treasure, then get the Treasure; if not, then remove the most recently drawn one. After getting one Treasure, discard all cards in play that have been drawn.

	discardCard() method: Remove the card from player’s hand. If the card is the only card or the last card in hand, remove it directly and reduce number of cards in hand. If not, replace the card with the last card, and then remove the last card and reduce number of cards in hand.

	updateCoins() method: Update the value of state->coins by calculating the number of coins in player’s hand.


