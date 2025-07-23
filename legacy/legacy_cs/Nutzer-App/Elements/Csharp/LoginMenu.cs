using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace LINQ_Exercise
{
    internal class LoginMenu : Menu
    {
        public override void DisplayMenu()
        {
            bool Certified = false;
            MyDirectory = AppContext.BaseDirectory;
            ProjectDir = Directory.GetParent(MyDirectory);

            XDocument xDocument = XDocument.Load(ProjectDir + "Nutzer.xml");
            Console.WriteLine("Gebe dein Vornamen ein:");
            string Output_FirstName = Console.ReadLine();
            Console.WriteLine("Jetzt deine ID:");
            string Output_ID = Console.ReadLine();
            Console.WriteLine("Und jetzt noch das Passwort:");
            string Output_Pw = Console.ReadLine();

            //var CheckingTheInformationss = from info in xDocument.Descendants("Nutzer")
            //                              where (string)info.Attribute("Vor_Name") == Output_FirstName
            //                              where (string)info.Attribute("ID") == Output_ID
            //                              where (string)info.Attribute("Password") == Output_Pw
            //                              select info;

            var CheckingTheInformationss = xDocument.Descendants()
                                            .Where(info => (string)info.Attribute("Vor_Name") == Output_FirstName &&
                                            (string)info.Attribute("ID") == Output_ID &&
                                            (string)info.Attribute("Password") == Output_Pw);




            foreach (var info in CheckingTheInformationss)
            {

                Console.WriteLine($"ERFOLGREICH BESTÄTIGT\tSIE SIND {info.Name}");
                Certified = true;
            }
            if (!Certified) { Console.Clear(); Console.WriteLine("Fehler: 'Sie haben entweder die Daten falsch geschrieben oder haben ein Falsche Person ausgewählt.' "); }



                Console.ReadKey();
        }
    }
}
