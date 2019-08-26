import System.IO
import Data.Char

separar :: Eq a => a-> [a] -> [[a]]
separar x y = funcao x y [[]]
    where
        funcao x [] z = reverse $ map (reverse) z
        funcao x (y:ys) (z:zs) = if y==x then
            funcao x ys ([]:(z:zs))
        else
            funcao x ys ((y:z):zs)

-- Converter para Float
stringToFloat s = read s :: Float
-- Converter para String
floatToString s = show s

main :: IO()
main = do

    arqRead <- openFile "dbHaskell.txt" ReadMode
    arqWrite <- openFile "dbProlog.txt" WriteMode
    percorreArq arqRead arqWrite
    hClose arqRead
    hClose arqWrite

percorreArq arqRead arqWrite = 
    do eof <- hIsEOF arqRead
       if eof
          then return()
          else do
                    linhaEntrada <- hGetLine arqRead
                    let cadastro = separar ';' linhaEntrada
                    let cidOrigem = head cadastro
                    let cidDestin = head (tail cadastro)
                    let cadDistancia = head (tail (tail cadastro))
                    let distancia = (stringToFloat cadDistancia)
                    let tempoGasto = round (distancia * 1.5)
                    let tempo = (floatToString tempoGasto)
                    let saidaProlog = "gps(" ++ "\"" ++ cidOrigem ++ "\"" ++ "," ++ "\"" ++ cidDestin ++ "\"" ++ "," ++ cadDistancia ++ "," ++ tempo ++ ")."
                    hPutStrLn arqWrite (saidaProlog)
                    percorreArq arqRead arqWrite