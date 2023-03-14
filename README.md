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

Änderung | Zeit		| FPS
-------- | -------- | ---------
Nichts   | 55,3s	| 0,0
Debugger ausgaben auskommentieren   | 41,1s   | 0,0
Prüferegeln neu geschrieben | 39,0 s | 0,0
gotoxy entfernt | 38,5s | 0,0

### Debugger ausgaben auskommentieren
Bei dem Ürsprünglichen Version des Programms werden die Anzahl der lebenden Nachbarn ausgegeben.
Um die Zeit für diese Ausgabe zu sparen haben wir sie vorerst nur auskommentiert.
Damit kann man diese Ausga später wieder Verwenden falls das Programm von uns "kapputt verbessert" wird, und wir es wieder debuggen müssen.

