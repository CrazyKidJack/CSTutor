point(_,_).
line(point(_,_), point(_,_)).

horizontal(line(point(X,_), point(X,_))).
vertical(line(point(_,Y), point(_,Y))).
