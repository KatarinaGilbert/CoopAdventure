// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"

void PrintString(const FString& Str) {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, Str);
	}
}

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	//PrintString("MultiplayerSessionsSubsystem Constructor");

	bCreateServerAfterDestroy = false;
	DestroyServerName = "";
	ServerNameToFind = "";
	MySessionName = FName("Co-op Adventure Session Name");


}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//PrintString("MultiplayerSessionsSubsystem Initialize");

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem) {
		FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
		PrintString(SubsystemName);

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			//PrintString("Session interface is valid");
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnJoinSessionComplete);
		}
	}
}

void UMultiplayerSessionsSubsystem::Deinitialize()
{
	//UE_LOG(LogTemp, Warning, TEXT("MultiplayerSessionsSubsystem Deinitialize"));
}

void UMultiplayerSessionsSubsystem::CreateServer(FString ServerName)
{
	PrintString("Creating Server");

	if (ServerName.IsEmpty()) {
		PrintString("Server name cannot be empty!");
		ServerCreateDel.Broadcast(false);
		return;
	}

	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(MySessionName);
	if (ExistingSession) {
		FString Msg = FString::Printf(TEXT("Session with name %s already exists, destroying it"), *MySessionName.ToString());
		PrintString(Msg);
		bCreateServerAfterDestroy = true;
		DestroyServerName = ServerName;
		SessionInterface->DestroySession(MySessionName);
		return;
	}

	FOnlineSessionSettings SessionSettings = SetSessionSettings(ServerName);
	

	SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}

void UMultiplayerSessionsSubsystem::FindServer(FString ServerName)
{
	if (ServerName.IsEmpty()) {
		PrintString("Server name cannot be empty!");
		ServerJoinDel.Broadcast(false);
		return;
	}

	SetSessionSearch();

	ServerNameToFind = ServerName;

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	PrintString("Finding Server");
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	PrintString(FString::Printf(TEXT("OnCreateSessionComplete: %d"), bWasSuccessful));

	ServerCreateDel.Broadcast(bWasSuccessful);

	if (bWasSuccessful) {
		FString Path = "/Game/ThirdPerson/Maps/ThirdPersonMap?listen";
		if (!GameMapPath.IsEmpty()) {
			Path = FString::Printf(TEXT("%s?listen"), *GameMapPath);
		}
		GetWorld()->ServerTravel(Path);
	}
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	PrintString(FString::Printf(TEXT("OnDestroySessionComplete, SessionName: %s, Success: %d"), *SessionName.ToString(), bWasSuccessful));
	
	if (bWasSuccessful) {
		if (bCreateServerAfterDestroy) {
			bCreateServerAfterDestroy = false;
			CreateServer(DestroyServerName);
		}
	}
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (!bWasSuccessful)
		return;
	if (ServerNameToFind.IsEmpty())
		return;

	TArray<FOnlineSessionSearchResult> SessionSearchResults = SessionSearch->SearchResults;
	FOnlineSessionSearchResult* CorrectResult = 0;

	if (SessionSearchResults.Num() > 0) {
		PrintString(FString::Printf(TEXT("OnFindSessionsComplete, %d sessions found"), SessionSearchResults.Num()));

		for(FOnlineSessionSearchResult Result : SessionSearchResults) {
			if (Result.IsValid()) {
				FString ServerName = "No-name";
				Result.Session.SessionSettings.Get(FName("SERVER_NAME"), ServerName);

				PrintString(FString::Printf(TEXT("ServerName: %s"), *ServerName));

				if (ServerName.Equals(ServerNameToFind)) {
					CorrectResult = &Result;
					PrintString(FString::Printf(TEXT("Found server with name: %s"), *ServerName));
					break;
				}
			}
		}
		if (CorrectResult) {
			SessionInterface->JoinSession(0, MySessionName, *CorrectResult);
		}
		else {
			PrintString(FString::Printf(TEXT("Couldn't find server with name: %s"), *ServerNameToFind));
			ServerNameToFind = "";
			ServerJoinDel.Broadcast(false);
		}
	}
	else {
		PrintString("0 sessions found.");
		ServerJoinDel.Broadcast(false);
	}
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
	ServerJoinDel.Broadcast(JoinResult == EOnJoinSessionCompleteResult::Success);

	if (JoinResult == EOnJoinSessionCompleteResult::Success) {
		PrintString(FString::Printf(TEXT("Successfully joined session %s"), *SessionName.ToString()));

		FString Address = "";
		bool Success = SessionInterface->GetResolvedConnectString(MySessionName, Address);
		if (Success) {
			PrintString(FString::Printf(TEXT("Address: %s"), *Address));
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController) {
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
		else {
			PrintString("GetResolvedConnectString returned false. Could not connect to session.");

		}
	}
	else {
		PrintString("Joining the session failed");

	}
}

FOnlineSessionSettings UMultiplayerSessionsSubsystem::SetSessionSettings(FString ServerName)
{
	bool bIsLAN = false;
	FOnlineSessionSettings SessionSettings;

	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") {
		bIsLAN = true;
	}

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bIsLANMatch = bIsLAN;
	SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	return SessionSettings;
}

void UMultiplayerSessionsSubsystem::SetSessionSearch()
{
	bool bIsLAN = false;
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") {
		bIsLAN = true;
	}

	SessionSearch->MaxSearchResults = 9999;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->bIsLanQuery = bIsLAN;
}

