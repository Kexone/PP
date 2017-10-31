module LogicCircuits where

import Prelude
import Data.List
import Data.Char(toUpper)


data LogicCircuit = Value Bool
        | AND LogicCircuit LogicCircuit
        | OR LogicCircuit LogicCircuit
        | NOT LogicCircuit
        | NAND LogicCircuit LogicCircuit
        | NOR LogicCircuit LogicCircuit
        | XOR LogicCircuit LogicCircuit
        | XNOR LogicCircuit LogicCircuit


e1 = XOR (Value False) (Value False)
e2 = NAND (Value True) (Value True)

--Jednobitová sčítačka poloviční
halfAdder:: (Bool, Bool) ->(Bool, Bool)
halfAdder (a,b) = (eval(AND (Value a) (Value b)), eval(XOR (Value a) (Value b)))

-- Jednobitová sčítačka úplná
fullAdder:: (Bool, Bool, Bool) ->(Bool, Bool)
fullAdder (a, b, c) =   ( valC , valS ) where
                        valS = eval(XOR (Value (eval(XOR (Value a) (Value b)))) (Value c))
                        valC = eval( OR (Value (eval(OR (Value (eval(AND (Value a) (Value b)))) ((Value (eval(AND (Value b) (Value c)))))) )) ((Value (eval(AND (Value b) (Value c))))))

--rippleCarryAdder :: (Bool,Bool, Bool) -> (Bool, Bool, Bool,Bool)
--rippleCarryAdder (a,b,c0,) (c,_) = fullAdder 



eval :: LogicCircuit -> Bool
eval (Value x) = x
eval (AND x y)  | (eval x) == (eval y) && (eval x) == True  = True
                    | otherwise = False
eval (OR x y)   | (eval x) == True || (eval y) == True = True
                    | otherwise = False 
eval (NOT x)    | (eval x) == True = False
                    | otherwise = True
eval (NAND x y) = not (eval(AND x y))
eval (XOR x y)  | (eval x) /= (eval y)  = True
                    | otherwise = False
eval (NOR x y)  = not (eval(OR x y))
eval (XNOR x y) = not (eval(XOR x y))

showIt :: LogicCircuit -> String
showIt (Value x) = show x
showIt (AND x y)  = "(" ++ showIt x ++ ")==(" ++ showIt y ++ ") && (" ++ showIt x ++ ") == 1" 
showIt (OR x y)   = "(" ++ showIt x ++ ") " ++ "== (" ++showIt y ++ ")" 


showTo :: (Bool, Bool) -> IO ()
showTo (a, b) =  putStr ("Vysledek: " ++ show (convB2I b) ++ " Preteceni:" ++ show (convB2I b)  ++ "\n")


convB2I :: Bool -> Int
convB2I True = 1
convB2I False = 0
