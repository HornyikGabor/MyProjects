using System;
using System.Collections.Generic;

#nullable disable

namespace EFCore
{
    public partial class Problemak
    {
        public int Id { get; set; }
        public DateTime? Idopont { get; set; }
        public int? Iranyitoszam { get; set; }
        public string Varos { get; set; }
        public string Utca { get; set; }
        public int? Hazszam { get; set; }
        public override string ToString()
        {
            return $"Beérkezés időpontja: {Idopont}\nBejelentett meghibásodás helyszíne: {Iranyitoszam} {Varos} {Utca} {Hazszam}";
        }
    }
}
