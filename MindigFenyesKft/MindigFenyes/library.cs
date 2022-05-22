using EFCore;
using EFCore.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace MindigFenyes
{
    /// <summary>
    /// Ez az osztály végzi a lekérdezések eredményének kimentését
    /// </summary>
    public class Sorosito
    {
        /// <summary>
        /// Json sorosító osztály, ha létezik a json fájl, akkot hozzá írja a kimentendő statisztikát, ha nem új fájlt hoz létre
        /// </summary>
        /// <param name="file">A fájl neve, ahova a metódus kimenti a statisztikát</param>
        /// <param name="items">Azokat a "Fealadat"-okat tartalmazó lista, ami ki lesz mentve.</param>
        /// <returns></returns>
        public bool Sorositas(string file, List<Feladat> items)
        {
            if (File.Exists(file))
            {

                try {
                    string jsonString = JsonSerializer.Serialize(items);
                    File.AppendAllText(file, jsonString);
                }
                catch (JsonException)
                {
                    return false;
                }
                return true;
            }
            else
            {
                try
                {
                    string jsonString = JsonSerializer.Serialize(items);
                    File.WriteAllText(file, jsonString);
                }
                catch (JsonException)
                {
                    return false;
                }
                return true;
            }
        }
    }
    /// <summary>
    /// Ez az osztály felelős a Problémák tábla feltöltéséért.
    /// </summary>
    public class LoadPanasz
    {
        /// <summary>
        /// A függvény a paraméterül kapott címet eldarabolja cím összetevőkre, majd kimenti az adatbázisba
        /// </summary>
        /// <param name="cim">A cím, amit ki kell menteni</param>
        /// <param name="neve">Annak a személynek a neve, aki a problémát jelezte</param>
        /// <returns>Egy stringet add vissza, ez lesz a reakció a WEB-es modulban a felhasználó</returns>
        public string LoadProb(string cim, string neve)
        {
            var db = new MindigFenyesContext();
            var panasz = new Problemak();
            int spaceDB = 0;
            string temp = "";
            for (int i = 0; i < cim.Length; i++)
            {
                if (cim[i] == ' ' && spaceDB == 0)
                {
                    panasz.Iranyitoszam = int.Parse(temp);
                    temp = "";
                    spaceDB++;
                }
                else if (cim[i] == ' ' && spaceDB == 1)
                {
                    panasz.Varos = temp;
                    temp = "";
                    spaceDB++;
                }
                else if (cim[i] == ' ' && 48 <= cim[i + 1] && cim[i + 1] <= 57)
                {
                    panasz.Utca = temp;
                    temp = "";
                }
                else if (cim[i] == '.')
                {
                    panasz.Hazszam = int.Parse(temp);
                }
                else
                {
                    temp += cim[i];
                }
            }

            panasz.Idopont = DateTime.Now;
            db.Problemaks.Add(panasz);

            db.SaveChanges();
            return $"Kedves {neve} észrevételét rögzítetük.\n A megadott címet továbbítottuk az illetékes szervízelő kollégáinknak.\n";
        }
    }
    /// <summary>
    /// A Beolvas osztály segitségével lehet a consle-ról olyan sorból beolvasni szöveget, ahol már a sorban előrébb másmilyen szöveg is szerepel
    /// </summary>
    public static class Beolvasas
    {
        /// <summary>
        /// A ReadIn() osztály szöveget olvasbe
        /// </summary>
        /// <param name="szo"> Referencia ként kapja meg az a stringet, amibe a beolvasott szöveget fogja írni</param>
        /// <param name="x">Az X koordináta a console-on, ahonnan az olvasást kell kezdeni</param>
        /// <param name="y">Az Y koordináta a console-on, ahonnan az olvasást kell kezdeni</param>
        public static void ReadIn(ref string szo, int x, int y)
        {
            Console.SetCursorPosition(x, y);
            int currentPosX = x;
            while (true)
            {
                char a = (char)Console.Read();
                if (a == '\t')
                {
                    Console.Read();
                    Console.Read();
                    break;
                }
                szo += a;
            }
        }
    }
    /// <summary>
    /// Ez az osztáy végzi az elvégzett munkák(feladatok) és az azokat elvégző munkatársak adatbázisban történő eltárolását
    /// </summary>
    public class LoadElvegzettMunka
    {
        /// <summary>
        /// A Beolvas osztály ReadIn() függvényét felhasználva beolvassa egy elvégzett feladat típusát, az elvégző nevét és Id-ját
        /// és eltárolja azokat az adatbázisban, a feladat elvégzésének dátuma a feladat eltárolásának dátum, automatikusan generálódik.
        /// </summary>
        public void LoadMunka()
        {
            var db = new MindigFenyesContext();
            Console.SetWindowSize(120, 40);
            Console.SetBufferSize(120, 40);
            Console.SetCursorPosition(0, 3);

            Console.WriteLine("Ennek a modulnak a segítségével tudja a vállalkozás munkatársa a nap végén eltárolni\naz aznap elvégzett munkát a cég adatbázisában.");
            Console.WriteLine("Adja meg az elvégzett munka típusát, valamint a munkát elvégző személy Id-ját és nevét\n(az adat beírása után nyomjon TAB-ot, majd ENTER-t).");

            string tipus = "";
            Console.WriteLine("Típus: ");
            Beolvasas.ReadIn(ref tipus, 7, 7);
            
            string id = "";
            Console.WriteLine("Id: ");
            Beolvasas.ReadIn(ref id, 5, 8);

            string nev = "";
            Console.Write("Nev: ");
            Beolvasas.ReadIn(ref nev, 5, 9);
            Munkatars munkatars;
            if(db.Munkatars.Select(m => m.Nev).Contains(nev) == false)
            {
                munkatars = new Munkatars()
                {
                    Id = id,
                    Nev = nev,

                };
                db.Munkatars.Add(munkatars);
            }
            else
            {
                munkatars = new Munkatars();
                munkatars = db.Munkatars.Where(m => m.Nev == nev).FirstOrDefault();
            }
            var feladat = new Feladat()
            {
                Tipus = tipus,
                TeljesitesDatum = DateTime.Now
            };
            var elvegzettMunka = new ElvegzettMunka()
            {
                Feladat = feladat,
                Munkatars = munkatars
            };

            db.Feladats.Add(feladat);
            db.ElvegzettMunkas.Add(elvegzettMunka);

            db.SaveChanges();
        }
    }
    /// <summary>
    /// Ez az osztály végzi az adatbázisban szereplő, a WEB-es felületen megadott feladatok lekérdezését
    /// </summary>
    public class ElvegzendoMunkakLekerdezes
    {
        /// <summary>
        /// Kiirja az összes elvégzendő feladatot a console-ra
        /// </summary>
        private void LekMindenMunka()
        {
            var db = new MindigFenyesContext();

            Console.Clear();
            Console.SetWindowSize(120, 40);
            Console.SetBufferSize(120, 40);
            Console.SetCursorPosition(0, 3);
            foreach (var problema in db.Problemaks.ToList())
            {
                Console.WriteLine(problema + "\n");
            }
            Console.WriteLine();
        }
        /// <summary>
        /// Kiírja a felhasználó által megadott irányítószámhoz tartozó elvégzendő munkákat
        /// </summary>
        private void LekIrSzamAlap()
        {
            var db = new MindigFenyesContext();
            Console.Clear();
            Console.SetWindowSize(120, 40);
            Console.SetBufferSize(120, 40);
            Console.SetCursorPosition(0, 3);
            var kiirando_szoveg = "Adja meg a lekérdezni kívánt terület irányítószámát (majd TAB és ENTER): ";
            Console.WriteLine(kiirando_szoveg);
            string iranyitoszam = "";
            Beolvasas.ReadIn(ref iranyitoszam, kiirando_szoveg.Length, 3);
            var kilista = db.Problemaks.Where(p => p.Iranyitoszam == int.Parse(iranyitoszam)).ToList();
            foreach (var problema in kilista)
            {
                Console.WriteLine(problema + "\n");
            }
        }
        /// <summary>
        /// Kiírja a felhasználó által megadott kerületben elvégzendő munkákat, vagy kiírja azokat az elvégzendő feladatokat,
        /// amik a felhasználó által megadott nap számnál régebben kerültek az adatbázisba
        /// </summary>
        private void LekBudAlap()
        {
            var db = new MindigFenyesContext();
            Console.Clear();
            Console.SetWindowSize(120, 40);
            Console.SetBufferSize(120, 40);
            Console.SetCursorPosition(0, 3);
            var kiirando_szoveg = "Adja meg a lekérdezni kívánt kerület számát (pl 6. kerület -> 106) (végén TAB, majd ENTER): ";
            Console.WriteLine(kiirando_szoveg);
            string iranyitoszam = "";
            Beolvasas.ReadIn(ref iranyitoszam, kiirando_szoveg.Length, 3);
            if (100 <= int.Parse(iranyitoszam) && int.Parse(iranyitoszam) <= 123)
            {
                var kerulet = int.Parse(iranyitoszam) % 100;
                var kilista = db.Problemaks.Where(p => p.Iranyitoszam / 1000 == 1 && (p.Iranyitoszam % 1000) / 10 == kerulet).ToList();
                foreach (var problema in kilista)
                {
                    Console.WriteLine(problema + "\n");
                }
            }
            else
            {
                Console.WriteLine("Nem megfelelő a megadott formátum!");
            }
        }
        /// <summary>
        /// Kiírja azokat a munkákat, amelyek a felhasználó által megadott napszámnál régebben kerület az adatbázisba
        /// </summary>
        private void LekNapszam()
        {
            var db = new MindigFenyesContext();
            Console.Clear();
            Console.SetWindowSize(120, 40);
            Console.SetBufferSize(120, 40);
            Console.SetCursorPosition(0, 3);
            var kiirando_szoveg = "Adja meg azt a napszámot, amelynél régebben beküldött meghibásodásokat akarja kilistázni (végén TAB, majd ENTER): ";
            Console.WriteLine(kiirando_szoveg);
            string iranyitoszam = "";
            Beolvasas.ReadIn(ref iranyitoszam, kiirando_szoveg.Length, 3);
            if (100 > int.Parse(iranyitoszam))
            {
                var nap = int.Parse(iranyitoszam);
                var kilista = db.Problemaks.Where(p => p.Idopont.Value.AddDays(nap) < DateTime.Now);
                foreach (var problema in kilista)
                {
                    Console.WriteLine(problema + "\n");
                }
            }
            else
            {
                Console.WriteLine("Nem megfelelő a megadott formátum!");
            }
        }
        /// <summary>
        /// Ez a függvény egy végtelen ciklus segítségével vezérli a különböző lekérdezéseket
        /// </summary>
        public void Lekerdezes()
        {
            while (true)
            {
                Console.Clear();
                Console.SetWindowSize(120, 40);
                Console.SetBufferSize(120, 40);
                Console.SetCursorPosition(0, 3);
                var listazasTipus = new Dictionary<int, string>()
                {
                    [1] = "Minden munka lekérdezése",
                    [2] = "Irányítószám alapján történő lekérdezés",
                    [3] = "Budapesti cím lekérdezése",
                    [4] = "Megadott napszámnál régebbi munkák lekérdezése"
                };

                Console.WriteLine("A cég dolgozói itt tudják lekérdezni az elvégzendő munkákat.");
                Console.WriteLine("Válassza ki a keresett lekérdezésnek megfelelő menüpontot!\n");
                ConsoleKey valogatva;
                foreach (var item in listazasTipus)
                {
                    Console.WriteLine($"{item.Key} - {item.Value}");
                }
                valogatva = Console.ReadKey(true).Key;
                switch (valogatva)
                {
                    case ConsoleKey.D1:
                        LekMindenMunka();
                        break;
                    case ConsoleKey.D2:
                        LekIrSzamAlap();
                        break;
                    case ConsoleKey.D3:
                        LekBudAlap();
                        break;
                    case ConsoleKey.D4:
                        LekNapszam();
                        break;
                }
                Console.WriteLine("Akar még más feltételnek megfelelő munkát lekérdezni?");
                string valasz = Console.ReadLine();
                if (valasz == "Nem" || valasz == "nem")
                    break;
            }
        }
    }
}
