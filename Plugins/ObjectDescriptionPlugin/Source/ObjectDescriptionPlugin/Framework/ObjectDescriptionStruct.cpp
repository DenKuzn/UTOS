// Copyright by Denis Kuznetsov. 2023. All Rights Reserved.

#include "ObjectDescriptionStruct.h"

const FObjectDescription FObjectDescription::EmptyData{};

FObjectDescription::FObjectDescription()
{
}

bool FObjectDescription::operator==( const FObjectDescription& ComparedObjectDescription ) const
{
	return MainName.EqualTo( ComparedObjectDescription.MainName )
		&& ShortDescription.EqualTo( ComparedObjectDescription.ShortDescription )
		&& FullDescription.EqualTo( ComparedObjectDescription.FullDescription )
		&& Image == ComparedObjectDescription.Image;
}

bool FObjectDescription::IsSet() const
{
	return !MainName.IsEmpty()
		&& !MainName.EqualTo( FText::FromString( TEXT( "Default Name" ) ) );
}
