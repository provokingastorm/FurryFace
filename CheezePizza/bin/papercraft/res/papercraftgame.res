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

Texture idleShip
{
 filename=origins\res\graphics\Idle.png
 resgroup=1
}

Sprite sprIdleShip
{
 texture=idleShip
 rect=0,0,,
 hotspot=,
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 resgroup=1
}