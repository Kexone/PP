import Data.List (transpose)
type Pic = [String]
obr = [ "....#....",
        "...###...",
        "..#.#.#..",
        ".#..#..#.",
        "....#....",
        "....#....",
        "....#####"]

-- Print the pic in correct format as it
pp :: Pic -> IO()
pp = putStr . concat . map (++"\n")


-- Rotate the pic horizontally
flipH :: Pic -> Pic
flipH  = reverse 

-- Rotate the pic vertically
flipV :: Pic -> Pic
flipV = map reverse

-- Print two pic above self
above:: Pic -> Pic -> Pic
above a b =  a ++ b

-- Print two pic side by side
side:: Pic -> Pic -> Pic
side (a:as) (b:bs) = (a ++ b) : side as bs 
side _ _ = []    

-- Rotate the pic to left
rotateL :: Pic -> Pic
rotateL [x] = (reverse(sloupec x))
rotateL (x:xs) = (reverse(sloupec x)) `side` (rotateL xs)


-- Rotate the pic to right
rotateR :: Pic -> Pic
rotateR [x] = (reverse(sloupec x))
rotateR (x:xs) = (reverse(rotateR xs)) `side` (sloupec x)

-- Reverse the column
sloupec :: String -> Pic
sloupec xs = [ [x] | x <- xs]

-- Change scale of pic
scale :: Pic -> Int -> Pic
scale  xs n= copyN [copyN x n | x <- xs ] n

-- dunno
copyN :: [a] -> Int -> [a]
copyN xs n = concat [repeat x n| x<-xs] where
    repeat x n = [x | y <-[1..n]]



        --(a:as) b = map [[a*b]| a <-as]
--row :: String -> Pic
--row 