using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LINQ_Exercise
{
    internal class StartClass : Menu
    {
        public override void DisplayMenu()
        {
            Console.WriteLine("Willkommen im Startmenü!");
            Console.WriteLine("---------------------------");
            Console.WriteLine("[1] Einloggen");
            Console.WriteLine("[2] Registrieren");
            Console.WriteLine("Oder drücken sie eine Beliebige daste um abzubrechen.");
            int Homeinput = Convert.ToInt32(Console.ReadLine());
            if (Homeinput == 1)
            {
                LoginMenu loginMenu = new LoginMenu();
                loginMenu.DisplayMenu();
            }
            else if (Homeinput == 2)
            {
                RegisterHomeClass register = new RegisterHomeClass();
            }
            else
            {
                //break;
            }
        }
    }
}
