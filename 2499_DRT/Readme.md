Support me at: 
[https://www.buymeacoffee.com/jpzambrano](https://www.buymeacoffee.com/jpzambrano)
 
[paypal.me/jpzambrano99](https://www.paypal.me/jpzambrano99)

# The 2499 DRT Process: A Breakdown of the most important stuff

The DRT process consists of mainly four key steps, some focused on technical aspects and others on aesthetics. 
Let's explore them in the order they are applied:

## **1. Density/luminance Adjustment:** 
This step acts like exposure control but specifically targets saturated areas. 
It multiplies each red, green, and blue (RGB) value by a specific amount. While primarily an aesthetic choice, 
it also helps prevent overly bright areas produced by the IDT matrix. This step is extremely smooth to prevent rings around 
achromatic areas, or blurred areas, this is normally something that happens with other similar adjustments.

## **2. Gamut Mapping/Guard Rail:** 
This step ensures colors stay within the open domain representable range. 
It's a non-linear process, as chromaticity linear mapping often produces undesirable results. 
This approach achieves a similar effect to a per-channel sigmoid function, smoothly compressing negative values and creating continuous gradients. 
Additionally, it includes an "energy fix" to recover detail loss that can occur during other gamut mapping options.

## **3. Aesthetic Matrices:** 
These are two matrices that significantly impact the final look. 
One affects the entire image, while the other targets only the brightness values. They are crucial for achieving the desired visual style 
and should be adjustable by the user, as a single setting won't work for all scenarios. While consistency within a project is recommended, 
different projects may require unique parameters for these matrices.

## **4. Attenuation refinement:** 
This final step ensures there are no abrupt changes in saturation at high values.
It builds upon the adjustments made in the previous step, it's very subtle but important. For example, 
it helps with sensor that clip early at high exposures.

The rest of the operations are a sigmoid, and a final purity matrix, this matrix will re-introduce some negative values aswell as above 1, an extra gamut mapping helps to prevent emissive looking values for objects that shouldn't be emissive and clipping at the display level

>Non of the sample images were original taken by me, I found many images freely available as RAW files from cameras of all vendors. Sony, Canon, Leica, Fuji, and Nikon.

# Some Projects Graded under 2499

[The Man Who Could Not Remain Silent - Short Film - Multiple Award Winner](https://www.festival-cannes.com/en/f/the-man-who-could-not-remain-silent/)

[Pokemon Go - Teaser Trailer - Colorist: Juan Pablo Zambrano](https://www.youtube.com/watch?v=OZGerzRXzUE)

[Walking with Water - Short Film - Colorist: Menelaos Primerakis
](https://www.instagram.com/p/C6tBxsvNFRh/?img_index=2)

[Mezzetta - Campaing Spots - Colorist: Brandon Thomas](https://www.instagram.com/p/C8dUEnTNeUH/)

[Adidas Messi - Campaign Spot - Colorist: Darren Hartman](https://www.instagram.com/p/C9GMWINyIiP/?img_index=1)

[Harry | White Swan Houston Sound Guy - Documentary - Colorist: Zaire ](https://www.instagram.com/p/C_a917MJkx2/)

[VULGAR - Movie - Colorist: Santiago Rivero - Color Engineer: Juan Pablo Zambrano](https://www.youtube.com/watch?v=3o0YqRdl6YA)

[All Season 5 of MasterChef South Africa - Colorist: Misha Beare - Color Engineer: Juan Pablo Zambrano](https://www.youtube.com/watch?v=YvV4OOZlSEY)

[LIA PARIS | LOBO - Music Video - Colorist: Gabriel Ferreira](https://vimeo.com/1012934243?fbclid=PAZXh0bgNhZW0CMTEAAaZXbFSchxGkb4oiFm2MeiZzTEMMOFYvI-NjoDfszmr6wGwPyDvkLiw3t0w_aem_edasINX5b1p5eP85_SndsA)

[Treasure Imagination - Short Film - Colorist: Brandon Thomas](https://www.instagram.com/p/C_dutjpxv2-/)

[Just North - Short Film - Colorist: Nathan Sexton](https://nathansextoncolour.com/portfolios/just-north/)

[Gold Mining - Documentary - Colorsit: Nathan Sexton](https://nathansextoncolour.com/portfolios/africa-gold-mining-documentary/)

[Mama by Kolby Cooper - Music Video - Colorist: Dan Diaz](https://www.instagram.com/p/C9QirQDvzZc/?img_index=1)

[The Caller Return - Feature Film - Colorsit: Dan Diaz](https://www.instagram.com/p/C-VZJ_cPYuV/?img_index=2)

[Blood,Sweat & Gears - Adidas Spot - Colorist: Dan Diaz](https://www.instagram.com/p/DBJQmkfvI2N/)

[Always Good Together - Jack Links Spot - Colorist: Iris Devins](https://vimeo.com/989604254)

[I Ran Out of White Claws Once ft T-Pain - Spot - Colorist: Iris Devins](https://www.instagram.com/tpain/reel/C8o7Ds6uywQ/)

[Unwid Longer - Fruit by the Foot Spot - Colorist: Iris Devins](https://www.youtube.com/watch?v=ACKjc2i-C5w)

[Vertical Anamorphic - Lens Test - Colorist: Miggy Vision](https://www.youtube.com/watch?v=tmM1QYb6Vr8)

