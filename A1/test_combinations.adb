-- Scott Giorlando

-- Code Help from Rosetta Code
-- URL: http://rosettacode.org/wiki/Combinations#Ada

-- I'm not entirely sure how to code in Ada or what any of it means, so this is my best attempt to figure out what exactly everything means.

-- I believe this line is similar to a #include <iostream> line in C++.  So basically this program is using an input/output, and this line just accesses that library and its objects.
with Ada.Text_IO; use Ada.Text_IO;

-- This line creates the test_combinations program, I originally had my file name different from this line and my program wouldn't compile.
-- This is also basically a function that uses integers and uses an array of positive integers, it creates an array named Combination that holds a positive range of integers.
-- First is the first value that is received in the array.
-- Next is the next number in the range that is received in the array.
-- Put places X into the array Combination.
-- end Combinations is the end of this procedure/function.

procedure Test_Combinations is
  generic
    type Integers is range <>;
  package Combinations is
    type Combination is array (Positive range <>) of Integers;
    procedure First (X : in out Combination);
    procedure Next (X : in out Combination);
    procedure Put (X : Combination);
  end Combinations;

-- The package body Combination defines the implementation of the package Combination.
-- After this a procedure is made and it assigns X at position 1 to the first integer that appears.
-- A loop starts and it goes from element to up to the last number in the the array, this loop assigns X at the specific position to the number in the range, starting the combination sequence.
-- After the loop, the procedure for Next is made.  There is a conditional for Next which checks to see if X at the specific element I is less than the element before, If so then X is assigned that new value, if not then it keeps the old value and continues.
-- When the procedure isn't satisfied, an error pops up.
-- After this the new value of X for Next is placed.
  package body Combinations is
    procedure First (X : in out combination) is
    begin
      X (1) := Integers'First;
      for I in 2..X'Last loop
        X (I) := X (I - 1) + 1;
      end loop;
    end First;
    procedure Next (X : in out Combination) is
    begin
      for I in reverse X'Range loop
        if X (I) < Integers'Val (Integers'Pos (Integers'Last) - X'Last + I) then
           X (I) := X (I) + 1;
           for J in I + 1..X'Last loop
              X (J) := X (J - 1) + 1 ;
           end loop;
           return;
        end if;
      end loop;
      raise Constraint_Error;
    end Next;
    procedure Put (X : Combination) is
    begin
      for I in X'Range loop
        Put (Integers'Image (X (I)));
      end loop;
    end Put;
  end Combinations;

-- This line creates a range of five numbers from 1 to 4.
-- The range of Five is made into an array of combinations called Fives.
  type Five is range 1..4;
  package Fives is new Combinations (Five);
  use Fives;

-- This line makes X a Combination of Fives, then outputs the Array so it will look like (1, 2) , (1, 3) , ... , etc.  Each number is followed by a new line.
-- An error appears if this does not work correctly as well.
  X : Combination (1..2);
begin
    First (X);
    loop
      Put (X); New_Line;
      Next(X);
    end loop;
exception
    when Constraint_Error =>
      null;
end Test_Combinations;
