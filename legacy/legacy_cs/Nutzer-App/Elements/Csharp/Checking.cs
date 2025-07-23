using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;

namespace LINQ_Exercise
{
    internal class Checking
    {
        public static void CheckingUserInput(string firstname, string lastname, int id)
        {
            XDocument CeckForDuplikates = XDocument.Load("C:\\Users\\User\\source\\repos\\LINQ Exercise\\Nutzer.xml");

            var elements = CeckForDuplikates.Descendants("Nutzer").Attributes("Vor_Name");
            foreach (var element in elements)
            {
                Console.WriteLine(element);
            }


        }
    }
}
