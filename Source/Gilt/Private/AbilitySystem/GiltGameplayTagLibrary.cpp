// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GiltGameplayTagLibrary.h"

UGiltGameplayTagLibrary::UGiltGameplayTagLibrary()
{
}

FGameplayTagContainer UGiltGameplayTagLibrary::FilterGameplayTagContainer(FGameplayTagContainer GameplayTagToFilter, FGameplayTagContainer FilterToApply)
{
	return GameplayTagToFilter.Filter(FilterToApply);
}
