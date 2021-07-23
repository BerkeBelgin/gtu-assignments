% facts

when(102,10).
when(108,12).
when(341,14).
when(455,16).
when(452,17).

where(102,z23).
where(108,z11).
where(341,z06).
where(455,207).
where(452,207).

enroll(a,102).
enroll(a,108).
enroll(b,102).
enroll(c,108).
enroll(d,341).
enroll(e,455).

% rules

schedule(S, P, T) :-
    enroll(S, C),
    when(C, T),
    where(C, P).

usage(P, T) :-
    where(C, P),
    when(C, T).

conflict(C1, C2) :-
	when(C1,T),
	when(C2,T),
	where(C1,P),
	where(C2,P).

meet(S1, S2) :-
    enroll(S1, C1),
    enroll(S2, C2),
    when(C1,T),
	when(C2,T),
	where(C1,P),
	where(C2,P).