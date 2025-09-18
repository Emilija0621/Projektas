# Projektas studentų pažymiai

## Trumpas projekto aprašymas:

ši programa skaičiuoja studentų galutinius įvertinimus:
#### Galutinis = 0.4 * vidurkis(ND pažymių)/mediana(ND pažymių) + 0.6 * egzamino pažymys.

Vartotojui leidžia pasirinkti:
1. Įvesti studentus su savo turimais duomenimis.
2. Įvesti studentų vardus, pavardes su savo turimais duomenimis ir namų darbų, egzamino pažymius generuoti atsitiktinai.
3. Spausdinti studentų rezultatus (pasirinkus ar su vidurkiu ar su mediana ar su abiem yra norima skaičiuoti galutinį pažymį).
4. Nuskaityti studentų duomenis iš failo (pavadinimas.txt).
5. Išeiti iš programos.

Failas (pavadinimas.txt), iš kurio norima nuskaityti duomenis turi atrodyti taip:

|  Vardas  |  Pavardė  | ND1 | ND2 | ND3 | ... | NDn | Egzaminas |
|:--------:|:---------:|:---:|:---:|:---:|:---:|:---:|:---------:|
| Vardas1  | Pavardė1  |  8  |  7  |  6  | ... |  9  |     9     |
| Vardas2  | Pavardė2  |  9  |  8  |  8  | ... |  8  |     9     |
| Vardas3  | Pavardė3  |  6  |  5  |  7  | ... |  8  |     9     |
|   ...    |   ...     | ... | ... | ... | ... | ... |    ...    |

Programa buvo testuota su:
- 10 000 studentų failu
- 100 000 studentų failu
- 1 000 000 studentų failu

Naudojant "chrono" modelį, buvo nustatyta per kiek laiko įvyksta failo nuskaitymas bei rezultatų išvedimas (tinkrinta su vieno modelio kompiuteriu, tad rezultatai nėra išsamūs):

| Studentų skaičius | Nuskaitymas (ms) | Skaičiavimas ir spausdinimas (ms)  |
|:-----------------:|:----------------:|:----------------------------------:|
| 10 000            | 137.16           | 1 568.67                           |
| 100 000           | 941.01           | 4 569.07                           |
| 1 000 000         | 4 871.99         | 33 839.26                          |

Naudotos komandos:
- std::chrono::high_resolution_clock::now()
- start_read, end_read
- std::chrono::duration<double, std::milli>

Prie projekto įkelti failai:
- kursiokai.txt
- studentai10000.txt
- studentai100000.txt


