// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::setPlayerControllerState(bool state) {
	if (GetPawn()) {
		if (state == false) {
			GetPawn()->DisableInput(this);
		}
		else {
			GetPawn()->EnableInput(this);
		}
	}
	bShowMouseCursor = state;
}

