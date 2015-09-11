Smithy:
I simply created a function and then copied the existing code over. I passed in currentPlayer, state pointer, and handPos.
Bug: I changed the for loop from i < 3 to i <= 3

Adventurer:
I copied over the logic of the code, plus 3 variables: cardDrawn, temphand[], and drawntreasure.
Bug: In the first while loop and the second if statement I changed:  drawntreasure++ to drawntreasure = drawntreasure + 2

Council_Room:
I simply copied the code over and created the function. I passed in currentPlayer, state pointer, and handPos.
Bug: In the second for loop the i changed from 0 to 1.

Village:
I, once again, simply copied the code over and created the function. I passed in currentPlayer, state pointer, and handPos.
Bug: I changed the first game state struct varaible from: state->numActions = state->numActions + 2 to state->numActions = state numActions + 3

Minion:
I copied over the code / logic from the case statement. I passed into the function currentPlayer, gameState *state, choice1, choice2, handPos.
Bug: In the first else if statement I changed choice2 to choice1.


