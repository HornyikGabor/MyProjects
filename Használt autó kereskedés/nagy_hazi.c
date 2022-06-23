#include<stdio.h>
#include<stdlib.h>
#include<string.h>


enum {SIZE_OF_WORD = 15, LONG_OF_LINE = 26, SIZE_OF_BOX1 = 13, SIZE_OF_BOX2 = 20}; 

typedef struct{ //*Az autok azon adatait, amik nem tartalmaznak szamokat, csak stringbol allnak a car_datas structura definiálja*//
    char *desgin; 
    char *fuel;
    char *condition;
    char *propulsion;
}car_datas; 

typedef struct{ //*A car struktura egy autot definiál a specifikacioinak és adatainak megadasaval*//
    char *car_name;
    int production_year;
    int mileage;
    int cylinder_capacity;
    int horsepower;
    car_datas car;
}car;

typedef struct{ //*A production_time_interval stuktura definiálja azt az intervallumot, ami azt az idoszakot adja meg, amelyik idoszakban gyartott autok erdeklik a vevot*//
    int from; 
    int to;
}production_time_interval;

typedef struct{ //*A mileage_interval struktura azt a ket kilometer allast adja meg, aminel tobbel, illetve kevesebbel rendelkezo autok erdeklik a vevot*//
    int from; 
    int to; 
}mileage_interval;

typedef struct{ //*A cylinder_capacity struktura szinten egy intervallumot definiál, az also es a felso hatar koze eso kobcentimeteres motorral rendelkezo autok erdeklik a vevot*//
    int from; 
    int to; 
}cylinder_capacity;

typedef struct{ //*A horse_power struktura azt az intervallumot definiálja, ami a teljesitmenyre vonatkozik, amit az auto motorja le tud adni.*//
    int from;
    int to;
}horse_power;

typedef struct{ //*A customer struktura egy vevot ad meg az adatai es igenyei alapjan*//
    char *name;
    char *phone_mumber;
    char *postcode;
    production_time_interval time_interval;
    mileage_interval  distance_interval;
    cylinder_capacity capacity_interval;
    horse_power power_interval;
    car_datas car;
}customer;

typedef struct list_customer{//*A vasarlokat tartalmazo lista egy-egy elemeben a vasarlo, valamint a megelozo es a kovetkezo elem cime van*//
    customer person;
    struct list_customer *next, *prev;
}list_customer;

typedef struct list_car{//*Az autokat tartalmazo lista egy-egy elemeben az auto, valamint a megelozo es a kovetkezo elem cime van*//
    car car;
    struct list_car *next, *prev;
}list_car;

typedef struct{//*Stuktura a vevoket tartlamzo lista fejet es farkat definialja*//
    list_customer *head, *tail;
}list1;

typedef struct {//*Struktura az autokat tartalmazo lista fejet es farkat definialja*//
    list_car *head, *tail;
}list2;

typedef struct pair{//*Ez a lista az egyes vevoknek ajanlot autot, valamint a vevot tarolja*//
    car car;
    customer person;
    struct pair *next;
}pairlist;


//*program mukodesehez szukseges fuggvenyek letrehozazasa*//

/**
 * @brief A függvényt szavak beolvasására használja a program.
 * @param filepoiner Az éppen megnyitott fájlra mutató pointer.
 * @param u Egy pointer, ami arra a memória területre mutat, ahol a string lesz eltárolva
 * @return char * Karakterre mutató pointer (string)
 */
char *scan(FILE *filepointer, char *u)
{
    if(filepointer != NULL && u != NULL)
        fscanf(filepointer, "%s ", u);
    return u;
}

/**
 * @brief A függvény egy autó adatainak a beolvasására képes, 
 * majd ezeket az adatokat eltárolja a 'car' tipúsú listában.
 * @param filepointer_autos Pointer, ami arra a megnyitott,  autokat tartalmazó , fáljra mutat, amiből a program be fog olvasni.
 * @param an_auto Pointer, ami egy "autóra" mutat, amelyik "autóban" lesznek eltárolva a beolvasott adatok.
 * @return int igaz érték, a beolvasásban részt vevő while() ciklusnál lesz szerepe
 * 
 */
int scan_car_datas(FILE *filepointer_autos, car *an_auto) 
{
    car automobile;
    char *t = malloc(SIZE_OF_WORD * sizeof(char));
    automobile.car_name = scan(filepointer_autos, t);
    fscanf(filepointer_autos, "%d %d %d %d ", &automobile.production_year, &automobile.mileage, &automobile.cylinder_capacity, &automobile.horsepower);
    char *p = malloc(SIZE_OF_WORD * sizeof(char));
    automobile.car.desgin = scan(filepointer_autos, p);
    char *q = malloc(SIZE_OF_WORD * sizeof(char));
    automobile.car.fuel = scan(filepointer_autos, q);
    char *r = malloc(SIZE_OF_WORD * sizeof(char));
    automobile.car.condition = scan(filepointer_autos, r);
    char *m = malloc(SIZE_OF_WORD * sizeof(char));
    automobile.car.propulsion = scan(filepointer_autos, m);
    *an_auto = automobile;
    return 1;
}

/**
 * @brief Ez a függvény egy ember adatait és igényeit képes beolvasni.
 * @param filepointer_customers Pointer, ami arra a megnyitott, vevőket tartalmazó, fáljra mutat, amiből a program be fog olvasni.
 * @param Pointer, ami egy "vevőre" mutat, amelyik "vevőbe" lesznek eltárolva a beolvasott adatok.
 * @return int igaz érték, a beolvasásban részt vevő while() ciklusnál lesz szerepe
 */ 
int scan_customer_datas(FILE *filepointer_customers, customer *a_person) 
{
    customer person;
    char *p = malloc(SIZE_OF_WORD * sizeof(char));
    person.name = scan(filepointer_customers, p);
    char *t = malloc(SIZE_OF_WORD * sizeof(char));
    person.phone_mumber = scan(filepointer_customers, t);
    char *n = malloc(SIZE_OF_WORD * sizeof(char));
    person.postcode = scan(filepointer_customers, n);
    fscanf(filepointer_customers, " %d %d", &person.time_interval.from, &person.time_interval.to); 
    fscanf(filepointer_customers, " %d %d", &person.distance_interval.from, &person.distance_interval.to);
    fscanf(filepointer_customers, " %d %d", &person.capacity_interval.from, &person.capacity_interval.to);
    fscanf(filepointer_customers, " %d %d", &person.power_interval.from, &person.power_interval.to);
    char *q = (char *)malloc(SIZE_OF_WORD * sizeof(char));
    person.car.desgin = scan(filepointer_customers, q);
    char *r = (char *)malloc(SIZE_OF_WORD * sizeof(char));
    person.car.fuel = scan(filepointer_customers, r);
    char *s = (char *)malloc(SIZE_OF_WORD * sizeof(char));
    person.car.condition = scan(filepointer_customers, s);
    char *m = (char *)malloc(SIZE_OF_WORD * sizeof(char));
    person.car.propulsion = scan(filepointer_customers, m);
    *a_person = person;
    return 1;
}

/**
 * @brief Ez a függvény egy két strázsás, két irányba láncolt listát hoz létre, amely a beolvasott vevőket tárolni fogja.
 */
list1 create_list1(void)
{
    list1 l;
    l.head = malloc(sizeof(list_customer));
    l.tail = malloc(sizeof(list_customer));
    l.head -> next = l.tail;
    l.tail -> prev = l.head;
    l.tail->next = NULL;
    return l;
}

/**
 * @brief Ez a függvény egy két strázsás, két irányba láncolt listát hoz létre, amely a beolvasott autókat tárolni fogja.
 */
list2 create_list2(void)
{
    list2 l;
    l.head = malloc(sizeof(list_car));
    l.tail = malloc(sizeof(list_car));
    l.head -> next = l.tail;
    l.tail -> prev = l.head;
    l.tail->next = NULL;
    return l;
}

/**
 * @brief Ez a függvény egy új elem beillesztérésre alkalmas a vevőket tartalmazó listába.
 * @param prev A beillesztendő elemet megelőző elemre mutató pointer
 * @param next A beillesztendő elemet követő elemre mutató pointer
 * @param ps A beillesztendő elem (vevő)
 * @return void
 */ 
void insert_between_customers(list_customer *prev, list_customer *next, customer ps)
{
    list_customer *p = malloc(sizeof(list_customer));
    p -> person = ps;
    p -> prev = prev;
    prev -> next = p;
    p -> next = next;
    next -> prev = p;
}

/**
 * @brief Ez a függvény egy új eleme beillesztésére alkalmas az autókat tartalmazó listába.
 * @param prev A beillesztendő elemet megelőzőre mutató pointer
 * @param next A beillesztendő elemet követőre mutató pointer
 * @param cr A beillesztendő elem (autó)
 * @return void
 */
void insert_between_cars(list_car *prev, list_car *next, car cr)
{
    list_car *p = malloc(sizeof(list_car));
    p -> car = cr;
    p -> prev = prev;
    prev -> next = p;
    p -> next = next;
    next -> prev = p;
}

/**
 * @brief A függvény az insert_between_customers() segítségével hátulról előre haladva tölti fel a a vevőket tartalmazó listát.
 * @param g A listára mutató pointer, amibe beilleszt
 * @param ps Az elem, amit beilleszt
 * @return void
 */
void push_front1(list_customer *g, customer ps){  
    insert_between_customers(g->prev, g, ps);
}

/**
 * @brief A függvény az insert_between_customers() segítségével hátulról előre haladva tölti fel a a vevőket tartalmazó listát.
 * @param h A listára mutató pointer, amibe beilleszt
 * @param cr Az elem, amit beilleszt
 * @return void
 */
void push_front2(list_car *h, car cr){
    insert_between_cars(h->prev, h, cr);
}

/**
 * @brief A függvény a beolvasótt autókat egy táblázatban kilistázza. A fejlécben vannak megadva az adatok fajtái.
 * @param autos A lista, aminek a tartalmát kilistázza a program.
 * @return void
 */
void print_cars(list2 autos)
{
    list_car *p;
    for(int i = 0; i < 10 * SIZE_OF_BOX1 + 4; i++)
        printf("_");
    printf("\n");
    printf("| Auto neve    "); printf("| Gyartas      "); printf("| Megtett tav  "); 
    printf("| Urtartalom   "); printf("| Loero        "); printf("| Kialakitas   "); 
    printf("| Uzemanyag    "); printf("| Allapot      "); printf("| Meghajtas   |");
    printf("\n|");
    for(int i = 0; i < 10 * SIZE_OF_BOX1 + 3; i++)
        printf("_");
    printf("|\n");
    for(p = autos.head->next->next; p != autos.tail; p = p->next)
    {
        int hossz1 = strlen(p->car.car_name);
        int hossz2 = strlen(p->car.car.desgin);
        int hossz3 = strlen(p->car.car.fuel);
        int hossz4 = strlen(p->car.car.condition);
        int hossz5 = strlen(p->car.car.propulsion);
        printf("| %s", p->car.car_name);
        for(int i = 0 ; i < (SIZE_OF_BOX1 - hossz1); i++) printf(" ");
        printf("| %d", p->car.production_year);
        for(int i = 0 ; i < SIZE_OF_BOX1 - 4; i++) printf(" ");
        printf("| %d", p->car.mileage);
        if(p->car.mileage > 100000)
            for(int i = 0 ; i < SIZE_OF_BOX1 - 6; i++) printf(" ");
        else 
            for(int i = 0 ; i < SIZE_OF_BOX1 - 5; i++) printf(" ");
        printf("| %d", p->car.cylinder_capacity);
        for(int i = 0; i < SIZE_OF_BOX1 - 4; i++) printf(" ");
        printf("| %d", p->car.horsepower);
        for(int i = 0; i < SIZE_OF_BOX1 - 3; i++) printf(" ");
        printf("| %s", p->car.car.desgin);
        for(int i = 0 ; i < SIZE_OF_BOX1 - hossz2; i++) printf(" ");
        printf("| %s", p->car.car.fuel);
        for(int i = 0 ; i < SIZE_OF_BOX1 - hossz3; i++) printf(" ");
        printf("| %s", p->car.car.condition);
        for(int i = 0 ; i < SIZE_OF_BOX1 - hossz4; i++) printf(" ");
        printf("| %s", p->car.car.propulsion);
        for(int i = 0 ; i < SIZE_OF_BOX1 - hossz5 - 1; i++) printf(" ");
        printf("|\n");
    }
    printf("|");
    for(int i = 0; i < 10 * SIZE_OF_BOX1 + 3; i++)
        printf("_");
    printf("|\n");
}

/**
 * @brief A függvény a beolvasott autókat egy táblázatban kilistázza. A fejlécben vannak megadva az adatok fajtái.
 * @param people A lista, aminek az elemit kilistázza a program.
 * @return void 
 */
void print_customers(list1 people)
{
    list_customer *p;
    for(int i = 0; i < 10 * SIZE_OF_BOX2 - 2; i++)
        printf("_");
    printf("\n");
    printf("| Vevo neve           "); printf("| Gyartas(tol,ig)     "); printf("|  Megtett tav(tol,ig)"); 
    printf("| Urtartalom(tol,ig)  "); printf("| Loero(tol,ig)       "); printf("|  Kialakitas         "); 
    printf("| Uzemanyag           "); printf("| Allapot             "); printf("|  Meghajtas         |");
    printf("\n|");
    for(int i = 0; i < 10 * SIZE_OF_BOX2 - 4; i++)
        printf("_");
    printf("|\n");
    for(p = people.head->next->next; p != people.tail; p = p->next)
    {
        int hossz1 = strlen(p->person.name);
        int hossz2 = strlen(p->person.car.desgin);
        int hossz3 = strlen(p->person.car.fuel);
        int hossz4 = strlen(p->person.car.condition);
        int hossz5 = strlen(p->person.car.propulsion);
        printf("| %s", p->person.name);
        for(int i = 0 ; i < (SIZE_OF_BOX2 - hossz1); i++) printf(" ");
        printf("| %d-%d", p->person.time_interval.from, p->person.time_interval.to);
        for(int i = 0 ; i < SIZE_OF_BOX2 - 9; i++) printf(" ");
        printf("| %d-%d", p->person.distance_interval.from, p->person.distance_interval.to);
        if(p->person.distance_interval.from == 0 && p->person.distance_interval.to >= 100000)
            for(int i = 0 ; i < SIZE_OF_BOX2 - 8; i++) printf(" ");
        else 
            for(int i = 0 ; i < SIZE_OF_BOX2 - 13; i++) printf(" ");
        printf("| %d-%d", p->person.capacity_interval.from, p->person.capacity_interval.to);
        for(int i = 0; i < SIZE_OF_BOX2 - 9; i++) printf(" ");
        printf("| %d-%d", p->person.power_interval.from, p->person.power_interval.to);
        for(int i = 0; i < SIZE_OF_BOX2 - 7; i++) printf(" ");
        printf("| %s", p->person.car.desgin);
        for(int i = 0 ; i < SIZE_OF_BOX2 - hossz2; i++) printf(" ");
        printf("| %s", p->person.car.fuel);
        for(int i = 0 ; i < SIZE_OF_BOX2 - hossz3; i++) printf(" ");
        printf("| %s", p->person.car.condition);
        for(int i = 0 ; i < SIZE_OF_BOX2 - hossz4; i++) printf(" ");
        printf("| %s", p->person.car.propulsion);
        for(int i = 0 ; i < SIZE_OF_BOX2 - hossz5 - 1; i++) printf(" ");
        printf("|\n");
    }
    printf("|");
    for(int i = 0; i < 10 * SIZE_OF_BOX2 - 4; i++)
        printf("_");
    printf("|\n");
}

/**
 * @brief A függvény feltölt egy listát autó-vevő párokkal. A párokat az alapján hozza létre, 
 * horgy egy autó megfelel-e egy vevő igényeinek.
 * @param recom Listára mutató pointer, amelyik listában a párokat el fogja tárolni a program
 * @param car Az autó, amelyik megfelel az igényeknek
 * @param person A vevő, akihez a "car" autót rendelte a program.
 * @return A párokat tartalmazó lista 
 */ 
pairlist *push_front(pairlist *recom, car car, customer person)
{
    pairlist *p = malloc(sizeof(pairlist));
    p->car = car;
    p->person = person;
    p->next = recom;
    recom = p;
    return recom;
}

/**
 * @brief Megvizsgálja, hogy egy adott autó tulajdonságai megfelelnek-e egy adott vevő igényeinek.
 *
 * @param assign A változó azt figyeli, hogy hány tulajdonság felel meg az igényeknek 
 * @param p A vevőket tartalmazó listára mutató pointer.
 * @param q Az autókat tartalmazó listára mutató pointer.
 * @return int Ha megegyezik az autó adatainak számával, akkor az autó megfelel az igényeknek
 */
int compare_cars_and_customers(int assign, list_customer *p, list_car *q)
{
    if(p->person.time_interval.from <= q->car.production_year && q->car.production_year <= p->person.time_interval.to)
        assign += 1;
    if(p->person.distance_interval.from <= q->car.mileage && q->car.mileage <= p->person.distance_interval.to)
        assign += 1;
    if(p->person.capacity_interval.from <= q->car.cylinder_capacity && q->car.cylinder_capacity <= p->person.capacity_interval.to)
        assign += 1;
    if(p->person.power_interval.from <= q->car.horsepower && q->car.horsepower <= p->person.power_interval.to)
        assign += 1;
    if(strcmp(p->person.car.desgin, q->car.car.desgin) == 0)
        assign += 1;
    if(strcmp(p->person.car.fuel, q->car.car.fuel) == 0)
        assign += 1;
    if(strcmp(p->person.car.condition, q->car.car.condition) == 0)
        assign += 1;
    if(strcmp(p->person.car.propulsion, q->car.car.propulsion) == 0)
        assign += 1;
    return assign;
}

/**
 * @brief A függvény egy új pár (autó-vevő) elemet hoz létre, amit beilleszt a párok listájába
 * 
 * @param r Pointer, ami a recom lista azon elemére mutat, ahova az új párlista elemet beszúrjuk.
 * @param assign Ha beszúrunk egy új elemet az assign-t ki kell nullázni.
 * @param dupla Az figyeli, hogy az adott vevőnek ajánlott-e már a program autót.
 * @param q Az autókat tartalmazó lista egy adott elemére mutató pointer.
 * @param p A vevőket tartalmazó lista egy adott elemére mutató pointer.
 */
void insert_pairs(pairlist *r, int assign, int dupla, list_car *q, list_customer *p)
{
    pairlist *n;
    n = r->next;
    r->next = malloc(sizeof(pairlist));
    r->next->car = q->car;
    r->next->person = p->person;
    r->next->next = n;
    assign = 0;
    dupla = 1;
}

/**
 * @brief A függvény két autó közül eldönti, hogy melyik a jobb, tuljadonságaik alapján.
 * @param an_auto1
 * @param an_auto2
 * @return 1, 0 vagy -1, attól függően melyik autó "nyert".
 */ 
int compare_autos(car an_auto1, car an_auto2)
{
    int assign1 = 0, assign2 = 0;
    if(an_auto1.mileage < an_auto2.mileage) assign1++;
    else if(an_auto1.mileage > an_auto2.mileage) assign2++;
    if(an_auto1.horsepower > an_auto2.horsepower) assign1++;
    else if(an_auto1.horsepower < an_auto2.horsepower) assign2++;
    if(an_auto1.cylinder_capacity > an_auto2.cylinder_capacity) assign1++;
    else if(an_auto1.cylinder_capacity < an_auto2.cylinder_capacity) assign2++;
    if(*an_auto1.car.propulsion == 'A') assign1++;
    else if(*an_auto2.car.propulsion == 'A') assign2++;
    if(assign1 > assign2)
        return 1;
    else {
        if(assign1 < assign2)
            return -1;
        else 
            return 0;
    }
}

/**
 * @brief A függvény kiírja a kapot autót.
 * @param car
 */
void print_car_name(car car)
{
    printf("%s", car.car_name);
}

/**
 * @brief A függvény kiírja, hogy melyik autó jobb az adott tulajdonság szempontjából.
 * @param an_auto1
 * @param an_auto2
 * @return void
 */
void print_car_compare(car an_auto1, car an_auto2)
{
    printf("A kevesebb kilometer megtett auto: ");
    if(an_auto1.mileage < an_auto2.mileage) print_car_name(an_auto1);
    else if(an_auto1.mileage > an_auto2.mileage) print_car_name(an_auto2);
    printf("\nA nagyobb teljesitmenyu motorral rendelkezo auto: ");
    if(an_auto1.horsepower > an_auto2.horsepower) print_car_name(an_auto1);
    else if(an_auto1.horsepower < an_auto2.horsepower) print_car_name(an_auto2);
    printf("\nA nagyobb hengerurtartalommal rendelkezo auto: ");
    if(an_auto1.cylinder_capacity > an_auto2.cylinder_capacity) print_car_name(an_auto1);
    else if(an_auto1.cylinder_capacity < an_auto2.cylinder_capacity) print_car_name(an_auto2);
    printf("\nOsszkerekhajtassal rendelkezo auto: ");
    if(*an_auto1.car.propulsion == 'A') print_car_name(an_auto1);
    else if(*an_auto2.car.propulsion == 'A') print_car_name(an_auto2);
    printf("\n");
}

/**
 * @brief A függvény 2 autómárka összehasonlítására képes. A függvény beolvas két autót, elraktározza azokat, majd eldönti, hogy melyik
 * a jobb. A függvény ki is listázza, hogy az melyik autónak melyik tulajdonsága a jobb.
 * 
 * @param autos A lista, amelyik az autókat tartalmazza.
 */
void print_compares(list2 autos)
{
    char *auto1; char *auto2; car an_auto1, an_auto2;
    int is_there1 = 0, is_there2 = 0;
    list_car *q; 
    printf("(Ha tobb autora nem kivancsi, irja /STOP/)\n");
    while(1)
    {
        printf("Adjon meg ket olyan auto markat, amit ossze szeretne hasonlitani: \n");
        auto1 = malloc(20 * sizeof(char));
        auto2 = malloc(20 *sizeof(char));
        scanf("%s", auto1);
        if(strcmp(auto1, "STOP") == 0) 
        {
            free(auto1); free(auto2);
            return;
        }
        scanf("%s", auto2);
        if(strcmp(auto1, auto2) == 0)
        {
            printf("\n--error--\nUgyanazt az autot adta meg ketszer\n");
            free(auto1); free(auto2);
            continue;
        }
        for(q = autos.head->next; q != autos.tail; q = q->next)
        {
            if(strcmp(q->car.car_name, auto1) == 0)
            {
                an_auto1 = q->car;
                is_there1++;
            }
            if(strcmp(q->car.car_name, auto2) == 0)
            {
                an_auto2 = q->car;
                is_there2++;
            }
        }
        if(is_there1 == 0 || is_there2 == 0)
        {
            printf("Az egyik auto (esetleg mindeketto) nem talalhato meg az adatbazisban\n");
            free(auto1); free(auto2);
            continue;
        }
        printf("A specifikacioi alapjan a jobb auto: \n");
        if(compare_autos(an_auto1, an_auto2) > 0)
            printf("%s\n", auto1);
        else {
            if(compare_autos(an_auto1, an_auto2) < 0)
                printf("%s\n", auto2);
        else 
            printf("A ket auto ugyanolyan specifikaciokkal rendelkezik.\n");
        }
        print_car_compare(an_auto1, an_auto2);
        free(auto1); free(auto2);
    }
}

/**
 * @brief A függvény kiírja a párokat tartalmazó lista tartalmát. 
 * Táblázatos formában teszi ezt, minden sor egy ajánlás.
 * @param recom A párokat tartalmazó listára mutató pointer
 * @return void
 */
void print_results(pairlist *recom) 
{
    pairlist *m; 
    for(int k = 0; k < 2 * LONG_OF_LINE + 4; k++) 
            printf("_"); 
    for(m = recom; m != NULL; m = m->next)
    {
        int hossz, hossz2, hossz4;
        printf("\n");
        printf("| Nev: %s", m->car.car_name); 
        hossz = strlen(m->car.car_name);
        for(int i = 0; i < LONG_OF_LINE - hossz - 5; i++)
            printf(" ");
        printf("| Nev: %s", m->person.name); 
        hossz2 = strlen(m->person.name);
        for(int i = 0; i < LONG_OF_LINE - hossz2 - 5; i++)
            printf(" ");
        printf("|\n");
        printf("| Gyartasi ev: %d", m->car.production_year);
        for(int i = 0; i < LONG_OF_LINE - 4 - 13; i++)
            printf(" ");
        printf("| Telefon szam: %s", m->person.phone_mumber);
        for(int i = 0; i < LONG_OF_LINE - 11 - 14; i++)
            printf(" ");
        printf("|\n");
        printf("| Megtett tav: %d", m->car.mileage); 
        if(m->car.mileage < 100000)
            hossz4 = 5;
        else 
            hossz4 = 6;
        for(int i = 0; i < LONG_OF_LINE - hossz4 - 13; i++)
            printf(" "); 
        printf("| Iranyitoszam: %s", m->person.postcode); 
        for(int i = 0; i < LONG_OF_LINE - 4 - 14; i++)
            printf(" ");
        printf("|\n|");
        for(int k = 0; k < 2 * LONG_OF_LINE + 3; k++)
            printf("_");
        printf("|");   
    }
}

/**
 * @brief A függvény beolvas egy automarkat es kiirja annak fajlagos teljesitmenyet, vagyis az egysegnyi kobcentimeterre juto loerot.
 * @param autos Az autokat tartalmazo lista. 
 */
void print_specific_performance(list2 autos)
{
    printf("(Ha tobb autora nem kivancsi, irja /STOP/)\n");
    double max_specific_performance = 0;
    char *max_specific_performance_car = malloc(15 * sizeof(char));
    while(1)
    {
        char *str = malloc(15 * sizeof(char)); double specific_performance = 0.0;
        scanf("%s", str);
        if(strcmp(str, "STOP") == 0)
        {
            free(str);
            break;
        }
        if(strcmp(str, "Tesla") == 0)
        {
            printf("A Tesla markaju autonak nincsen robbanomotorja, mivel elektromos jarmu, ezert a motor terfogatarol se beszelunk.\n");
            free(str);
            continue;
        }
        for(list_car *p = autos.head->next->next; p != autos.tail; p = p->next)
            if(strcmp(str, p->car.car_name) == 0)
            {
                specific_performance = (double)p->car.horsepower / (double)p->car.cylinder_capacity;
                break;
            }
        if(specific_performance == 0.0)
            printf("A megadott markaju auto nem szerepel az adatbazisban.\n");
        else 
            printf("A motor fajlagos loereje %.4f loero/cm^3\n", specific_performance);
        if(specific_performance > max_specific_performance)
        {
            max_specific_performance = specific_performance;
            strcpy(max_specific_performance_car, str);
        }
        free(str);
    }
    printf("A legnagyobb fajlagos teljesitmeny (azaz az egy kobcentimeterre juto teljesitmeny): %f loero/cm^3\nEs az azzal rendelkezo auto: %s", max_specific_performance, max_specific_performance_car);
    free(max_specific_performance_car); 
}

/**
 * @brief A függvény felszabadítja az autokat tartalmazó lista létrehozásánál lefoglalt memóriát.
 * @param autos Az autókat tartalmazó lista.
 */
void delete_autos(list2 autos)
{
    while(1)
    {
        list_car *p;
        p = autos.head->next;
        char *a = p->car.car_name; char *b = p->car.car.condition; char *c = p->car.car.desgin;
        char *d = p->car.car.fuel; char *e = p->car.car.propulsion;
        if(p == autos.tail) break;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p); free(a); free(b); free(c); free(d); free(e);
    }
    free(autos.head); free(autos.tail);
}

/**
 * @brief A függvény felszabadítja az vevőket tartalmazó lista létrehozásánál lefoglalt memóriát.
 * @param people Vevőket tartalmazó lista.
 */
void delete_people(list1 people)
{
    while(1)
    {
        list_customer *p;
        p = people.head->next;
        char *a = p->person.name, *b = p->person.phone_mumber, *c = p->person.postcode;
        char *d = p->person.car.condition, *e = p->person.car.desgin, *f = p->person.car.fuel, *g = p->person.car.propulsion;
        if(p == people.tail) break;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p); free(a); free(b); free(c); free(d); free(e); free(f); free(g);
    }
    free(people.head); free(people.tail);
}

/**
 * @brief A függvény felszabadítja a párokat tartalmazó lista létrehozásánál lefoglalt memóriát. 
 * @param recom Pointer, ami a párokat tartalmazó listára mutat.
 */
void delete_recom(pairlist *recom)
{
    while(recom != NULL)
    {
        pairlist *p = recom;
        recom = recom->next;
        free(p);
    }
}



//*foprogram*//
int main(void)
{
    //*memoria foglalas*//
    list1 people = create_list1(); list2 autos = create_list2(); pairlist *recom = NULL; //*A program álltal beolvasott, valamint előállított adatok eltárolására szolgáló listák létrehozása.*//
    car an_auto; customer a_person; list_customer *p; list_car *q; int assign = 0; //*Ideiglenesen tárolt autó és vevő típusú memória terület lefoglalása, valamint a vevők igényeinek és az autó adatainak összehasonlítását segítő "assign".*//
    list_car *h = autos.tail; list_customer *g = people.tail; //*Az autók és a vevő adatainak beolvasását segítő pointerek.*//


    //*beolvasas*//
    FILE *filepointer_autos = fopen("autok_adatai.txt", "r"); //*A program megnyitja az autók adatai tartalmazó fájlt.*//
    FILE *filepointer_customers = fopen("vevok_adatai.txt", "r"); //*A program megnyitja a vevők adatai tartalamzó fájlt.*//
    if(filepointer_customers == NULL || filepointer_autos == NULL) //*Ha az egyik, esetleg mindkét fájl üres, hibaüzenet kerül a kimenetre.*//
    {
        printf("Hiba: valamelyik fajl, esetleg mindketto, nem talalhato!");
        return 1;
    }
    while(scan_car_datas(filepointer_autos, &an_auto))//*Végtelen ciklus segítségével az autók adatainak beolvasása. Az olvasás a végjelig tart (0).*//
    {
        push_front2(h, an_auto); 
        h = h->prev;
        char *q;
        q = an_auto.car_name; 
        if(*q == '0')
            break;
    }
    fclose(filepointer_autos); //*Autókat tartalmazó fájl bezárása.*//
    while(scan_customer_datas(filepointer_customers, &a_person))//*Végtelen ciklus segítségével a vevők adatainak beolvasása. Az olvasás a végjelig tart (0).*//
    {
        push_front1(g, a_person);
        g = g->prev;
        char *q;
        q = a_person.name;
        if(*q == '0')
            break;
    }
    fclose(filepointer_customers); //*Vevőket tartalmazó fájl bezárása.*//

    //*beolvasott adatok kiírása*//
    printf("A kereskedesnel arult autokat az alabbi tablazatban lehet megtekinteni, a tablazat tartalmazza az autok adatait is.\n");
    print_cars(autos);//*Táblázatban az autók adatainak kiírása.*//
    printf("Korabban az erdeklodo vevok megadtak igenyeiket, hogy milyen parameterrel rendelkezo auto erdekelne oket.\nAz alabbi tablazat tartalmazza a vevoket es az igenyeket:\n");
    print_customers(people); //*Táblázatban a vevők adatainak kiírása.*//

    //*vizsgalat, hogy az auto megfelel-e az igenyeknek*//
    for(p = people.head->next->next; p != people.tail; p = p->next) //*Két, egymásba ágyazott for ciklussal bejárja a program az autók és a vevők listáját,*//
        for(q = autos.head->next->next; q != autos.tail; q = q->next) //*és ha egy autó megfelel a vevő igényeinek akkor egy párt hot létre, amit a recom listában tárol el.*//
        {
            assign = compare_cars_and_customers(assign, p, q);
            if(assign == 8 &&  recom != NULL)
            {
                int dupla = 0;
                for(pairlist *r = recom->next; r != NULL; r = r->next)
                    if(r->person.name == p->person.name)
                        insert_pairs(r, assign, dupla, q, p);
                if(dupla == 1)
                    break;
            }
            if(assign == 8)
            {
                recom = push_front(recom, q->car, p->person);
                assign = 0;
            }
            assign = 0;
        }


    //*eredmeny kiirasa*//
    printf("\n\nA program az alabbi autokat ajanlja az egyes vevoknek.\nNem feltetlenul ajanl minden erdeklodonek autot.\n");
    printf("A tablazat feltunteti a vevok es az autok adatait is.\n");
    printf("\n");
    print_results(recom);//*Táblázatos formában a korábban létrehozott párokat tartalmazó lista kiírása.*//
    printf("\n\n");

    //*két autó összehasonlítása*//
    printf("A program kepes arra, hogy osszehasonlitson ket automarkat.\n");
    printf("Figyeljen arra, hogy pontosan adja meg az automarka nevet, mert az esetleges elirasok eseten a program nem talalja meg az adott markat.\n");
    print_compares(autos); //*A program összehasonlít két autó márkát, eldönti melyik a jobb valamint kiírja, hogy az egyes tulajdonságokból melyik autó a jobb.*//
    printf("A program tovabba kepes a fajlagos teljesitmeny kiszamitasara.\n Adjon meg egy auto markat es ha benne vannak az adatbazisban, a program kiirja a fajlagos teljesitmeny.\n");
    printf("(A fajlagos teljesitmeny az egysegnyi kobcentimeterre juto teljesitmeny hatarozza meg)\n");
    print_specific_performance(autos);//*A program végül kiszámolja a "fajlagos teljesítményt" egy megadott autómárkára, ha több autót adtak meg kiszámolja a maxot és kiírja azt a számot és az azzal rendelező autót.*//
    
    //A program működése során lefoglalt memória visszaszolgáltatása az operációs rendszernek.*//
    delete_autos(autos);//Az autók számára lefoglalt memóriaterület felszabadítása.*//
    delete_people(people);//A vevők számára lefoglalt memóriaterület felszabadítása.*//
    delete_recom(recom);//A párokat tartalmazó lista számára lefoglalt memóriaterület felszabadítása.*//

    return 0;
}