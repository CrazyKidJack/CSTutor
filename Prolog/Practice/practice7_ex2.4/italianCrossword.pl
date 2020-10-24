word(astante,  a,s,t,a,n,t,e).
word(astoria,  a,s,t,o,r,i,a).
word(baratto,  b,a,r,a,t,t,o).
word(cobalto,  c,o,b,a,l,t,o).
word(pistola,  p,i,s,t,o,l,a).
word(statale,  s,t,a,t,a,l,e).

/*
crossword(
  word(V1, L1, L2, L3, L4, L5, L6, L7),
  word(V2, L8, L9, L10,L11,L12,L13,L14),
  word(V3, L15,L16,L17,L18,L19,L20,L21),
  
  word(H1, L22,L2,L23,L9, L24,L16,L25),
  word(H2, L26,L4,L27,L11,L28,L18,L29),
  word(H3, L30,L6,L31,L13,L32,L20,L33)
).
*/

not(Goal):-
  Goal,!,fail.
not(Goal).

crossword(V1,V2,V3, H1,H2,H3):-
  word(V1, L1, L2, L3, L4, L5, L6, L7),
  word(V2, L8, L9, L10,L11,L12,L13,L14),
  word(V3, L15,L16,L17,L18,L19,L20,L21),
  
  word(H1, L22,L2,L23,L9, L24,L16,L25),
  word(H2, L26,L4,L27,L11,L28,L18,L29),
  word(H3, L30,L6,L31,L13,L32,L20,L33),

  not(V1 = V2),
  not(V1 = V3),
  not(V1 = H1),
  not(V1 = H2),
  not(V1 = H3),
  
  not(V2 = V3),
  not(V2 = H1),
  not(V2 = H2),
  not(V2 = H3),
  
  not(V3 = H1),
  not(V3 = H2),
  not(V3 = H3),
  
  not(H1 = H2),
  not(H1 = H3),
  
  not(H2 = H3).

