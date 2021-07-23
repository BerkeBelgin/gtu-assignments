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

% rules

path(X, Y) :-
    flight(X, Y);
    flight(Y, X).

route(X, Y, V) :- 
	path(X, Z),
	not(member(Z, V)),
	(
        Y = Z ;
        route(Z, Y, [X | V])
    ).

route(X, Y) :-
    route(X, Y, []).
