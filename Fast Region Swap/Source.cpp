#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "usernameStorage.h"

class InvalidInputException
{
public:
	void getErrorMessage() { std::cout << "Error input must be a number.\n"; }
};

void overwriteFile(std::vector<std::string> &v)
{
	std::ofstream f;

	f.open("Config/LeagueClientSettings.yaml");
	if (f.is_open())
	{
		for (int i = 0; i < v.size(); i++)
		{
			f << v[i] << '\n';
		}

		f.close();
	}
	else
	{
		std::cout << "Error opening file.\n";
	}

}

std::string regionSelect()
{
	std::cout << "Enter number of your region: \n1) North America\n2) Latin America North\n3) Latin America South\n4) Brazil\n5) EU West\n6) EU Nordic and East\n7) Japan\n8) Turkey\n9) Russia\n10) Oceana\n";
	std::string region;
	int regnum;
	do
	{
		try
		{
			std::cout << "Region #: ";
			std::cin >> regnum;
			if (std::cin.fail())
			{
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException e)
		{
			e.getErrorMessage();
			std::cin.clear();
			std::cin.ignore(99999, '\n');
		}

		if (regnum > 10 ^ regnum < 0)
		{
			std::cout << "Please select the number of the region.\n";
		}
	} while (regnum > 10 ^ regnum < 0);

	switch (regnum)
	{
	case 1:
		region = "NA";
		break;
	case 2:
		region = "LA1";
		break;
	case 3:
		region = "LA2";
		break;
	case 4:
		region = "BR";
		break;
	case 5:
		region = "EUW";
		break;
	case 6:
		region = "EUNE";
		break;
	case 7:
		region = "JP";
		break;
	case 8:
		region = "TR";
		break;
	case 9:
		region = "RU";
		break;
	case 10:
		region = "OC1";
		break;
	default:
		break;
	}

	return region;
}

void writeFile()
{	
	std::ifstream f;
	std::vector<std::string> filelines;
	std::string line;
	std::string currentRegion;
	std::string otherRegion;
	std::string currentUser;
	
	f.open("Config/LeagueClientSettings.yaml");
	if (f.is_open())
	{
		while (!f.eof())
		{
			std::getline(f, line); //search each line in the file
			if (line.size() > 8)
			{
				if (line[8] == 'r' && line[10] == 'g')
				{
					//std::cout << "Found region\n";
					//std::cout << line << '\n';
					currentRegion = line;
					std::string regionCode = regionSelect();
					otherRegion = "        region: \"" + regionCode + "\"";
					filelines.push_back(otherRegion);
				}
				else if (line[8] == 'r' && line[10] == 'm' && line[20] == 't') //rememberme = true
				{
					filelines.push_back(line);
					std::getline(f, line);
					currentUser = line;
					storeUsername(currentRegion, currentUser);
					std::string otherName = getUsername(otherRegion);
					filelines.push_back(otherName);
				}
				else
				{
					filelines.push_back(line);
				}
			}
			else
			{
				filelines.push_back(line);
			}
		}
	}
	else
	{
		std::cout << "Error opening file...\n";
	}

	f.close();

	overwriteFile(filelines);
}

void run()
{
	system("LeagueClient.exe");
}

int main()
{
	writeFile();
	run();
	return 0;
}