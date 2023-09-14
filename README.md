
### 1) Název datové struktury / algoritmu / problému
AVL strom.
### 2) Použitý programovací jazyk
c++
### 3) Použité knihovny a k čemu
queue - ve funkcích wide_print() a depth()
iomanip - pro std::set a std::right
iostream
stack - ve funkci findNode(string y)
### 4) Popis a diskuze zvolených algoritmů
  Funkce insert(int x, node* t, string y) přidá nový vrchol do stromu na odpovídající místo a poté rotuje s vrcholy za účelem uchování vyváženosti. 
Funkce přidává vrcholy na konec(jako list) a potom se rekursivně vrací a určuje potřebu rotaci, popř. to vykoná náležité rotace.
  Funkce remove(int x, node* t) odstraní daný vrchol a poté kontroluje množství potomků(kvůli zachování struktury stromu).
Potom zkontroluje rekursivně jako u insert potřebu rotací.
### 5) Použití 
K ukládání dat do uspořádané databáze. AVL strom v případech kdy vyhledávání převažuje nad přidáváním/odstraňováním.
### 6) Příklad testů metod 
    tree t;
    t.insert(14, "e");
    t.insert(50, "f");
    t.insert(565, "g");
    t.insert(300, "h");
    t.insert(222, "i");
    t.insert(144, "j");
    t.insert(144, "k");
    t.display();
    t.wide_print();
    t.remove(300);
    t.display();
    t.wide_print();
    t.remove("g");
    t.display();
    t.wide_print();
### 7) Diskuze výběru algoritmů
Obě funkce insert a remove při rekursivním provedením zajistí že všechny vrcholy, kterými jsme procházeli při hledaní(správného místa pro insert a náležitého vrcholu pro insert), budou zpětně kontrolované v opačném pořadí.
### 8) Porovnání s STL knihovnou - pouze v případě že programujete kontejner, jehož alternativa se nachází v STL knihovně
Vkládání a mazaní prvku je pomalejší, ale  urychlí to vyhledávání.

### 9) Diskuze k implementaci - možnosti dalšího vylepšení
Na funkci findNode(string y) jsem mohl využít queue jako u jiných funkcí a tím se starat o knihovnu méně.
