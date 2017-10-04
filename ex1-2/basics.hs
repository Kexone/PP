-- Fibonacci sequence - by recurse
fib:: Int -> Int
fib 0 = 0
fib 1 = 1 
fib n = fib (n-1) + fib (n-2)

-- Greatest common divisor
nsd :: Int -> Int -> Int
nsd a b 
    |  a == b    = a 
    |  a >  b    = nsd (a-b) b
    |  a <  b    = nsd a (b-a)

-- Find the length of list
delka:: [a] -> Int
delka [] = 0
delka (x:xs)  = 1 + delka xs

-- Concatetion of two list
spoj:: [a] -> [a] -> [a]
spoj xs [] = xs
spoj [] ys = ys
spoj (x:xs) (y) = x:(spoj xs y)

-- Create tuple from two lists
dvojice:: [a] -> [b] -> [(a,b)]
dvojice [] _ = []
dvojice  _ [] = []
dvojice (x:xs) (y:ys) = (x, y):dvojice xs ys

-- Reverse of list
otoc:: [a] -> [a]
otoc [] = []
otoc (x:xs) = otoc (otoc(xs))

otoc2 x = tmp x []

tmp [] ys = ys 
tmp (x:xs) ys = tmp xs (x:ys)


spojs :: (a->b->c) -> [a] -> [b] -> [c]
spojs  a (x:xs) (y:ys) = a x y : spojs a xs ys
spojs a x y = []

ss :: [Int]->[Int]->Int
ss (x:xs) (y:ys) = x*y + ss xs ys
ss x y = 0

-- Create list of tuples from two lists
ks :: [a] -> [b] -> [(a,b)]
ks (a:as) (b:bs) = [(a,b)| a<-a:as, b<-b:bs]

ks2 [] _ = []
--ks2 x (x:xs) ys = (ks2tmp x ys) ++ ks2 xs ys



ks2tmp x [] = []
ks2tmp x (y:ys) = (x,y) : ks2tmp x ys


ks3 [x] [y] = [(x,y)]
--ks3 [x] (y:ys) =  (x:y) : ks3 [x]  ys
--ks3 (x:xs) ys  = ks3 x ys ++ ks3 xs ys


npvs :: (Ord a) => [a]->a
npvs [x] = x
npvs (x:y:xs) = npvs ((if x < y
                       then x 
                       else y):xs)

-- Find the min in list
nejmensi :: (Ord a) => [a]->a
nejmensi (x:xs) = tmp x xs where
    tmp mn [] = mn
    tmp mn (x:xs) | mn > x = tmp x xs
                   | otherwise = tmp mn xs


delitel x = [y | y <- [1..x], mod x y == 0]