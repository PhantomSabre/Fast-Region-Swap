#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void storeUsername(std::string r, std::string u)
{
	std::ifstream f;
	std::string line;
	bool userStored = false;
	bool regionStored = false;
	f.open("usernames.txt");
	if (f.is_open())
	{
		while (!f.eof())
		{
			std::getline(f, line);
			if (line == r)
			{
				regionStored = true;
				if (!f.eof())
				{
					std::getline(f, line);
					if (line == u)
					{
						userStored = true;
						break;
					}
				}
				
			}
		}
	}
	else
	{
		std::cout << "Error opening file.\n";
	}

	f.close();

	if (!userStored && regionStored)
	{
		std::ifstream file;
		std::string line;
		std::vector<std::string> filelines;
		std::string oldUser;

		file.open("usernames.txt");
		if (file.is_open())
		{
			while (!file.eof())
			{
				std::getline(file, line);
				if (line.size() > 8)
				{
					if (line == r)
					{
						line = '\n';
						filelines.push_back(line);
						filelines.push_back(u);
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
			std::cout << "Error opening file.\n";
		}

		file.close();

		std::ofstream replaceName;

		replaceName.open("usernames.txt");
		if (replaceName.is_open())
		{
			for (int i = 0; i < filelines.size(); i++)
			{
				replaceName << filelines[i] << '\n';
			}
		}

		replaceName.close();
	}

	if (!userStored && !regionStored)
	{
		std::ofstream updatef;
		updatef.open("usernames.txt", std::ios::app);
		if (updatef.is_open())
		{
				updatef << r << '\n';
				updatef << u << '\n';
		}
		else
		{
			std::cout << "Error opening file.\n";
		}

		updatef.close();
	}

}

std::string getUsername(std::string r)
{
	std::string username = "        username: \"\"";
	std::ifstream f;
	std::string line;
	f.open("usernames.txt");
	if (f.is_open())
	{
		while (!f.eof())
		{
			std::getline(f, line);	
			if (line == r)
			{
				std::getline(f, line);
				f.close();
				return line;
			}
		}
	}
	else
	{
		std::cout << "Error opening file.\n";
	}

	f.close();
	return username;
}