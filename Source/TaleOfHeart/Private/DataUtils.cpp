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
	deaths = count;
}
void UDataUtils::SetRecordedGameTime(float time)
{
	gameTime = time;
}
void UDataUtils::SetIntroSkips(int count)
{
	introSkips = count;
}
void UDataUtils::SetOutroSkips(int count)
{
	outroSkips = count;
}

void UDataUtils::SaveToFile()
{
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
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Error attempting to read from data.txt!");
	}
}