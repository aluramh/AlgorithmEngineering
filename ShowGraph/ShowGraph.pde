final int h = 590;
final int w = 590;
BufferedReader reader;
String line;
float xi = 0; float yi = 0;
char mode;
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
    
    switch(node){
      case 'u':
        mode = 'u';
        break;
      case 'c':
        mode = 'c';
        fill(30);
        ellipse(610/2, 610/2, 610-20, 610-20);
        break;
      case 's': 
        mode = 's';
        break;
      case 'n':
        if(mode == 'u'){ //Unit square
          
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
      case 'e':
        if(mode == 'u'){ //Unit square
          
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