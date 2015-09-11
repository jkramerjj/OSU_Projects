Joseph Kramer
CS 362 Soft Eng II
06-23-15
Assign #2


Smithy Card:
The code allows for three more calls of the drawCard() function, just like the card indicates should happen. It then discards the Smithy card, because it has been played. It costs 4 coins and the majority of the code is handled with a forloop. 

Adventurer Card:
This code will cycle through the first while loop until drawntreasure is greater than or equal 2. While cycling through the while loop it first checks if the deck is empty and if it is it will call for a reshuffle. It will then draw a card and that will be stored into cardDrawn. If it’s a copper, silver, or gold card drawntreasure will be incremented otherwise the cardDrawn is placed into a temp hand and the hand count is decremented and the card drawn variable is incremented.   
The second while loop will cycle through while z-1 is greater than or equal to zero and it discards all the cards already in play. It costs 6 coins

discardCard() Method:
Firstly the function will check if the card is supposed to trashed. i.e. the player user a card discard action. Otherwise it will add the card to the players pile. This method will decrement the card counter. It takes 4 arguments: The first is “handpos” which is the position of the card, second is “player” which is simply what player is on, third is “state” which us a struct that store all the card related data, and finally is the “trashFlag” used to decided if the card should be deleted or not. 

updateCoins() Method:
This code will cycle through the particular players hand and add up their total coins based on if they have copper, silver, or gold and their respective values. “player” is passed in to identify the player, the struct is passed in to process all the card data, and “bonus” is passed in which holds any bonus coins gained. 












