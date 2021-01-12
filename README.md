![Build WAM](https://github.com/olilarkin/PDSynth/workflows/Build%20WAM/badge.svg)
![Build Native](https://github.com/olilarkin/PDSynth/workflows/Build%20Native/badge.svg)

Edit the DSP in the SOUL online compiler

https://soul.dev/lab/?id=87652b5e75b61811d5edc14bba51ce3a&0=-6&1=3&2=0.64

Then copy and paste into PDSynth/PDSynth_DSP.soul

and use the soul cli to update the C++

```soul generate --cpp PDSynth_DSP.soul --output=PDSynth_DSP.h```

