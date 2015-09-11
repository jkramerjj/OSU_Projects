code coverage for file  dominion.c : 35.63%

By the command  gcov dominion.c -b  , we get the following results
File  dominion.c 
Lines executed:35.63% of 581
Branches executed:35.42% of 415
Taken at least once:27.47% of 415
Calls executed:20.00% of 95

The overall statement coverage is 35.63%, which is somewhat low, that due to we only test part of functions.  Let s look at each function we tested. Here are report after command   gcov dominion.c -f  and report in  unittesrresults.out  file
For function  updateCoins :
Function 'updateCoins'
	Lines executed:100.00% of 11
	Branches executed:100.00% of 8
	Taken at least once:100.00% of 8
	No calls
 
     1394: 1332:int updateCoins(int player, struct gameState *state, int bonus)
        -: 1333:{
        -: 1334:  int i;
        -: 1335:        
        -: 1336:  //reset coin count
     1394: 1337:  state->coins = 0;
        -: 1338:
        -: 1339:  //add coins for each Treasure card in player s hand
     7014: 1340:  for (i = 0; i < state->handCount[player]; i++)
        -: 1341:    {
     5620: 1342:      if (state->hand[player][i] == copper)
        -: 1343:        {
     3602: 1344:          state->coins += 1;
        -: 1345:        }
     2018: 1346:      else if (state->hand[player][i] == silver)
        -: 1347:        {
      330: 1348:          state->coins += 2;
        -: 1349:        }
     1688: 1350:      else if (state->hand[player][i] == gold)
        -: 1351:        {
      330: 1352:          state->coins += 3;
        -: 1353:        }       
        -: 1354:    }   
        -: 1355:
        -: 1356:  //add bonus
     1394: 1357:  state->coins += bonus;
        -: 1358:
     1394: 1359:  return 0;
        -: 1360:}

In this function, each statement and each branch are test, which means the statement coverage and branch coverage are 100%. Also the number of tests in each branch has no big difference. Regarding to boundary , we have covered all the boundaries, include when handcount is 0. Therefore, our unittest for this function is good. 

For function  getCost  
	Function 'getCost'
	Lines executed:96.67% of 30
	Branches executed:100.00% of 28
	Taken at least once:96.43% of 28
	No calls


       54:  588:int getCost(int cardNumber)
        -:  589:{
       54:  590:  switch( cardNumber ) 
        -:  591:    {
        -:  592:    case curse:
        2:  593:      return 0;
        -:  594:    case estate:
        2:  595:      return 2;
        -:  596:    case duchy:
        2:  597:      return 5;
        -:  598:    case province:
        2:  599:      return 8;
        -:  600:    case copper:
        2:  601:      return 0;
        -:  602:    case silver:
        2:  603:      return 3;
        -:  604:    case gold:
        2:  605:      return 6;
        -:  606:    case adventurer:
        2:  607:      return 6;
        -:  608:    case council_room:
        2:  609:      return 5;
        -:  610:    case feast:
        2:  611:      return 4;
        -:  612:    case gardens:
        2:  613:      return 4;
        -:  614:    case mine:
        2:  615:      return 5;
        -:  616:    case remodel:
        2:  617:      return 4;
        -:  618:    case smithy:
        2:  619:      return 4;
        -:  620:    case village:
        2:  621:      return 3;
        -:  622:    case baron:
        2:  623:      return 4;
        -:  624:    case great_hall:
        2:  625:      return 3;
        -:  626:    case minion:
        2:  627:      return 5;
        -:  628:    case steward:
        2:  629:      return 3;
        -:  630:    case tribute:
        2:  631:      return 5;
        -:  632:    case ambassador:
        2:  633:      return 3;
        -:  634:    case cutpurse:
        2:  635:      return 4;
        -:  636:    case embargo: 
        2:  637:      return 2;
        -:  638:    case outpost:
        2:  639:      return 5;
        -:  640:    case salvager:
        2:  641:      return 4;
       -:  644:    case treasure_map:
        2:  645:      return 4;
        -:  646:    }

In this function, each statement and each branch are tested. Also the number of tests in each branch are equal.  Regarding to boundary , we have covered all the boundaries, including the first case and the last case.  However, the number of test may not enough, in future, we may try to improve that.


For function  gainCard :
	Function 'gainCard'
	Lines executed:100.00% of 13
	Branches executed:100.00% of 6
	Taken at least once:100.00% of 6
	Calls executed:100.00% of 1

      222: 1295:int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
        -: 1296:{
        -: 1297:  //Note: supplyPos is enum of choosen card
        -: 1298:        
        -: 1299:  //check if supply pile is empty (0) or card is not used in game (-1)
      222: 1300:  if ( supplyCount(supplyPos, state) < 1 )
        -: 1301:    {
      120: 1302:      return -1;
        -: 1303:    }
        -: 1304:        
        -: 1305:  //added card for [whoseTurn] current player:
        -: 1306:  // toFlag = 0 : add to discard
        -: 1307:  // toFlag = 1 : add to deck
        -: 1308:  // toFlag = 2 : add to hand
        -: 1309:
      102: 1310:  if (toFlag == 1)
        -: 1311:    {
       34: 1312:      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
       34: 1313:      state->deckCount[player]++;
        -: 1314:    }
       68: 1315:  else if (toFlag == 2)
        -: 1316:    {
       34: 1317:      state->hand[ player ][ state->handCount[player] ] = supplyPos;
       34: 1318:      state->handCount[player]++;
        -: 1319:    }
        -: 1320:  else
        -: 1321:    {
       34: 1322:      state->discard[player][ state->discardCount[player] ] = supplyPos;
       34: 1323:      state->discardCount[player]++;
        -: 1324:    }
        -: 1325:        
        -: 1326:  //decrease number in supply pile
      102: 1327:  state->supplyCount[supplyPos]--;
        -: 1328:         
      102: 1329:  return 0;
        -: 1330: }

In this function, each statement and each branch are tested. Also the number of tests in each branch has no big difference. Regarding to boundary , we have covered all the boundaries, including when the count of hand, discard and supply count is 0. Therefore, our unittest for this function is good. 



For the function  discardCard 
	Function 'discardCard'
	Lines executed:92.31% of 13
	Branches executed:100.00% of 6
	Taken at least once:83.33% of 6
	No calls

      340: 1257:int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFla
g)
        -: 1258:{
        -: 1259:        
        -: 1260:  //if card is not trashed, added to Played pile 
      340: 1261:  if (trashFlag < 1)
        -: 1262:    {
        -: 1263:      //add card to played pile
      335: 1264:      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      335: 1265:      state->playedCardCount++;
        -: 1266:    }
        -: 1267:        
        -: 1268:  //set played card to -1
      340: 1269:  state->hand[currentPlayer][handPos] = -1;
        -: 1270:        
        -: 1271:  //remove card from player s hand
      340: 1272:  if ( handPos == (state->handCount[currentPlayer] - 1) )       //last card in hand array is played
        -: 1273:    {
        -: 1274:      //reduce number of cards in hand
        2: 1275:      state->handCount[currentPlayer]--;
        -: 1276:    }
      338: 1277:  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
        -: 1278:    {
        -: 1279:      //reduce number of cards in hand
    #####: 1280:      state->handCount[currentPlayer]--;
        -: 1281:    }
        -: 1282:  else  
        -: 1283:    {
        -: 1284:      //replace discarded card with last card in hand
      338: 1285:      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        -: 1286:      //set last card to -1
      338: 1287:      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        -: 1288:      //reduce number of cards in hand
      338: 1289:      state->handCount[currentPlayer]--;
        -: 1290:    }
        -: 1291:        
      340: 1292:  return 0;
        -: 1293:}

In this function, the branch coverage is 100%. However, the statement coverage is 92.31%, we are missing one statement to test. When  state->handCount[currentPlayer] == 1 , we should focus on this in our future improvement.


For the function  villageCard 
	Function 'villageCard'
	Lines executed:100.00% of 5
	No branches
	Calls executed:100.00% of 2

      110:  709:void villageCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag){
        -:  710:      //+1 Card
      110:  711:      drawCard(currentPlayer, state);
        -:  712:
        -:  713:      //+ Actions
      110:  714:      state->numActions = state->numActions++;
        -:  715:
        -:  716:      //discard played card from hand
      110:  717:      discardCard(handPos, currentPlayer, state, 0);
      110:  718:}

In this function, each statement is tested, no branch in this function though. Regarding to boundary , we have covered all the boundaries, include when handcount is 1. Therefore, our unittest for this function is good. 



For the function  greatHallCard 
	Function 'greatHallCard'
	Lines executed:100.00% of 5
	No branches
	Calls executed:100.00% of 2

      110:  721:void greatHallCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag){
        -:  722:      //+1 Card
      110:  723:      drawCard(currentPlayer, state);
        -:  724:
        -:  725:      //+ Actions
      110:  726:      state->numActions = state->numActions++;
        -:  727:
        -:  728:      //discard played card from hand
      110:  729:      discardCard(handPos, currentPlayer, state, 0);
      110:  730:}

In this function, each statement is tested, no branch in this function though. Regarding to boundary , we have covered all the boundaries, include when handcount is 1. Therefore, our unittest for this function is good.

For the function  adventurerCard 
	Function 'adventurerCard'
	Lines executed:100.00% of 17
	Branches executed:100.00% of 12
	Taken at least once:83.33% of 12
	Calls executed:100.00% of 2

     180:  652:void adventurerCard(struct gameState *state, int currentPlayer, int cardDrawn, int temphand[MAX_HAND]){
      180:  653:     int drawntreasure=0;
      180:  654:     int z=0;// this is the counter for the temp hand
     2820:  655:     while(drawntreasure<2){
     2460:  656:        if (state->handCount[currentPlayer] <1){//if the hand is empty we need to shuffle discard and add to deck
     1920:  657:          shuffle(currentPlayer, state);
        -:  658:        }
     2460:  659:        drawCard(currentPlayer, state);
     2460:  660:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
     2820:  661:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      360:  662:          drawntreasure++;
        -:  663:        else{
     2100:  664:          temphand[z]=cardDrawn;
     2100:  665:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
     2100:  666:          z++;
        -:  667:        }
        -:  668:      }
     2460:  669:      while(z-1>=0){
     2100:  670:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
     2100:  671:        z=z-1;
        -:  672:      }
      180:  673:}

In this function, each statement and branch are tested. Regarding to boundary , we have covered all the boundaries, include when handcount is 1. Therefore, our unittest for this function is good.


For the function  smithyCard 
	Function 'smithyCard'
	Lines executed:100.00% of 5
	Branches executed:100.00% of 2
	Taken at least once:100.00% of 2
	Calls executed:100.00% of 2


      110:  676:void smithyCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag){
        -:  677:   int i;
      330:  678:   for (i = 1; i < 3; i++)
        -:  679:   {
      220:  680:      drawCard(currentPlayer, state);
        -:  681:   }
        -:  682:                        
        -:  683:   //discard card from hand
      110:  684:   discardCard(handPos, currentPlayer, state, 0);
      110:  685:}

In this function, each statement and each branch are tested. Also the number of tests in each branch has no big difference. Regarding to boundary , we have covered all the boundaries, include when handcount is 1. Therefore, our unittest for this function is good. 

