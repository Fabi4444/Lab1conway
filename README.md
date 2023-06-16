# Lab1conway Effiziente Programme

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

Änderung | Zeit		| FPS	| Verbesserung in % | Verbesserung absolut
-------- | -------- | ------| ---------- | -----
Nichts   | 55,3s	| 0,0	| 0% | 0%
Debugger Ausgaben auskommentieren   |	41,1s   | 0,0 | 26% | 26 %
Prüferegeln neu geschrieben | 39,0s | 0,0	|	5% | 29%
gotoxy entfernt | 38,5s | 0,0	|	1% | 30%
Fehler ausgebessert | 39,1s | 0,0	|	-2% | 29%
Arrays von int auf char | 37,6s | 0,0 | 4% | 32%
zähle lebende verbessert | 28,8s | 0,0 | 23% | 48%
finde Nachbarn ohne Loop | 15,8s | 0,0 | 45% | 71%
nachbarn array nicht verwenden | 13,4s | 0,0 | 15% | 76%
char statt int | 12,9s | 0,0 | 4% | 77%
switch case statt if | 12,0s | 0,0 | 7% | 78%
funktionsaufrufe eliminieren | 10,2s | 0,0 | 15% | 82%
mehr funktionen eliminieren | 9,9s | 0,1 | 3% | 82%
``++i`` statt ``i++`` | 9,9s | 0,1 | 0% | 82%
anderer compiler command | 7,7s | 0,1 | 22% | 86%
print for Loop | 7,2s | 0,1 | 6% | 87%
char statt long | 6,1s | 0,1 | 15% | 89%
nur lebende Zellen ausgeben | 5,7 | 0,1 | 7% | 90%
== 1 entfernt | 5,3 | 0,1 | 7% | 90%

![Graph](/bilder/neue_coole_grafik.PNG)

Grafik 1: Zeit über die Änderung & verbesserung in %


## Laborzyklus 1: 


### Debugger ausgaben auskommentieren
Bei der ursprünglichen Version des Programms werden die Anzahl der lebenden Nachbarn ausgegeben.
Um die Zeit für diese Ausgabe zu sparen haben wir sie vorerst nur auskommentiert.
Damit kann man diese Ausgabe später wieder Verwenden, falls das Programm von uns "kaputt verbessert" wird, und wir es wieder debuggen müssen.

### Prüferegeln neu geschrieben
Die prüferegeln-Funktion war sehr inneffizient geschrieben weshalb wir die ganze Funktion neu geschrieben haben.

### gotoxy entfernt
Nach analysieren des Codes haben wir bemerkt, dass der Ausdruck ``gotoxy(0, 0)`` unnötig ist, da diese Funktion später wieder aufgerufen, und die Position somit überschrieben wird. 

### Fehler ausgebessert
Wir haben einen Fehler im Programm ausgebessert, der einer anderen Gruppe aufgefallen ist. Dadurch wurde das Programm allerdings wieder langsamer.


## Laborzyklus 2:


### Arrays von int auf char
Da char nur 1 Byte zur Speicherung bzw. Berechnung benötigt ist es schneller char arrays anstelle von integers zu verwenden.

### Zähle lebende & finde Nachbarn
Die ineffizienten for-loops aus den zaehlLebende, und findNachbarn die durch die alle Zellen in dem Nachbarn-array gehen, wurden durch eine hard-gecodete liste ersetzt.

### Nachbarn array nicht verwenden 
Damit das Nachbarn array nicht unnötig kopiert werden muss, werden die lebenden einfach bereits im finde Nachbarn gezählt.

### char statt int
Die lebende, x und y variablen wurden auf chars geändert, um geringere Datenmenge zu übergeben.


## Laborzyklus 3:


### Switch-Case statt if in prueferegeln
Switch case abfragen sind schneller durchführbar, als if abfragen.
Allerdings können nur ``==`` abfragen machen, und keine ``<`` oder ``>`` abfragen.
Dadurch können nicht alle if-abfragen mit Switch-Case ersetz werden.
Wir haben die Funktion ``pruefeRegeln`` mit verändert.

### Funktionsaufrufe eliminieren
Jeder Funktionsaufruf benötigt Zeit, um die an die richtige Stelle im Programm zu springen, und danach wieder zurückzukommen.
Das wird umgangen, indem das Ganze Programm einfach untereinander "in einer Wurst" gepackt wurde.

### Funktionsaufrufe printSpielfeld / initSpielfeld eliminieren
Als diese Funktionen einfach so kopiert wurden, hat der Compiler den Fehler ``Mixed declarations and code are not supported`` gemeldet.
Grund dafür war, dass die Deklarationen der Variablen alle an den Anfang gehören.

### ``++i`` statt ``i++``
In der [Dokumentation des c65 compilers](https://cc65.github.io/doc/coding.html), stand dass ``++i`` statt ``i++`` verwendet werden soll.
Nach erneutem ausführen war keine Änderung ersichtlich.
Als allerdings eine alte Version mit dem neuen Compiler command ausgeführt wurde, war eine Änderung erkennbar.

### Neuer compiler command 
Durch die [Dokumentation des Compilers](https://cc65.github.io/doc/cl65.html) wurden Flags für die Codeoptimierung dazu geschrieben.
Deshalb wurde die Flag ``-Oirs`` hinzugefügt.

Neuer compile command: ``cl65 -Oirs -t c64 -o conway.prg conway.c``

Das Flag ``Oirs`` ist eine Kombination aus 3 Optimierungs-Flags:
1. ``Oi`` - Optimize code, inline more code
1. ``Or`` - Optimize code, honour the register keyword
1. ``Os`` - Optimize code, inline standard funtions

### Print for loop weggelassen
Die Print Funktionen waren in einem eigenen for loop.
Durch das Kopieren der If - Abfrage in den anderen for Loop, wird der andere loop nichtmehr benötigt.

### Char statt long
Bei erneutem Durschauen des Codes ist uns noch eine weitere Variable aufgefallen, die noch nicht auf Char umgeändert wurde. Und zwar: ``x_spiel, y_spiel, x_init und y_init``.


## Laborzyklus 4:


### Nur lebende Zellen ausgeben
In dem originalen code werden Lebende Zellen geschrieben und tote gelöscht.
``` C
if (spielfeld[x][y] == 1) 
{
	revers(1);
}
else
{
 	revers(0);
}
```
urspünglicher code 

Da dieses if - else langsamer ist als eine einfache if - Abfrage werden nur noch die lebenden Zellen abgefragt.
Um die alten Zellen zu löschen, muss aber nun vor jeder Runde ``clrscr();`` aufgerufen werden, damit alle Zellen zuvor einmal gelöscht werden.
``` C
if (spielfeld[x][y] == 1) 
{
	revers(1);
	cputcxy(x, y, 32);
}
```
neuer Code

### == 1 entfernt
Da die Abfrage ``if (spielfeld[x][y])`` das gleiche Ergebnis wie if ``if (spielfeld[x][y] ==1 )`` ergibt,
und die == Abfrage eine längere Zeit benötigt, haben wir diese geändert. 
Das funktioniert, weil in C alle Werte, die nicht 0 sind, eine logische 1 sind.

### arrays im Grafikspeicher speichern
Um sich die Funktionsaufrufe der Print-Funktionen zu sparen, werden die Arrays einfach an die Stelle des Grafikspeichers geschrieben. 

#### pointer Variablen statt 
Dazu müssen zu allererst das Spielfeld-Array, und das Temp-Array als Pointer gespeichert werden.
``` C
char* temp;
char* spielfeld;
int main(void)
{
	temp = (char *)0x800;
	spielfeld = (char *)0x400;
}
```
Dieser Pointer kann nun wie ein 1-Dimensionales Array ausgelesen werden. ``spielfeld[5] = 2;``
Da es aber nun statt einem 2-Dimensionlen Array, nur eine Aneinanderreihung von Pointer Adressen ist muss die Formel ``[x + y * (XMAX - 1)]`` statt ``[x][y]`` verwendet werden.

#### änderung der Speicheradressen auf die der Grafikchip zugreift
In dem [Wiki zum VIC im C64](https://www.c64-wiki.de/wiki/VIC) bekommt man Informationen wie man die Basisadresse des Bildschirmspeichers ändern kann.
Damit diese auf die Speicheradresse ``0x400`` zeigt müssen die Bits 4-7 im  ``VIC.addr`` 1 ergeben. 
Daraus ergibt sich die Zeile ``VIC.addr = (VIC.addr & 0x0F) | (1 << 4);``.

#### eigener Zeichensatz
Wenn das Programm so ausgeführt wird zeigt der C46 viele @ und a Zeichen an.
Das liegt daran dass der Zeichencode von 0 einem @, und der Zeichencode von 1 einem a entspricht.
Um wieder Kästchen zu bekommen müssen nun ein eigener Zeichensatz ersellt werden.
Dieser wird an der Adresse ``0x2000`` gespeichert, da das der erste freie Speicherpaltz nach den anderen Zeichensätzen ist.

``` C
charset = (char*) 0x2000;
	memset(charset, 0, 8);
	memset(&charset[8], 0xFF, 8);
```

#### Vertauschen der Pointer
Anstatt nun das ganze Array mit einem ``memcpy`` zu kopieren wie es vorher der Fall war, kann man nun einfach nach jeder Runde die beiden Pointeradressen vertauschen.
``` C
a = spielfeld; // vertauschen der pointer
spielfeld = temp;
temp = a;
VIC.addr ^= (VIC.addr & 0x0F) | (0b11 << 4);
```
Damit muss allerdings auch die Speicheradresse des Grafikspeichers geändert werden.
Mit einem XOR kann ganz einfach jeder Runde ein 1er zu einem 2er, bzw. ein 2er zu einem 1er geändert werden.
Damit ändert sich die Adresse auf die der Grafikspeicher zugreift von ``0x400`` auf ``0x800`` bzw. umgekehrt.

### Fehleausbesserung
Mit diesen Änderungen kam das Programm nicht weiter als die Initialisierung.
Das lag daran, dass die Speicheradressen ``0x800`` bereits von anderen C-Variablen besetzt war.


Da diese Optimierung sehr Komplex ist konnte das Programm aufgrund von Zeitmangel nichtmehr in funktionierenden Code Verbessert werden.
Der letzte funktionierende Version der conway.c Datei ist der Commit ``== 1 entfernt`` mit dem Hash ``175ef976443565da6adf76e056bf31993cd50289``.

## Weitere Optimierungsmöglichkeiten
* In dem Code sind noch viele Berechnungen für y Koordinaten die außerhalb des einen Loop geschrieben werden können, weil sie immer gleich sind.
* Nur 1 Loop und statt Multiplikationen Additionen
* Die Kooridnatenberechnung mittles Lookup-Tables
