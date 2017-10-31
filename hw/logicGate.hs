module LogicCircuits where

import Prelude
import Data.List

data LogicCircuit = Value Bool
        | AND LogicCircuit LogicCircuit
        | OR LogicCircuit LogicCircuit
        | NOT LogicCircuit
        | NAND LogicCircuit LogicCircuit
        | NOR LogicCircuit LogicCircuit
        | XOR LogicCircuit LogicCircuit
        | XNOR LogicCircuit LogicCircuit


e1 = OR (Value True) (Value False)
e2 = NAND (Value True) (Value True)


evaluate :: LogicCircuit -> Bool
evaluate (Value x) = x
evaluate (AND x y)  | (evaluate x) == (evaluate y) && (evaluate x) == True  = True
                    | otherwise = False
evaluate (OR x y)   | (evaluate x) == (evaluate y) = True
                    | otherwise = False 
evaluate (NOT x)    | (evaluate x) == True = False
                    | otherwise = True
evaluate (NAND x y) = not (evaluate(AND x y))
evaluate (NOR x y)  | (evaluate x) == True && (evaluate y) == True = False
                    | otherwise = True
evaluate (XOR x y)  = not (evaluate(OR x y))
evaluate (XNOR x y) = not (evaluate(XOR x y))

showIt :: LogicCircuit -> String
showIt (Value x) = show x
showIt (AND x y)  = "(" ++ showIt x ++ ")==(" ++ showIt y ++ ") && (" ++ showIt x ++ ") == 1" 
showIt (OR x y)   = "(" ++ showIt x ++ ") " ++ "== (" ++showIt y ++ ")" 
