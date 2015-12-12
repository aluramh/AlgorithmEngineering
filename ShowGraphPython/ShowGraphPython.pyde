h = int(600/1)
w = int(1200/1)
padding = 60
axispad = 60
xi = 0
yi = 0
zi = 0
mode = ''
colors = 1
colorNodes = []
s = "C:/Users/Alex/Desktop/nodes.txt"


def setup():
    background(255) 
    size(w + padding, h + padding)
    graph(s)

def createSquareGraph():
    frame.setTitle("Unit square RGG")
    fill(0)
    textAlign(CENTER, TOP)  # LEFT, RIGHT, CENTER

    # Left
    line(axispad, padding, axispad, h - axispad + padding)
    # Top
    line(axispad, padding, w, padding)
    # Right
    line(w, padding, w, h - axispad + padding)
    # Bottom
    line(axispad, h - axispad + padding, w, h - axispad + padding)

    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    divisions = 10
    dis = ((1.0) * (w - axispad) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad + (dis * i), h - axispad + padding, axispad + (dis * i), h - axispad + padding + 15)
        text(str((1.0 / divisions) * i), axispad + (dis * i), h - axispad + padding + 15)
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad + (subdis * j)+displacement, h - axispad + padding, axispad + (subdis * j)+displacement, h - axispad + padding + 7)

    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    divisions = 10
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad, padding + (dis) * i, axispad - 15, padding + (dis) * i)
        text(str(1.0 - ((1.0 / divisions) * i)), axispad - 20, padding + (dis * i))
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad, (padding + (subdis) * j)+displacement, axispad - 7, (padding + (subdis) * j)+displacement)
    
    #Write axis
    tx = width/2
    ty = 10
    textAlign(CENTER, CENTER)
    translate(tx,ty)
    rotate(-HALF_PI)
    text("Y-Coordinate",-height/2,-width/2+5)
    rotate(HALF_PI)
    translate(-tx,-ty)
    text("X-Coordinate",width/2,height-15)
    
    f = open("C:/Users/Alex/Desktop/graphData.txt")
    for lin in f:
        data = lin.split(" ")
        loc = 25
        print data[0]
        if data[0] == "avgdeg":
            text("Avg. Degree = "+data[1], width/3*2, loc)
        elif data[0] == "maxdeg":
            text("Max Degree = "+data[1], width/3*1, loc+20)
        elif data[0] == "colors":
            text("Colors = "+data[1], width/3*2, loc+20)
        elif data[0] == "radius":
            text("R = "+data[1], width/3*1, loc)
        

def createCircleGraph():
    frame.setTitle("Unit circle")
    fill(255)
    textAlign(CENTER, TOP)  # LEFT, RIGHT, CENTER
    
    # Left
    line(axispad, padding, axispad, h - axispad + padding)
    # Bottom
    line(axispad, h - axispad + padding, w, h - axispad + padding)
    
    #ellipse(X, Y, width, height)
    ellipse(((w-axispad)/2)+axispad, ((h-axispad)/2)+padding, w-axispad, h-axispad)
    
    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    fill(0)
    divisions = 10
    dis = ((1.0) * (w - axispad) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad + (dis * i), h - axispad + padding, axispad + (dis * i), h - axispad + padding + 15)
        text(str((((2.0 / divisions) * i))-1), axispad + (dis * i), h - axispad + padding + 15)
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad + (subdis * j)+displacement, h - axispad + padding, axispad + (subdis * j)+displacement, h - axispad + padding + 7)

    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad, padding + (dis) * i, axispad - 15, padding + (dis) * i)
        text(str(2-(((2.0 / divisions) * i))-1), axispad - 20, padding + (dis * i))
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad, (padding + (subdis) * j)+displacement, axispad - 7, (padding + (subdis) * j)+displacement)
    
    #Write axis
    tx = width/2
    ty = 10
    textAlign(CENTER, CENTER)
    translate(tx,ty)
    rotate(-HALF_PI)
    text("Y-Coordinate",-height/2,-width/2+5)
    rotate(HALF_PI)
    translate(-tx,-ty)
    text("X-Coordinate",width/2,height-15)
    f = open("C:/Users/Alex/Desktop/graphData.txt")
    for lin in f:
        data = lin.split(" ")
        loc = 25
        print data[0]
        if data[0] == "avgdeg":
            text("Avg. Degree = "+data[1], width/3*2, loc)
        elif data[0] == "maxdeg":
            text("Max Degree = "+data[1], width/3*1, loc+20)
        elif data[0] == "colors":
            text("Colors = "+data[1], width/3*2, loc+20)
        elif data[0] == "radius":
            text("R = "+data[1], width/3*1, loc)
    
def createSphereGraph():
    frame.setTitle("Unit sphere")
    fill(255)
    textAlign(CENTER, TOP)  # LEFT, RIGHT, CENTER
    
    # Left
    line(axispad, padding, axispad, h - axispad + padding)
    # Bottom
    line(axispad, h - axispad + padding, w/2, h - axispad + padding)
    
    # Left
    line(w/2 + axispad, padding, w/2 + axispad, h - axispad + padding)
    # Bottom
    line(w/2 + axispad, h - axispad + padding, w, h - axispad + padding)
    
    #ellipse(X, Y, width, height)
    ellipseMode(CORNER)
    fill(255)
    
    ellipse(axispad, padding, (w/2)-axispad, h-axispad)
    ellipse(w/2 + axispad, padding, (w/2)-axispad, h-axispad)
    
    #For the first graph
    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    fill(0)
    divisions = 5
    dis = ((1.0) * (w/2 - axispad) / divisions)
    for i in range(0, divisions + 1):
        line(axispad + (dis * i), h - axispad + padding, axispad + (dis * i), h - axispad + padding + 15)
        text(str((((2.0 / divisions) * i))-1), axispad + (dis * i), h - axispad + padding + 15)
    
    #For 2nd graph
    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    fill(0)
    dis = ((1.0) * (w/2 - axispad) / divisions)
    for i in range(0, divisions + 1):
        line((w/2+axispad) + (dis * i), h - axispad + padding, (w/2+axispad) + (dis * i), h - axispad + padding + 15)
        text(str((((2.0 / divisions) * i))-1), (w/2+axispad) + (dis * i), h - axispad + padding + 15)

    
    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    for i in range(0, divisions + 1):
        line(axispad, padding + (dis) * i, axispad - 15, padding + (dis) * i)
        text(str(2-(((2.0 / divisions) * i))-1), axispad - 20, padding + (dis * i))
    
    
    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    for i in range(0, divisions + 1):
        line(w/2+axispad, padding + (dis) * i, (w/2+axispad) - 15, padding + (dis) * i)
        text(str(2-(((2.0 / divisions) * i))-1), (w/2+axispad) - 20, padding + (dis * i))
        
    textAlign(CENTER, CENTER)
    textFont(font, 15*1.5)
    textSize(20)
    text("Top half of the sphere (Z >= 0)",((w+axispad+padding)/4)*1,padding/2)
    text("Bottom half of the sphere (Z < 0)",((w+padding)/4)*3,padding/2)
    
    #Write axis
    tx = width/2
    ty = 10
    textSize(16)
    textAlign(CENTER, CENTER)
    translate(tx,ty)
    rotate(-HALF_PI)
    text("Y-Coordinate",-height/2,-width/2+5)
    rotate(HALF_PI)
    translate(-tx,-ty)
    text("X-Coordinate",width/2,height-15)
    
    f = open("C:/Users/Alex/Desktop/graphData.txt")
    for lin in f:
        data = lin.split(" ")
        loc = 25
        print data[0]
        i = 4
        divs = 9
        if data[0] == "avgdeg":
            text("Avg. Degree = "+data[1], width/divs*(i+1), loc)
        elif data[0] == "maxdeg":
            text("Max Degree = "+data[1], width/divs*i, loc+20)
        elif data[0] == "colors":
            text("Colors = "+data[1], width/divs*(i+1), loc+20)
        elif data[0] == "radius":
            text("R = "+data[1], width/divs*i, loc)
    
def graph(s):
    global font, colorNodes
    stroke(0)
    strokeWeight(1)
    # Font, 16 point, anti-aliasing
    font = createFont("Helvetica", 16, True)
    # Font variable and size
    textFont(font, 15)
    f = open(s)
    for lin in f:
        data = lin.split(" ")
        # print data
        x = float(data[1])
        y = float(data[2])
        z = float(data[3])
        ncolor = int(data[4])

        if data[0] == 'c':  # Setup for circle mode
            createCircleGraph()
            mode = 'c'
            
        elif data[0] == 'u':  # Setup for unit square mode
            createSquareGraph()
            mode = 'u'

        elif data[0] == 's':  # Setup for sphere mode
            createSphereGraph()
            wcanvas = (w/2)-axispad
            hcanvas = (height-axispad) - padding
            mode = 's';

        elif data[0] == 'k':  # Say how many distinct colors
            colors = int(data[1])
            print "Colors needed", colors

        # Have to draw a node
        elif data[0] == 'n':
            noStroke();
            if mode == 'u':  # Unit square
                xi = x * (w - axispad) + axispad
                yi = y * (h - axispad) + padding
                colorNodes.append((xi, yi, ncolor, 0))

            elif mode == 'c':  # Circle
                xi = (x/2 * (w - axispad) + axispad)
                yi = (y/2 * (h - axispad) + padding)
                colorNodes.append((xi, yi, ncolor, 0))
                
            elif mode == 's':  # Sphere
                xi = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yi = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                zi = z
                
                if zi >= 0:
                    colorNodes.append((xi, yi, ncolor, 0))
                else:
                    colorNodes.append((xi + w/2, yi, ncolor, 0))

        # Have to draw an edge
        elif data[0] == 'e':  # Need to draw an edge 
            stroke(0)
            if mode == 'u':  # Unit square
                line(xi, yi, x * (w - axispad) + axispad, y * (h - axispad) + padding)

            elif mode == 'c':  # Circle
                line(xi, yi, (x/2 * (w - axispad) + axispad), (y/2 * (h - axispad) + padding))

            elif mode == 's':  # Sphere
                xl = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yl = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                if z >= 0:
                    if zi < 0:
                        stroke(205);
                        
                    else:
                        stroke(0)
                    line(xi,yi,xl,yl)
                else:
                    if zi >= 0:
                        stroke(205);
                    else:
                        stroke(0)
                    offset = w/2
                    line(xi+offset,yi,xl+offset,yl)
                
        # Have to draw a terminal clique node
        elif data[0] == 'l':
            noStroke()
            if mode == 'u':  # Unit square
                xi = x * (w - axispad) + axispad;
                yi = y * (h - axispad) + padding;
                colorNodes.append((xi, yi, 0, 1))

            elif mode == 'c':  # Unit square
                xi = (x/2 * (w - axispad) + axispad)
                yi = (y/2 * (h - axispad) + padding)
                colorNodes.append((xi, yi, 0, 1))

            elif mode == 's':
                xi = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yi = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                zi = z
                if zi >= 0:
                    colorNodes.append((xi, yi, ncolor, 1))
                else:
                    colorNodes.append((xi + w/2, yi, ncolor, 1))

    for node in colorNodes:
        ellipseMode(CENTER);
        colorMode(HSB, 255);
        fill(color(node[2]*(255/colors) % 255, 255, 255))
        if (node[3] == 1):
            stroke(123)
            fill(color(0, 0, 0))
        ellipse(node[0], node[1], 10, 10)
    colorNodes = []
        
def keyPressed():
    print "PASO POR AQUI"
    xi = 0
    yi = 0
    zi = 0
    mode = ''
    colors = 1
    colorNodes = []
    if key == '1':
        background(255) 
        s = "C:/Users/Alex/Desktop/bipartite1.txt"
        graph(s)
    if key == '2':
        background(255) 
        s = "C:/Users/Alex/Desktop/bipartite2.txt"
        graph(s)
    elif key == 'g':
        background(255) 
        s = "C:/Users/Alex/Desktop/nodes.txt"
        graph(s)

def draw():
    asdf=1
#   if (keyPressed):
#     if (key == 'b' || key == 'B'):
#       fill(0)
#   else
#     fill(255)
#   rect(25, 25, 50, 50)