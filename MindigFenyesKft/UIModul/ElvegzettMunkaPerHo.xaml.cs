using EFCore;
using EFCore.Model;
using MindigFenyes;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace UIModul
{
    /// <summary>
    /// Az osztály felelős az ElvegzettMunkaPerHónap ablak létrehozásáért és definiálja a gombok által elvégzendő feladatokat.
    /// </summary>
    public partial class ElvegzettMunkaPerHo : Window
    {
        /// <summary>
        /// Létrehozza az ablakot
        /// </summary>
        public ElvegzettMunkaPerHo()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Kilistázza a textboxban megadott hónapba elvégzett feladatokat
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            var db = new MindigFenyesContext();
            var honap = 0;
            switch (textbox2.Text)
            {
                case "Január": honap = 1; break;
                case "Február": honap = 2; break;
                case "Március": honap = 3; break;
                case "Április": honap = 4; break;
                case "Május": honap = 5; break;
                case "Június": honap = 6; break;
                case "Július": honap = 7; break;
                case "Augusztus": honap = 8; break;
                case "Szeptember": honap = 9; break;
                case "Október": honap = 10; break;
                case "November": honap = 11; break;
                case "December": honap = 12; break;

            }
            Feladatok.ItemsSource = db.Feladats.Where(m => m.TeljesitesDatum.Month.ToString() == honap.ToString()).ToList();
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
            var sorositas = new Sorosito();
            var db = new MindigFenyesContext();
            var honap = 0;
            switch (textbox2.Text)
            {
                case "Január": honap = 1; break;
                case "Február": honap = 1; break;
                case "Március": honap = 1; break;
                case "Április": honap = 1; break;
                case "Május": honap = 1; break;
                case "Június": honap = 1; break;
                case "Július": honap = 1; break;
                case "Augusztus": honap = 1; break;
                case "Szeptember": honap = 1; break;
                case "Október": honap = 1; break;
                case "November": honap = 1; break;
                case "December": honap = 1; break;

            }
            if(sorositas.Sorositas("ElvegzettMunkaPerHo.json", db.Feladats.Where(m => m.TeljesitesDatum.Month.ToString() == honap.ToString()).ToList()) == true)
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
