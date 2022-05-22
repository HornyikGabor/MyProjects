using EFCore.Model;
using MindigFenyes;
using System;
using System.Collections.Generic;
using System.Linq;
using EFCore;

namespace Console1
{
    /// <summary>
    /// Ez az osztály felelős az adatbázisban tárolt elvégzendő feladatok lekérdezését végző osztály példányosításáért. 
    /// </summary>
    internal class Program
    {
        static void Main(string[] args)
        {            
            var elvegzendoMunkakaLekerdezese = new ElvegzendoMunkakLekerdezes();
            elvegzendoMunkakaLekerdezese.Lekerdezes();
        }
    }
}
