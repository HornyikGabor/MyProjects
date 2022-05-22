using EFCore;
using EFCore.Model;
using MindigFenyes;
using System;

namespace Console2
{
    /// <summary>
    /// Ez az osztály felelős az adatbázis feladatok és munkatársak tábláinak feltöltését végző osztály példányosításáért. 
    /// </summary>
    internal class Program
    {
        static void Main(string[] args)
        {
            var loadElvegzettMunka = new LoadElvegzettMunka();
            while (true)
            {
                loadElvegzettMunka.LoadMunka();
                Console.Clear();
                Console.SetWindowSize(120, 40);
                Console.SetBufferSize(120, 40);
                Console.SetCursorPosition(0, 3);
                Console.WriteLine("Kíván még elvégzett munkát eltárolni az adatbázisban?");
                var valasz = Console.ReadLine();
                if ( valasz == "nem" || valasz == "Nem")
                    break;
            }
        }
    }
}