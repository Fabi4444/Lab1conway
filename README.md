# Lab1conway

## Aufgabenstellung
Die Aufgabe ist ein Programm welches [Conways Spiel des Lebens](https://de.wikipedia.org/wiki/Conways_Spiel_des_Lebens) implementiert zu optimieren.
Das Ausgangsprogramm ist: conway.c eine Implementierung f�r den [C64](https://www.c64-wiki.de/wiki/C64) unter Verwendung des [CC65 Kompilers](https://cc65.github.io/).
Im Protokoll beschreiben Sie jede Optimierung einzeln. Besonders interessant sind u.a. die Schritte, die unerwartet viel oder wenig bringen.
Um beim Programm einen Vergleich zwischen den verschiedenen L�sungen zu erm�glichen, notieren sie die Zeit welche es f�r einen Durchlauf ben�tigt.

### Vorgehensweise
Der Installationsanweisung folgen und cc65 installieren.
Es wird wie folgt kompiliert
``
cl65 -t c64 -o conway.prg conway.c
``
Ausgef�hrt werden kann das Programm mittels Vice durch einfaches hineinziehen oder
``
x64dtv test.prg
``
### Arbeitsschritte
Zusammengefasst die Arbeitsschritte
1. Vorbereitung: Installation des Compilers CC65 und Vice.
1. Einlesen in Conways Way of Life und dessen Regeln
1. Quellcode anschauen und grob verstehen
1. Code schrittweise Optimieren
1. Optimierungen 

## Conway's Game of Life
Das zu optimierende Programm ist "Conway's Game of Life" was f�r den Kommodore 64 programmiert ist.

"Conway's Game of Life" ist kein Spiel, das von Menschen gespielt wird wie ein Gesellschaftsspiel oder ein Computerspiel, sondern ein Geschehen nach bestimmten regeln.
In dem Spiel das 1970 von John Conway entworfen wurde gibt es tote und lebende Zellen.
Ob die Zelle Tot oder lebendig ist, h�ngt von seinen Nachbarn ab. 
Jede Zelle ist ein K�stchen in einem unendlich gro�es Gitterquadrat.
In einem realen Spielfeld muss es einen Rand geben, der entweder aus dauerhaft toten Zellen besteht oder Zellen die ebenfalls am gegen�berliegenden Rand liegen.

### Spielregeln
Ob eine Zelle im n�chsten durchgang tot oder lebendig ist wird durch folgende 4 Spielregeln bestimmt.

* Eine tote Zelle mit genau drei lebenden Nachbarn wird in der Folgegeneration �geboren� (zum Leben erweckt).
* Eine lebende Zelle mit weniger als zwei lebenden Nachbarn stirbt in der Folgegeneration (an Einsamkeit).
* Eine lebende Zelle mit zwei oder drei lebenden Nachbarn bleibt in der Folgegeneration am Leben.
* Eine lebende Zelle mit mehr als drei lebenden Nachbarn stirbt in der Folgegeneration (an �berbev�lkerung).

### Objekte
In Conway's Game of Life k�nnen sehr interssante Strukturen enstehen. Einige dieser Objekte sind statisch, bleiben also immer gleich.
Ein sehr einfaches Beispiel ist der Block. Das sind einfach 4 ananeinander liegende K�stchen die Stabil immer bestehen bleiben.

Es gibt auch sehr viele bewegte Objekte, wie zum Beispiel oszillierende Objekte, die sich immer wieder wiederholen, oder Gleiter und Segler die sich weiterbewegen.

## Verbesserungen

�nderung | Zeit		| FPS
-------- | -------- | ---------
Nichts   | 55,3s	| 0,0
Debugger ausgaben auskommentieren   | 41,1s   | 0,0
Pr�feregeln neu geschrieben | 39,0 s | 0,0
gotoxy entfernt | 38,5s | 0,0
Fehler ausgebessert | 39,1s | 0,0
Arrays von int auf char | 37,6s | 0,0
z�hle lebende verbessert | 28,8 | 0,0
finde Nachbarn ohne Loop | 15,8 | 0,0
nachbarn array nicht verwenden | 13,4s | 0,0
char statt int | 12,9s | 0,0


### Debugger ausgaben auskommentieren
Bei dem �rspr�nglichen Version des Programms werden die Anzahl der lebenden Nachbarn ausgegeben.
Um die Zeit f�r diese Ausgabe zu sparen haben wir sie vorerst nur auskommentiert.
Damit kann man diese Ausga sp�ter wieder Verwenden falls das Programm von uns "kapputt verbessert" wird, und wir es wieder debuggen m�ssen.

### Pr�feregeln neu geschrieben
Die pr�feregeln-Funktion war sehr inneffizient geschrieben welshab wir die ganze Funktion neu geschrieben haben.

### gotoxy entfernt
Nach analysieren des codes haben wir bemerkt, dass der ausdruck ``gotoxy(0, 0)`` unn�tig ist, da diese funktion sp�ter wieder aufgerufen, und die Position somit �berschrieben wird. 

### Fehler ausgebessert
Wir haben einen Fehler im Programm ausgebessert, der einer anderen Gruppe aufgefallen ist. Dadurch wurde das Programm allerdings wider langsamer.

### Arrays von int auf char
Da char nur 1 byte zur speicherung bzw. berechnung ben�tigt ist es schneller char arrays anstelle von integers zu verwenden.

### Z�hle lebende & finde nachbarn
Die innefizenten for-loops aus den zaehlLebende, und findNachbarn die durch die alle Zellen in dem nachbarn-array gehen, wurden durch eine hard-gecodete liste ersetzt.

### Nachbarn array nicht verwenden 
Damit das Nachbarn array nicht unn�tig kopiert werden muss, werden die lebenden einfach bereits im finde nachbarn gez�hlt.

### char statt int
Die lebende, x und y variblen wurden auf chars ge�ndert um geringere datenmenge zu �bergeben.
