Font CourierNew
{
 filename=".\..\res\fonts\couriernew.fnt"
 tracking=1.0
 resgroup=2
}

Texture prototypeBackground
{
 filename=origins\res\graphics\prototypeBackground.png
 resgroup=1
}

Sprite sprPrototypeBG
{
 texture=prototypeBackground
 rect=0,0,640,480
 hotspot=320, 240
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 resgroup=1
}

Texture linkRight
{
 filename=origins\res\graphics\anim_link_right.png
 resgroup=1
}

Sprite sprLinkRight
{
 texture=linkRight
 rect=0,0,640,480
 hotspot=320, 240
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 resgroup=1
}

Texture linkUp
{
 filename=origins\res\graphics\anim_link_up.png
 resgroup=1
}

Sprite sprLinkUp
{
 texture=linkUp
 rect=0,0,182,25
 hotspot=91, 12.5
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 resgroup=1
}

Texture link
{
 filename=origins\res\graphics\link_run.png
 resgroup=1
}

Animation sprLink
{
 texture=link
 rect=0,0,64,64
 hotspot=32,32
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 frames=6
 fps=4.0
 mode=FORWARD,LOOP
 resgroup=1
}