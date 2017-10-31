import import
main = do hin <- off "From: " ReadMore
        hout <- opf "To: " WriteMode
        contents <- hGetContents cisluj hin
        hClose hout
        putStr "Done."


cisluj x = concat (ziWith (\x y -> ((show x)++". " ++y++"\n")) [1..] (lines "asdsadsad\nfdsfdfygsfs\nfsdsfsdf"))

opf :: String ->IOMode -> IO Handle
opf prompt mode = do putStr prompt
                   name <- getLine
                   openFile name mode 