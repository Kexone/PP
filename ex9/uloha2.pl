female(amy).
female(johnette).
 
male(anthony).
male(bruce).
male(ogden).

parentof(amy,johnette).
parentof(amy,anthony).
parentof(amy,bruce).
parentof(ogden,johnette).
parentof(ogden,anthony).

siblingof(X,Y) :- parentof(Z,X), parentof(Z,Y).