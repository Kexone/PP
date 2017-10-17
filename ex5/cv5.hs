module ExerciseFive where

data Expr = Num Int
    | Add Expr Expr
    | Sub Expr Expr
    | Mul Expr Expr
    | Div Expr Expr
    | Var Char
    deriving (Eq)




-- 4 * 5 + 8 * 2
el = Add (Mul (Num 4) (Num 5)) (Mul(Num 8) (Num 2))
e2 = Add (Add (Num 1) (Num 2)) (Num 3)
e3 = Add (Mul (Num 2) (Var 'x')) (Mul (Var 'x') (Var 'x'))


eval :: Expr -> Int
eval (Num x) = x
eval (Add x y) = (eval x )   +   (eval y)
eval (Sub x y) = (eval x )   -   (eval y)
eval (Mul x y) = (eval x )   *   (eval y)
eval (Div x y) = (eval x ) `div` (eval y)

showExpr :: Expr -> String
showExpr (Num x) = show x
showExpr' (Var c)  f = [c]
showExpr (Add x y) = "(" ++ showExpr x ++ ")" ++ "  +  " ++ "(" ++ showExpr y ++ ")"
showExpr (Sub x y) = "(" ++ showExpr x ++ ")" ++ "  -  " ++ "(" ++ showExpr y ++ ")"
showExpr (Mul x y) = "(" ++ showExpr x ++ ")" ++ "  *  " ++ "(" ++ showExpr y ++ ")"
showExpr (Div x y) = "(" ++ showExpr x ++ ")" ++ "`div`" ++ "(" ++ showExpr y ++ ")"


--show e1 
-- aby se showExpr stal instanci teto tridy abych mohl tisknout "e1" jen
-- e 