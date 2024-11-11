// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EndingWidget.h"
#include "Components/Image.h"

UEndingWidget::UEndingWidget()
{
}

void UEndingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
    //MID = EndingVideoImage->GetDynamicMaterial();

}

//void UEndingWidget::SetMID_Texture(UTexture* _MediaTexture)
//{
//    MID->SetTextureParameterValue(TEXT("TextureParameterName"), _MediaTexture);
//
//    if (EndingVideoImage)
//    {
//        EndingVideoImage->SetBrushFromMaterial(MID);
//    }
//}
