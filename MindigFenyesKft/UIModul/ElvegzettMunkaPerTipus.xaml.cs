using EFCore;
using EFCore.Model;
using MindigFenyes;
using System;
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
    /// Az osztály felelős az ElvegzettMunkaPerTípus ablak létrehozásáért és definiálja a gombok által elvégzendő feladatokat.
    /// </summary>
    public partial class ElvegzettMunkaPerTipus : Window
    {
        /// <summary>
        /// Létrehozza az ablakot
        /// </summary>
        public ElvegzettMunkaPerTipus()
        {
            InitializeComponent();
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
        /// Kilistázza a textboxban megadott típusú feladatokat
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            var db = new MindigFenyesContext();
            Feladatok2.ItemsSource = db.Feladats.Where(m => m.Tipus == textbox3.Text).ToList();
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
            if(sorositas.Sorositas("ElvegzettMunkaPerTipus.json", db.Feladats.ToList().Where(m => m.Tipus == textbox3.Text).ToList()) == true)
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
