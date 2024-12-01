module Main where

split :: (Char -> Bool) -> String -> [String]
split p s = case dropWhile p s of
                      "" -> []
                      s' -> w : split p s''
                            where (w, s'') = break p s'


paper :: [Int] -> Int
paper [l, w, h] =
    let sufArea = 2 * (l * w + w * h + h * l)
        sidesAreas = [l * w, w * h, h * l]
        smallSide = minimum sidesAreas
    in sufArea + smallSide
paper _ = error "Expected three dimensions."

ribbon :: [Int] -> Int
ribbon [l, w, h] =
    let perimeters = [2 * (l + w), 2 * (w + h), 2 * (h + l)]
        smallPer = minimum perimeters
        volume = l * w * h
    in smallPer + volume
ribbon _ = error "Expected three dimensions."

processLine :: String -> (Int, Int)
processLine line =
    let dimensions = map read (split (=='x') line) :: [Int]
    in (paper dimensions, ribbon dimensions)

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let linesList = lines contents
    let results = map processLine linesList
    let (wTotal, rTotal) = unzip results
    let totalW = sum wTotal
    let totalR = sum rTotal
    print totalW
    print totalR
