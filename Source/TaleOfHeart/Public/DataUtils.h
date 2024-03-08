// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataUtils.generated.h"

/**
 * 
 */
UCLASS()
class TALEOFHEART_API UDataUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Data Utilities")
	static int GetDeathCount();

	UFUNCTION(BlueprintPure, Category = "Data Utilities")
	static float GetRecordedGameTime();

	UFUNCTION(BlueprintPure, Category = "Data Utilities")
	static int GetIntroSkips();

	UFUNCTION(BlueprintPure, Category = "Data Utilities")
	static int GetOutroSkips();

	UFUNCTION(BlueprintCallable, Category = "Data Utilities")
	static void SetDeathCount(int count);

	UFUNCTION(BlueprintCallable, Category = "Data Utilities")
	static void SetRecordedGameTime(float time);

	UFUNCTION(BlueprintCallable, Category = "Data Utilities")
	static void SetIntroSkips(int count);

	UFUNCTION(BlueprintCallable, Category = "Data Utilities")
	static void SetOutroSkips(int count);

	UFUNCTION(BlueprintCallable, Category = "Data Utilities")
	static void SaveToFile();

private:

	static void ReadFromFile();

};
