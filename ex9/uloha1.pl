city(bohumin, 22000).
city(ostrava, 250000).
city(praha,   1000000).
city(berlin,  3500000).

smaller(X,Y):-city(X, P1), city(Y, P2), P1<P2