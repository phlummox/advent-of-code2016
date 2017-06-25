
module Main
(main)
where

import System.Environment 
import Test.QuickCheck

-- solution to day 19, part B - a variant on the Josephus problem,
-- where the person "opposite" is removed, rather than a person
-- n places on 

-- | get position of person remaining alive in this variation
-- on the Josephus problem.
--
-- For a circle of size n, the person at position n `div` 2 is removed.
-- The solution can then be reduced to solving the problem for n-1,
-- but with the position "re-mapped" to the positions in our current
-- circle:
--    - we need to shift the solution up by 1 - person 0 in the (n-1)
--      solution becomes person 1 in the size n solution 
--      (they're the "next person along");
--    - once we've done that, we'll have to take the answer modulo n,
--      in case it has "looped round" the circle from finish to start; 
--    - the (n-1) solution might now point to the removed person -
--      so if it's >= k (where k is the removed person), we
--      add 1 and take the modulus again. 
josephus :: Integer -> Integer
josephus = (+1) . j
  where
    j :: Integer -> Integer
    j n
      | n <= 0 = error "must be gte 1"
      | n == 1 = 0
      | n == 2 = 0
      | otherwise = 
          let kill_idx = n `div` 2 
          -- only time the "next person" /= 1 is for n = 2, 
          -- which we've hardcoded. 
              -- get result for the next n down.
              prev_res     = j (n - 1)  
          -- we now have a result; we need to map it back
          -- relative to idx 1, so add 1, then mod.
          -- Could point to the killed person, so skip them, then mod.
              res' = (prev_res + 1) `mod` n
          in if res' < kill_idx
             then res'
             else (res' + 1) `mod` n 


-- By inspection: the `josephus` function above follows a pattern related to
-- the largest power of 3 less than or equal to n,
-- so the following implementation is equivalent.

-- | highest power of p that is <= n
highestPowLtN 0 _ = error "n must be >= 1"
highestPowLtN n p = 
  let powers = [0..] 
  in  last $ takeWhile (\i -> p ^ i <= n) powers

-- | quicker implementation of `josephus`
quickJosephus :: Integer -> Integer
quickJosephus n 
    | threeToK == n                           = n
    | n >= threeToK + 1 && n <= threeToK * 2  = n - threeToK
    | otherwise                               = 2*n - (3 ^ (k+1))
  where
    k = highestPowLtN n 3
    threeToK = 3 ^ k

-- | Used for testing that the 2 implementations give the same results
prop_impls_equiv :: Positive Integer -> Bool
prop_impls_equiv (Positive i) =
  quickJosephus i == josephus i

main =  do
  (n : _) <- getArgs
  print $  quickJosephus (read n) 
  
