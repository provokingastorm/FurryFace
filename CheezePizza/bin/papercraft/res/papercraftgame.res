Font CourierNew
{
 filename=".\..\res\fonts\couriernew.fnt"
 tracking=1.0
 resgroup=2
}

Texture prototypeBackground
{
 filename=papercraft\res\graphics\prototypeBackground.png
 resgroup=1
}

Sprite sprPrototypeBG
{
 texture=prototypeBackground
 rect=0,0,72,72
 hotspot=36,36
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 resgroup=1
}

Texture idleShip
{
 filename=papercraft\res\graphics\Idle.png
 resgroup=1
}

Sprite sprIdleShip
{
 texture=idleShip
 rect=0,0,72,72
 hotspot=36,36
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 resgroup=1
}

Animation animBullet
{
 texture=papercraft\res\graphics\Bullet.png
 rect=0,0,20,20
 hotspot=10,10
 blendmode=COLORMUL,BLEND_ALPHABLEND,NOZWRITE
 frames=5
 fps=12.0
 mode=FORWARD,LOOP
 resgroup=1
}