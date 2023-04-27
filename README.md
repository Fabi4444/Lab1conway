# Lab1conway

## Aufgabenstellung
Die Aufgabe ist ein Programm welches [Conways Spiel des Lebens](https://de.wikipedia.org/wiki/Conways_Spiel_des_Lebens) implementiert zu optimieren.
Das Ausgangsprogramm ist: conway.c eine Implementierung für den [C64](https://www.c64-wiki.de/wiki/C64) unter Verwendung des [CC65 Kompilers](https://cc65.github.io/).
Im Protokoll beschreiben Sie jede Optimierung einzeln. Besonders interessant sind u.a. die Schritte, die unerwartet viel oder wenig bringen.
Um beim Programm einen Vergleich zwischen den verschiedenen Lösungen zu ermöglichen, notieren sie die Zeit welche es für einen Durchlauf benötigt.

### Vorgehensweise
Der Installationsanweisung folgen und cc65 installieren.
Es wird wie folgt kompiliert
``
cl65 -t c64 -o conway.prg conway.c
``
Ausgeführt werden kann das Programm mittels Vice durch einfaches hineinziehen oder
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
Das zu optimierende Programm ist "Conway's Game of Life" was für den Kommodore 64 programmiert ist.

"Conway's Game of Life" ist kein Spiel, das von Menschen gespielt wird wie ein Gesellschaftsspiel oder ein Computerspiel, sondern ein Geschehen nach bestimmten regeln.
In dem Spiel das 1970 von John Conway entworfen wurde gibt es tote und lebende Zellen.
Ob die Zelle Tot oder lebendig ist, hängt von seinen Nachbarn ab. 
Jede Zelle ist ein Kästchen in einem unendlich großes Gitterquadrat.
In einem realen Spielfeld muss es einen Rand geben, der entweder aus dauerhaft toten Zellen besteht oder Zellen die ebenfalls am gegenüberliegenden Rand liegen.

### Spielregeln
Ob eine Zelle im nächsten durchgang tot oder lebendig ist wird durch folgende 4 Spielregeln bestimmt.

* Eine tote Zelle mit genau drei lebenden Nachbarn wird in der Folgegeneration „geboren“ (zum Leben erweckt).
* Eine lebende Zelle mit weniger als zwei lebenden Nachbarn stirbt in der Folgegeneration (an Einsamkeit).
* Eine lebende Zelle mit zwei oder drei lebenden Nachbarn bleibt in der Folgegeneration am Leben.
* Eine lebende Zelle mit mehr als drei lebenden Nachbarn stirbt in der Folgegeneration (an Überbevölkerung).

### Objekte
In Conway's Game of Life können sehr interssante Strukturen enstehen. Einige dieser Objekte sind statisch, bleiben also immer gleich.
Ein sehr einfaches Beispiel ist der Block. Das sind einfach 4 ananeinander liegende Kästchen die Stabil immer bestehen bleiben.

Es gibt auch sehr viele bewegte Objekte, wie zum Beispiel oszillierende Objekte, die sich immer wieder wiederholen, oder Gleiter und Segler die sich weiterbewegen.

## Verbesserungen

Änderung | Zeit		| FPS	| Verbesserung in %
-------- | -------- | ---------
Nichts   | 55,3s	| 0,0	|	-
Debugger ausgaben auskommentieren   |	41,1s   | 0,0 | 26%
Prüferegeln neu geschrieben | 39,0s | 0,0	|	5%
gotoxy entfernt | 38,5s | 0,0	|	1%
Fehler ausgebessert | 39,1s | 0,0	|	-2%
Arrays von int auf char | 37,6s | 0,0 | 4%
zähle lebende verbessert | 28,8s | 0,0 | 23%
finde Nachbarn ohne Loop | 15,8s | 0,0 | 45%
nachbarn array nicht verwenden | 13,4s | 0,0 | 15%
char statt int | 12,9s | 0,0 | 4%
switch case statt if | 12,0 | 0,0 | 7%
funktionsaufrufe eliminieren | 10,2 | 0,0 | 15%


![Graph](/bilder/Aenderung_Conway_graph_3.png)
Grafik 1: Zeit über die Änderung & verbesserung in %


## Laborzyklus 1 : 


### Debugger ausgaben auskommentieren
Bei dem Ürsprünglichen Version des Programms werden die Anzahl der lebenden Nachbarn ausgegeben.
Um die Zeit für diese Ausgabe zu sparen haben wir sie vorerst nur auskommentiert.
Damit kann man diese Ausga später wieder Verwenden falls das Programm von uns "kapputt verbessert" wird, und wir es wieder debuggen müssen.

### Prüferegeln neu geschrieben
Die prüferegeln-Funktion war sehr inneffizient geschrieben welshab wir die ganze Funktion neu geschrieben haben.

### gotoxy entfernt
Nach analysieren des codes haben wir bemerkt, dass der ausdruck ``gotoxy(0, 0)`` unnötig ist, da diese funktion später wieder aufgerufen, und die Position somit überschrieben wird. 

### Fehler ausgebessert
Wir haben einen Fehler im Programm ausgebessert, der einer anderen Gruppe aufgefallen ist. Dadurch wurde das Programm allerdings wider langsamer.


## Laborzyklus 2 :


### Arrays von int auf char
Da char nur 1 byte zur speicherung bzw. berechnung benötigt ist es schneller char arrays anstelle von integers zu verwenden.

### Zähle lebende & finde nachbarn
Die innefizenten for-loops aus den zaehlLebende, und findNachbarn die durch die alle Zellen in dem nachbarn-array gehen, wurden durch eine hard-gecodete liste ersetzt.

### Nachbarn array nicht verwenden 
Damit das Nachbarn array nicht unnötig kopiert werden muss, werden die lebenden einfach bereits im finde nachbarn gezählt.

### char statt int
Die lebende, x und y variblen wurden auf chars geändert um geringere datenmenge zu übergeben.

### Switch-Case statt if in prueferegeln
Switch case abfragen sind schneller durchführbar, als if abfragen.
Allerdings können nur ``==`` abfragen machen, und keine ``<`` oder ``>`` abfragen.
Dadurch können nicht alle if-abfragen mit Switch-Case ersetz werden.
Wir haben die funktion ``pruefeRegeln`` mit verändernt.

### funktionsaufrufe eliminieren
Jeder funktionsaufruf benötigt zeit, um die an die richige Stelle im Programm zu springen, und danach wieder zurück zu kommen.
Das wird umgangen indem das Ganze Programm einfach untereinander "in einer Wurst" gepackt wurde.
