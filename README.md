## Question 1 : C++

Les fonctions labda (plus avancé que le cours)

En C++, une fonction lambda est comme une petite fonction (sans nom) que tu écris directement là où tu en as besoin, sans avoir à lui donner un nom. Elle ne peut être utilisez qu'une seule fois. Par exemple, si je veux additionner deux nombres, je peux écrire ```auto add = [](int a, int b) { return a + b; };``` et ensuite faire ```int result = add(2, 3);```. Ce qui est pratique, c’est que la lambda peut utiliser des variables qui sont à l’extérieur d’elle grâce à la capture. Par exemple, ```int x = 10; auto multiply = [x](int y) { return x * y; };``` va utiliser la valeur de x même si elle est définie avant la lambda. On peut capturer par valeur ```[x]``` ou par référence ```[&x]``` si on veut pouvoir modifier la variable originale, comme ```int counter = 0; auto increment = [&counter]() { counter++; };```. Les lambdas sont utiles pour des petites fonctions locales, pour trier des listes ou pour donner des instructions à des fonctions comme sort.

### Exemple
```
int x = 10;
auto multiply = [x](int y) { return x * y; }; // x capturé par valeur
int result2 = multiply(5); // result2 vaut 50
```

## Question 2 : Options de développement possible

Le projet de bibliothèque serait plus facile à réaliser en Python grâce à sa flexibilité avec les types de données et ses bibliothèques intégrées pour gérer les fichiers, les dates et les listes. Par exemple, enregistrer un livre ou un utilisateur dans un fichier .txt se fait en quelques lignes avec open(), split() et join(), sans avoir besoin de s'occuper des conversions compliquées entre nombres et textes ou de la gestion manuelle de la mémoire. De plus, Python permet de manipuler facilement des listes d’objets et de trier ou filtrer les résultats avec sorted() ou des compréhensions de liste. Cela rend le code plus simple, clair et rapide à écrire, contrairement au C++ où il faut gérer plus de détails techniques comme la gestion de mémoire et les conversions de types.