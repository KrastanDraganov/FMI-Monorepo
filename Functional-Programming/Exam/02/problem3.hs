import Data.Ord (comparing)

type Day = Int

type MerchantName = String

type PurchaseSum = Int

type Spending = (Day, MerchantName, PurchaseSum)

maximumBy :: (a -> a -> Ordering) -> [a] -> a
maximumBy _ [] = error "maximumBy: empty list"
maximumBy cmp (x : xs) = foldl pick x xs
  where
    pick best y = if cmp y best == GT then y else best

maxDay :: [Spending] -> Day
maxDay [] = error "maxDay: empty list"
maxDay ((d, _, a) : xs) = go d a xs
  where
    go bestDay bestAmt [] = bestDay
    go bestDay bestAmt ((d2, _, a2) : rest)
      | a2 > bestAmt = go d2 a2 rest
      | otherwise = go bestDay bestAmt rest

daysPerShop :: [Spending] -> [(MerchantName, [Day])]
daysPerShop = foldl step []
  where
    step :: [(MerchantName, [Day])] -> Spending -> [(MerchantName, [Day])]
    step acc (d, s, _) = insertDay s d acc

    insertDay :: MerchantName -> Day -> [(MerchantName, [Day])] -> [(MerchantName, [Day])]
    insertDay s d [] = [(s, [d])]
    insertDay s d ((s2, ds) : xs)
      | s == s2 =
          if d `elem` ds
            then (s2, ds) : xs
            else (s2, d : ds) : xs
      | otherwise = (s2, ds) : insertDay s d xs

topShop :: [Spending] -> MerchantName
topShop [] = error "topShop: empty list"
topShop txs =
  fst $
    maximumBy
      (comparing snd)
      [(s, length ds) | (s, ds) <- daysPerShop txs]

streak :: [Spending] -> Int
streak txs =
  maximum (0 : [maxIncreasingRun (map snd daySums) | (_, daySums) <- perShopDaySums txs])

perShopDaySums :: [Spending] -> [(MerchantName, [(Day, PurchaseSum)])]
perShopDaySums = foldl addTx []
  where
    addTx :: [(MerchantName, [(Day, PurchaseSum)])] -> Spending -> [(MerchantName, [(Day, PurchaseSum)])]
    addTx acc (d, s, a) = addToShop acc s d a

    addToShop :: [(MerchantName, [(Day, PurchaseSum)])] -> MerchantName -> Day -> PurchaseSum -> [(MerchantName, [(Day, PurchaseSum)])]
    addToShop [] s d a = [(s, [(d, a)])]
    addToShop ((s2, ds) : xs) s d a
      | s == s2 = (s2, addToDaySum ds d a) : xs
      | otherwise = (s2, ds) : addToShop xs s d a

    addToDaySum :: [(Day, PurchaseSum)] -> Day -> PurchaseSum -> [(Day, PurchaseSum)]
    addToDaySum [] d a = [(d, a)]
    addToDaySum ((d2, sumA) : xs) d a
      | d == d2 = (d2, sumA + a) : xs
      | otherwise = (d2, sumA) : addToDaySum xs d a

maxIncreasingRun :: [PurchaseSum] -> Int
maxIncreasingRun [] = 0
maxIncreasingRun (x : xs) = go 1 1 x xs
  where
    go best curr prev [] = max best curr
    go best curr prev (y : ys)
      | y > prev = go best (curr + 1) y ys
      | otherwise = go (max best curr) 1 y ys

example :: [Spending]
example =
  [ (1, "A", 10),
    (1, "A", 11),
    (2, "A", 15),
    (3, "A", 17),
    (3, "B", 10),
    (4, "B", 14),
    (5, "B", 15),
    (6, "B", 16)
  ]
