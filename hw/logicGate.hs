module LogicCircuits where

import Prelude
import Data.List
import Data.Char(toUpper)

data LogicCircuit = Value Int
        | AND LogicCircuit LogicCircuit
        | OR LogicCircuit LogicCircuit
        | NOT LogicCircuit
        | NAND LogicCircuit LogicCircuit
        | NOR LogicCircuit LogicCircuit
        | XOR LogicCircuit LogicCircuit
        | XNOR LogicCircuit LogicCircuit

e1 = XOR (Value 0) (Value 0)
e2 = AND (Value 1) (Value 1)

--Jednobitová sčítačka poloviční
halfAdder:: (Int, Int) ->(Int, Int)
halfAdder (a, b) = (eval(AND (Value a) (Value b)), eval(XOR (Value a) (Value b)))

-- Jednobitová sčítačka úplná
fullAdder:: (Int, Int) -> Int ->(Int, Int)
fullAdder (a, b) c =   ( valC , valS ) where
                        valS = eval( XOR (Value (eval(XOR (Value a) (Value b)))) (Value c))
                        valC = eval( OR(Value (eval(AND (Value(eval(XOR (Value a) (Value b)))) (Value c))) ) (Value (eval( AND (Value a) (Value b)))))
                        --valC = eval( OR (Value (eval(OR (Value (eval(AND (Value a) (Value b)))) ((Value (eval(AND (Value b) (Value c)))))) )) ((Value (eval(AND (Value b) (Value c))))))

rippleCarryAdder :: [(Int, Int)] -> Int -> [Int]
rippleCarryAdder [] a = [a] 
rippleCarryAdder ((a, b): xs) c  = reverse [valS] ++ rippleCarryAdder xs valC  where
                                                           valC = fst (fullAdder (a,b) c)
                                                           valS = snd (fullAdder (a,b) c)

eval :: LogicCircuit -> Int
eval (Value x) = x
eval (AND x y)  | (eval x) == (eval y) && (eval x) == 1  = 1
                    | otherwise = 0
eval (OR x y)   | (eval x) == 1 || (eval y) == 1 = 1
                    | otherwise = 0 
eval (NOT x)    | (eval x) == 1 = 0
                    | otherwise = 1
eval (NAND x y) = eval (NOT(Value (eval(AND x y))))
eval (XOR x y)  | (eval x) /= (eval y)  = 1
                    | otherwise = 0
eval (NOR x y)  =  eval (NOT(Value (eval(OR x y))))
eval (XNOR x y) =  eval (NOT(Value (eval(XOR x y))))

printExamples :: String -> [(Int, Int)]-> String
printExamples _ []  =  rep 15 "-" ++ "\n"
printExamples "AND"  ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 2 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( eval( AND  (Value a) (Value b))) ++ rep 1 " " ++ "|\n" ++ printExamples "AND" xs   
printExamples "OR"   ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 2 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( eval( OR   (Value a) (Value b))) ++ rep 1 " " ++ "|\n" ++ printExamples "OR" xs   
printExamples "NOT"  ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 5 " "                        ++ "||" ++ rep 1 " " ++  show ( eval( NOT  (Value a) ))          ++ rep 1 " " ++ "|\n" ++ printExamples "NOT" xs   
printExamples "NAND" ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 2 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( eval( NAND (Value a) (Value b))) ++ rep 1 " " ++ "|\n" ++ printExamples "NAND" xs   
printExamples "NOR"  ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 2 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( eval( NOR  (Value a) (Value b))) ++ rep 1 " " ++ "|\n" ++ printExamples "NOR" xs   
printExamples "XOR"  ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 2 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( eval( XOR  (Value a) (Value b))) ++ rep 1 " " ++ "|\n" ++ printExamples "XOR" xs   
printExamples "XNOR" ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 2 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( eval( XNOR (Value a) (Value b))) ++ rep 1 " " ++ "|\n" ++ printExamples "XNOR" xs   
printExamples "HALF" ((a, b):xs)  = "|"  ++ rep 2 " " ++ show a ++ rep 1 " " ++ show b ++ rep 2 " " ++ "||" ++ rep 1 " " ++  show ( fst (halfAdder(a,b))) ++ rep 1 " " ++ show ( snd (halfAdder(a,b))) ++ rep 1 " " ++ "|\n" ++ printExamples "HALF" xs   

printFullAdder :: [(Int, Int, Int)] -> String
printFullAdder  []  =  rep 15 "-" ++ "\n"
printFullAdder ((a, b, c):xs)  = "|"  ++ rep 1 " " ++ show a ++ rep 1 " " ++ show b ++ rep 1 " " ++ show c ++ rep 1 " " ++ "||" ++ rep 1 " " ++  show ( fst (fullAdder(a,b) c)) ++ rep 1 " " ++ show ( snd (fullAdder(a,b) c)) ++ rep 1 " " ++ "|\n" ++ printFullAdder xs   

showTo :: [Int] -> String
showTo [] = []
showTo  (x:xs) =   show x ++  showTo xs

lineLength :: String -> Int
lineLength (_:xs) = 1 + lineLength xs
lineLength []     = 0

--repeat some char N times
rep :: Int -> String -> String
rep 0 x = []
rep n x= x ++ rep (n-1) x

--print header for gates
printHeaderG x = rep 15 "_" ++ "\n|" ++ rep 5 " " ++ x ++ rep (8 - lineLength x) " " ++ "|\n" ++ rep 15 "-" ++ "\n" ++ "|"  ++ rep 2 " " ++ "A" ++ rep 2 " " ++ "B" ++ rep 2 " " ++ "||" ++ rep 1 " " ++ "S" ++ rep 1 " " ++ "|\n"

--print header for half adder
printHeaderA x = rep 15 "_" ++ "\n|" ++ rep 2 " " ++ x ++ rep (12 - lineLength x) " " ++ "|\n" ++ rep 15 "-" ++ "\n" ++ "|"  ++ rep 2 " " ++ "A" ++ rep 1 " " ++ "B" ++ rep 2 " " ++ "||" ++ rep 1 " " ++ "C" ++  rep 1 " " ++ "S" ++ rep 1 " " ++ "|\n"

--print header for full adder
printHeaderAF x = rep 15 "_" ++ "\n|" ++ rep 2 " " ++ x ++ rep (12 - lineLength x) " " ++ "|\n" ++ rep 15 "-" ++ "\n" ++ "|"  ++ rep 1 " " ++ "A" ++ rep 1 " " ++ "B" ++ rep 1 " " ++ "C" ++ rep 1 " " ++ "||" ++ rep 1 " " ++ "C" ++  rep 1 " " ++ "S" ++ rep 1 " " ++ "|\n"

--print header for ripple carry adder
printHeaderRA x = rep 23 "_" ++ "\n|" ++ rep 2 " " ++ x ++ rep (20 - lineLength x) " " ++ "|\n" ++ rep 23 "-" ++ "\n" ++ "|"  ++ rep 1 " " ++ "A" ++ rep 1 " " ++ "B" ++ rep 1 " " ++ "C" ++ rep 1 " " ++ "||" ++ rep 1 " " ++ "C" ++  rep 1 " " ++ "S" ++ rep 1 " " ++ "|\n"

--printMessage :: String -> String
printMessage x = x

main = do
 let truthTables = [(0,0), (0,1), (1,0), (1,1)] 
-- Logic Gates Truth Tables

 putStr (printMessage rep 5 "\t" ++ rep 15 "_" ++ "\n\n")
 putStr (printMessage rep 5 "\t" ++ " LOGIC GATES \n" ++ rep 5 "\t" ++ " TRUTH TABLES \n")
 putStr (printMessage rep 5 "\t" ++ rep 15 "_" ++ "\n")

 putStr (printHeaderG "AND")
 putStr (printExamples "AND" truthTables )

--OR
 putStr (printHeaderG "OR")
 putStr (printExamples "OR" truthTables )


--NOT 
 putStr (printHeaderG "NOT")
 putStr (printExamples "NOT" [(0,0), (1,1)] )

--NAND
 putStr (printHeaderG "NAND")
 putStr (printExamples "NAND" truthTables )

--NOR 
 putStr (printHeaderG "NOR")
 putStr (printExamples "NOR" truthTables )

--XOR 
 putStr (printHeaderG "XOR")
 putStr (printExamples "XOR" truthTables )

--XNOR
 putStr (printHeaderG "XNOR")
 putStr (printExamples "XNOR" truthTables )

 --One BIT
 putStr (printMessage rep 5 "\t" ++ rep 15 "_" ++ "\n\n")
 putStr (printMessage rep 5 "\t" ++ " ONE BIT \n" ++ rep 5 "\t" ++ " HALF ADDER \n")
 putStr (printMessage rep 5 "\t" ++ rep 15 "_" ++ "\n")

 putStr (printHeaderA "HALF ADDER")
 putStr (printExamples "HALF" truthTables )
 
--One BIT full
 putStr (printMessage rep 5 "\t" ++ rep 15 "_" ++ "\n\n")
 putStr (printMessage rep 5 "\t" ++ " ONE BIT \n" ++ rep 5 "\t" ++ " FULL ADDER \n")
 putStr (printMessage rep 5 "\t" ++ rep 15 "_" ++ "\n")

 putStr (printHeaderAF "FULL ADDER")
 putStr (printFullAdder [(0,0,0),(0,0,1), (0,1,0), (0,1,1), (1,0,0), (1,0,1), (1,1,0), (1,1,1)] )

 putStr (printMessage rep 5 "\t" ++ rep 20 "_" ++ "\n\n")
 putStr (printMessage rep 5 "\t" ++ " FOUR BIT \n" ++ rep 5 "\t" ++ " RIPPLE CARRY ADDER \n")
 putStr (printMessage rep 5 "\t" ++ rep 20 "_" ++ "\n\n")
 putStr (printMessage " 011\n 110 C=0\n" ++ rep 6 "-" ++ "\n")
 putStr ( showTo (rippleCarryAdder [(0,1), (1, 1), (1, 0)] 0 ) )

 putStr (printMessage rep 3 "\n")
--GOOD ONE
--( showTo (rippleCarryAdder ( [ (1,1), (1, 0), (1, 0)] ) 0))


--rippleCarryAdder [(1, 1), (0,1)] 0

--rippleCarryAdder [(0, 0, 0), (0, 0, 1), (0, 1, 0), (0, 1, 1), (1, 0, 0), (1, 0, 1),(1,1,0), (1, 1, 1)]
