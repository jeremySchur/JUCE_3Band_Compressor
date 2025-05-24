/*
  ==============================================================================

    Parameters.h
    Created: 24 May 2025 1:42:08pm
    Author:  jerem

  ==============================================================================
*/

#pragma once

namespace Parameters
{
    enum Names
    {
        Low_Mid_Crossover_Freq,
        Mid_High_Crossover_Freq,

        Threshold_Low_Band,
        Threshold_Mid_Band,
        Threshold_High_Band,

        Attack_Low_Band,
        Attack_Mid_Band,
        Attack_High_Band,

        Release_Low_Band,
        Release_Mid_Band,
        Release_High_Band,

        Ratio_Low_Band,
        Ratio_Mid_Band,
        Ratio_High_Band,

        Bypassed_Low_Band,
        Bypassed_Mid_Band,
        Bypassed_High_Band,
    };

    inline const std::map<Names, juce::String>& GetParams()
    {
        static std::map<Names, juce::String> params = 
        {
            {Low_Mid_Crossover_Freq, "Low-Mid Crossover Frequency"},
            {Mid_High_Crossover_Freq, "Mid-High Crossover Frequency"},
            {Threshold_Low_Band, "Threshold Low Band"},
            {Threshold_Mid_Band, "Threshold Mid Band"},
            {Threshold_High_Band, "Threshold High Band"},
            {Attack_Low_Band, "Attack Low Band"},
            {Attack_Mid_Band, "Attack Mid Band"},
            {Attack_High_Band, "Attack High Band"},
            {Release_Low_Band, "Release Low Band"},
            {Release_Mid_Band, "Release Mid Band"},
            {Release_High_Band, "Release High Band"},
            {Ratio_Low_Band, "Ratio Low Band"},
            {Ratio_Mid_Band, "Ratio Mid Band"},
            {Ratio_High_Band, "Ratio High Band"},
            {Bypassed_Low_Band, "Bypassed Low Band"},
            {Bypassed_Mid_Band, "Bypassed Mid Band"},
            {Bypassed_High_Band, "Bypassed High Band"},
        };

        return params;
    }
}