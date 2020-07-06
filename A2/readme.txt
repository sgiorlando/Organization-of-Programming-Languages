Name: Scott Giorlando
Partner: Zachary Palmer
Assignment: Syntax Error Recovery
Submission #: 2

What's working and what's not:

We have completely finished the following aspects of the program:
  * The translation of the starter code from C to C++
  [25% of the assignment grade according to the rubric]

  * Extend the language with if and do/check statements
  [25% of the assignment grade according to the rubric]

  * Output the complete syntax tree
  [25% of the assignment grade according to the rubric]

The following aspects of the program are a work in progress:

  * Implement exception-based syntax error recovery
  [25% of the assignment grade according to the rubric]

    - Currently the error recovery is mostly working though
      it does not fully delete the tokens in order to successfully
      recover. But it does output the error token and the expected token

Running Instructions:

  1.) type "make"
  2.) type "make test"
  3.) you can test any additional desired test with "./parse < -test file-"

Output on correct input:

make test
cat primes.cl | ./parse


Begin Output:

(program
[ (read "n")
(:= "cp" (num "2"))
(do
[ (check (id "n") > (num "0"))
(:= "found" (num "0"))
(:= "cf1" (num "2"))
(:= "cf1s" (id "cf1") * (id "cf1"))
(do
[ (check (id "cf1s") <= (id "cp"))
(:= "cf2" (num "2"))
(:= "pr" (id "cf1") * (id "cf2"))
(do
[ (check (id "pr") <= (id "cp"))
(if
((id "pr") == (id "cp"))
[ (:= "found" (num "1"))
]
)
(:= "cf2" (id "cf2") + (num "1"))
(:= "pr" (id "cf1") * (id "cf2"))
]
)
(:= "cf1" (id "cf1") + (num "1"))
(:= "cf1s" (id "cf1") * (id "cf1"))
]
)
(if
((id "found") == (num "0"))
[ (write "(id "cp"))
(:= "n" (id "n") - (num "1"))
]
)
(:= "cp" (id "cp") + (num "1"))
]
)
]
)

Output on incorrect input:

./parse < test1.txt

Token Expected was: od
Unexpected token: endPrgm

Token Expected was: endPrgm
Unexpected token: od

Program had the above syntax errors fix them before running the program again in order to generate a correct syntax tree.
Below is the best syntactically correct version that this program can generate:


Begin Output:

(program
[ (read "n")
(:= "cp" (num "2"))
(do
[ (check (id "n") > (num "0"))
(:= "found" (num "0"))
(:= "cf1" (num "2"))
(:= "cf1s" (id "cf1") * (id "cf1"))
(do
[ (check (id "cf1s") <= (id "cp"))
(:= "cf2" (num "2"))
(:= "pr" (id "cf1") * (id "cf2"))
(do
[ (check (id "pr") <= (id "cp"))
(if
((id "pr") == (id "cp"))
[ (:= "found" (num "1"))
]
)
(:= "cf2" (id "cf2") + (num "1"))
(:= "pr" (id "cf1") * (id "cf2"))
(:= "cf1" (id "cf1") + (num "1"))
(:= "cf1s" (id "cf1") * (id "cf1"))
]
)
(if
((id "found") == (num "0"))
[ (write "(id "cp"))
(:= "n" (id "n") - (num "1"))
]
)
(:= "cp" (id "cp") + (num "1"))
]
)
]
