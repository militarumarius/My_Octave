### Copyright Militaru-Ionut-Marius

### Generator de octave 

### Descrierea programului:

* Programul dat efectueaza diferite operatii cu matrici dintr-un vector,
in functie de litera mare primita de la tastatura.
* Pentru fiecare comanda este asociata  o litera si se apeleaza functia 
corespunzatoare .In caz ca comanda nu este recunoscuta se afiseaza mesajul :
"Unrecognized command".Numarul de matrici il retin in variabila index.
Programul se opreste cand citesc de la tastatura litera Q

### Comenzile sunt urmatoarele:

* "L": citeste de la tastatura dimensiunile noi matrici ce trebuie adaugata 
    in vectorul de matrici. Daca nu mai este spatiu alocat , realoc spatiu .
    Dimensiunile le retin in doi vectori , vectorul lin si col.
* "D": afisez dimensiunea matrici date, daca matricea nu exista afisez un mesaj
    corespunzator
* "P": afisez matricea corespunzatoare numarului citit,daca matricea nu exista
    afisez un mesaj corespunzator
* "C": redimensionez matricea ceruta in functie de dimensiunile primite de 
    la tastatura, daca nu exita matricea afisez un mesaj corespunzator.
    Formez noua matrice intr-o matrice auxiliara si dupa sterg din memorie
    vechea matrice si o adaug pe cea noua, modificand si dimensiunile acesteia.
* "M": inmultesc doua matrici intre ele. Functia **inmultire_matrici returneaza
    produsul a doua matrici . In functia inmultire citesc indexul celor doua
    matrici , daca nu se poate efectua inmultirea afisez un mesaj corespunzator
    si dupa efectuez inmultirea punand noua matrice formata in capatul 
    vectorului de matrici.
* "O": sortez elemtele vectorului de matrici in functie de suma elementelor,
    Calculez suma intr un vector si dupa efectuez sortare, sortand atat 
    vectorul linie si coloana cat si matricile
* "T": calculez transpusa matricei corespunzatoare indexului citit , daca nu 
    exista afisez un mesaj corespunzator. Transpusa o retin intr-o matrice
    auxiliara si dupa sterg din memorie vechea matrice si o inlocuiesc cu 
    trasnpusa
* "R": ridic matricea data la o putere citita de la tastatura. Daca nu se poate
    ridica la putere se afiseaza un mesaj corespunzator.Initializez matricea
    rez cu matricea identitate. Dupa efectuez algortimul de ridicare in timp
    logaritmic si daca puterea este impara inmultesc rez cu matricea data,iar
    dupa ridic la patrat matricea intiliala, cat timp puterea este diferita de
    0.La final eliberez vechea matrice si adaug noua matrice
* "F": eliberez matricea cu indexul dat , daca aceasta exista , si dupa 
    mut restul matricelor din vector cu un index inapoi
* "S": inmultesc doua matrici de dimensiune 2^a cu algoritmul lui Strassen.
    Impart matricele date (A si B)in cate 4 matrici blocuri de dimensiune n/2.
    Dupa calculez cele 7 matrici M din algorimul dat. Cu matricele M calculez
    matricile blocuri ale matricei rezultat(adica C) si i le atribui lui C.
    Petru simplitate am un vector mat care retine toate matricele blocuri 
    necesare, alocand memorie la inceput si stergand la final prin functiile
    cu nume sugestiv. Apelez recursiv algoritmul pana cand n=1 si inmultesc
    doua numere intre ele.La final returnez matricea formata .In functia 
    strassen aloc memorie pentru matricea rez si o adaug la finalul vectorului
    de matrici
* "Q": nu se mai citeste nimic de la tastatura si se elibereaza toata memoria
    folosita, adica cei doi vectori lin si col si vectorul de matrici.
    Toate matricile formate sunt calculate modulo 10007 si pozitive.
