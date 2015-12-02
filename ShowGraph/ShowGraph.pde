final int h = 590;
final int w = 590;
BufferedReader reader;
String line;
float xi = 0; float yi = 0;
char mode;
int colors = 1;
void setup() {
  size(610, 610);
  background(30);
  noSmooth();
  reader = createReader("C:/Users/Alex/Desktop/nodes.txt");  
}

void draw() {
  stroke(255);
  strokeWeight(1);
  
  //Draw frame
  line(10, 10, 10, 600);
  line(10, 10, 600, 10);
  line(600, 10, 600, 600);
  line(10, 600, 600, 600);
  
  //Read file
  try {
    line = reader.readLine();
  } 
  catch (IOException e) {
    e.printStackTrace();
    line = null;
  }
  if (line == null) {
    // Stop reading because of an error or file is empty
    noLoop();  
    println("Done");
  } 
  else {
    String[] pieces = split(line, " ");
    
    char node = pieces[0].charAt(0);
    float x =     float(pieces[1]);
    float y =     float(pieces[2]);
    float z =     float(pieces[3]);
    int ncolor =     int(pieces[4]);
    
    switch(node){
      case 'k': //Update needed colors
        colors = int(pieces[1]);
        println("Colors"+colors);
      case 'u': //Unit square mode
        mode = 'u';
        break;
      case 'c': //Circle mode
        mode = 'c';
        fill(30);
        ellipse(610/2, 610/2, 610-20, 610-20);
        break;
      case 's': //Sphere mode
        mode = 's';
        break;
      case 'n': //Need to draw a point
        noStroke();
        if(mode == 'u'){ //Unit square
          xi = x*w;
          yi = y*h;
          xi = xi + 10;
          yi = yi + 10;
          //ellipse(x, y, w, h);
          colorMode(HSB, 255);
          fill( color((((255-100)/colors))*ncolor, 255, 170) );
          ellipse(xi,yi,15,15);
          point(xi, yi);
        }
        else if(mode == 'c'){ //Circle
          xi = x*w;
          yi = y*h;
          xi = xi/2 + 10;
          yi = yi/2 + 10;
          point(xi, yi);
        }  
        else{ //Sphere
          
        }
        break;
      case 'e': //Need to draw an edge 
        stroke(255);
        if(mode == 'u'){ //Unit square
          line(xi, yi, (x*w)+10, (y*h)+10);
        }
        else if(mode == 'c'){ //Circle
          line(xi, yi, (x*w)/2+10, (y*h)/2+10);
        }  
        else{ //Sphere
          
        }
        break;
    }
    
  }
}