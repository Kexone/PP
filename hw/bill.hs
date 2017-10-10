module Bill where

import Prelude
import Data.List

type Name = String
type Price  = Integer
type BarCode = Integer
type Database = [(BarCode, Name, Price)]
type TillType = [BarCode]
type BillType = [(Name,Price)]
type Pic = [String]

base = [(110, "Rohlik", 3),(666, "Maslo", 98),(111, "Hovezi maso 1kg", 165),(112, "Nescafe",99),(113, "Slepici bujon", 12)]
till =  [110, 666, 666, 666, 112,113,110,110,111]

repeatNTimes :: Int -> String -> String
repeatNTimes 0 x = []
repeatNTimes n x= x ++ repeatNTimes (n-1) x

countSame :: Name -> BillType -> Int
countSame x b = length [[name] | (name, _) <- b, name == x]

formatRow :: (Name, Price) -> BillType -> String
formatRow (n, p) b =  "  " ++ partName n 16 ++ repeatNTimes (29 - lineLen (partName n 16 ++ show p) - lineLen (show (countSame n b))) " " ++ show (countSame n b) ++ "x " ++ show p ++ ",-\n"

partName :: String -> Int -> String
partName s x | lineLen s <= x = s
              | otherwise = take x s ++ "   "

prodejnaPrint :: String
prodejnaPrint = " Prodejna: 666 \t Pokladni: Alena\n \tINFOLINKA: 800 115 436\n"

printLogo :: String
printLogo = "   ___      ___   ______   ___     \n  |   |    |   | |      | |   |    \n  |   |    |   | |  _    ||   |    \n  |   |    |   | | | |   ||   |    \n  |   |___ |   | | |_|   ||   |___ \n  |       ||   | |       ||       |\n  |_______||___| |______| |_______|"

adresaPrint :: String
adresaPrint = "\n     Lidl Ceska Republika v.o.s.\n   Narozni 1359/11 158 00, Praha 5\n     IC: 26178541, DIC: CZ26178541\n"


header:: String
header = repeatNTimes 36 "_" ++ repeatNTimes 2 "\n" ++ prodejnaPrint ++ printLogo ++ repeatNTimes 1 "\n" ++ adresaPrint ++ repeatNTimes 2 "\n" ++ repeatNTimes 31 " " ++ "CZK"  ++ "\n"

footerAd :: String
footerAd = "\t ***Italsky tyden!***\n\tJiz od pondeli 9.10.\n\tu nas najdete sirovy vyber\n  originalnich italskych specialit.\n  Objevte s nami chut slunneho\n\t     stredmori!\n\n"

footer:: String
footer = "\t    Nashledanou \n    tesime se na dalsi navstevu\n" ++ repeatNTimes 36 "_" ++ "\n\n"


lineLen :: String -> Int
lineLen (_:xs) = 1 + lineLen xs
lineLen []     = 0

makeBill :: TillType -> BillType
makeBill [] = []
makeBill (x:xs) = item x ++ makeBill xs where
item x = [(name, price) | (barcode, name, price) <- base, x == barcode] 

formatBill :: BillType -> String
formatBill till = header ++ concat [formatRow (name, price) till | (name, price) <- nub till] ++ repeatNTimes 36 "-" ++ "\n" ++ clk till ++ repeatNTimes 30 " " ++ repeatNTimes 6 "-" ++ "\n" ++ footerAd ++ footer where
    clk b = "   k platbe" ++ repeatNTimes  (22 - lineLen (show (sum [price | (_, price) <- b]))) " " ++ show (sum [price | (_, price) <- b]) ++ ",- \n"

produceBill :: TillType -> String
produceBill = formatBill . makeBill

pb :: String -> IO ()
pb = putStr 