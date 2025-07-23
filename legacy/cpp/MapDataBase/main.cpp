// Database - Statistics of video games
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>

#include <map>
#include <string>
#include <unordered_map>


using std::string;

struct Popularity
{
    double _TotalPopulation    = 0;
    double _StoryPopulation    = 0;
    double _GamePlayPopulation = 0;

    double _percentStory       = 0;
    double _percentGamePlay    = 0;

    Popularity(double downloads, double percentStory, double percentGamePlay) :

        _TotalPopulation(downloads),
        _StoryPopulation(downloads    * (percentStory    / 100)),
        _GamePlayPopulation(downloads * (percentGamePlay / 100)),

        _percentStory(percentStory),
        _percentGamePlay(percentGamePlay)
    {
        
    }
};

struct VideoGameProduct
{
    const char* _name   = 0;
    int _downloads      = 0;
    Popularity _population; // only 7bits so the max value is 128, but we need only 0 until 128 to rate it for example 78 so it is 7,8/10.

    VideoGameProduct() : _name(nullptr), _downloads(0), _population(0, 0, 0)
    {

    };

    VideoGameProduct(const char* Name, double Downloads, double percentStory, double gamePlay) :
                     _name(Name), _downloads((int)Downloads),
                     
                     _population((int)_downloads, percentStory, gamePlay)
    {

    }
    
};

namespace std
{
    template<>
    struct hash<VideoGameProduct>
    {
        size_t operator()(const VideoGameProduct& key)
        {
            return hash<double>()(key._downloads);
        }
    };
}

// Search fimiliar | of VideoGameMap
void SearchFModule(std::map<std::string, VideoGameProduct>& videoGameMap, std::string& input)
{
    string  currentInput;

    int  decision     = 0;
    int  commonWords  = 0;
    bool loop         = true;
    bool exists       = true;
    bool HadNotCommon = false;

    while (true)
    {
        std::cin.ignore();
        std::system("cls");

        std::cout << "Input: ____" << '\b' << '\b' << '\b' << '\b';
        std::getline(std::cin, input);
        currentInput = input;
        std::cout << "Fimiliar Words to: " << input << '\n';

        if (input[0] != '\0')
        {
#pragma    region ForExitORErrorHandling
            if (input == "return" || input == "back")
            {
                break;
            }
            else if (input == "exit")
            {
                std::cout << "You can't exit directely!" << '\n';
                Sleep(2500);
                input = "";
            }

            std::system("cls"); // clearing the notifications & other info's.
#pragma endregion ForExitORErrorHandling

            // the words has been changed
            
            for (int i = 0; i < input.length(); i++)
            {
                if (currentInput[i] != input[i])
                {
                    std::system("cls"); break; //Not Same anymore 
                }
            }

            //std::cout << '\n' << '\n';

            for (auto itr = videoGameMap.begin(); itr != videoGameMap.end(); itr++)
            {
                HadNotCommon = false;
                commonWords  = 0;

                for (int i = 0; i < input.length(); i++) // char iteration
                {
                    char a = itr->second._name[i];
                    char b = input[i];

                    if (a == b)
                    {
                        ++commonWords;
                    }
                    else
                    {
                        HadNotCommon = true;
                    }
                    

                    if (commonWords == input.length())
                    {
                        std::cout << itr->second._name << '\n';
                        break;
                    }
                    if (HadNotCommon)
                    {
                        break;
                    }
                    // Not even the first letter is the same.
                    // Or it have found already the respective string.  
                    
                    
                }
            }
        }
        std::cin.get();
        
    }
}


// Search conrecte
void SearchModule(std::map<std::string, VideoGameProduct> videoGameMap, std::string &input)
{
    
    int decision = 0;
    bool loop = true;
    bool exists = true;
    while (loop)
    {
        std::cin.ignore(); // clear Input-Handling Buffer
        std::system("cls");
        input = "";
        
        std::cout << std::endl;
        
        std::getline(std::cin, input);
        if (input != "")
        {
#pragma    region ForExitORErrorHandling
            if (input == "return" || input == "back")
            {
                break;
            }
            else if (input == "exit")
            {
                std::cout << "You can't exit directely!" << '\n';
                Sleep(2500);
                input = "";
            }

            std::map<std::string, VideoGameProduct>::iterator itr = videoGameMap.find(input);
            exists = itr != videoGameMap.end() && itr->first != "";

            if (!exists)
            {
                std::cout << "No one List found with " << "\'" << input << "\'" << '\n';
                Sleep(1500);
                continue; // back to the beginning of the loop
            }

            std::system("cls"); // clearing the notifications & other info's.
#pragma endregion ForExitORErrorHandling


            VideoGameProduct& product = videoGameMap.find(input)->second;
            
            std::cout << "What information do you would like to know about " << "\'" << product._name << "\'" << '?' << "\n"
                      << "1.     : Show the default information" << '\n'
                      << "2.     : The popularity in Gameplay"   << '\n'
                      << "3.     : The popularity in Story"      << '\n'
                      << "4.     : Exit"                         << '\n'
                        ;

            std::cout << '\n' << '\n' << '\n';
            std::cin >> decision;

            while (true)
            {
                switch (decision)
                {
                    case 1:
                    {
                        std::cout << product._name << " have " << product._downloads << " Downloads";

                        break;
                    }
                    case 2:
                    {
                        std::cout << product._name << " have " << product._population._percentGamePlay << "%" << " popularity for Gameplay" << '\n';

                        break;
                    }
                    case 3:
                    {
                        std::cout << product._name << " have " << product._population._percentStory << "%" << " popularity for his Story" << '\n';

                        break;
                    }
                    case 4:
                    {
                        loop = false;
                        goto breakloop; // l: 162
                    }
                    default:
                    {
                        

                        break;
                    }
                }
                std::cin.ignore(); // clear the buffer, to wait again for your input.
                std::cin.get();
                std::system("cls");

               

                std::cout << "What information do you would like to know about " << "\'" << product._name << "\'" << '?' << "\n"
                    << "1.     : Show the default information" << '\n'
                    << "2.     : The popularity in Gameplay" << '\n'
                    << "3.     : The popularity in Story" << '\n'
                    << "4.     : Exit" << '\n'
                    ;

                std::cout << '\n' << '\n' << '\n';
                std::cin >> decision;
            }
        }
        std::cin.get();

        breakloop:
        if (!loop)
        {
            break;
        }
    }
}

int main()
{
    

    std::string input = {};
    std::map<std::string, VideoGameProduct> videoGameMap;

    int downloads = 2000000;

#pragma region GameLists
    videoGameMap["Grand Theft Auto V"]                      = VideoGameProduct{ "Grand Theft Auto V", 140000000, 60, 40 };
    videoGameMap["The Witcher 3: Wild Hunt"] = { VideoGameProduct("The Witcher 3: Wild Hunt", 28000000, 70, 30) };
    videoGameMap["Cyberpunk 2077"] = { VideoGameProduct("Cyberpunk 2077", 13000000, 80, 20) };
    videoGameMap["Call of Duty: Warzone"] = { VideoGameProduct("Call of Duty: Warzone", 75000000, 20, 80) };
    videoGameMap["Among Us"] = { VideoGameProduct("Among Us", 100000000, 10, 90) };
    videoGameMap["FIFA 22"] = { VideoGameProduct("FIFA 22", 5000000, 25, 75) };
    videoGameMap["Apex Legends"] = { VideoGameProduct("Apex Legends", 50000000, 15, 85) };
    videoGameMap["League of Legends"] = { VideoGameProduct("League of Legends", 115000000, 5, 95) };
    videoGameMap["Valorant"] = { VideoGameProduct("Valorant", 50000000, 30, 70) };
    videoGameMap["Counter-Strike: Global Offensive"] = { VideoGameProduct("Counter-Strike: Global Offensive", 200000000, 40, 60) };
    videoGameMap["Fortnite"] = { VideoGameProduct("Fortnite", 200000000, 50, 50) };
    videoGameMap["Minecraft"] = { VideoGameProduct("Minecraft", 500000000, 10, 90) };
    videoGameMap["Overwatch"] = { VideoGameProduct("Overwatch", 50000000, 35, 65) };
    videoGameMap["Rainbow Six Siege"] = { VideoGameProduct("Rainbow Six Siege", 75000000, 25, 75) };
    videoGameMap["Rocket League"] = { VideoGameProduct("Rocket League", 75000000, 20, 80) };
    videoGameMap["Assassin's Creed Valhalla"] = { VideoGameProduct("Assassin's Creed Valhalla", 10000000, 60, 40) };
    videoGameMap["The Elder Scrolls V: Skyrim"] = { VideoGameProduct("The Elder Scrolls V: Skyrim", 30000000, 30, 70) };
    videoGameMap["God of War"] = { VideoGameProduct("God of War", 15000000, 70, 30) };
    videoGameMap["Halo Infinite"] = { VideoGameProduct("Halo Infinite", 8000000, 20, 80) };
    videoGameMap["The Last of Us Part II"] = { VideoGameProduct("The Last of Us Part II", 10000000, 80, 20) };
    videoGameMap["Death Stranding"] = { VideoGameProduct("Death Stranding", 5000000, 60, 40) };
    videoGameMap["Final Fantasy VII Remake"] = { VideoGameProduct("Final Fantasy VII Remake", 6000000, 70, 30) };
    videoGameMap["Ghost of Tsushima"] = { VideoGameProduct("Ghost of Tsushima", 8000000, 50, 50) };
    videoGameMap["Horizon Zero Dawn"] = { VideoGameProduct("Horizon Zero Dawn", 10000000, 40, 60) };
    videoGameMap["Monster Hunter: World"] = { VideoGameProduct("Monster Hunter: World", 15000000, 40, 60) };
    videoGameMap["Persona 5"] = { VideoGameProduct("Persona 5", 4000000, 80, 20) };
    videoGameMap["Resident Evil Village"] = { VideoGameProduct("Resident Evil Village", 6000000, 70, 30) };
    videoGameMap["Sekiro: Shadows Die Twice"] = { VideoGameProduct("Sekiro: Shadows Die Twice", 5000000, 60, 40) };
    videoGameMap["Spider-Man: Miles Morales"] = { VideoGameProduct("Spider-Man: Miles Morales", 7000000, 50, 50) };
    videoGameMap["Star Wars Jedi: Fallen Order"] = { VideoGameProduct("Star Wars Jedi: Fallen Order", 9000000, 40, 60) };
    videoGameMap["Watch Dogs: Legion"] = { VideoGameProduct("Watch Dogs: Legion", 3000000, 60, 40) };
    videoGameMap["Yakuza: Like a Dragon"] = { VideoGameProduct("Yakuza: Like a Dragon", 2000000, 70, 30) };
    videoGameMap["Control"] = { VideoGameProduct("Control", 3000000, 40, 60) };
    videoGameMap["Cyber Shadow"] = { VideoGameProduct("Cyber Shadow", 1000000, 20, 80) };
    videoGameMap["Disco Elysium"] = { VideoGameProduct("Disco Elysium", 1000000, 70, 30) };
    videoGameMap["Doom Eternal"] = { VideoGameProduct("Doom Eternal", 3000000, 50, 50) };
    videoGameMap["F1 2020"] = { VideoGameProduct("F1 2020", 2000000, 40, 60) };
    videoGameMap["Fall Guys: Ultimate Knockout"] = { VideoGameProduct("Fall Guys: Ultimate Knockout", 2000000, 30, 70) };
    videoGameMap["Gears 5"] = { VideoGameProduct("Gears 5", 2000000, 60, 40) };
    videoGameMap["Half-Life: Alyx"] = { VideoGameProduct("Half-Life: Alyx", 1000000, 40, 60) };
    videoGameMap["Mortal Kombat 11"] = { VideoGameProduct("Mortal Kombat 11", 3000000, 70, 30) };
    videoGameMap["Nioh 2"] = { VideoGameProduct("Nioh 2", 2000000, 50, 50) };
    videoGameMap["Ori and the Will of the Wisps"] = { VideoGameProduct("Ori and the Will of the Wisps", 1000000, 40, 60) };
    videoGameMap["Outer Wilds"] = { VideoGameProduct("Outer Wilds", 1000000, 60, 40) };
    videoGameMap["Phasmophobia"] = { VideoGameProduct("Phasmophobia", 2000000, 70, 30) };
    videoGameMap["Spiritfarer"] = { VideoGameProduct("Spiritfarer", 1000000, 40, 60) };
    videoGameMap["Streets of Rage 4"] = { VideoGameProduct("Streets of Rage 4", 1000000, 50, 50) };
    videoGameMap["The Outer Worlds"] = { VideoGameProduct("The Outer Worlds", 3000000, 30, 70) };
    videoGameMap["The Pathless"] = { VideoGameProduct("The Pathless", 1000000, 60, 40) };
    videoGameMap["Wasteland 3"] = { VideoGameProduct("Wasteland 3", 1000000, 40, 60) };

#pragma endregion GameLists

    // Main-Loop
    while (true)
    {
        std::system("cls");

        std::cout << "------------------------------------Tips------------------------------------\n\t\t\t\t'back' & 'exit'" << '\n'
                  << "\t <Sometimes you have to press Enter multiple times.> " << '\n'
                  << "----------------------------------------------------------------------------" << '\n' << '\n' << '\n';
                  
        
        std::cout << "type \'search_f\' for search fimiliar Data name" << '\n'
            << "type '\search_e\' for the exact Data name"
            << '\n'
            << '\n'
            << '\n';

        std::cin >> input;

        if (GetAsyncKeyState(VK_ESCAPE) & 0b1)
        {
            break;
        }
        if (input == "search_e")
        {
            SearchModule(videoGameMap, input);
        }
        if (input == "search_f")
        {
            SearchFModule(videoGameMap, input);
        }
        else if (input == "close" || input == "exit")
        {
            break;
        }
        else
        {
            std::cout << "No Function found!" << '\n';
        }

        Sleep(1000);

    }
    

    return 0;
}

