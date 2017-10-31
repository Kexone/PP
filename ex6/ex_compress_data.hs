import Data.List

data Tree  = List Char 
            | Node Tree Tree
            deriving Show  

type Cetnost = [(Tree, Float)]


text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccdddddddddddddddddddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeegggggggggggggggggggggggggggggggg"


spoctiCetnost :: String -> Cetnost
spoctiCetnost  text = let delka = length text
                      in [(List x, fromIntegral (length (filter (==x) text)) / fromIntegral delka )| x <- (nub text)]
                    
porovnej :: (Tree, Float) -> (Tree, Float) -> Ordering
porovnej (s1, c1) (s2,c2)  = compare c1 c2

vytvorStrom :: Cetnost -> Tree
vytvorStrom  = tmp (sortBy porovnej x) where
 tmp [(s,_)] = s 
tmp ((s1,c1):(s2,c2):xs) = tmp (sortBy porovnej (Node s1 s2, c1+c2):xs)



--vytvorStrom ((s1,c1):(s2,c2):xs) = vytvorStrom (sortBy porovnej( ( Node s1 s2, c1+c2 ):xs))


tabulka (List x) kod = [(x, kod)]
tabulka (Node x y) kod = (tabulka x (kod++"0") ) ++ (tabulka y (kod++"1"))


--vytvorStrom xs = tmp [(z, cetnost, List z) | (z, cestnost) <-xs] where
  --  tmp [(_,)]






  -- sortBy vytvorStrom (spoctiCetnost text)