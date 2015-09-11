//Decided to incorporate shuffle while testing Adventure
//my test doesn't catch the bug I introduced about when to shuffle
//adventurer doesn't properly shuffle if the deck is empty
//it should move discard into deck and shuffle. DrawCard does this so this line of code
//doesn't mess with the functioning
//Realized my previous test for SMithy didn't consider what happens at discard


/**
 *randomtestadventure.c
 *This was an enlightening exercise for many reasons. First I realized my first
 *random tests were overly complex. While they covered almost all cases, I realized
 *I was rewriting the entire card behavior again. I now realize this was not the 
 *best approach.
 *
 *I also discovered that the intentional error I introduced didn't make any difference in
 *these tests. I had set the adventurer to shuffle when there was only 1 card left in the
 *deck instead of 0. Shuffle only shuffles the cards currently in the deck when I 
 *originally thought it would shuffle in the discard pile as well. This portion of
 *adventurer is completely unnecessary. Not only does shuffling do nothing to an empty
 *deck, but drawCard handles empty decks in the appropriate way. 
 *
 *I left all errors I found/introduced in expectation of assignment 5 where we
 *see if our tests can find errors in other's code. I did remove all errors to 
 *insure my code correctly handled good code. I then reintroduced all errors.
 *My test will fail on the very first test because playAdventure doesn't discard
 *the card at all. Furthermore, discardCard() doesn't work either; it puts the card
 *on playedCards instead of discard. Both of these errors were not fixed.
 *
 *I am glad we did random testing. I had a pesky error that wouldn't show up
 *often unless 500k tests were run. It took me forever to track down. There was
 *an issue with my random setup algorithm. If it weren't for random testing where
 *all possible situations that can arise do, I would have thought my test was good.
 *I now don't get the error even when running on 500m. I ultimately believe the
 *issue arose from my lack of understanding of Random().
 *
 *Since my assignment3 used random testing in a loop it had good coverage when
 *it came to branch coverage: 94.74%. My new test now has 100% branch coverage.
 *This is thanks to testing more situations my previous random test ignored:
 *empty decks. I also feel my new test is much better because it can handle 
 *situations where the treasure is in the discard pile, but not the deck. This
 *increased the coverage of dominion.c tremendously: over 100% increase.
 **/

/**
 *randomtestcard.c
 *As with the above test, I found many bugs in the dominion.c code. Again, 
 *in the previous assignment I created tests that ignored the bugs that
 *I didn't introduce. This time I tested much more and had to temporarily
 *fix the code in dominion.c because I wanted to make sure my tests would
 *correctly work with correct code.
 *
 *I had to fix how discardCard worked. It wasn't doing it properly as
 *mentioned above. I also had to undo my introduced error of trashing
 *the card instead of discarding. After running my tests and getting my
 *new coverage numbers I undid my changes.
 *
 *This test didn't generate nearly as many problems for me as the previous
 *one did. I think that is because it is a simpler card, but also my
 *experience with the headache earlier.
 *
 *Unlike the previous test, this new random test didn't drastically change
 *the coverage. Both cardtest1 and this test had 100% branch coverage. The
 *cardtest1 had less line coverage but greater taken at least once. This is
 *a bit unexpected but considering I completely reworked cardtest1 they don't
 *resemble eachother that much. When it comes to coverage of dominion.c both
 *the old and new tests were almost identical. This is to be expected because
 *the smithy doesn't really deal with much of dominion.c and nothing
 *was changed from cardtest1 to this new test when it came to calling dominion.c
 **/
