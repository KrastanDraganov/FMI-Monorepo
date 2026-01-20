type Currency = String

type Price = (Double, Currency)

type Fixing = (Currency, Double, Currency)

neighbors :: Currency -> [Fixing] -> [(Currency, Double)]
neighbors c = foldr step []
  where
    step (a, r, b) acc
      | c == a = (b, r) : acc
      | c == b = (a, 1 / r) : acc
      | otherwise = acc

findRate :: Currency -> Currency -> [Fixing] -> [Currency] -> Maybe Double
findRate from to fixings visited
  | from == to = Just 1
  | from `elem` visited = Nothing
  | otherwise =
      try (neighbors from fixings)
  where
    try [] = Nothing
    try ((n, r) : xs) =
      case findRate n to fixings (from : visited) of
        Just k -> Just (r * k)
        Nothing -> try xs

convert :: Price -> Currency -> [Fixing] -> Price
convert (x, cFrom) cTo fixings
  | cFrom == cTo = (x, cTo)
  | otherwise =
      case findRate cFrom cTo fixings [] of
        Just k -> (x * k, cTo)
        Nothing -> (x, cFrom)

convertAll :: [Price] -> Currency -> [Fixing] -> [Price]
convertAll ps cTo fixings =
  let conv (x, cFrom)
        | cFrom == cTo = Just (x, cTo)
        | otherwise =
            fmap
              (\k -> (x * k, cTo))
              (findRate cFrom cTo fixings [])
   in if Nothing `notElem` map conv ps
        then map ((\(Just v) -> v) . conv) ps
        else []

-- fixing = [("USD", 1.85, "BGN"), ("EUR", 1.95, "BGN"), ("GBP", 2.3, "BGN")]
-- convert (20, "BGN") "EUR" fixing
-- convertAll [(20, "BGN"), (10, "USD"), (20, "GBP")] "EUR" fixing
