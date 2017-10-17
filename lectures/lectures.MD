#PP

##Overview
-KZ
-domácí úkoly

Haskell Hugs
funkcionální programování 
-paradigma, jdoucí proti programování imperaktivnímu


množina funkcí, vykonání množiny funkcí

Funkce  - zobrazení z definičního oboru hodnot na obor fce
Sémantika
Operátor - relace
Funkce v Haskelu nemá žádný vedlejší efekt, stejný vstup, stejný výstup
Syntaxe Haskellu podobná Pythonu 
(*hs) - everything is program  -- commnet
(*lhs) everything is comment,  > program
Haskel má moduly, dají se importovat (module *** where import Ant)
Prelude (podobný balíček java.lang) obsahuje základní funkce
schovávání funkcí  import Prelude hiding (max, min)
Volání funkcí bez závorek (když je použiji, mění to vyznám, jeden parametr, dvojice)
volání je f 5 3
aplikace fce je silnější než cokoliv jiného  (f 5+3 4  - překladač by zařval, že očekával nějakou funkci, aby mohl přičíst 3, operátor + je slabší než funkce)
operátor funkce můžu použít pomocí ' '
(+)  operátor můžu použít jako funkci


#PP 2 přednáška

nepovinný silně typový systém

##Práce se seznamy
    type String = [Char] - typové synonymum - říkám seznamu charu jako String
    

#PP 3 přednáška

##lambda- calculus 
    - calculus - nějaký ucelený model s vypočetními možnostmi, v Hasellu se dá calculus přeložit na turingův stroj
    
    syntaxe - jak zapsat 
    sémantika - význam instrukcí

    lanbda - calculus
    Substituce
        -  můžu přeznačit  [g z /f ]  místo g a z dát f

    substitucím se říká alfa redukce
    gamma redukce - odstranují abstrakce, které jsou zbytečné

    redex - výraz, který obsahuje už nějakou redukci
    normální forma - už neexistuje žádná beta redukce
    
  

#PP přednáška 4


 lambda calculus
 - používá známé funkce
 beta- redukce - nahrazení výrazu


weak head normal form - zjednodušil by levou funkci

strategie - říká jak nakládat/ předávat parametry
př f(5+5)   jak naložit s parametrem (5+5)
haskell předává  hodnotou/referencí/jménem (nějak pojmenuji)
používá lazy vyhodnocování (nechci vyhodnocovat nic dopředu a ani ne dvakrát) v Jave to moc nejde

Nestriktní  - obsahuje části, které nelze vyhodnotit, ale nejsou potřeba pro hlavní část výsledku - tak je prostě přeskočí
Neplatí pro haskell: pokud nelze vyraz vyhodnotit = pak celý program nelze vyhodnotit 
Nekonečná struktura 1.. 


#PP přednáška 5
#odvozené třídy
typ Ordering - 3 hodnoty větší, menší, rovno
max, min  :: a -> a-> a
compare  a -> a > Ordering
show - udělá string


haskell napříště zásobník