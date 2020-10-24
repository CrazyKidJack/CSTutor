chair(1).
chair(2).
chair(3).
chair(4).
chair(5).
chair(6).
chair(7).

person('Amy').
person('Brad').
person('Beth').
person('Charles').
person('Debbie').
person('Emily').
person('Frances').

nextTo(X,Y):-
  

happy('Amy'):-
  nextTo('Amy','Alan'),
  NOTnextTo('Amy','Brad'),
  NOTnextTo('Amy','Beth'),
  NOTnextTo('Amy','Charles').

happy('Alan'):-
  next('Alan','Amy'),
  NOTnextTo('Alan','Brad'),
  NOTnextTo('Alan','Beth'),
  NOTnextTo('Alan','Debbie'),
  NOTnextTo('Alan','Emily').
  
happy('Brad'):-
  nextTo('Brad','Beth'),
  NOTnextTo('Brad','Charles'),
  NOTnextTo('Brad','Frances').
  
happy('Beth'):-
  nextTo('Beth','Brad').

happy('Charles'):-
  nextTo('Charles','Debbie');
  nextTo('Charles','Emily').

happy('Frances'):-
  nextTo('Frances','Debbie').
  
happy('Debbie'):-
  NOTnextTo('Debbie','Emily').
  
happy('Emily'):-
  NOTnextTo('Emily','Debbie').