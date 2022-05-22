using System.Windows;

namespace UIModul
{
    /// <summary>
    /// Az osztály felelős a fő ablak létrehozásáért és definiálja a gombok által elvégzendő feladatokat.
    /// </summary>
    public partial class MainWindow : Window
    {
        /// <summary>
        /// Létrehozza az ablakot
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Becsukja a főablakot és megnyitja azta az ablakot, ahol egy a felhasználó által megadott munkatárs által elvégzett munkákat lehet kilistázni.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var elvegzettMunkaPerMunkatars = new ElvegzettMunka();
            elvegzettMunkaPerMunkatars.Top = this.Top; 
            elvegzettMunkaPerMunkatars.Left = this.Left;
            elvegzettMunkaPerMunkatars.Show();
            this.Close();
        }
        /// <summary>
        /// Becsukja a főablakot és megnyitja azta az ablakot, ahol egy a felhasználó által megadott hónapban elvégzett munkákat lehet kilistázni.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            var elvegzettMunkaPerHo = new ElvegzettMunkaPerHo();
            elvegzettMunkaPerHo.Top = this.Top;
            elvegzettMunkaPerHo.Left = this.Left;
            elvegzettMunkaPerHo.Show();
            this.Close();
        }
        /// <summary>
        /// Becsukja a főablakot és megnyitja azta az ablakot, ahol egy a felhasználó által megadott típusó munkákat lehet kilistázni.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            var elvegzettMunkaPerTipus = new ElvegzettMunkaPerTipus();
            elvegzettMunkaPerTipus.Top = this.Top;
            elvegzettMunkaPerTipus.Left = this.Left;
            elvegzettMunkaPerTipus.Show();
            this.Close();
        }
    }
}
