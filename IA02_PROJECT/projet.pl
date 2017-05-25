:-dynamic(board_pieces/1).
%Variable dynamique contenant toutes les pieces
:-dynamic(board_coord_pieces_rouge/1).
%Variable dynamique contenant toutes les pieces rouges
:-dynamic(board_coord_pieces_ocre/1).
%Variable dynamique contenant toutes les pieces ocres
:-dynamic(kalista_rouge/1).
%Variable dynamique contenant true ou false si la kalista rouge existe ou non sur le jeu
:-dynamic(kalista_ocre/1).
%Variable dynamique contenant true ou false si la kalista ocre existe ou non sur le jeu
:-dynamic(khan/2).
%Variable dynamique contenant la couleur du Khan et sa position
:-dynamic(nbJoueurs/1).
%Variable dynamique contenant le nombre de joueurs humains
:-dynamic(board_coord_pieces_rouge_supprime/1).   
%Variable dynamique contenant toutes les pieces rouges que l'on supprime au fur et à mesure
:-dynamic(board_coord_pieces_ocre_supprime/1).
%Variable dynamique contenant toutes les pieces ocres que l'on supprime au fur et à mesure


reset :- consult('C:/Users/Jules/Desktop/IA02/Projet/projet.pl'), jeu.
%Pour ne pas avoir à refaire consult en permanence.

empty([]).
%True si la liste des vide

board_coord_pieces_rouge([]).
%board_coord_pieces_rouge([[1,2], [1,3], [1,5], [2,3], [5,4], [3,5]]).
board_coord_pieces_ocre([]).
board_pieces([[null,null,null,null,null,null],[null,null,null,null,null,null],[null,null,null,null,null,null],[null,null,null,null,null,null],[null,null,null,null,null,null],[null,null,null,null,null,null]]).	
kalista_rouge(true).
kalista_ocre(true).
khan(ocre, []). 
nbJoueurs(0).
board_coord_pieces_rouge_supprime([]).  
board_coord_pieces_ocre_supprime([]).
%Initialisation des différentes variables dynamiques


goto_coord_rouge(X) :- board_coord_pieces_rouge(Z),  retract(board_coord_pieces_rouge(Z)), asserta(board_coord_pieces_rouge(X)).
goto_coord_ocre(X) :- board_coord_pieces_ocre(Z),  retract(board_coord_pieces_ocre(Z)), asserta(board_coord_pieces_ocre(X)).
goto_kalista_rouge(X) :-kalista_rouge(Z), retract(kalista_rouge(Z)), asserta(kalista_rouge(X)).
goto_kalista_ocre(X) :-kalista_ocre(Z), retract(kalista_ocre(Z)), asserta(kalista_ocre(X)).
goto_khan(Joueur, List) :- khan(X, Y), retract(khan(X, Y)), asserta(khan(Joueur, List)).
goto_nbJoueurs(X) :- nbJoueurs(Z), retract(nbJoueurs(Z)), asserta(nbJoueurs(X)).
goto_coord_rouge_supprime(X) :- board_coord_pieces_rouge_supprime(Z), retract(board_coord_pieces_rouge_supprime(Z)), asserta(board_coord_pieces_rouge_supprime(X)).
goto_coord_ocre_supprime(X) :- board_coord_pieces_ocre_supprime(Z), retract(board_coord_pieces_ocre_supprime(Z)), asserta(board_coord_pieces_ocre_supprime(X)).
goto(X) :- board_pieces(Z), retract(board_pieces(Z)), asserta(board_pieces(X)).
%Les fonctions goto des variables dynamiques : On récupére la valeur, on enlève (retract) le prédicat actuel, on ajoute le nouveau prédicat avec le paramètre X.
	
		
board([[2,3,1,2,2,3],[2,1,3,1,3,1],[1,3,2,3,1,2],[3,1,2,1,3,2],[2,3,1,3,1,3],[2,1,3,2,2,1]]). 
%Constante contenant les valeurs des cases du plateau de jeu

replace([_|T], 0, X, [X|T]):- !.
replace([H|T], I, X, [H|R]):- I > -1, NI is I-1, replace(T, NI, X, R), !.
replace(L, _, _, L).
%remplacer la valeur de position I dans la liste par X et renvoie le résultat par dernier paramètre.

	
nieme(1,[X|_],X) :- !.
nieme(N,[_|R],X) :- Temp is N-1, nieme(Temp,R,X).	
%Récupére dans X le N ième élément de la liste R

verif_pion(U) :- U = null,!.
verif_pion(_) :-write('Deja un pion dans cette case, merci de faire plus attention, fermeture du programme'), fail. 
%Si U != null alors écris il y a déjà un pion dans cette case et ferme le programme

trouver_element_liste(K, J, I, Pion_joueur) :-  /*write(K),*/ nieme(J, K, U), Var is J-1, verif_pion(U), replace(K, Var, Pion_joueur, G), board_pieces(X), Var2 is I-1, replace(X, Var2, G, Z), /*write(Z),*/ goto(Z). /*Trouve l'élément U de la liste K à la place J */
trouver_liste(I, J, I, Pion_joueur) :- board_pieces(X), nieme(I, X, K),trouver_element_liste(K, J, I, Pion_joueur). %Trouve la liste K à la place I
placer_pion_liste(I,J, Pion_joueur) :- trouver_liste(I, J, I, Pion_joueur). %appelle la fonction qui va trouver dans la liste l'élément à la placer : liste I, élément J de cette liste
	
trouver_element_liste_2(K, J, I, Pion_joueur) :-  /*write(K),*/ nieme(J, K, _), Var is J-1, replace(K, Var, Pion_joueur, G), board_pieces(X), Var2 is I-1, replace(X, Var2, G, Z), /*write(Z),*/ goto(Z). /*Trouve l'élément U de la liste K à la place J */
trouver_liste_2(I, J, I, Pion_joueur) :- board_pieces(X), nieme(I, X, K),trouver_element_liste_2(K, J, I, Pion_joueur). %Trouve la liste K à la place I
placer_pion_liste_2(I,J, Pion_joueur) :- trouver_liste_2(I, J, I, Pion_joueur). %appelle la fonction qui va trouver dans la liste l'élément à la placer : liste I, élément J de cette liste

	
ajout_Queue([],X,[X]).
ajout_Queue([H|T],X,[H|L]):- ajout_Queue(T,X,L).
%ajoute dans le première paramètre, à la fin, l'élément X et met le résultat dans le troisième paramètre

copy(L,R) :- accCp(L,R).
accCp([],[]).
accCp([H|T1],[H|T2]) :- accCp(T1,T2).
%Copie L dans R

pion_or_kalista(6, pion_rouge, red_kalista):- !.
pion_or_kalista(6, pion_ocre, ocre_kalista):- !.
pion_or_kalista(Nombre, Pion_joueur, X) :- X = Pion_joueur-Nombre. 
%Créé le nom des pions.

placer_pions_bord(_, Nombre, _):- Nombre=7,!.	
placer_pions_bord(Bord, Nombre, Pion_joueur):- Nombre<7, Bord = 1, write('Quelle est la position de votre pion n':Nombre:' la colonne j (1 - 6) = '), read(J), write('  et la ligne i (1 - 2) = '),read(I), J <7, J > 0, I > 0, I < 3, integer(I), integer(J), pion_or_kalista(Nombre, Pion_joueur, X), placer_pion_liste(I,J, X), (Pion_joueur = pion_rouge -> ajouter_pion_list_rouge(I,J) ; ajouter_pion_list_ocre(I,J)), Tmp is Nombre + 1, nl, placer_pions_bord(1, Tmp, Pion_joueur).
placer_pions_bord(Bord, Nombre, Pion_joueur):- Nombre<7, Bord = 2, write('Quelle est la position de votre pion n':Nombre:' la colonne j (5 - 6) = '), read(J), write('  et la ligne i (1 - 6) = '),read(I), J <7, J > 4, I > 0, I < 7, integer(I), integer(J), pion_or_kalista(Nombre, Pion_joueur, X), placer_pion_liste(I,J, X), (Pion_joueur = pion_rouge -> ajouter_pion_list_rouge(I,J) ; ajouter_pion_list_ocre(I,J)), Tmp is Nombre + 1, nl, placer_pions_bord(2, Tmp, Pion_joueur).
placer_pions_bord(Bord, Nombre, Pion_joueur):- Nombre<7, Bord = 3, write('Quelle est la position de votre pion n':Nombre:' la colonne j (1 - 6) = '), read(J), write('  et la ligne i (5 - 6) = '),read(I), J <7, J > 0, I > 4, I < 7, integer(I), integer(J), pion_or_kalista(Nombre, Pion_joueur, X), placer_pion_liste(I,J, X), (Pion_joueur = pion_rouge -> ajouter_pion_list_rouge(I,J) ; ajouter_pion_list_ocre(I,J)), Tmp is Nombre + 1, nl, placer_pions_bord(3, Tmp, Pion_joueur).
placer_pions_bord(Bord, Nombre, Pion_joueur):- Nombre<7, Bord = 4, write('Quelle est la position de votre pion n':Nombre:' la colonne j (1 - 2) = '), read(J), write('  et la ligne i (1 - 6) = '),read(I), J <3, J > 0, I > 0, I < 7, integer(I), integer(J), pion_or_kalista(Nombre, Pion_joueur, X), placer_pion_liste(I,J, X), (Pion_joueur = pion_rouge -> ajouter_pion_list_rouge(I,J) ; ajouter_pion_list_ocre(I,J)), Tmp is Nombre + 1, nl, placer_pions_bord(4, Tmp, Pion_joueur).
%placer_pions_bord permet d'initialiser les pieces sur les lignes et colonnes en fonction du bord choisi

ajouter_pion_list_rouge(I,J) :-  board_coord_pieces_rouge(U), ajout_Queue(U, [I,J], List_result), goto_coord_rouge(List_result).
ajouter_pion_list_ocre(I,J) :-  board_coord_pieces_ocre(U), ajout_Queue(U, [I,J], List_result), goto_coord_ocre(List_result).
%Fonction qui nous permet d'accelerer le traitement de l'ajout d'un élément dans la liste correspondante

afficher_bords(_):-  write('B'), write('               B'), nl,
				 	 write('o'), write('               o'), nl,
					 write('r'), write('               r'), nl,
				 	 write('d'), write('               d'), nl,
					 write('4'), write('               2'), nl.
%afficher_bords affiche uniquement les bords pour l'utilisateur

%Display pour valeurs des cases + bords
affiche([]).
affiche([X|R]) :- write(X), affiche(R). %Affiche tous les éléments d'une liste

afficher_board([]).
afficher_board([A|B]) :- affiche(A), nl, afficher_board(B). %Affiche tous les éléments de l'ensemble des listes

display_board(_):- board(X), afficher_board(X). %Récupére les listes dans la constante board et appelle la fonction qui affichera celles ci


%Display pour les pions
affiche_pieces([]) :- !.
affiche_pieces([X|R]) :- (X = null -> write('       null      '); write('   '), write(X), write('   ')), /*(X = pion_rouge -> write('R ') ; (X = null -> write('N ') ; write('O '))),*/ affiche_pieces(R). %Affiche tous les éléments d'une liste
afficher_board_pieces([]) :- !.
afficher_board_pieces([A|B]) :- affiche_pieces(A), nl, afficher_board_pieces(B). %Affiche tous les éléments de l'ensemble des listes

display_pieces(_) :-board_pieces(X), afficher_board_pieces(X).
%Recuperer et aafiche toutes les pieces du jeu actuel

remplacer_pion_rouge(Coup1, Coup2) :- board_coord_pieces_rouge(X), subtract(X, [Coup1], Res1), ajout_Queue(Res1, Coup2, Res2), goto_coord_rouge(Res2).
remplacer_pion_ocre(Coup1, Coup2) :- board_coord_pieces_ocre(X), subtract(X,  [Coup1], Res1), ajout_Queue(Res1, Coup2, Res2), goto_coord_ocre(Res2).
%Supprime l'élément Coup1 de sa liste puis ajoute le Coup2 dans cette meme liste

suppression_pion_ocre(Coup2_X, Coup2_Y, Coup2_Value) :- (Coup2_Value = red_kalista -> goto_kalista_rouge(false) ; (Coup2_Value = ocre_kalista -> goto_kalista_ocre(false); (Coup2_Value \= null -> board_coord_pieces_ocre_supprime(X), ajout_Queue(X, [Coup2_X, Coup2_Y], Res), goto_coord_ocre_supprime(Res); true))).
suppression_pion_rouge(Coup2_X, Coup2_Y, Coup2_Value) :- (Coup2_Value = red_kalista -> goto_kalista_rouge(false) ; (Coup2_Value = ocre_kalista -> goto_kalista_ocre(false); (Coup2_Value \= null -> board_coord_pieces_rouge_supprime(X), ajout_Queue(X, [Coup2_X, Coup2_Y], Res), goto_coord_rouge_supprime(Res); true))).
%Supprime le coup (Cou2_X, Coup2_y) en le mettant dans la liste des pions supprimés correspondante. Si kalista, met à jour le prédicat la concernant

initBoard(NbJoueurs):-	write('      Bord1'), nl, afficher_bords(_), nl, write('      Bord3'), nl, display_board(_), write('Joueur Rouge, choisissez un bord (entre 1 et 4)'), read(X), X < 4, X > -1, integer(X), placer_pions_bord(X,1, pion_rouge), nl,
						write('Joueur Ocre, choisissez un bord (entre 1 et 4)'), read(Y), Y > -1, Y < 4, integer(Y), placer_pions_bord(Y,1, pion_ocre), display_pieces(NbJoueurs), (NbJoueurs \= 0 -> write('Joueur rouge, quel pion voulez vous jouer ?'), 
						nl, board_coord_pieces_rouge(List), print_pion_joueur_rouge(List, 1), length(List, Length), entree_pion_joueur_rouge(List, Length, Coup1, List_cases), print_cases_joueur_rouge(List_cases, 1), length(List_cases, Length_cases), 
						entree_cases_joueur_rouge(List_cases, Length_cases, Coup2), jouer_premier_coup(Coup1, Coup2), jouer(NbJoueurs);  board_coord_pieces_rouge(List_Pions_Res), write(List_Pions_Res),  nieme(1, List_Pions_Res, Valeur_De_Khan), goto_khan(ocre, Valeur_De_Khan), jouer(NbJoueurs)).
%initBoard est la fonction qui gére tout le plateau initial.
%Pas de khan au début donc le joueur rouge "fait" un premier coup exempt de toute condition. Il devient le khan et le jeu peut commencer.


print_pion_joueur_rouge([], _) :- !.
print_pion_joueur_rouge([H|T], Numero) :- write('Pion numero '), write(Numero), write(' : '), write(H), nl, Tmp is Numero+1, print_pion_joueur_rouge(T, Tmp).
%Affiche tous les pions et les numeros possibles

entree_pion_joueur_rouge(Res, Length, Coup, List_cases) :- write('Quel est le numero du pion que vous voulez jouer ? (Entre 1 et '),  write(Length), write(')'), read(Numero), integer(Numero), Numero > 0, Numero =< Length, nieme(Numero, Res, Coup), nieme(1, Coup, X), nieme(2, Coup, Y), recup_valeur_case(X, Y, Value), (Value =:= 1 -> generer_list_coup_1(X, Y, List_cases);(Value =:= 2 -> generer_list_coup_2_final(X, Y, List_cases) ; generer_list_coup_3_final(X, Y, List_cases))).
%Utilisateur saisit un pion

print_cases_joueur_rouge([], _) :- !.
print_cases_joueur_rouge([H|T], Numero) :- write('Case numero '), write(Numero), write(' : '), write(H), nl, Tmp is Numero+1, print_cases_joueur_rouge(T, Tmp).
%Affiche toutes les cases et les numeros possibles

entree_cases_joueur_rouge(Res, Length, Coup) :- write('Quel est le numero de la case pour y mettre le pion ? (Entre 1 et '),  write(Length), write(')'), read(Numero), integer(Numero), Numero > 0, Numero =< Length, nieme(Numero, Res, Coup).
%Utilisateur saisit une cases

jouer_premier_coup(Coup1, Coup2) :- nieme(1, Coup1, Coup1_X), nieme(2, Coup1, Coup1_Y), nieme(1, Coup2, Coup2_X), nieme(2, Coup2, Coup2_Y), recup_pion_case(Coup1_X, Coup1_Y, Coup1_Value),  placer_pion_liste_2(Coup1_X, Coup1_Y, null), placer_pion_liste_2(Coup2_X, Coup2_Y, Coup1_Value), remplacer_pion_rouge(Coup1, Coup2), goto_khan(rouge, Coup2), write('Premier coup effectue, place au jeu !'), nl.
%Appelle tous les prédicats nécessaires à la mise des listes. Coup1 est l'origine et Coup2 la destination

inserer_debut(X,List,[X|List]).
%insere au début de Liste l'élément X et met le résultat dans le troisième paramètre

%generer_list_coup_2_1([[1,2],[2,3]],[[[3,3],[1,3],[2,4],[2,2]],[[2,2],[1,3],[1,1]]])	

generer_list_coup_1_partiel(I, J, List) :- Var1 is I+1, ((Var1 <7, Var1 > 0) -> ajout_Queue([], [Var1, J], Res_1); copy([], Res_1)),
											  Var2 is I-1, ((Var2 <7, Var2 > 0) -> ajout_Queue(Res_1, [Var2, J], Res_2);  copy(Res_1, Res_2)),
											  Var3 is J+1, ((Var3 <7, Var3 > 0) -> ajout_Queue(Res_2, [I, Var3], Res_3); copy(Res_2, Res_3)),
											  Var4 is J-1, ((Var4 <7, Var4 > 0) -> ajout_Queue(Res_3, [I, Var4], List); copy(Res_3, List)). 
%Predicat non recursif pour recuperer tous les coups de value 1


generer_list_coup_1(I, J, Res) :- generer_list_coup_1_partiel(I,J,List), khan(X,_), (X = rouge -> board_coord_pieces_ocre(List_Res); board_coord_pieces_rouge(List_Res)), subtract(List, List_Res, Res).
%Version recursive probablement possible mais pas trouvee par nous.
								   
generer_list_coup_2_1([], []) :- !.
generer_list_coup_2_1([H|T], List_Result):- nieme(1, H, I), nieme(2, H, J), generer_list_coup_1(I, J, Result), nl, generer_list_coup_2_1(T, Tmp), ajout_Queue(Tmp, Result, List_Result).
%Predicat recursif pour recuperer tous les coups de value 2

generer_list_coup_3_2([], []) :- !.
generer_list_coup_3_2([H|T], List_Result):- nl, generer_list_coup_2_1(H, Result), generer_list_coup_3_2(T, Tmp), ajout_Queue(Tmp, Result, List_Result).
%Predicat recursif pour recuperer tous les coups de value 3

generer_list_coup_2(I, J, Result) :- generer_list_coup_1(I, J, Res1), generer_list_coup_2_1(Res1, Result).
%On appelle generer_list_coup avec 1 puis 2 sur cette liste prédécedente, Result est le résultat
generer_list_coup_3(I, J, Result) :- generer_list_coup_1(I, J, Res1), generer_list_coup_2_1(Res1, Res2), generer_list_coup_3_2(Res2, Result).
%On appelle generer_list_coup avec 1 puis 2 sur cette liste précédente et enfin 3 sur cette liste prédécedente, Result est le résultat

subtract_rec(_, _, [], []) :- !.
subtract_rec(I, J, [H|T], Resultat) :- subtract(H, [[I,J]], Tmp), subtract_rec(I, J, T, Result), ajout_Queue(Result, Tmp, Resultat).
%Supprime tous les doublons [I,J] dans la liste en deuxième paramètre et place le tout dans Resultat 

recreer_list_from_flatten([] ,[]) :-!.
recreer_list_from_flatten([X,Y|XYs],[[X,Y]|As]) :- recreer_list_from_flatten(XYs,As).
%Après flatten, recreer une liste en associant les elements deux à deux

delete_retours(I, J, To_Delete, Result) :- Var1 is I+1, Var2 is I-1, Var3 is J+1, Var4 is J-1, subtract(To_Delete, [[Var1, J]], Res1), subtract(Res1, [[Var2, J]], Res2), subtract(Res2, [[I, Var3]], Res3), subtract(Res3, [[I, Var4]], Result).
%Supprime les retours de 1 = retour à la place de départ [I,J], place le resultat dans Result

generer_list_coup_2_partiel(I, J, Result) :- generer_list_coup_2(I, J, Res), subtract_rec(I, J, Res, To_Flatten), flatten(To_Flatten, To_Recreer), recreer_list_from_flatten(To_Recreer, To_Sort), sort(To_Sort, Result). %reverse(To_Reverse, Result). %Result = liste sans les retours sur la place de départ.
generer_list_coup_3_partiel(I, J, Result) :- generer_list_coup_3(I, J, Res), subtract_rec(I, J, Res, To_Flatten), flatten(To_Flatten, To_Recreer), recreer_list_from_flatten(To_Recreer, To_Sort), sort(To_Sort, To_Delete), delete_retours(I, J, To_Delete, Result). %Result = liste sans les retours sur la place de départ.
%On utilise tous les prédicats précédents pour former tous les coups de value 2 à partir de la case [I,J] et place le tout dans Result

generer_list_coup_2_final(I, J, Result) :- generer_list_coup_2_partiel(I,J,List),khan(X,_), (X = rouge -> board_coord_pieces_ocre(List_Res); board_coord_pieces_rouge(List_Res)), subtract(List, List_Res, Result).
generer_list_coup_3_final(I, J, Result) :- generer_list_coup_3_partiel(I,J,List),khan(X,_), (X = rouge -> board_coord_pieces_ocre(List_Res); board_coord_pieces_rouge(List_Res)), subtract(List, List_Res, Result).
%Predicat final, on utilise le partiel et on enlève les pions de sa couleur, on ne peut pas prendre ses propres pions !

intersection([], _, []) :- !.
intersection([X|T], L, Intersect) :-
	memberchk(X, L), !,
	Intersect = [X|R],
	intersection(T, L, R).
intersection([_|T], L, R) :-
	intersection(T, L, R).
%Predicat qui fait l'intersection entre deux listes.
	
	
union([], L, L).
union([Head|L1tail], L2, L3) :-
        memberchk(Head, L2),
        !,
        union(L1tail, L2, L3).
union([Head|L1tail], L2, [Head|L3tail]) :-
        union(L1tail, L2, L3tail).
%Predicat qui fait l'union entre deux listes.

get_list_value_case([], []) :- !.
get_list_value_case([H|T], Result) :- nieme(1, H, I), nieme(2, H, J), board(X), nieme(I, X, Res), nieme(J, Res, Value), get_list_value_case(T, Tmp), ajout_Queue(Tmp, Value, Result).
%Récupére toutes les values des pions dans la première liste. Place le tout dans Result

get_list_value_case_with_parameter([], [], _) :- !.
get_list_value_case_with_parameter([H|T], Result, Valeur) :- nieme(1, H, I), nieme(2, H, J), board(X), nieme(I, X, Res), nieme(J, Res, Value), get_list_value_case_with_parameter(T, Tmp, Valeur), (Value =:= Valeur , ajout_Queue(Tmp, [I,J], Result); transmet([],Tmp,Result)), !.
transmet([],Y,Y).   %Quand Value /= Valeur, on juste transmet la valeur à resultat.
%Idem que le prédicat précédent mais avec un paramètre supplémentaire qui nous permet de spécifier la value que l'on garder



verif_khan_type_case(I, J, List, List_Result) :- get_list_value_case(List, Result), board(X), nieme(I, X, Res), nieme(J, Res, Value), intersection(Result, [Value], List_Resultat), length(List_Resultat, Length), Length > 0 -> get_list_value_case_with_parameter(List, List_Result, Value); List_Result = [].
%verif_khan_type_case(I du khan, J du khan, List des pions du joueur rouge ou ocre, List_Result) 
%Recupere dans List_Result, la liste des pions du joueur rouge ou ocre qui respectent le khan

/*test :- goto_khan(rouge, [1,1]), goto_coord_ocre([[1,5]]), goto_coord_rouge([[6,6], [5,6], [6,1]]).
test2(X):- get_list_value_case([[1,2], [1,3], [1,5], [2,3], [5,4], [3,5]], X).
test3(X) :-verif_khan_condition_2_bis_3([[1,3], [2,5], [1,6], [2,3], [4,5]], X).*/
%Pour nos tests

/*
verif_chemin_pion_value_3(CoordX_Origin, CoordY_Origin, CoordX_Destination, CoordY_Destination, Resultat) :- generer_list_coup_2_final(CoordX_Origin, CoordY_Origin, Res1), generer_list_coup_1(CoordX_Origin, CoordY_Origin, Res2), intersection(Res1, Res2, Res3), intersection(Res3, [[CoordX_Destination,CoordY_Destination]], Resultat).
verif_chemin_pion_value_2(CoordX_Origin, CoordY_Origin, CoordX_Destination, CoordY_Destination, Resultat) :- generer_list_coup_1(CoordX_Origin, CoordY_Origin, Res), intersection(Res, [[CoordX_Destination,CoordY_Destination]], Resultat).
% Si jamais Resultat > 0, le passage est bouché*/

verif_khan_condition_1(Boolean_possible) :- khan(X, List), nieme(1, List, KhanX), nieme(2, List, KhanY), (X = rouge -> board_coord_pieces_ocre(List_pions); board_coord_pieces_rouge(List_pions)), verif_khan_type_case(KhanX, KhanY, List_pions, Result), length(Result, Length), nl, (Length > 0 -> Boolean_possible = true ; Boolean_possible = false).
%True si il respecte le khan
   
verif_khan_condition_2_bis_1(X, X).
%Verif la condition 2 pour un coup de value 1

verif_khan_condition_2_bis_2([],[]) :- !.    
verif_khan_condition_2_bis_2([H|T], List_Result) :- nieme(1, H, X), nieme(2, H, Y), generer_list_coup_1(X, Y, Res), board_coord_pieces_ocre(List_pions_ocre), board_coord_pieces_rouge(List_pions_rouge), union(List_pions_ocre, List_pions_rouge, Res_To_Sub), subtract(Res_To_Sub, [H], Resultat), intersection(Res, Resultat, List_Resultante), verif_khan_condition_2_bis_2(T, Tmp), length(List_Resultante, Length), ( Length > 0 -> ajout_Queue(Tmp, List_Resultante, List_Result);  transmet([],Tmp,List_Result)).
%Verif la condition 2 pour un coup de value 2

verif_khan_condition_2_bis_3([],[]) :- !.    
verif_khan_condition_2_bis_3([H|T], List_Result) :- nieme(1, H, X), nieme(2, H, Y), generer_list_coup_1(X, Y, Res1), generer_list_coup_2_final(X, Y, Res2), union(Res1, Res2, Res3), board_coord_pieces_ocre(List_pions_ocre), board_coord_pieces_rouge(List_pions_rouge), union(List_pions_ocre, List_pions_rouge,Res_To_Sub), subtract(Res_To_Sub, [H], Res4), intersection(Res3, Res4, List_Resultante), verif_khan_condition_2_bis_3(T, Tmp), length(List_Resultante, Length), ( Length > 0 -> ajout_Queue(Tmp, List_Resultante, List_Result);  transmet([],Tmp,List_Result)).
%Verif la condition 2 pour un coup de value 3

verif_khan_condition_2(Boolean_possible) :- khan(X, List), nieme(1, List, KhanX), nieme(2, List, KhanY), recup_valeur_case(KhanX, KhanY, Value), (X = rouge -> board_coord_pieces_ocre(List_pions); board_coord_pieces_rouge(List_pions)), verif_khan_type_case(KhanX, KhanY, List_pions, List_Resultante), (Value =:= 1 -> verif_khan_condition_2_bis_1(List_Resultante, List_Result);( Value =:= 2 -> verif_khan_condition_2_bis_2(List_Resultante, List_Result); verif_khan_condition_2_bis_3(List_Resultante, List_Result))), length(List_Result, Length), (Length > 0 -> (  Boolean_possible = false ); Boolean_possible = true).
%Version actuelle de la condition 2, appelle tous les prédicats précédents, renvoie TRUE si les pions du joueur vérifie la condition 2 ou non

verif_khan(_) :- verif_khan_condition_1(Bool1), verif_khan_condition_2(Bool2), (Bool1 = true, Bool2 = true) ->  respecter_le_khan(2); ne_pas_respecter_le_khan(2).
%Coup du joueur humain, appellée par la boucle principale jouer(NbJoueurs).

/*
*****

Joueur humain

Joueur humain

*****
*/


respecter_le_khan(_) :- recup_list_rouge_or_ocre(List, Valeur), get_list_value_case_with_parameter(List, Res, Valeur), nbJoueurs(Nombre), length(Res, Length), nl, proposer_pions_joueur(Res, 0,Length), entree_pion_joueur(List, Length, Pion).
%Condition 1 et 2 sont à TRUE donc on peut proposer tous les pions.

proposer_pions_joueur([], Length, Length) :- !.
proposer_pions_joueur([H|T], Number, Length) :- write('Pion numero '), Tmp is Number+1, write(Tmp),	write(' : '), nieme(1, H, X), nieme(2, H, Y), recup_pion_case(X, Y, Pion), write(Pion), nl, proposer_pions_joueur(T, Tmp, Length).
%On affiche tous les pions de la liste en premier paramètre

entree_pion_joueur(Res, Length, Coup) :- write('Quel est le numero du pion que vous voulez jouer ? (Entre 1 et '),  write(Length), write(')'), read(Numero), integer(Numero), Numero > 0, Numero =< Length, nieme(Numero, Res, Coup), nieme(1, Coup, X), nieme(2, Coup, Y), recup_valeur_case(X, Y, Value), (Value =:= 1 -> generer_list_coup_1(X, Y, Liste_Resultante);(Value =:= 2 -> generer_list_coup_2_final(X, Y, Liste_Resultante) ; generer_list_coup_3_final(X, Y, Liste_Resultante))), length(Liste_Resultante, Length_2), proposer_coups_joueur(Liste_Resultante, 0, Length_2), entree_coup_joueur(Liste_Resultante, Length_2, Coup).
%On read le numero du pion que l'humain veut jouer

proposer_coups_joueur([], Length, Length) :- !.
proposer_coups_joueur([H|T], Numero, Length) :- write('Coup numero '), Tmp is Numero+1, write(Tmp), write(' : '), write(H), nl, proposer_coups_joueur(T, Tmp, Length).
%On affiche toutes les cases de la liste en premier paramètre, en fonction du pion préalablement choisi

entree_coup_joueur(Res, Length, Coup_1) :- write('Quel est le numero de la case vous voulez deplacer le pion ? (Entre 1 et '),  write(Length), write(')'), read(Numero), integer(Numero), Numero > 0, Numero =< Length, nieme(Numero, Res, Coup_2), lancer_action(Coup_1, Coup_2).
%On read le numero de la case que l'humain veut jouer

lancer_action(Coup1, Coup2) :- khan(Khan, _), nieme(1, Coup1, Coup1_X), nieme(2, Coup1, Coup1_Y), nieme(1, Coup2, Coup2_X), nieme(2, Coup2, Coup2_Y), recup_pion_case(Coup2_X, Coup2_Y, Coup2_Value), (Khan = rouge -> suppression_pion_ocre(Coup2_X, Coup2_Y, Coup2_Value);  suppression_pion_rouge(Coup2_X, Coup2_Y, Coup2_Value)),recup_pion_case(Coup1_X, Coup1_Y, Coup1_Value),  placer_pion_liste_2(Coup1_X, Coup1_Y, null), placer_pion_liste_2(Coup2_X, Coup2_Y, Coup1_Value), (Khan = rouge -> remplacer_pion_ocre(Coup1, Coup2); remplacer_pion_rouge(Coup1, Coup2)), khan(X, Y), (X = rouge -> goto_khan(ocre, Coup2); goto_khan(rouge, Coup2)), write('Coup effectue !').
%On déplace le pion du Coup1 vers le Coup2. On met à jour les listes le concernant ainsi que la kalista.

/*

FAIT PAR LUCAS 

*/
ne_pas_respecter_le_khan(_) :- verif_khan_lucas(Lucas).
%Condition 1 ou 2 n'est pas TRUE donc on ne peut pas respecter le khan

get_tous_possible_case(7, 1, _, Tmp, Tmp):- !.
get_tous_possible_case(Index, Index_ver, Valeur, Tmp, Result):- Index < 7, (Index_ver < 7 -> board(X), nieme(Index,X,Res), nieme(Index_ver,Res,Value), (Value =:= Valeur -> ajout_Queue(Tmp,[Index,Index_ver], Result_Tmp), Index_ver_plus is Index_ver + 1, get_tous_possible_case(Index, Index_ver_plus, Valeur, Result_Tmp, Result); Index_ver_plus is Index_ver + 1, get_tous_possible_case(Index, Index_ver_plus, Valeur, Tmp, Result) ); Index_plus is Index + 1, Index_ver_plus is 1, get_tous_possible_case(Index_plus, Index_ver_plus, Valeur, Tmp, Result)).
%Par rapport à ce prédicat, on veut trouver toutes les cases qui ont la même valeur. Parce que notre board est 6*6, il ira jusqu'à 7,1. 

get_case(Index,Index_ver,Valeur,Tmp,Result):- get_tous_possible_case(Index, Index_ver, Valeur, Tmp, Result), afficher(Result).
% Pour afficher le résultat.

verif_khan_lucas(_) :-  khan(X, _), (X = rouge ->  board_coord_pieces_ocre_supprime(List) ; board_coord_pieces_rouge_supprime(List)), length(List, Length), (Length =:= 0 -> condition_3(Nouveau_List), nieme(1,Nouveau_List,Tmp1), nieme(2,Nouveau_List,Tmp2), recup_valeur_case(Tmp1,Tmp2,Valeur), write(Valeur), recup_pion_case(Tmp1,Tmp2,Nom_Pion), possible_move(Tmp1, Tmp2, Valeur, Result), nl, nouveau_afficher(Result,1), read(Num_Case), nieme(Num_Case,Result,Pos_Case), verif_kalista_delete(Pos_Case), gagnant(1),suppression_pion(Nouveau_List), suppression_pion_ancien(Nouveau_List),verif_case(Pos_Case,Nom_Pion), board_pieces(List_Resultante), write(List_Resultante) ; write('choisit condition3 ou condition 4: '), nl, write('condition 3:  Bouger une autre pièce.'), nl, write('condition 4 : Remettre un pion supprimé sur le board.'), nl, write('Votre choix?'), read(Con), (Con = 3 ; Con = 4), (Con =:= 3 -> condition_3(Nouveau_List), write(Nouveau_List), nieme(1,Nouveau_List,Tmp1), nieme(2,Nouveau_List,Tmp2), recup_valeur_case(Tmp1,Tmp2,Valeur), write(Valeur), recup_pion_case(Tmp1,Tmp2,Nom_Pion), write(Nom_Pion), possible_move(Tmp1, Tmp2, Valeur, Result), nl, nouveau_afficher(Result,1), read(Num_Case), nieme(Num_Case,Result,Pos_Case), verif_kalista_delete(Pos_Case), gagnant(2),suppression_pion(Nouveau_List),  suppression_pion_ancien(Nouveau_List),verif_case(Pos_Case,Nom_Pion), board_pieces(List_Resultante), write(List_Resultante), nl;  condition_4(_))).
%Ce prédicat est le plus important. Ce prédicat est utilisé pour donner lau joueur deux choix s’il ne respecte pas le khan. 
%D’abord, on va vérifier s’il y a un pion dans le tableau supprime(Si le khan est rouge, on vérifie le tableau supprime d’ocre). 
%Après, le joueur va choisir un pion. Pour le condition 3, on obtient la position du pion que le joueur a choisit via le prédicat condition_3(..). 
%Et on traite cette position dans ce prédicat. Il va générer toutes les cases auxqulles il peut accéder par rapport au type de case de ce pion. Le joueur va en choisir une. 
%On va vérifie si dans cette case, il y a déjà un pion ou pas. Pour tous les pions supprimés, il faut ajouter la position de pion ou supprimer la position du tableau supprime. 
%On ajoute ce pion dans la liste des coordonnées du pion de la couleur actuelle. Il faut aussi renouveler la situation de board_pieces. 
%Pour la condition 4, on réalise toutes les fonctionnalités dans le prédicat condition_4(_).  

get_value_case_khan(Tmp1, Tmp2, Valeur):- khan(X,List), nieme(1,List,Tmp1), nieme(2,List,Tmp2), board(Y), nieme(Tmp1,Y,Res), nieme(Tmp2,Res,Valeur).
%Par ce prédicat, je veux obtenir le type de case du Khan.

possible_move(I, J, Valeur, Result):- (Valeur =:= 1 -> generer_list_coup_1(I, J, Result); (Valeur =:= 2 -> generer_list_coup_2_final(I,J,Result) ; generer_list_coup_3_final(I,J,Result))).
%Par ce prédicat, on va générer tous les moves possibles par rapport à l'entrée = valeur de la case.

verif_case(Pos_Case,Nom_Pion_Change):- khan(Y, List), (Y = rouge -> goto_khan(ocre, Pos_Case), board_coord_pieces_ocre(Z), ajout_Queue(Z, Pos_Case, Result), goto_coord_ocre(Result) ; goto_khan(rouge, Pos_Case), board_coord_pieces_rouge(Z), ajout_Queue(Z, Pos_Case, Result), goto_coord_rouge(Result)), nieme(1,Pos_Case,PC1), nieme(2,Pos_Case,PC2), board_pieces(X), nieme(PC1,X,Tmp), nieme(PC2,Tmp,Res), (Res = null -> placer_pion_liste_2(PC1,PC2,Nom_Pion_Change); khan(B,List_2), (B = ocre -> suppression_pion(Pos_Case), board_coord_pieces_rouge_supprime(C), ajout_Queue(C, Res, Result_Sup), goto_coord_rouge_supprime(Result_Sup), placer_pion_liste_2(PC1,PC2,Nom_Pion_Change) ; suppression_pion(Pos_Case), board_coord_pieces_ocre_supprime(C), ajout_Queue(C, Res, Result_Sup), goto_coord_ocre_supprime(Result_Sup), placer_pion_liste_2(PC1,PC2,Nom_Pion_Change))).
%Dans ce prédicat, on entre la position de la case à laquelle le joueur veut accéder et le nom de pion que le joueur choisit de bouger. 
%D’abord, cette position va devenir le nouveau khan. Après, il faut placer ce pion à la nouvelle case.
%Mais on doit vérifier s’il y a déjà un pion sur cette case. Si oui, on doit supprimer la position de ce pion de tableau et 
%on ajoute le nom de ce pion dans le tableau supprime. Sinon, on place directement le pion que le joueur avait choisit. 


get_list_value_case_with_parameter_condition3([], [], _) :- !.
get_list_value_case_with_parameter_condition3([H|T], Result, Valeur) :- nieme(1, H, I), nieme(2, H, J), board(X), nieme(I, X, Res), nieme(J, Res, Value), get_list_value_case_with_parameter_condition3(T, Tmp, Valeur), (Value =\= Valeur ->  ajout_Queue(Tmp, [I,J], Result); transmet([],Tmp,Result)).
%Pour réaliser le condition 3, le joueur peut choisir les pions dont les valeurs ne sont pas égale à 'valeur' entrée.
%Donc, tous les cases que l'on obtient ont le type de case différent du type de case du khan.

condition_3(Nouveau_List):- khan(X, List), nieme(1, List, KhanX), nieme(2, List, KhanY), recup_valeur_case(KhanX,KhanY,Value), nl, (X = rouge -> board_coord_pieces_ocre(List_pions), get_list_value_case_with_parameter_condition3(List_pions, Result, Value), nl, write('Choisir le numero du pion: '), nl, nouveau_afficher(Result,1), read(Numero), nieme(Numero,Result,Nouveau_List); board_coord_pieces_rouge(List_pions), get_list_value_case_with_parameter_condition3(List_pions, Result, Value), nl, write('Choisir le numero du pion: '), nl, nouveau_afficher(Result,1), read(Numero), nieme(Numero,Result,Nouveau_List)).
%Ce prédicat est pour trouver tous les cases dont le type de case est différent de type de case de khan.
%Et on affiche toutes les cases que l'on trouve et le joueur va en choisir une. Et ce prédicat va renvoyer cette case. 
%On va traiter cette case dans le prédicat vérif_khan_lucas.

condition_4(_):- khan(X, List), (X = rouge -> board_coord_pieces_ocre_supprime(Y), nl, write('Choisir le numero de pion que vous voulez jouer :'),
 nl, nouveau_afficher(Y,1), read(Val_pion), nieme(Val_pion, Y, Res_Tmp), subtract(Y, [Res_Tmp], N_Sup), goto_coord_ocre_supprime(N_Sup),
 khan(X_Khan, List_Khan), nieme(1, List_Khan, Khan_X), nieme(2, List_Khan, Khan_Y),
 recup_valeur_case(Khan_X, Khan_Y, Khan_Valeur), get_tous_possible_case(1,1,Khan_Valeur,[],Resultante), board_coord_pieces_ocre(L1), 
 board_coord_pieces_rouge(L2), union(L1,L2,L3), subtract(Resultante,L3, Result), write('Le khan choisit une case:'), nl, nouveau_afficher_2(Result,1), 
 read(Pos_Case), nieme(Pos_Case, Result, Nouveau_Position), verif_kalista_delete(Nouveau_Position), gagnant(1), 
 goto_khan(rouge, Nouveau_Position), board_coord_pieces_ocre(Z),  ajout_Queue(Z, Nouveau_Position, Z_Y), goto_coord_ocre(Z_Y), board_coord_pieces_ocre(A),write(A), nl, 
 nieme(1,Nouveau_Position,NP1), nieme(2,Nouveau_Position,NP2),  recup_pion_case(NP1, NP2, Res), (Res = null -> placer_pion_liste_2(NP1,NP2,Res_Tmp);
 suppression_pion(Nouveau_Position), board_coord_pieces_rouge_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_ocre_rouge(Res_S),
 placer_pion_liste_2(NP1, NP2, Res_Tmp);
 
 suppression_pion(Nouveau_Position), board_coord_pieces_rouge_supprime(C),
 ajout_Queue(C,Res,Res_S), goto_coord_rouge_supprime(Res_S), placer_pion_liste_2(NP1, NP2, Res_Tmp)) ;
 
 board_coord_pieces_rouge_supprime(Y), write('Y: '), write(Y), nl, write('Choisir le numero du pion :'),
 nl, nouveau_afficher(Y,1), read(Val_pion), nieme(Val_pion, Y, Res_Tmp), subtract(Y, [Res_Tmp], N_Sup), write('N_Sup = '),
 write(N_Sup), goto_coord_rouge_supprime(N_Sup), khan(X_Khan, List_Khan), nieme(1, List_Khan, Khan_X), nieme(2, List_Khan, Khan_Y),
 recup_valeur_case(Khan_X, Khan_Y, Khan_Valeur), get_tous_possible_case(1,1,Khan_Valeur,[],Resultante), board_coord_pieces_ocre(L1), 
 board_coord_pieces_rouge(L2), union(L1,L2,L3), subtract(Resultante,L3, Result), write('Le khan choisit une case:'), nl, nouveau_afficher_2(Result,1), 
 read(Pos_Case), nieme(Pos_Case, Result, Nouveau_Position), verif_kalista_delete(Nouveau_Position), gagnant(1), 
 goto_khan(rouge, Nouveau_Position), board_coord_pieces_rouge(Z),  ajout_Queue(Z, Nouveau_Position, Z_Y), goto_coord_rouge(Z_Y), board_coord_pieces_rouge(A),write(A), nl, 
 nieme(1,Nouveau_Position,NP1), nieme(2,Nouveau_Position,NP2),  recup_pion_case(NP1, NP2, Res), (Res = null -> placer_pion_liste_2(NP1,NP2,Res_Tmp);
 suppression_pion(Nouveau_Position), board_coord_pieces_ocre_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_ocre_supprime(Res_S),
 placer_pion_liste_2(NP1, NP2, Res_Tmp))). 
 %Pour condition 4, d’abord, on obtient tous les pions supprimés qui sont conservés dans le tableau supprime.
 %Le joueur va en choisir un. Ensuite, par rapport au type de case du khan, on va chercher toutes les cases qui ont le même type que la case du khan. 
 %On va parcourir le board_pieces. On installe deux constantes: Un est lorsqu'il n’y a pas de pion sur la case; Deux lorsque l'on ne peut pas choisir une case sur laquelle la kalista est placée.
 %Enfin, le joueur va choisir une case pour y accéder. L’ajout et la suppression sont les mêmes que la condition3.
 
verif_kalista_delete(Nouveau_List) :- nieme(1, Nouveau_List, Coup_X), nieme(2, Nouveau_List, Coup_Y), recup_pion_case(Coup_X, Coup_Y, Coup_Value), (Coup_Value = red_kalista -> goto_kalista_rouge(false) ; (Coup_Value = ocre_kalista -> goto_kalista_ocre(false); true)).
%Update les predicats red_kalista et ocre_kalista en fonction de la valeur Nouveau_List

nouveau_afficher([],_):- !.
nouveau_afficher([H|T],Index):- write('La case numero '), write(Index), write(':'), write(H), nl, Index_plus is Index + 1, nouveau_afficher(T,Index_plus).
			%Pour condition4
nouveau_afficher_2([],_):- !.
nouveau_afficher_2([H|T],Index):- write('La case numero '), write(Index), write(':'), write(H), nl, Index_plus is Index + 1, nouveau_afficher_2(T,Index_plus).
%C’est pour afficher toutes les cases que l'on obtient avec un meilleur aspect

element(Pion, [Pion|_], 1).
element(Pion, [T|Q], Valeur):- Pion \= T, element(Pion, Q, Valeur_moins), Valeur is Valeur_moins + 1.
%Ce prédicat est pour obtenir la valeur de la position de l'élément  d’une liste.

remove_at(Pion,[Pion|Reste],1,Reste). 
remove_at(Pion,[Y|Reste],Position,[Y|Ys]) :- Position > 1, K1 is Position - 1, remove_at(Pion,Reste,K1,Ys).
%Ce prédicat est pour supprimer un élément dans une liste par rapport à la valeur entrée.(Elle est transmets par la variable Position).

suppression_pion(Nouveau_List):- khan(X,List), (X = rouge -> board_coord_pieces_ocre(Y), element(Nouveau_List,Y,Valeur), remove_at(Nouveau_List, Y, Valeur, Result), goto_coord_ocre(Result), board_coord_pieces_ocre(Z), write(Z); board_coord_pieces_rouge(Y), element(Nouveau_List,Y,Valeur), remove_at(Nouveau_List, Y, Valeur, Result), goto_coord_rouge(Result), board_coord_pieces_rouge(Z), write(Z)). 
%Ce prédicat est pour supprimer une valeur de position de pion du tableau(board_coord_pieces_rouge par exemple.). Il utilise les deux prédicats prédents(element et remove_at).

suppression_pion_ancien(List_Ancien):- nieme(1,List_Ancien,LA1), nieme(2,List_Ancien,LA2), board_pieces(X), nieme(LA1,X,Res_Tmp), Tmp1 is LA1 - 1, Tmp2 is LA2 - 1, replace(Res_Tmp, Tmp2, null, Res_Tmp_2), replace(X, Tmp1, Res_Tmp_2, Result), goto(Result).
%Ce prédicat est pour supprimer un pion de board_pieces. Il va remplacer le pion que l'on veut supprimer par la valeur ‘null’. 
%Et il va remplacer un élément de board_pieces par le nouvel élément. 
%Et ce élément conserve tous les pions que l'on ne supprime pas et la valeur null dans la position de pion que l'on a déjà supprimé.
%Donc, ici, j’utilise deux fois replace. Une pour remplacer une valeur dans une liste.
%Une autre est pour remplacer une liste de board_pieces(On a 6 sous-listes dans board_pieces).
%Et on utilise le predicat nieme avant Tmp1 is LA1 - 1 parce que sinon on a soucis lorsque que LA1 est égale à 1, quand on fait moins 1, cela donne 0. 
%Mais notre prédicat nieme ne peut pas vérifier le cas avec 0 en premier paramètre


/*

FAIT PAR LUCAS 

*/


 /*
*****

*****
*/

 
recup_list_rouge_or_ocre(List_pions, Valeur) :- khan(X, List), nieme(1, List, KhanX), nieme(2, List, KhanY), recup_valeur_case(KhanX, KhanY, Valeur), (X = rouge -> board_coord_pieces_ocre(List_pions); board_coord_pieces_rouge(List_pions)).
%Recupere la liste des pions en fonction du Khan ainsi que la valeur du khan actuel. La liste est placée dans List_Pions et la valeur dans Valeur.

/*
*****

IA

STRATEGIE IDIOTE : choisi le premier élément

Tous les read() sont enlevés et on prend le première élément.
Seule différence notable : si il y a des éléments dans le tableau contenant les pions supprimés du joueur actuel, on choisit la condition 4 plutot que la condition 3.

IA

*****
*/


verif_khan_ordi(_) :- verif_khan_condition_1(Bool1), verif_khan_condition_2(Bool2), write(Bool1), write(Bool2), (Bool1 = true, Bool2 = true) ->  respecter_le_khan_ordi(Res); ne_pas_respecter_le_khan_ordi(Res).

respecter_le_khan_ordi(Res) :- recup_list_rouge_or_ocre(List, Valeur), get_list_value_case_with_parameter(List, Res, Valeur), nbJoueurs(Nombre), length(Res, Length), nl, proposer_pions_joueur_ordi(Res, 0,Length), entree_pion_joueur_ordi(List, Length, Pion).

proposer_pions_joueur_ordi([], Length, Length) :- !.
proposer_pions_joueur_ordi([H|T], Number, Length) :- write('Pion numero '), Tmp is Number+1, write(Tmp),	write(' : '), nieme(1, H, X), nieme(2, H, Y), recup_pion_case(X, Y, Pion), write(Pion), nl, proposer_pions_joueur(T, Tmp, Length).

entree_pion_joueur_ordi(Res, Length, Coup) :- write('Quel est le numero du pion que vous voulez jouer ? (Entre 1 et '),  write(Length), write(')'), nieme(1, Res, Coup), nieme(1, Coup, X), nieme(2, Coup, Y), recup_valeur_case(X, Y, Value), (Value =:= 1 -> generer_list_coup_1(X, Y, Liste_Resultante);(Value =:= 2 -> generer_list_coup_2_final(X, Y, Liste_Resultante) ; generer_list_coup_3_final(X, Y, Liste_Resultante))), length(Liste_Resultante, Length_2), proposer_coups_joueur_ordi(Liste_Resultante, 0, Length_2), write('Liste_Resultante ' ), write(Liste_Resultante), nl, write('Length =  '), write(Length_2), nl, entree_coup_joueur_ordi(Liste_Resultante, Length_2, Coup).

proposer_coups_joueur_ordi([], Length, Length) :- !.
proposer_coups_joueur_ordi([H|T], Numero, Length) :- write('Coup numero '), Tmp is Numero+1, write(Tmp), write(' : '), write(H), nl, proposer_coups_joueur(T, Tmp, Length).

entree_coup_joueur_ordi(Res, Length, Coup_1) :- write('Quel est le numero de la case vous voulez deplacer le pion ? (Entre 1 et '),  write(Length), write(')'), nieme(1, Res, Coup_2), lancer_action(Coup_1, Coup_2).

ne_pas_respecter_le_khan_ordi(_) :- verif_khan_lucas_ordi(Lucas).


verif_khan_lucas_ordi(_) :-  khan(X, _), (X = rouge ->  board_coord_pieces_ocre_supprime(List) ; board_coord_pieces_rouge_supprime(List)), length(List, Length), (Length =:= 0 -> condition_3_ordi(Nouveau_List), write(Nouveau_List), nieme(1,Nouveau_List,Tmp1), nieme(2,Nouveau_List,Tmp2), recup_valeur_case(Tmp1,Tmp2,Valeur), write(Valeur), recup_pion_case(Tmp1,Tmp2,Nom_Pion), write(Nom_Pion), possible_move(Tmp1, Tmp2, Valeur, Result), nl, nouveau_afficher(Result,1), nieme(1,Result,Pos_Case), verif_kalista_delete(Pos_Case), gagnant(1),suppression_pion(Nouveau_List), suppression_pion_ancien(Nouveau_List),verif_case(Pos_Case,Nom_Pion), board_pieces(List_Resultante), write(List_Resultante) ; write('Choisissez la condition 3 ou la condition 4 : '), nl, write('Pour rappel -> '), nl, write('condition 3:  Bouger une autre pièce.'), nl, write('condition 4 : Remettre un pion supprimé sur le board.'), nl, write('Votre choix?'),(X = rouge -> board_coord_pieces_ocre_supprime(List_Result_Pions);board_coord_pieces_ocre_supprime(List_Result_Pions)), length(List_Result_Pions, Length_List), (Length_List> 0 -> Con is 4 ; Con is 3), nl, (Con =:= 3 -> condition_3_ordi(Nouveau_List), write(Nouveau_List), nieme(1,Nouveau_List,Tmp1), nieme(2,Nouveau_List,Tmp2), recup_valeur_case(Tmp1,Tmp2,Valeur), write(Valeur), recup_pion_case(Tmp1,Tmp2,Nom_Pion), write(Nom_Pion), possible_move(Tmp1, Tmp2, Valeur, Result), nl, nouveau_afficher(Result,1), nieme(1,Result,Pos_Case), verif_kalista_delete(Pos_Case), gagnant(2),suppression_pion(Nouveau_List),  suppression_pion_ancien(Nouveau_List),verif_case(Pos_Case,Nom_Pion), board_pieces(List_Resultante), write(List_Resultante), nl;  condition_4_ordi(_))).



condition_3_ordi(Nouveau_List):- khan(X, List), nieme(1, List, KhanX), nieme(2, List, KhanY), recup_valeur_case(KhanX,KhanY,Value), write('Value: '), write(Value), nl, (X = rouge -> board_coord_pieces_ocre(List_pions), get_list_value_case_with_parameter_condition3(List_pions, Result, Value), write('Result: '), write(Result), nl, write('Choisir le numero du pion: '), nl, nouveau_afficher(Result,1), nieme(1,Result,Nouveau_List); board_coord_pieces_rouge(List_pions), get_list_value_case_with_parameter_condition3(List_pions, Result, Value), write('Result: '), write(Result), nl, write('Choisir le numero du pion: '), nl, nouveau_afficher(Result,1), nieme(1,Result,Nouveau_List)).

condition_4_ordi(_):- khan(X, List), (X = rouge -> board_coord_pieces_ocre_supprime(Y), nl, write('Choisir le numero de pion que vous voulez jouer :'),
 nl, nouveau_afficher(Y,1), nieme(1, Y, Res_Tmp), subtract(Y, [Res_Tmp], N_Sup), goto_coord_ocre_supprime(N_Sup),
 khan(X_Khan, List_Khan), nieme(1, List_Khan, Khan_X), nieme(2, List_Khan, Khan_Y),
 recup_valeur_case(Khan_X, Khan_Y, Khan_Valeur), get_tous_possible_case(1,1,Khan_Valeur,[],Resultante), board_coord_pieces_ocre(L1), 
 board_coord_pieces_rouge(L2), union(L1,L2,L3), subtract(Resultante,L3, Result), write('Le khan choisit une case:'), nl, nouveau_afficher_2(Result,1), 
 nieme(1, Result, Nouveau_Position), verif_kalista_delete(Nouveau_Position), gagnant(1), 
 goto_khan(rouge, Nouveau_Position), board_coord_pieces_ocre(Z),  ajout_Queue(Z, Nouveau_Position, Z_Y), goto_coord_ocre(Z_Y), board_coord_pieces_ocre(A),write(A), nl, 
 nieme(1,Nouveau_Position,NP1), nieme(2,Nouveau_Position,NP2),  recup_pion_case(NP1, NP2, Res), (Res = null -> placer_pion_liste_2(NP1,NP2,Res_Tmp);
 suppression_pion(Nouveau_Position), board_coord_pieces_rouge_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_ocre_rouge(Res_S),
 placer_pion_liste_2(NP1, NP2, Res_Tmp);
 
 suppression_pion(Nouveau_Position), board_coord_pieces_rouge_supprime(C),
 ajout_Queue(C,Res,Res_S), goto_coord_rouge_supprime(Res_S), placer_pion_liste_2(NP1, NP2, Res_Tmp)) ;
 
 board_coord_pieces_rouge_supprime(Y), write('Y: '), write(Y), nl, write('Choisir le numero du pion :'),
 nl, nouveau_afficher(Y,1),nieme(1, Y, Res_Tmp), subtract(Y, [Res_Tmp], N_Sup), write('N_Sup = '),
 write(N_Sup), goto_coord_rouge_supprime(N_Sup), khan(X_Khan, List_Khan), nieme(1, List_Khan, Khan_X), nieme(2, List_Khan, Khan_Y),
 recup_valeur_case(Khan_X, Khan_Y, Khan_Valeur), get_tous_possible_case(1,1,Khan_Valeur,[],Resultante), board_coord_pieces_ocre(L1), 
 board_coord_pieces_rouge(L2), union(L1,L2,L3), subtract(Resultante,L3, Result), write('Le khan choisit une case:'), nl, nouveau_afficher_2(Result,1), 
 nieme(1, Result, Nouveau_Position), verif_kalista_delete(Nouveau_Position), gagnant(1), 
 goto_khan(rouge, Nouveau_Position), board_coord_pieces_rouge(Z),  ajout_Queue(Z, Nouveau_Position, Z_Y), goto_coord_rouge(Z_Y), board_coord_pieces_rouge(A),write(A), nl, 
 nieme(1,Nouveau_Position,NP1), nieme(2,Nouveau_Position,NP2),  recup_pion_case(NP1, NP2, Res), (Res = null -> placer_pion_liste_2(NP1,NP2,Res_Tmp);
 suppression_pion(Nouveau_Position), board_coord_pieces_ocre_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_ocre_supprime(Res_S),
 placer_pion_liste_2(NP1, NP2, Res_Tmp))).


/*
*****

IA

STRATEGIE : RANDOM
Tous les read() sont enlevés et on prend un élément random entre 1 et la longueur de la liste actuelle.
Seule différence notable : si il y a des éléments dans le tableau contenant les pions supprimés du joueur actuel, on choisit la condition 4 plutot que la condition 3.

IA

*****
*/
/*

verif_khan_ordi(_) :- write(' est on ici  or what '), verif_khan_condition_1(Bool1), write(' est on ici '), verif_khan_condition_2(Bool2), write(' est on ici 2 '), write(Bool1), write(Bool2), (Bool1 = true, Bool2 = true) ->  respecter_le_khan_ordi(Res); ne_pas_respecter_le_khan_ordi(Res).

respecter_le_khan_ordi(Res) :- recup_list_rouge_or_ocre(List, Valeur), get_list_value_case_with_parameter(List, Res, Valeur), nbJoueurs(Nombre), length(Res, Length), nl, proposer_pions_joueur_ordi(Res, 0,Length), entree_pion_joueur_ordi(List, Length, Pion).

proposer_pions_joueur_ordi([], Length, Length) :- !.
proposer_pions_joueur_ordi([H|T], Number, Length) :- write('Pion numero '), Tmp is Number+1, write(Tmp),	write(' : '), nieme(1, H, X), nieme(2, H, Y), recup_pion_case(X, Y, Pion), write(Pion), nl, proposer_pions_joueur(T, Tmp, Length).

entree_pion_joueur_ordi(Res, Length, Coup) :- write('Quel est le numero du pion que vous voulez jouer ? (Entre 1 et '),  write(Length), write(')'), (Length = 1 -> Nb_Random is 1 ;random(1,Length,Nb_Random)), nieme(Nb_r, Res, Coup), nieme(1, Coup, X), nieme(2, Coup, Y), recup_valeur_case(X, Y, Value), (Value =:= 1 -> generer_list_coup_1(X, Y, Liste_Resultante);(Value =:= 2 -> generer_list_coup_2_final(X, Y, Liste_Resultante) ; generer_list_coup_3_final(X, Y, Liste_Resultante))), length(Liste_Resultante, Length_2), proposer_coups_joueur_ordi(Liste_Resultante, 0, Length_2), write('Liste_Resultante ' ), write(Liste_Resultante), nl, write('Length =  '), write(Length_2), nl, entree_coup_joueur_ordi(Liste_Resultante, Length_2, Coup).

proposer_coups_joueur_ordi([], Length, Length) :- !.
proposer_coups_joueur_ordi([H|T], Numero, Length) :- write('Coup numero '), Tmp is Numero+1, write(Tmp), write(' : '), write(H), nl, proposer_coups_joueur(T, Tmp, Length).

entree_coup_joueur_ordi(Res, Length, Coup_1) :- write('Quel est le numero de la case vous voulez deplacer le pion ? (Entre 1 et '),  write(Length), write(')'), (Length = 1 -> Nb_Random is 1 ; random(1,Length,Nb_Random)), nieme(Nb_Random, Res, Coup_2), lancer_action(Coup_1, Coup_2).

ne_pas_respecter_le_khan_ordi(_) :- verif_khan_lucas_ordi(Lucas).


verif_khan_lucas_ordi(_) :-  khan(X, _), (X = rouge ->  board_coord_pieces_ocre_supprime(List) ; board_coord_pieces_rouge_supprime(List)), length(List, Length), (Length =:= 0 -> condition_3_ordi(Nouveau_List), write(Nouveau_List), nieme(1,Nouveau_List,Tmp1), nieme(2,Nouveau_List,Tmp2), recup_valeur_case(Tmp1,Tmp2,Valeur), write(Valeur), recup_pion_case(Tmp1,Tmp2,Nom_Pion), write(Nom_Pion), possible_move(Tmp1, Tmp2, Valeur, Result), nl, nouveau_afficher(Result,1), nieme(1,Result,Pos_Case), verif_kalista_delete(Pos_Case), gagnant(1),suppression_pion(Nouveau_List), suppression_pion_ancien(Nouveau_List),verif_case(Pos_Case,Nom_Pion), board_pieces(List_Resultante), write(List_Resultante) ; write('Choisissez la condition 3 ou la condition 4 : '), nl, write('Pour rappel -> '), nl, write('condition 3:  Bouger une autre pièce.'), nl, write('condition 4 : Remettre un pion supprimé sur le board.'), nl, write('Votre choix?'), khan(Le_X_Du_Khan, _), (Le_X_Du_Khan = rouge -> board_coord_pieces_ocre_supprime(List_Result_Pions); board_coord_pieces_ocre_supprime(List_Result_Pions)), length(List_Result_Pions, Length_List), (Length_List> 0 -> Con is 4 ; Con is 3), nl, (Con =:= 3 -> condition_3_ordi(Nouveau_List), write(Nouveau_List), nieme(1,Nouveau_List,Tmp1), nieme(2,Nouveau_List,Tmp2), recup_valeur_case(Tmp1,Tmp2,Valeur), write(Valeur), recup_pion_case(Tmp1,Tmp2,Nom_Pion), write(Nom_Pion), possible_move(Tmp1, Tmp2, Valeur, Result), nl, nouveau_afficher(Result,1), nieme(1,Result,Pos_Case), verif_kalista_delete(Pos_Case), gagnant(2),suppression_pion(Nouveau_List),  suppression_pion_ancien(Nouveau_List),verif_case(Pos_Case,Nom_Pion), board_pieces(List_Resultante), write(List_Resultante), nl;  condition_4_ordi(_))).

condition_3_ordi(Nouveau_List):- khan(X, List), nieme(1, List, KhanX), nieme(2, List, KhanY), recup_valeur_case(KhanX,KhanY,Value), write('Value: '), write(Value), nl, (X = rouge -> board_coord_pieces_ocre(List_pions), get_list_value_case_with_parameter_condition3(List_pions, Result, Value), write('Result: '), write(Result), nl, write('Choisir le numero du pion: '), nl, nouveau_afficher(Result,1), length(Result, Longueur_De_Result), (Longueur_De_Result = 1 -> Number is 1 ;random(1, Longueur_De_Result, Number)), nieme(Number,Result,Nouveau_List); board_coord_pieces_rouge(List_pions), get_list_value_case_with_parameter_condition3(List_pions, Result, Value), write('Result: '), write(Result), nl, write('Choisir le numero du pion: '), nl, nouveau_afficher(Result,1), length(Result, Longueur_De_Result), (Longueur_De_Result = 1 -> Number is 1 ; random(1, Longueur_De_Result, Number)), nieme(Number,Result,Nouveau_List)).

condition_4(_):- khan(X, List), (X = rouge -> board_coord_pieces_ocre_supprime(Y), nl, write('Choisir le numero de pion que vous voulez jouer :'),
 nl, nouveau_afficher(Y,1), length(Y, Length_De_Y), random(1, Length_De_Y, Number), nieme(Number, Y, Res_Tmp), subtract(Y, [Res_Tmp], N_Sup), goto_coord_ocre_supprime(N_Sup),
 khan(X_Khan, List_Khan), nieme(1, List_Khan, Khan_X), nieme(2, List_Khan, Khan_Y),
 recup_valeur_case(Khan_X, Khan_Y, Khan_Valeur), get_tous_possible_case(1,1,Khan_Valeur,[],Resultante), board_coord_pieces_ocre(L1), 
 board_coord_pieces_rouge(L2), union(L1,L2,L3), subtract(Resultante,L3, Result), write('Le khan choisit une case:'), nl, nouveau_afficher_2(Result,1), length(Result, Length_Result),
(Length_Result = 1 -> Nb_Random is 1 ; random(1,Length_Result,Nb_Random)), nieme(Nb_Random, Result, Nouveau_Position), verif_kalista_delete(Nouveau_Position), gagnant(1), 
 goto_khan(rouge, Nouveau_Position), board_coord_pieces_ocre(Z),  ajout_Queue(Z, Nouveau_Position, Z_Y), goto_coord_ocre(Z_Y), board_coord_pieces_ocre(A),write(A), nl, 
 nieme(1,Nouveau_Position,NP1), nieme(2,Nouveau_Position,NP2),  recup_pion_case(NP1, NP2, Res), (Res = null -> placer_pion_liste_2(NP1,NP2,Res_Tmp);
 suppression_pion(Nouveau_Position), board_coord_pieces_rouge_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_ocre_rouge(Res_S),
 placer_pion_liste_2(NP1, NP2, Res_Tmp);
 
  suppression_pion(Nouveau_Position), board_coord_pieces_rouge_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_rouge_supprime(Res_S), placer_pion_liste_2(NP1, NP2, Res_Tmp)) ;
 
 board_coord_pieces_rouge_supprime(Y), write('Y: '), write(Y), nl, write('Choisir le numero du pion :'),
 nl, nouveau_afficher(Y,1), length(Y, Length_Y), 
(Length_Y = 1 -> Nb_Random is 1 ; random(1,Length_Y,Nb_Random)), nieme(Nb_Random, Y, Res_Tmp), subtract(Y, [Res_Tmp], N_Sup), goto_coord_rouge_supprime(N_Sup), khan(X_Khan, List_Khan), nieme(1, List_Khan, Khan_X), nieme(2,List_Khan, Khan_Y),
 recup_valeur_case(Khan_X, Khan_Y, Khan_Valeur), get_tous_possible_case(1,1,Khan_Valeur,[],Resultante), board_coord_pieces_ocre(L1), 
 board_coord_pieces_rouge(L2), union(L1,L2,L3), subtract(Resultante,L3, Result), write('Le khan choisit une case:'), nl, nouveau_afficher_2(Result,1), 
length(Result_List, Length_Result_List), (Length_Result_List = 1 -> Nb_Random is 1 ; random(1,Length_Result_List,Nb_Random)), nieme(Nb_Random, Result, Nouveau_Position), verif_kalista_delete(Nouveau_Position), gagnant(1), 
 goto_khan(rouge, Nouveau_Position), board_coord_pieces_rouge(Z),  ajout_Queue(Z, Nouveau_Position, Z_Y), goto_coord_rouge(Z_Y), board_coord_pieces_rouge(A),write(A), nl, 
 nieme(1,Nouveau_Position,NP1), nieme(2,Nouveau_Position,NP2),  recup_pion_case(NP1, NP2, Res), (Res = null -> placer_pion_liste_2(NP1,NP2,Res_Tmp);
 suppression_pion(Nouveau_Position), board_coord_pieces_ocre_supprime(C), ajout_Queue(C,Res,Res_S), goto_coord_ocre_supprime(Res_S),
 placer_pion_liste_2(NP1, NP2, Res_Tmp))).

*/
/*
*****

IA

STRATEGIE MEILLEURE : On regarde la distance entre tous les coups possibles et la kalista.
RESTE A FAIRE. Manque de temps.

IA

*****
*/
/*
verif_khan_ordi_meilleure(_) :- verif_khan_condition_1(Bool1), verif_khan_condition_2(Bool2), (Bool1 = true, Bool2 = true) ->  respecter_le_khan_ordi_meilleure(Res); ne_pas_respecter_le_khan_ordi_meilleure(Res).

respecter_le_khan_ordi_meilleure(Res) :- recup_list_rouge_or_ocre(List, Valeur), get_list_value_case_with_parameter(List, Res, Valeur), nbJoueurs(Nombre), length(Res, Length),proposer_pions_joueur_ordi_meilleure(List, 0,Length), entree_pion_joueur_ordi_meilleure(List, Length, Pion).

proposer_pions_joueur_ordi_meilleure([], Length, Length) :- !.
proposer_pions_joueur_ordi_meilleure([H|T], Number, Length) :- write('Pion numero '), Tmp is Number+1, write(Tmp),	write(' : '), nieme(1, H, X), nieme(2, H, Y), recup_pion_case(X, Y, Pion), write(Pion), nl, proposer_pions_joueur_ordi_meilleure(T, Tmp, Length).

entree_pion_joueur_ordi_meilleure(Res, Length, Coup) :- write('Quel est le numero du pion que vous voulez jouer ? (Entre 1 et '),  nieme(Numero, Res, Coup), nieme(1, Coup, X), nieme(2, Coup, Y), recup_valeur_case(X, Y, Value), (Value =:= 1 -> generer_list_coup_1(X, Y, Liste_Resultante);(Value =:= 2 -> generer_list_coup_2_final(X, Y, Liste_Resultante) ; generer_list_coup_3_final(X, Y, Liste_Resultante))), length(Liste_Resultante, Length_2), proposer_coups_joueur_ordi_meilleure(Liste_Resultante, 0, Length_2), entree_coup_joueur_ordi_meilleure(Liste_Resultante, Length_2, Coup).

proposer_coups_joueur_ordi_meilleure([], Length, Length) :- !.
proposer_coups_joueur_ordi_meilleure([H|T], Numero, Length) :- write('Coup numero '), Tmp is Numero+1, write(Tmp), write(' : '), write(H), nl, proposer_coups_joueur_ordi_meilleure(T, Tmp, Length).

entree_coup_joueur_ordi_meilleure(Res, Length, Coup_1) :- write('Quel est le numero de la case vous voulez deplacer le pion ? (Entre 1 et '),  nieme(1, Res, Coup_2), lancer_action_ordi_meilleure(Coup_1, Coup_2).

lancer_action_ordi_meilleure(Coup1, Coup2) :- khan(Khan, _), nieme(1, Coup1, Coup1_X), nieme(2, Coup1, Coup1_Y), nieme(1, Coup2, Coup2_X), nieme(2, Coup2, Coup2_Y), recup_pion_case(Coup2_X, Coup2_Y, Coup2_Value), (Khan = rouge -> suppression_pion_ocre(Coup2_X, Coup2_Y, Coup2_Value);  suppression_pion_rouge(Coup2_X, Coup2_Y, Coup2_Value)),recup_pion_case(Coup1_X, Coup1_Y, Coup1_Value),  placer_pion_liste_2(Coup1_X, Coup1_Y, null), placer_pion_liste_2(Coup2_X, Coup2_Y, Coup1_Value), (Khan = rouge -> remplacer_pion_ocre(Coup1, Coup2); remplacer_pion_rouge(Coup1, Coup2)), khan(X, Y), (X = rouge -> goto_khan(ocre, Coup2); goto_khan(rouge, Coup2)), write('Coup effectue !').
*/

/*
*****

IA

IA

*****
*/

recup_pion_case(I, J, Value):- board_pieces(X), nieme(I, X, Result), nieme(J, Result, Value).
%Recupére le nom du pion [I,J] dans Value

recup_valeur_case(I, J, Value):- board(X), nieme(I, X, Result), nieme(J, Result, Value).
%Recupére le nom du pion [I,J] dans Value

jeu:- write('Combien de joueurs humains ? (0 - 1 - 2) '), read(X), integer(X), initBoard(X). %Ne pas oublier le cas de ordinateur contre ordinateur
%Appelé par reset, gère le nombre de joueurs humains

gagnant(_) :- kalista_ocre(K_o), kalista_rouge(K_r), ((K_o, K_r) -> true; (K_o = false -> nl, write('Le joueur rouge gagne'), fail ; nl, write('Le joueur ocre gagne'), fail)). %determine s'il y a gagnant ou non
%Regarde si les kalista sont encore présentes sur le board. C'est notre prédicat qui fail intentionnellement et termine le jeu s'il n'y a plus qu'une kalista.

jouer(0):- gagnant(0), nl, display_pieces(0), nl, verif_khan_ordi(0), gagnant(0), nl, display_pieces(0), nl, verif_khan_ordi(0), jouer(0).  %2 * coup ordi
jouer(1):- gagnant(1), nl, display_pieces(1),  nl, verif_khan_ordi(1), gagnant(1), nl, display_pieces(1), nl, write('Player red, your turn !'), nl, verif_khan(1), jouer(1).  %AJOUTER verif_khan. + coup ordi
jouer(2):- gagnant(2), nl, display_pieces(2), nl,  write(' Player ocre, your turn !'), nl,verif_khan(2), gagnant(2), nl, display_pieces(2), nl,  write(' Player red, your turn !'), nl,verif_khan(2), jouer(2).  %AJOUTER verif_khan.
%Boucles principales. Si 0 joueur : coup_ordi puis coup_ordi. Si 1 joueur : coup_ordi puis coup_humain. Si 2 joueurs : coup_humain puis coup_humain.
%Entre chaque coup, on vérifie notre prédicat gagnant(_) et on affiche le board.