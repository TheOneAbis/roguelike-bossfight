// Fill out your copyright notice in the Description page of Project Settings.


#include "DataUtils.h"
#include <fstream>

static float gameTime = 0;
static int deaths = 0;
static int introSkips = 0;
static int outroSkips = 0;
static bool fileRead = false;

int UDataUtils::GetDeathCount()
{
	if (!fileRead)
		ReadFromFile();
	return deaths;
}
float UDataUtils::GetRecordedGameTime()
{
	if (!fileRead)
		ReadFromFile();
	return gameTime;
}
int UDataUtils::GetIntroSkips()
{
	if (!fileRead)
		ReadFromFile();
	return introSkips;
}
int UDataUtils::GetOutroSkips()
{
	if (!fileRead)
		ReadFromFile();
	return outroSkips;
}
void UDataUtils::SetDeathCount(int count)
{
	if (!fileRead)
		ReadFromFile();
	deaths = count;
}
void UDataUtils::SetRecordedGameTime(float time)
{
	if (!fileRead)
		ReadFromFile();
	gameTime = time;
}
void UDataUtils::SetIntroSkips(int count)
{
	if (!fileRead)
		ReadFromFile();
	introSkips = count;
}
void UDataUtils::SetOutroSkips(int count)
{
	if (!fileRead)
		ReadFromFile();
	outroSkips = count;
}

void UDataUtils::SaveToFile()
{
	// If we're here before reading in data, writing to it will end up
	// zeroing out all saved data when the user may not want that. 
	// Thus we will not write anything.
	if (!fileRead)
		return;

	std::ofstream file;
	file.open("data.txt");
	if (file.is_open())
	{
		file << "Total_Game_Time=" << gameTime << std::endl;
		file << "Total_Fails=" << deaths << std::endl;
		file << "Time_Intro_Skipped=" << introSkips << std::endl;
		file << "Time_Outro_Skipped=" << outroSkips << std::endl;
		file.close();
	}
	else if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Error attempting to write to data.txt!");
	}
}

void UDataUtils::ReadFromFile()
{
	fileRead = true;
	std::ifstream file;
	file.open("data.txt");
	if (file.is_open())
	{
		int ptrOffset = 0;
		while (!file.eof())
		{
			char line[512]{};
			file >> line;
			FString data(line), dataLeft, dataRight;
			if (data.Split("=", &dataLeft, &dataRight))
			{
				if (dataLeft.Equals("Total_Game_Time"))
					gameTime = FCString::Atof(&dataRight[0]);
				if (dataLeft.Equals("Total_Fails"))
					deaths = FCString::Atoi(&dataRight[0]);
				if (dataLeft.Equals("Time_Intro_Skipped"))
					introSkips = FCString::Atoi(&dataRight[0]);
				if (dataLeft.Equals("Time_Outro_Skipped"))
					outroSkips = FCString::Atoi(&dataRight[0]);
			}
		}
		file.close();
	}
	else if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Error attempting to read from data.txt! The file likely doesn't exist.");
	}
}