#pragma once

#include "Set.h"

#include "FiniteSet.h"
#include "BiggerSet.h"
#include "UnionSet.h"
#include "IntersectionSet.h"
#include "DifferenceSet.h"
#include "SymmetricalDifferenceSet.h"

char setTypeToChar(SetType type)
{
    switch (type)
    {
    case SetType::FiniteSet:
        return 'F';
    case SetType::BiggerSet:
        return 'B';
    case SetType::UnionSet:
        return 'U';
    case SetType::IntersectionSet:
        return 'I';
    case SetType::DifferenceSet:
        return 'D';
    case SetType::SymmetricalDifferenceSet:
        return 'S';
    default:
        return '?';
    }
}

SetType charToSetType(char c)
{
    switch (c)
    {
    case 'F':
        return SetType::FiniteSet;
    case 'B':
        return SetType::BiggerSet;
    case 'U':
        return SetType::UnionSet;
    case 'I':
        return SetType::IntersectionSet;
    case 'D':
        return SetType::DifferenceSet;
    case 'S':
        return SetType::SymmetricalDifferenceSet;
    default:
        return SetType::Unknown;
    }
}

Set *createSetByType(SetType type)
{
    switch (type)
    {
    case SetType::FiniteSet:
        return new FiniteSet();
    case SetType::BiggerSet:
        return new BiggerSet();
    case SetType::UnionSet:
        return new UnionSet();
    case SetType::IntersectionSet:
        return new IntersectionSet();
    case SetType::DifferenceSet:
        return new DifferenceSet();
    case SetType::SymmetricalDifferenceSet:
        return new SymmetricalDifferenceSet();
    default:
        return nullptr;
    }
}
