#include <Servo.h>
Servo motor_A;
Servo motor_B;
Servo motor_C;
float O1 ,O2, O3 , O ;        // angles motor in degree
 
float rad_O1 , rad_O2, rad_O3, rad_O ; // angles motor in Radian
   
float L1, L2, L3;        // lengths Arm
 
float x, x1, x2;       //Points
float y, y1, y2;

float pi = 3.14159265359;


void setup() {
  motor_A.attach(3);
  motor_B.attach(5);
  motor_C.attach(6);
  Serial.begin(9600);
  
 Serial.println("Enter the length(L1) in centimeter ");
 while(Serial.available()==0){}
 L1=Serial.parseFloat();
 Serial.print("your length (L1) = "); 
 Serial.println(L1);
   
 Serial.println("Enter the length(L2) in centimeter ");
 while(Serial.available()==0){}
 L2=Serial.parseFloat();
 Serial.print("your length (L2) = "); 
 Serial.println(L2);

 Serial.println("Enter the length(L3) in centimeter ");
 while(Serial.available()==0){}
 L3=Serial.parseFloat();
 Serial.print("your length (L3) = "); 
 Serial.println(L3);
 
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
   }

void loop() {

 if (Serial.available())  {
 
    char ch = Serial.read();
    if (ch == '1'){               
  //--------------------------Forwad kinematics Case--------------------------------  
                     
  Serial.println("Enter the angle (motor_A) in degree ");
  while(Serial.available()==0){}
  O1=Serial.parseFloat();
  Serial.print("your angle (motor_A) = "); 
  Serial.println(O1);
  
  Serial.println("Enter the angle (motor_B) in degree ");
  while(Serial.available()==0){}
  O2=Serial.parseFloat();
  Serial.print("your angle (motor_B) = "); Serial.println(O2);

  Serial.println("Enter the angle (motor_C) in degree ");
  while(Serial.available()==0){}
  O3=Serial.parseFloat();
  Serial.print("your angle (motor_C) = "); Serial.println(O3);

//-------------------------------------calculation
  rad_O1 = (O1*pi)/180;    
  rad_O2 = (O2*pi)/180;
  rad_O3 = (O3*pi)/180;
  rad_O = (O*pi)/180;
  
  motor_A.write(O1); 
  motor_B.write(O2);
  motor_C.write(O3);
  
  x = L1 * cos(rad_O1) +L2 * cos(rad_O1 + rad_O2) + L3 * cos(rad_O1 + rad_O2 + rad_O3);
  y = L1 * sin(rad_O1) +L2 * sin (rad_O1 + rad_O2)+ L3 * sin (rad_O1 + rad_O2 + rad_O3);
  O = O1 + O2 + O3;
  x1 = L1 * cos(rad_O1);
  y1 = L1 * sin(rad_O1);           
  x2 = L1 * cos(rad_O1) +L2 * cos(rad_O1 + rad_O2);
  y2 = L1 * sin(rad_O1) +L2 * sin (rad_O1 + rad_O2);
  
  //-----------------------------Print data 
 Serial.print("X = "); Serial.print(x);
 Serial.print(" & Y = "); Serial.println(y); 
 Serial.print("Total angle (O) = "); Serial.println(O);
 Serial.print("motor_A moved to angle  "); Serial.println(O1);
 Serial.print("motor_B moved to angle "); Serial.println(O2);
 Serial.print("motor_C moved to angle "); Serial.println(O3);
 Serial.println("motor_A position(0 , 0)"); 
 Serial.print("motor_B position("); Serial.print(x1);Serial.print(" , ");Serial.print(y1);Serial.println(")");
 Serial.print("motor_C position("); Serial.print(x2);Serial.print(" , ");Serial.print(y2);Serial.println(")");
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
 }
 
else if(ch == '0')

//-----------------------------inverse kinematics case----------------------------------

      {Serial.println("Enter the value X ");
      while(Serial.available()==0){}
      x=Serial.parseFloat();
      Serial.print("your X = "); Serial.println(x);
      
      Serial.println("Enter the value Y ");
      while(Serial.available()==0){}
      y=Serial.parseFloat();
      Serial.print("your Y = "); Serial.println(y);

      Serial.println("Enter the Total Angle O  in degree");
      while(Serial.available()==0){}
      O=Serial.parseFloat();
      Serial.print("your O = ");Serial.println(O);
      
  //-------------------------------------calculation
  rad_O = (O*pi)/180;
  x2=x-L3*cos(rad_O);
  y2=y-L3*sin(rad_O);   
  rad_O2 = acos((sq(x2)+ sq(y2) - sq(L1) - sq(L2)) / (2*L1*L2));
      
  rad_O1= acos(((L1 + L2 * cos(rad_O2))*x2+(L2 * y2 * sin(rad_O2))) / (sq(x2)+ sq(y2)));

      O1= (rad_O1*180)/pi;
      O2= (rad_O2*180)/pi;
      O3= O-O1-O2;
     
      motor_A.write(O1); 
      motor_B.write(O2);
      motor_C.write(O3);
      x1 = L1 * cos(rad_O1) ;
      y1 = L1 * sin(rad_O1) ;
  
// ------------------->>> Print Data
 Serial.print("motor_A moved to angle O1 "); Serial.println(O1);
 Serial.print("motor_B moved to angle O2 "); Serial.println(O2);
 Serial.print("motor_C moved to angle O3 "); Serial.println(O3);
 
 Serial.println("motorA position(0 , 0)"); 
 Serial.print("motorB position("); Serial.print(x1);Serial.print(" , ");Serial.print(y1);Serial.println(")");
 Serial.print("motorC position("); Serial.print(x2);Serial.print(" , ");Serial.print(y2);Serial.println(")");
 
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
 }
 
 else {Serial.println("EROR!! Enter (0) OR (1) ONLY ");
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
 }
 }
 }
