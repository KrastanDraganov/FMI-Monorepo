type Statistic = [Int] -> Int

allStats :: [Int] -> [Int] -> [Statistic] -> [[Int]]
allStats _ [] _ = []
allStats d (w : ws) stats
  | w <= 0 = error "window sizes should be >= 0"
  | otherwise =
      let chunk = take w d
          rest = drop w d
          row = map (\s -> s chunk) stats
       in row : allStats rest ws stats

-- allStats [1..] (2:3:[1..]) [sum, length, maximum]