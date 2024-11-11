// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OpeningWidget.h"
#include "Components/Image.h"

UOpeningWidget::UOpeningWidget()
{
}

void UOpeningWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//MID = OpeningVideoImage->GetDynamicMaterial();
}

//void UOpeningWidget::SetMID_Texture(UTexture* _MediaTexture)
//{
//    MID->SetTextureParameterValue(TEXT("TextureParameterName"), _MediaTexture);
//
//    if (OpeningVideoImage)
//    {
//        OpeningVideoImage->SetBrushFromMaterial(MID);
//    }
//}

