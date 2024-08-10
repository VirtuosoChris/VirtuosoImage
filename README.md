VirtuosoImage
=============

Multidimensional array and image library.  This is for CPU side, C++, with templates.

I wrote this originally as an alternative to MATLAB for graduate Vision / Image Processing needs.

I used it quite a bit to prototype image algorithms back in the day instead of putting together a GPU implementation.

It hasn't been updated in quite a while and it's not my go-to for game development, but there's a pretty decent little library of basic functionality here and it's neat.

It is multi-dimensional, lets you use "windows" / slices into a larger image, lets you change the backing store layout (eg if you wanted to swap the images underlying memory layout from an Array Buffer to a z-order or tiled representation etc).
