using System;

public class Class1
{
	public static Data()
	{
		public static void SaveData(string firstname, string lastname, int age, int id, string password, bool IfFirstProfile)
		{
            string ProjectOrder = Directory.GetParent(AppContext.BaseDirectory);
            if ()

            if (IfFirstProfile == true)
			{
                XDocument xDocument = new XDocument();
                XElement Nutzer = new XElement("Nutzer");
                xDocument.Add(Nutzer);

                string UserName = Input_FirstName + Input_ID;

                XElement nutzer001 = new XElement(Input_FirstName + "_" + RandomID(),    //  Bei Nutzern sollst du nicht nutzer001 haben sondern {Name} - {Random_ID}

                    new XAttribute("Vor_Name", C_nutzer001.FirstName),
                    new XAttribute("Nach_Name", C_nutzer001.LastName),
                    new XAttribute("Alter", C_nutzer001.Age),
                    new XAttribute("ID", C_nutzer001.ID),
                    new XAttribute("Password", C_nutzer001.Password)

                    );
                Nutzer.Add(nutzer001);

                xDocument.Save(ProjectOrder + "Nutzer.xml");
                Console.WriteLine("Dein Profil Konnte erfolgreich erstellt werden!");
                Console.ReadKey();
            }
            else
            {
                //Hier wird der Zweite User erstellt egal was Passiert
            }
        }
	}
}
