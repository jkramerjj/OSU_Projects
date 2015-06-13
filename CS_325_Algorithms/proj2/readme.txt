To test the three algorithms, run the following commands:

python proj2.py -f amount.txt -o -a slow
python proj2.py -f amount.txt -o -a greedy
python proj2.py -f amount.txt -o -a dp

This will generate the results of each algorithm in a separate file. These
files will be named the following (respectively):

amount_slow_results.txt
amount_greedy_results.txt
amount_dp_results.txt

To output a help message, run 'python proj2.py' with no arguments. This
message will display the following information:

Usage:
  python proj2.py [OPTIONS]
  -a ALG_NAME   specify algorithm to run (slow, greedy, dp)
  -f FILE.txt   specify file FILE containing input data
  -o            output results of algorithm to file if -f flag given
  -t DATA_SET   prints timing information for algorithm using predefined data (overrides -f -p -o)
                  DATA_SET must be 1 or 2
  -p            prints data written to output file to stdout
  -h            display this message
