Autor:
Wolański Grzegorz
188463

Tytuł:
PEA Projekt 1 - TSP na bazie algorytmów Branch&Bound oraz przeglądu zupełnego

Wymogi:
1. Kompilator wspierający minimum C++14.
2. cmake w wersji minimum 3.6

Instrukcja kompilacji i uruchomienia:
1. W bieżącym katalogu roboczym stworzyć katalog dla pliku wykonywalnego (sugerowane nazwy "out" oraz "build").
2. Przejść do powyższego katalogu.
3. Wywołać komendę "cmake ..".
4. Wywołać komendę "make".
5. Plik wykonywalny "bin" powinien powstać w katalogu bieżącym.
   Może mieć rozszerzenie .exe jeżeli jest kompilowany na Windowsie.

Instrukcja dla obsługi plików wejściowych:
1. Wczytanie określonego problemu - program obsługuje format zgodny z opisem w instrukcji do zadania:
   - w pierwszej linicje powinna znajdować się liczba wierzchołków grafu - jedna wartość całkowita dodatnia
   - w każdej kolejnej powinny być wiersze macierzy sąsiedztwa - wartości całkowite dodatnie oddzielone białym znakiem
   - plik powinien się nazywać "tsp_data.txt"
2. Plik konfiguracyjny - jest wykorzystywany przy pomiarach czasu działania algorytmów. Jeżeli takiego pliku nie ma
   program wczyta predefiniowane wartości pomiarowe. Format pliku konfiguracyjnego jest następujący:
   - powinny być wypełnione dwie linijki
   - w pierwszej linijcie podana jest ilość pomiarów każdego z problemów - jedna wartość całkowita dodatnia
   - w drugiej linijce podane są rozmiary problemów do sprawdzenia - wartości całkowite dodatnie oddzielone białym znakiem
   - dla Przeszukiwania Wszerz plik powinien się nazywać "BruteForce_config.txt"
   - dla Branch & Bound plik powinien się nazywać "BranchAndBound_config.txt"
