using System;
using System.Collections.Generic;

#nullable disable

namespace EFCore
{
    public partial class Feladat
    {
        public Feladat()
        {
            ElvegzettMunkas = new HashSet<ElvegzettMunka>();
        }

        public int Id { get; set; }
        public string Tipus { get; set; }
        public DateTime TeljesitesDatum { get; set; }

        public virtual ICollection<ElvegzettMunka> ElvegzettMunkas { get; set; }
        public override string ToString()
        {
            return $"Típus: {Tipus} Teljesítés dat.: {TeljesitesDatum}";
        }
    }
}
