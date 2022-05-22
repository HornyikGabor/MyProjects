using System;
using System.Collections.Generic;

#nullable disable

namespace EFCore
{
    public partial class Munkatars
    {
        public Munkatars()
        {
            ElvegzettMunkas = new HashSet<ElvegzettMunka>();
        }

        public int MunkatarsId { get; set; }
        public string Id { get; set; }
        public string Nev { get; set; }

        public virtual ICollection<ElvegzettMunka> ElvegzettMunkas { get; set; }
        public override string ToString()
        {
            return $"Id: {Id} Név: {Nev}";
        }
    }
}
