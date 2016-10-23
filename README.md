# data_stats_cpp

I needed a short c++ program that calculates summary statistics of a bunch of numbers on the command-line.

## Dependencies

Aside from standard C++ (vectors, This program uses the really nice Boost::Accumulators and Boost::Program_Options so you'll need these.

## Compilation

So to compile this, please use:

g++ data_stats.cpp -o data_stats -lboost_program_options

Then to get help for the calling parameters etc, do

data_stats --help

...and follow the instructions.


