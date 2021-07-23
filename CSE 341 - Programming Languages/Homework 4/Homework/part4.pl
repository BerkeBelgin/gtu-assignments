% rules

element(E, S) :-
    memberchk(E, S).


equivalent(S1, S2) :-
    permutation(S1, S2).


union([], S, S).

union([H1 | S1], S2, S3) :-
    element(H1, S2),
    !,
    union(S1, S2, S3).

union([H | S1], S2, [H | S3]) :-
    union(S1, S2, S3).


intersect([], _, []).

intersect([H1 | S1], S2, S3) :-
    element(H1, S2),
    !,
    S3 = [H1 | T3],
    intersect(S1, S2, T3).

intersect([_ | S1], S2, S3) :-
    intersect(S1, S2, S3).
