// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/EntityAppearanceData.h"

const FEntityAppearanceData FEntityAppearanceData::EmptyData{};

bool FEntityAppearanceData::IsSet() const
{
	return *this != EmptyData;
}
