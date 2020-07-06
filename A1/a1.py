#Scott Giorlando

#Code Help from Rosetta Code, and Python.org (itertools is the link I gave, but I did search up a few other things to learn about on there too.)
#URL: http://rosettacode.org/wiki/Combinations#Python
#URL-2: http://docs.python.org/2/library/itertools.html

#I have my program take in two integers that are input at the command line
#it then prints the combinations of the n integers
#if 3 was input for k then an output would be 3 combinations of n numbers.
#I also have my program take in the range of numbers from 1 to n.

#The line below imports a combinations function from the itertools module
#(basically the same as a library in C++).
#all functions in this module use iterators which makes for a very efficient loop.
from itertools import combinations

#Imported sys in order to have command line arguments.
import sys

#The two lines below have int(command line argument)
#k and n take an input from the command line as a string and cast it to an integer.

k = int(sys.argv[1])
n = int(sys.argv[2])

#This line below prints out the combinations function with the two numbers that are input by the user.
#This line also uses the list function which takes iterables and returns a list of the sequence of iterables.
#This also uses the range function which takes the numbers input and organizes it as a range of the numbers input.
#When combined with the list function it takes the combinations and outputs it like this [(1,2) , (1,3)].
#I also use the argument n+1 here when giving the range so it can fully list the numbers from 1 to n.
#If I didn't have the 1 or the n+1 the range would be from 0 to n.
print(list(combinations(range(1, (n)+1), k)))
