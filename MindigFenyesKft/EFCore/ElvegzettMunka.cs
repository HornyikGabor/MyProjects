using System;
using System.Collections.Generic;

#nullable disable

namespace EFCore
{
    public partial class ElvegzettMunka
    {
        public int Id { get; set; }
        public int FeladatId { get; set; }
        public int MunkatarsId { get; set; }

        public virtual Feladat Feladat { get; set; }
        public virtual Munkatars Munkatars { get; set; }
    }
}
