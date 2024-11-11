// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TitleWidget.h"
#include "Components/Image.h"

UTitleWidget::UTitleWidget()
{
}

void UTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
    //MID = TitleVideoImage->GetDynamicMaterial();
}

//void UTitleWidget::SetMID_Texture(UTexture* _MediaTexture)
//{
//    MID->SetTextureParameterValue(TEXT("TextureParameterName"), _MediaTexture);
//
//    if (TitleVideoImage)
//    {
//        TitleVideoImage->SetBrushFromMaterial(MID);
//    }
//}
