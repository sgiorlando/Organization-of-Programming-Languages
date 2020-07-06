--Scott Giorlando
--This was another language Zachary did

--Code Help from Rosetta Code
--URL: http://rosettacode.org/wiki/Combinations#Haskell

--This seems to say that comb is an array of Ints and the element a is a type Int.
--It also looks to be a recursive implementation since it checks to see if x is in the result or not.
--If x isn't in the result then the program comtinues down the list xs.
comb :: Int -> [a] -> [[a]]
comb 0 _      = [[]]
comb _ []     = []
comb m (x:xs) = map (x:) (comb (m-1) xs) ++ comb m xs
