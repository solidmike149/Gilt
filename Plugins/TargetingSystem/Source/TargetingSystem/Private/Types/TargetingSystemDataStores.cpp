﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/TargetingSystemDataStores.h"

namespace UE
{
	namespace TargetingSystem
	{
		/** Data Stores used for Targeting Requests */
		TTargetingDataStore<FTargetingRequestData> GTargetingRequestDataStore;
		TTargetingDataStore<const FTargetingTaskSet*> GTargetingTaskSetDataStore;
		TTargetingDataStore<FTargetingSourceContext> GTargetingSourceDataStore;
		TTargetingDataStore<FTargetingDefaultResultsSet> GTargetingResultsDataStore;
		TTargetingDataStore<FTargetingAsyncTaskData> GTargetingAsyncTaskDataStore;
		TTargetingDataStore<FTargetingImmediateTaskData> GTargetingImmediateTaskDataStore;

#if ENABLE_DRAW_DEBUG

		TTargetingDataStore<FTargetingDebugData> GTargetingDebugDataStore;

#endif // ENABLE_DRAW_DEBUG

	} // TargetingSystem
} // UE