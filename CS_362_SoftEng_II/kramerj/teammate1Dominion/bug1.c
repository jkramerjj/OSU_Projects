/**
 * I was surprised to realize that my tests didn't catch all the bugs I introduced. I
 * realized that most of my introduced errors required testing a secondary function, 
 * which I tried to avoid. This seemed the prudent course of action: testing only one
 * function with each unit test.
 * 
 * cardtest3.c - Great Hall - Every single test fails because this is one of the functions
 * I altered in prior weeks. The number of actions will never match up due to this.
 *
 * unittest3.c - Check Shuffle - There are FAILS whenever this test is run due to the
 * nature of probability. With random data there is a chance the cards will be end
 * up in the same order after a shuffle. This test also makes sure there are no differences
 * in the number occurances. This test doesn't fail.
 * 
 * I also think I found a situation that may cause problems later. I could be wrong,
 * but I don't think the discard pile is set up correctly. There are some cards that
 * call for ALL players to discard, but it appears they first go to the played pile. End
 * Turn takes the played pile and puts it into the current player's discard. This 
 * appears like it isn't correct. Again, I could be miss understanding the code.
 *
 **/
