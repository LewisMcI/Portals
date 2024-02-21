#include "Portal.h"

APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	frame->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FrameVisualAsset(TEXT("/Game/StarterContent/Props/SM_WindowFrame"));

	if (FrameVisualAsset.Succeeded())
	{
		frame->SetStaticMesh(FrameVisualAsset.Object);
		frame->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}


	portalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	portalMesh->SetupAttachment(frame);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneVisualAsset(TEXT("/Engine/BasicShapes/Plane"));

	if (PlaneVisualAsset.Succeeded())
	{
		portalMesh->SetStaticMesh(PlaneVisualAsset.Object);
		portalMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

