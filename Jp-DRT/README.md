# Jp-DRT

Jp Picture Formation for DaVinci Resolve

# Who

This is an experimental image formation pipeline only for rec709

# What

Provides a flexible picture formation chain for DaVinci Resolve users.

# When

Currently testing out some things for folks who happen to find this repository. Not quite baked fully just yet.

# Where

In your DaVinci Resolve application `LUT` folder, create a subfolder called Jp-DRT. Place both files in there, and refresh your DaVinci Resolve installation.

# Why

You'll have to take it for a try.

# How

1. Install as per Where above.
2. Select the input Color Space,you can change the default input by using a text editor,by default is DavinciWideGamut -Davinci Intermediate.
3. Create a second instance and select Loginput and set output to HighContrast or Baserec709
4. Experiment with look tools in between these nodes.
For best results the n6Look tools should be in a specific order:

1st n6Chroma
2nd n6Value
3rd n6HueFlight

# Parameters
These parameters work together, and thus one can expect any single parameter to drive other potential colour qualia.

## Attenuation Rate
Greater values increase the rate of chromaticity attenuation as tristimulus values ascend. Lower values will slow the rate of attenuation. Slower rates may induce posterization.

## Hue Rotate
Controls the direction and rate of chromaticity angle flights. Value is degrees in CIE xy. Higher values will increase chromaticity angle flight speed toward the direction specified.



## Input Primaries
Input CIE colourimetry primaries for the working space.

## Working Log Encoding
Log-like transfer for the working space.

## Output Primaries
Output primaries encoding.

## Look Transforms
The n6HueFlight is made to work better on linear , if used in between the two instances of the DRT, select the LogZ input, this way it will be transformed correctly.

The n6Chroma in the other hand tends to produce better results when applied in a log state, but it can still work in linear.
