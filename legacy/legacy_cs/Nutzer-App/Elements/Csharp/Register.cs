using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace LINQ_Exercise
{
    public class RegisterHomeClass : Menu
    {
        public override void DisplayMenu()
        {

            

            bool NotExistingName = false;
            bool IfFirstProfile = false;
            bool correctpassword = false;
            string Input_Password = "";
            string Input_FirstName = "";
            string Input_LastName = "";
            int Input_Age = 0;
            int Input_ID = 0;
            try
            {

                do
                {
                    Console.WriteLine("Gebe dein Vor-Namen ein:");
                    Input_FirstName = Console.ReadLine();
                    Console.Clear();
                    Console.WriteLine("Gebe dein Nach-namen ein:");
                    Input_LastName = Console.ReadLine();
                    Console.Clear();
                    Console.WriteLine("Gebe dein Alter ein:");
                    Input_Age = Convert.ToInt32(Console.ReadLine());
                    Console.Clear();
                    Console.WriteLine($"Gebe deine ID an");
                    Input_ID = Convert.ToInt32(Console.ReadLine());
                    Console.Clear();
                    Checking.CheckingUserInput(Input_FirstName, Input_LastName, Input_ID);      // Dieses "Checking" ist dafür da, um zu Kontrollieren das der ID nicht gleich sein darf, zu den anderen nutzern.
                                                                                                // Und noch auch keine gleiche nach und vor-namen.

                } while (NotExistingName == true);


                do
                {
                    Console.Clear();
                    Console.WriteLine("Und jetzt gebe dein Passwort ein!");
                    string Input_Password_1 = Console.ReadLine();
                    Console.Clear();
                    Console.WriteLine("Schreibe ihn nochmal!");
                    string Input_Password_2 = Console.ReadLine();

                    if (Input_Password_1 != Input_Password_2)
                    {
                        Console.WriteLine("Dein Wiederholter Passwort stimmt nicht überein, schreibe ihn zwei mal erneut");
                        Console.ReadKey();
                    }
                    else
                    {
                        correctpassword = true;
                        Input_Password = Input_Password_1;
                    }

                } while (correctpassword == false);


            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                Console.WriteLine("Deine Eingabe ist in einem falschen Format geschrieben worden!");
            }


            string S_Input_Age = Convert.ToString(Input_Age);
            string S_Input_ID = Convert.ToString(Input_ID);


            C_Nutzer C_nutzer001 = new C_Nutzer(Input_FirstName, Input_LastName, Input_Age, Input_ID, Input_Password);      //First User



            Data.SaveData(Input_FirstName, Input_LastName, Input_Age, Input_ID, Input_Password, IfFirstProfile);








            


            Console.ReadKey();
        }
        public static string RandomID()
        {
           

            Random rnd01 = new Random();
            Random rnd02 = new Random();
            Random rnd03 = new Random();
            Random rnd04 = new Random();
            Random rnd05 = new Random();
            
            int rnd01numb = rnd01.Next(0, 9);
            int rnd02numb = rnd02.Next(0, 9);
            int rnd03numb = rnd03.Next(0, 9);
            int rnd04numb = rnd03.Next(0, 9);
            int rnd05numb = rnd03.Next(0, 9);

            int alpha_rnd01numb = rnd01.Next(0, 52);
            int alpha_rnd02numb = rnd02.Next(0, 52);
            int alpha_rnd03numb = rnd03.Next(0, 52);
            int alpha_rnd04numb = rnd04.Next(0, 52);
            int alpha_rnd05numb = rnd04.Next(0, 52);


            if (rnd01numb == rnd02numb)                     // Ich habe es so festgestellt das die ersten zwei nummer nicht gleich sein dürfen
            {
                while (rnd01numb == rnd02numb)
                {
                    rnd01numb = rnd01.Next(0, 9);
                }
            }
            if (rnd01numb == rnd03numb)                     // Ich habe es so festgestellt das die ersten zwei nummer nicht gleich sein dürfen
            {
                while (rnd01numb == rnd03numb)
                {
                    rnd01numb = rnd01.Next(0, 9);
                }
            }
            if (rnd03numb == rnd04numb)                     // Ich habe es so festgestellt das die ersten zwei nummer nicht gleich sein dürfen
            {
                while (rnd03numb == rnd04numb)
                {
                    rnd03numb = rnd03.Next(0, 9);
                }
            }


            string[] alphabet =
            {
                "A",
                "B",
                "C",
                "D",
                "E",
                "F",
                "E",
                "F",
                "G",
                "H",
                "I",
                "J",
                "K",
                "L",
                "M",
                "N",
                "O",
                "P",
                "Q",
                "R",
                "S",
                "T",
                "U",
                "V",
                "W",
                "X",
                "Y",
                "Z",
                "a",
                "b",
                "c",
                "d",
                "e",
                "f",
                "g",
                "h",
                "i",
                "j",
                "k",
                "l",
                "m",
                "n",
                "o",
                "p",
                "q",
                "r",
                "s",
                "t",
                "u",
                "v",
                "w",
                "x",
                "y",
                "z",
            };
            
            string rndChar01 = alphabet[alpha_rnd01numb];
            string rndChar02 = alphabet[alpha_rnd02numb];
            string rndChar03 = alphabet[alpha_rnd03numb];
            string rndChar04 = alphabet[alpha_rnd04numb];
            string rndChar05 = alphabet[alpha_rnd05numb];


            

           
            string str_rnd01 = Convert.ToString(rnd01numb);
            string str_rnd02 = Convert.ToString(rnd02numb);
            string str_rnd03 = Convert.ToString(rnd03numb);
            string str_rnd04 = Convert.ToString(rnd04numb);
            string str_rnd05 = Convert.ToString(rnd05numb);

            string newnumb = BoolLuck(rndChar01, str_rnd01) + BoolLuck(rndChar02, str_rnd02) + BoolLuck(rndChar03, str_rnd03) + BoolLuck(rndChar04, str_rnd04) + BoolLuck(rndChar05, str_rnd05);

            return newnumb;

        }
        private static string BoolLuck(string rndChar, string str_rndNumber)
        {
            int numbtimes = 0;
            int secondvalue = 3;
            Random rnd = new Random();

            if (numbtimes == 2)
            {
                secondvalue = 4;
            }

            int rndnumb = rnd.Next(1, secondvalue);



            if (rndnumb == 1)
            {
                numbtimes = numbtimes + 1;
                return rndChar;
               
            }
            else
            {
                return str_rndNumber;
            }
            
            
        }
        private static string NormalizeElementName(string name)
        {
            // Entferne ungültige Zeichen aus dem Namen
            string invalidChars = new string(System.IO.Path.GetInvalidFileNameChars()) + new string(System.IO.Path.GetInvalidPathChars());
            foreach (char c in invalidChars)
            {
                name = name.Replace(c.ToString(), "");
            }

            // Ersetze Leerzeichen durch Unterstriche
            name = name.Replace(" ", "_");

            return name;
        }

    }
    public class C_Nutzer
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public int Age { get; set; }
        public int ID { get; set; }

        public string Password { get; set; }
        public C_Nutzer(string firstname, string lastname, int age, int id, string password)
        {
            FirstName = firstname;
            LastName = lastname;
            Age = age;
            ID = id;
            Password = password;
        }
    }
}
