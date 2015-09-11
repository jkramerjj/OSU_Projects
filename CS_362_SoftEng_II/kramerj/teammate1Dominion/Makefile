CFLAGS = -Wall -fpic -coverage -lm
ARGS = 50000
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

oldAll: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Unit Test 1:" > unittestresults.out
	unittest1 ${ARGS} >> unittestresults.out
	echo -e "\nUnit Test 2:" >> unittestresults.out
	unittest2 ${ARGS} >> unittestresults.out
	echo -e "\nUnit Test 3:" >> unittestresults.out
	unittest3 ${ARGS} >> unittestresults.out
	echo -e "\nUnit Test 4:" >> unittestresults.out
	unittest4 ${ARGS} >> unittestresults.out
	echo "Card Test 1:" >> unittestresults.out
	cardtest1 ${ARGS} >> unittestresults.out
	echo -e "\nCard Test 2:" >> unittestresults.out
	cardtest2 ${ARGS} >> unittestresults.out
	echo -e "\nCard Test 3:" >> unittestresults.out
	cardtest3 ${ARGS} >> unittestresults.out
	echo -e "\nCard Test 4:" >> unittestresults.out
	cardtest4 ${ARGS} >> unittestresults.out
	echo -e "\nUnit Test 1 Coverage:"
	gcov -b unittest1.c >> unittestresults.out
	echo -e "\nUnit Test 2 Coverage:"
	gcov -b unittest2.c >> unittestresults.out
	echo -e "\nUnit Test 3 Coverage:"
	gcov -b unittest3.c >> unittestresults.out
	echo -e "\nUnit Test 4 Coverage:"
	gcov -b unittest4.c >> unittestresults.out
	echo -e "\nCard Test 1 Coverage:"
	gcov -b cardtest1.c >> unittestresults.out
	echo -e "\nCard Test 2 Coverage:"
	gcov -b cardtest2.c >> unittestresults.out
	echo -e "\nCard Test 3 Coverage:"
	gcov -b cardtest3.c >> unittestresults.out
	echo -e "\nCard Test 4 Coverage:"
	gcov -b cardtest4.c >> unittestresults.out


randomtestadventurer.out: randomtestadventurer
	echo -e "\Random Test Adventurer: " > randomtestadventurer.out
	randomtestadventurer ${ARGS} >> randomtestadventurer.out
	echo -e "\nRandom Test Adventurer Coverage:"
	gcov -b randomtestadventurer.c >> randomtestadventurer.out

randomtestcard.out: randomtestcard
	echo -e "\Random Test Card: " > randomtestcard.out
	randomtestcard ${ARGS} >> randomtestcard.out
	echo -e "\nRandom Test Card Coverage:"
	gcov -b randomtestcard.c >> randomtestcard.out