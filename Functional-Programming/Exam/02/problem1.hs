finDecRats :: [(Integer, Integer)]
finDecRats =
  (0, 1) : concatMap withSign (filter (isFiniteDecimalDen . snd) cw)
  where
    withSign (p, q) = [(p, q), (-p, q)]

cw :: [(Integer, Integer)]
cw = concat (iterate nextLevel [(1, 1)])
  where
    nextLevel :: [(Integer, Integer)] -> [(Integer, Integer)]

    children :: (Integer, Integer) -> [(Integer, Integer)]
    children (a, b) = [(a, a + b), (a + b, b)]
    nextLevel = concatMap children

isFiniteDecimalDen :: Integer -> Bool
isFiniteDecimalDen q = strip 5 (strip 2 q) == 1
  where
    strip :: Integer -> Integer -> Integer
    strip p n
      | n `mod` p == 0 = strip p (n `div` p)
      | otherwise = n