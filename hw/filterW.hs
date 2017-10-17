module FIlterWords where

import Prelude
import Data.List

type Index = [(String, [Int])]
type LocatedWords = [(Int, [String])]
txt = "In computer science, functional programming is a programming\nparadigm that treats computation as the evaluation of mathematical\nfunctions and avoids state and mutable data. It emphasizes the\napplication of functions in contrast tothe imperative programming style,\nwhich emphasizes changes in state"


sortWords :: (Ord a) => [a] -> [a]
sortWords = map head . group . sort

getWords :: String -> Int -> [String]
getWords str len = sortWords [x | x <-  (clearCh ',' (clearCh '.'(words str))), (length x) >= len]

searchWord :: String -> LocatedWords -> [Int]
searchWord word text = [x | (x, y) <- text, contains word y]

printText :: Index -> String
printText [] = ""
printText ((word, numb):xs) = ( "  " ++ word ++ " " ++   (show numb) ++ "\n") ++ (printText xs)

contains :: Eq a => a -> [a] -> Bool
contains elem [] = False
contains elem (x:xs) | elem == x = True 
                     | otherwise =  contains elem xs

clearCh :: Eq a => a -> [[a]] -> [[a]]
clearCh y xs = map (filter(/=y)) xs

prepare :: String -> LocatedWords
prepare str = zip [1..(length linesList)] linesList where
    linesList = map words (clearCh ',' (clearCh '.' (lines str)))

getIndex :: String -> Int -> Index
getIndex text len = [(word, searchWord word preparedText) | word <- getWords text len]  where
	preparedText = prepare text

--print anything
printThis :: String -> IO()
printThis = putStr

--print original text
pOT :: IO()
pOT = putStr ("\n\nOriginal text:\n\n" ++ txt ++ "\n\n" )

--print words with index
pI :: Int -> IO()
pI len= putStr ("\n\n" ++ printText (getIndex txt len) ++ "\n\n" )

--showIndex = putStr ("\nIndex:\n\n" ++ printText (buildIndex txt (prepare txt)) ++ "\n\nOriginal text:\n\n" ++ txt ++ "\n")

--putStr (printText (buildIndex txt (prepare txt)))