/*
Scott Giorlando
*/

/*
This was the last program Zachary did
*/

/*
Code Help from Rosetta Code
URL: http://rosettacode.org/wiki/Combinations#Prolog
Combinations is the overall driver
it takes L which is an output variable
as well as K (the length of permuations)
and the range of the numbers being from
1 to the given n. In order to run this Program
you would type
?- combinations(3,5,L), writeln(L), fail.
*/


combinations(K, N, L) :-
  /*Length seems to make the length of the combinations*/
  length(L ,K),
  /*This calls the fill function*/
  fill(L, 1, N).

fill([], _, _).

fill([H | T], Min, Max) :-
  /*The function between produces the numbers from 1 to n*/
  between(Min, Max, H),
  /*H1 is a copy of H but has 1 added to it, so it increments H.*/
  H1 is H + 1,
  /*A list T is created and is filled with the specific numbers*/
  fill(T, H1, Max).
