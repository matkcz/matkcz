### 1) Název datové struktury / algoritmu / problému
AVL strom
### 2) Základní popis
Krátce úvod oč se jedná, kdy kontejner vznikl, k čemu to slouží.
  AVL strom je samovyvažující binární strom. Vznikl v roce 1962, jméno pochází z iniciálu G. M. Adefson-Velskij a Je. M. Landis. Slouží k organizaci údajů do samovyvažující podoby.
Jeho vlastnost vyváženosti zaručuje, že bude maximálně o 45% vyšší než dokonale vyvážený strom složený ze stejných vrcholů.
### 3) Terminologie
R rotace, L rotace, RL rotace a LR rotace.
### 4) Výpis hlavních metod  / funkcí a jejich asymptotických složitostí 
  Funkce vlož(insert) - vloží vrchol s danými udáji do stromu a vyvaží strom. 
Oproti normálnímu binárnímu stromu, kde to v nejhorším případě muže trvat O(n) pro vložení na správné místo (byl by to vlastne spojový seznam), tak u AVL stromu k tomu nemůže dojít a náročnost vložení bude vždy O(logn)
Vkládání vrcholu na konec zabere O(1) a poté vracení se zpátky až ke kořeni(kvůli kontrole vyváženosti) potrvá O(logn), protože na každe úrovni stromu je potřeba vyvážit maximálně jeden vrchol a rotace zabere jen O(1).
  Funkce odstran(remove) - odstraní vrchol o dané hodnotě, nebo to dojde na konec až k nullptr za listem a tedy neodstraní nic.
V nejhorším případě je to stejné jako u vložení, jen je možnost že to nebude odstraňovat listový vrchol a tedy to bude kratší o pár úrovní stromu.
### 5) Podrobný popis algoritmů
Slovní popis včetně pseudokódů jednotlivých algoritmů včetně obrázků. V případě popisu stromů nebo grafů doporučuju použít grafické programy např. [draw.io](https://app.diagrams.net/).
Insert vloží vrchol se zadanými údaji na místo
    1-pokud aktuální vrchol je nullptr
    2-jinak pokud zjistí že aktuální vrchol je vetší než zadaná hodnota, tak dá (zase) insert do levého podstromu
    3-a nebo pokud to zjistí že aktuální vrchol je menší než zadaná hodnota, tak dá (zase) insert do pravého podstromu
  -při prvním dokončení (poslední) rekurze (v případě kdy došlo k podmínce 1) dojde k úprave výšky vrcholu
  -při dokončování předešlých rekurzí
      4-(v případe podmínky 2) se zjistí zda se liší výška levého podstromu - výška pravého podstromu se rovná 2
        -a pokud jsou data levého potomka větší než zadaná hodnota tak dojde k jedné pravé rotaci
          u R-rotace se nastaví pomocný vrchol na levého potomka aktuálního vrcholu;
          levý potomek aktuálního vrcholu se nastaví na pravý potomek pomocného vrcholu;
          pravý potomek se nastaví na aktuální potomek
          a upraví se výška aktuálního a pomocného vrcholu, aby odpovídala
        -jinak dojde k dvojité LR rotaci
          dvojitá LR-rotace nejprve dojde k L-rotaci(což je zrcadlová R-rotace) levého potomka a pak dojde k R-rotaci
        -znova se na konci rekurse změní výška vrcholů
      5-(v případe podmínky 2) dochází k zrcadlovému porvedení jako u případu podmínky 2
Remove odstraní vrchol o dané hodnotě
  1-pokud aktuální vrchol není nullptr
  2-jinak pokud je aktuální vrchol větší tak dá remove se zadanou hodnotou do levého podstromu
  3-jinak pokud je menší tak dá remove tak dá remove se zadanou hodnotou do pravého podstromu
  4-jinak pokud není aktuální vrchol nullptr, ani není měnší ani větší (tedy se rovná), tak zjistí jestli má dva potomky a pokud jo, tak upraví ukazatele aby se ani jeden potomek neztratil
  5-jinak vytvoří pomocnou proměnnou curr a zjistí
    -jestli levý potomek aktuálního vrcholu je nullptr a poté nastaví aktuální vrchol na pravého potomka (možná nullptr)
    -a nebo jestli pravý potomek je nullptr a poté nastaví aktuální vrchol na levého potomka
    vymaže curr
  -pokud aktuální vrchol je nullptr(stane se jen v posledním rekursivním volání) tak returne vrchol t(nullptr)
  -jinak to upraví výšku aktuálního vrcholu na odpovídající hodnotu a zjistí podobně jako u insertu stejně případy potřeby rotace 4 a 5 při následujícím dokončováním rekursí.
### 6) Reference
AVL tree-wikipedie
AVL tree-data structure
