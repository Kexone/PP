module FIlterWords where

import Prelude
import Data.List
--import Data.List.Split

type Index = [(String, [Int])]
type PreparedText = [(Int, [String])]
txt = "In computer science, functional programming is a programming\nparadigm that treats computation as the evaluation of mathematical\nfunctions and avoids state and mutable data. It emphasizes the\napplication of functions in contrast tothe imperative programming style,\nwhich emphasizes changes in state"


minWordLength = 4

remove :: Eq a => a -> [[a]] -> [[a]]
remove y xs = map (filter(/=y)) xs

prepare :: String -> PreparedText
prepare str = zip [1..(length lineList)] lineList where
    lineList = map words (remove ',' (remove '.' (lines str)))

unique :: (Ord a) => [a] -> [a]
unique = map head . group . sort

getWords :: String -> [String]
getWords str = unique [x | x <- (remove ',' (remove '.' (words str))), (length x) >= minWordLength]

toString :: Index -> String
toString ((word, lines):xs) = (word ++ " => " ++ (show lines) ++ "\n") ++ (toString xs)
toString [] = ""

contains :: Eq a => a -> [a] -> Bool
contains elem (x:xs) = if elem == x then True else contains elem xs
contains elem [] = False

searchWord :: String -> PreparedText -> [Int]
searchWord word text = [x | (x, y) <- text, contains word y]

buildIndex :: String -> PreparedText -> Index
buildIndex text prepared = [(word, l word) | word <- getWords text] where
    l word = searchWord word prepared

showIndex :: IO()
showIndex = putStr ("\nIndex:\n\n" ++ toString (buildIndex txt (prepare txt)) ++ "\n\nOriginal text:\n\n" ++ txt ++ "\n")