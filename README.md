SANDU ELENA ALEXANDRA 
GRUPA 312CD

//TASK 1
Pentru a oglindi imaginea pe orizontala , am parcurs matricea pe coloane pana la jumatate si am interschimbat elementul de pe poztia [i][j] cu cel de pe pozitia [i][M-j-1], unde M este numarul de coloane al matricei.

//TASK 2
Am alocat o matrice noua , deoarece in urma rotirii cu 90 de grade la stanga , N (numarul de linii ale matricei) si M (numarul de coloane) vor fi inversate. Asftfel, fiecare element de pe pozitia [i][j] din noua matrice va lua valoarea elementului de pe pozitia [j][M-i-1] din matricea originala.

//TASK 3
Am alocat dinamic o matrice care va avea noile dimensiuni primite prin parametru (h si w). Fie varibilele t = coloana pe care ne aflam in noua matrice si m = linia pe care ne aflam. Fiecare element de pe pozitia [t][m] ia valoarea elementului de la pozitia [i][j] din matricea initiala (i porneste de la y primit prin parametru si j porneste de la x),  fara a o depasi (de aceea avem nevoie de conditiile suplimentare : i < y + h si j < x + w).

//TASK 4
Pentru a extinde matricea cu rows randuri in sus si in jos si cu cols coloane in stanga si in dreapta, avem nevoie de o noua matrice de dimensiuni [N + 2 * rows][M + 2 * cols]. Aux va retine codul noului pixel. Am impartit apoi pe 4 zone pentru a atribui mai usor noii matrici noile valori.

//TASK 5
Utilizam 2 variabile ajutatoare pentru a ne arata pozitia pe care ne aflam in noua matrice. In acest sens , fiecare element de pe poztia [i][j] din matricea originala ia valoarea elementului de pe pozitia [t][m], incepand cu elementul aflat pe linia y si coloana x.

//TASK 6
Am folosit variabilele i,j pentru indicii liniilor si coloanelor din matricea originala si k,t pentru indicii liniilor si coloanelor din matricea filtru. Aux va fi dimensiunea filtrului/2 , in x si y retinem pozitiile vecinilor pixelilor (x = linia, y = coloana); s0, s1 si s2 reprezinta sumele cerute pentru cei 3 pixeli. Daca unul dintre vecini se afla in afara matricei , atunci in suma vom adauga 0, altfel vom adauga elementul de la pozitia [x][y]* elementul de la pozitia [k][t] din filtru. Facem acest lucru pentru toti pixelii. Elementul de pe pozitia [i][j] cu pixelul 0 din noua matrice ia valoarea lui s0, cel cu pixelul 1 lui s1 , iar cel cu pixelul 2 lui s2. Daca una dintre sume este < 0, elementul va fi 0, iar daca este > 255 , elementul va fi 255.

//TASK 7
Fie matricea a[k][i][j] unde k va fi indexul matriciilor de N[k] x M[k] elemente pentru fiecare culoare (R,G,B). In matricea filter[l][i][j] l va fi indexul matrciilor de size[l] x size[l] elemente, unde size[l] reprezinta dimensiunea matricei filter de la indexul l. In sirul de caractere in[] vom retine comanda primita. Daca aceasta este "exit" , dezalocam toate matricile a si cele filter si iesim din repetite . Pentru comanda "load" citim dimensiunile pentru noua matrice, si alocam o noua zona pentru matrice in a, insemnand ca se mareste si contorul pentru matrici (k). La comanda "save" , vom trimite salva matricea la calea primita. Pentru comenzile "Apply Horizontal Flip", "Apply Rotate", "Apply crop", "Apply Extend", "Apply Paste" si "Apply Filter" vom apela functiile descrise anterior. Pentru comanda "Create filter" alocam o matrice de size[l] x size[l] elemente , pe care il primim ca parametru , marind de asemenea contorul pentru matricile filter (l). Pentru functiile "Delete filter" si "Delete image" dezalocam memoria retinuta pentru matricile de la indexul primit ca parametru , stergem apoi efectiv matricile de pe pozitia indexului si contorul scade cu o unitate.