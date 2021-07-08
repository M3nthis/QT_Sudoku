# QT_Sudoku

Questa parte del progetto usa un algoritmo ricorsivo con backtracking per risolvere in modo
automatico un Sudoku.

Il metodo ricorsivo è solve_sudoku che controlla se la cella del Sudoku è piena e, in caso
negativo, prova a inserire un numero. Controlla se il numero può essere inserito tramite il
metodo isSafe (che verifica che non ci siano altri numeri uguali sulla stessa riga/colonna e
“sezione”) e in caso positivo richiama se stesso ricorsivamente passando il nuovo indice per la
colonna successiva.

All’inizio del metodo, se l’indice della colonna supera quello massimo questo viene impostato a
zero e viene aumentato di uno l’indice relativo alla riga.
Se si arriva al caso base, ovvero quando tutte le celle sono state riempite, viene ritornato il
valore true che conferma la riuscita dell’operazione.

Per scrivere e leggere il valore delle celle viene usata una variabile membro della classe
chiamata grid, che è una matrice di puntatori alle celle mostrate nella finestra dalla .ui.

Nel caso non si arrivi a una soluzione o nel caso i valori iniziali delle celle non fossero corretti (la
funzione thereAreInvalidCharacters controlla che l’utente non abbia inserito caratteri in posizioni
non consentite) viene mostrato un messaggio d’errore tramite la funzione showError che
riempie la label di errore nella ui e impedisce l’ulteriore modifica delle celle.

Per mostrare all’utente la soluzione step-by-step viene applicato lo stesso algoritmo di
risoluzione spiegato precedentemente ma applicato a una matrice momentanea. Una volta
trovata la soluzione viene presa la cella da riempire e viene settato il valore con gli stessi indici
presente nella matrice momentanea.
Per fare ciò la classe contiene un overload delle funzioni solve_sudoku e isSafe che modifica la
grid membro della classe o una temporanea passata tramite puntatore.

Nella parte di ui viene applicato il metodo setfixedSize per non permettere il cambiamento di
dimensione della finestra e sono presenti tre pulsanti che, tramite gli slot della classe
MainWindow, azionano le funzioni rispettivamente per trovare la soluzione, fare lo step-by-step,
o azzerrare il contenuto della griglia.
Viene inoltre applicato un validator alle celle che consente di inserire solo numeri da 1 a 9.
