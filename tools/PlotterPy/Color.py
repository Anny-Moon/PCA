import colorsys as cs
import random

def newSmartHSVcolor(r, g, b, dispH, dispS, dispV):
    (h,s,v) = cs.rgb_to_hsv(r, g, b);
    color = '#%02x%02x%02x' % (r, g, b);
#    print(color);
#    print(h,s,v);
    
    deltaH = random.uniform(-dispH, dispH);
    h = h+deltaH;
    if(h>1):
	h=h-2*deltaH;
    if(h<0):
	h=h+2*deltaH;
	
    deltaS = random.uniform(-dispS, dispS);
    s = s+deltaS;
    if(s>1):
	s=s-2*deltaS;
    if(s<0):
	s=s+2*deltaS;
    
    deltaV = random.uniform(-dispV,dispV);
#    print(deltaV);
    v = v+deltaV;
#    print(v)
    if(v>1):
	v=v-2*deltaV;
    if(v<0):
	v=v+2*deltaV;
#    print(v)
    (r,g,b) = cs.hsv_to_rgb(h, s, v);
    color = '#%02x%02x%02x' % (int(255*r), int(255*g), int(255*b));
    
#    print(color);
#    print(h);
#    print(s);
#    print(v);
    return color;
