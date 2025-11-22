KMP - liczy prefiksosufiksy

Okres słowa - oryginalne słowo jest niepełną wielokrotnością okresu
z każdego okresu o długości p można uzyskać pref-suf o długości n - p
Z każdego pref-suf o długości ps można uzyskać okres o długości n - ps

Lemat o okresowości:
Jeżeli słowo ma okresy o długości a i b (takie, że a + b <= n - 1), to ma też okres o długości NWD(a, b)

Pierwiastek słowa - okres który kończy się równo, oryginalne słowo to okres^k
Pierwiastek pierwotny - najkrótszy pierwiastek.
    Albo to jest najkrótszy okres albo całe słowo
    Każdy pierwiastek słowa jest wielokrotnością pierwiastka pierwotnego

Szablon - słowo którym można pokryć całe oryginalne słowo(mogą się nachodzić te szablony przykrywające na siebie)
    Szablon jest prefiksosufiksem
    Sprawdzenie czy słowo jest szablonem => KMP
    
    q, p - prefiksosufiksy, q - szablon
    jeśli q/2 <= p <= q , to p też szblon
    Jeżeli p nie jest szablonem to najkrótszy szablon ma co najmniej 2p

Ilość wystąpień różnych wzorców w jednym tekście
Jeśli tekst jest ograniczony przez N i sumaryczna długość wzorców jest ograniczona przez M, to w tekście naliczymy maksymalnie N sqrt(M) wystąpień wzorców. W jednym miejscu w tekście może kończyć się max sqrt(M) wzorców (każdy musi mieć inną długość).