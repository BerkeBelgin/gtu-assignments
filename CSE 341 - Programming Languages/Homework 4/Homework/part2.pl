% knowledge base

flight(istanbul, rize).
flight(rize, van).
flight(istanbul, van).
flight(van, ankara).
flight(istanbul, ankara).
flight(istanbul, gaziantep).
flight(ankara, konya).
flight(konya, antalya).
flight(gaziantep, antalya).
flight(istanbul, antalya).
flight(istanbul, izmir).
flight(izmir, isparta).
flight(isparta, burdur).
flight(edirne, edremit).
flight(edremit, erzincan).
distance(istanbul, rize, 967).
distance(rize, van, 373).
distance(istanbul, van, 1262).
distance(van, ankara, 920).
distance(istanbul, ankara, 351).
distance(istanbul, gaziantep, 847).
distance(ankara, konya, 227).
distance(konya, antalya, 192).
distance(gaziantep, antalya, 592).
distance(istanbul, antalya, 482).
distance(istanbul, izmir, 328).
distance(izmir, isparta, 308).
distance(isparta, burdur, 24).
distance(edirne, edremit, 914).
distance(edremit, erzincan, 736).

% rules

path(X, Y, D) :-
    distance(X, Y, D);
    distance(Y, X, D).

froute(X, Y, D, V) :- 
	path(X, Z, Q),
	not(member(Z, V)),
	(
        (Y = Z, D is Q);
        (froute(Z, Y, Y, [X | V]), D is Y + Q)
    ).

mroute(X, Y, Ds) :-
    findall(
        D, froute(X, Y, D, []), Ds
    ).

route(X, Y, V) :- 
	path(X, Z, _),
	not(member(Z, V)),
	(
        Y = Z;
        route(Z, Y, [X | V])
    ).

sroute(X, Y, D) :-
    route(X, Y, []),
    mroute(X, Y, Ds),
    min_list(Ds, D).
