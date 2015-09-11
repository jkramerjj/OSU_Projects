/**

File 'unittest1.c'
Lines executed:52.11% of 71
Branches executed:78.57% of 28
Taken at least once:57.14% of 28
Calls executed:41.67% of 24
unittest1.c:creating 'unittest1.c.gcov'

Analysis: The coverage for this test is not very broad. Only ~50% of the lines
were executed. This could be because there are lines in the conditionals for
failure that are not run. To increase line coverage I could intentionally
interject invalid data to prove the test catches such things. Branch
coverage is better, but not great. Again, some branches are only executed when
invalid data is present. All in all this is not a good test.

File 'unittest2.c'
Lines executed:83.33% of 24
Branches executed:100.00% of 8
Taken at least once:75.00% of 8
Calls executed:84.62% of 13
unittest2.c:creating 'unittest2.c.gcov'

Analysis: This test is much better. 100% of the branches were covered
which also means there was 100% statement coverage. This test appears
based on these numbers to have good coverage. More testing is needed
to determine if it also is a good test.

File 'unittest3.c'
Lines executed:71.21% of 66
Branches executed:87.50% of 32
Taken at least once:78.13% of 32
Calls executed:65.22% of 23
unittest3.c:creating 'unittest3.c.gcov'

Analysis: Another test with decent marks. What worries me is that this test
has regular failures due to shuffling a deck of 3 cards can lead to the same
order before and after. This means that the failure lines were executed but
the coverage tells me there are some lines that aren't executed. This could
be a sign that my test is constructed poorly. This warrants further study.

File 'unittest4.c'
Lines executed:77.42% of 62
Branches executed:100.00% of 32
Taken at least once:75.00% of 32
Calls executed:65.00% of 20
unittest4.c:creating 'unittest4.c.gcov'

Analysis: Most of the numbers are decent but I am a tad concerned that the
Calls executed was only 65%. I honestly don't know how 100% branch coverage
leads to such a low number of calls executed. I will have to discuss this 
with my peers so I can better understand testing.

File 'cardtest1.c'
Lines executed:89.36% of 47
Branches executed:100.00% of 18
Taken at least once:83.33% of 18
Calls executed:86.67% of 15
cardtest1.c:creating 'cardtest1.c.gcov'

Analysis: This is a solid test based upon the numbers. I would feel confident
sharing this test with others and not have them find a large testing error.
That said, I should also include invalid data to make sure the test actually
catches most invalid input.

File 'cardtest2.c'
Lines executed:79.52% of 83
Branches executed:91.67% of 24
Taken at least once:70.83% of 24
Calls executed:56.00% of 25
cardtest2.c:creating 'cardtest2.c.gcov'

Analysis: This test was perhaps the most complex and the one that gave me
the most fits. It is being asked to perform multiple actions because the
card itself has: draw, discard, and increase actions. I really feel
this test needs substantial work.

File 'cardtest3.c'
Lines executed:84.13% of 63
Branches executed:92.31% of 26
Taken at least once:73.08% of 26
Calls executed:77.78% of 18
cardtest3.c:creating 'cardtest3.c.gcov'

Analysis: This test is always FAIL due to a bug I introduced in previous weeks.
I turned off the FAIL messages because they made the results unwieldy.
This test's numbers may be off because the file contains some helper
functions that were used for testing. That said, the tests still has good coverage.
This test is the 3rd favorite based on coverage.

File 'cardtest4.c'
Lines executed:86.90% of 84
Branches executed:94.74% of 38
Taken at least once:81.58% of 38
Calls executed:77.27% of 22
cardtest4.c:creating 'cardtest4.c.gcov'

Analysis: This test has good coverage. This function also is asked to do multiple
actions that dominion.c has in multiple functions. This test could be made better by
elimnating some of the conditionals that are used to adjust the random numbers.
By modifying the random number generation directly these conditionals could be 
eleminated and increase coverage. Does that increase the quality of the test?
Not likely.

 **/
