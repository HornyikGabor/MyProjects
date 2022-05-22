using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using EFCore;
using EFCore.Model;
using MindigFenyes;

namespace UIModul
{
    /// <summary>
    /// Az osztály felelős az ElvegzettMunkaPerMukatárs ablak létrehozásáért és definiálja a gombok által elvégzendő feladatokat.
    /// </summary>
    public partial class ElvegzettMunka : Window
    {
        /// <summary>
        /// Létrehozza az ablakot
        /// </summary>
        public ElvegzettMunka() : base()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Kilistázza a textboxban megadott nevű munkatárs által elvégzett feladatokat
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            var db = new MindigFenyesContext();
            var munkatarsId = db.Munkatars.Where(m => m.Nev == textbox.Text).Select(m => m.MunkatarsId).ToList();
            var elvegzettMunkak = db.ElvegzettMunkas.Where(e => munkatarsId.Contains(e.MunkatarsId)).Select(e => e.FeladatId).ToList();
            var feladatok = db.Feladats.Where(f => elvegzettMunkak.Contains(f.Id)).ToList();
            Munkak.ItemsSource = feladatok;
        }
        /// <summary>
        /// Becsukja az aktuális ablakot és megnyitja a főablakot.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow();
            mainWindow.Show();
            this.Close();
        }
        /// <summary>
        /// A lekérdezés eredményét kiírja egy json fájlba.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            var sorosito = new Sorosito();

            var db = new MindigFenyesContext();
            var munkatarsId = db.Munkatars.Where(m => m.Nev == textbox.Text).Select(m => m.MunkatarsId);
            var elvegzettMunkak = db.ElvegzettMunkas.Where(e => munkatarsId.Contains(e.MunkatarsId)).Select(e => e.FeladatId);
            if(sorosito.Sorositas("ElvegzettMunkaPerMunkatars.json", db.Feladats.Where(f => elvegzettMunkak.Contains(f.Id)).ToList()) == true)
            {
                MessageBox.Show("Sikeres mentés!");
            }
            else
            {
                MessageBox.Show("Sikertelen mentés!");
            }
        }
    }
}
