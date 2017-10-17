module ConvertString where

txt = "In computer science,\tfunctional programming is a programming\nparadigm that treats computation\tas\t the evaluation of mathematical functions\nand avoids state and mutable data. It emphasizes the application of functions in contrast tothe imperative\nprogramming style, which emphasizes changes in state"

lineLength :: Int
lineLength = 30

clearWSpace :: String -> String
clearWSpace [] = []
clearWSpace (x:xs) | x == '\n' || x == '\t' = clearWSpace xs 
                   | otherwise  = x : clearWSpace xs 

justifyText :: Int -> String -> String
justifyText _ "" = ""
justifyText 0 (x:xs) = '\n' : x  : justifyText lineLength xs 
justifyText c (x:xs) =  x : justifyText (c-1) xs 

pThis :: String -> IO ()
pThis = putStr

-- call as "prepare [] 0 (words (txt))"

prepare  x cLength [] = x 
prepare [] 0 (y:ys) = prepare [[y]] (length y) ys 
prepare  (x:xs) cLength (y:ys) 
            | cLength + length y + 1 > lineLength = prepare ([y]:x:xs) (length y + 1) ys
            | otherwise                       = prepare ((x ++ [y]):xs ) (cLength + length y + 1) ys 


format x = concat x

format (x:xs) l rl= x ++ " " ++ format xs


realLength x = length (concat x)

procede x = let x' =  reverse (prepare [] 0 (words (x)))
            in concat [ (format y (length y) (lineLength - realLength y)) ++ "\n" |  y <- x']


-- Unikátní slova  delší alespoň 4 znaky, setřídit je a napsat na jakých řádcích se nachází