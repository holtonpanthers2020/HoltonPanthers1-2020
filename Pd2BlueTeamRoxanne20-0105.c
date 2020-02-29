#include <kipr/wombat.h>


/*

left wheel = port 0

right wheel = port 2

touch sensor = digital 0

ET sensor = analog 2

Top hat = analog 0

---

conveyor servo = 0

claw servo = 1

*/


//CONSTANTS

const int OPEN_CLAW = 880; //servo positions

const int CLOSE_CLAW = 160;

const int RAISE_CLAW = 500;

const int RAISE_CLAW_MORE = 0;

const int LOWER_CLAW = 1900;

const int TOPHAT_COLORSHIFT = 2500;


void forward(double inches)

{

double centimeters = inches * 2.54;

double diameter = 6.94; //cm

int ticks = centimeters/(3.14*diameter) * 1100*1.85;

mrp(0,800,ticks);

mrp(2,800,ticks);

bmd(0);

bmd(2);

ao();

}


void backward(double inches)

{

double centimeters = inches * 2.54;

double diameter = 6.94; //cm

int ticks = centimeters/(3.14*diameter) * 1100*1.85;

mrp(0,800,-ticks);

mrp(2,800,-ticks);

bmd(0);

bmd(2);

ao();

}


void turn_left(double degrees)

{

double ticks = 13.7 * degrees;

mrp(0,500,-ticks);

mrp(2,500,ticks);

bmd(0);

bmd(2);

ao();

}


void turn_right(double degrees)

{

double ticks = 13.7 * degrees;

mrp(0,500,ticks);

mrp(2,500,-ticks);

bmd(0);

bmd(2);

ao();

}


int align() //scan left and right until find black line

{

int ticks = 0; //establish tick count

while (analog(0) < 2000 && ticks < 300) //if white

{

mrp(0, 100, 2); //turn right

mrp(2, 100, -2);

bmd(0);

bmd(2);

ticks += 10; //keeps track of how many ticks turned

}


if (analog(0) < TOPHAT_COLORSHIFT) //if still white

{

ticks = 0; //reset tick count

while (analog(0) < TOPHAT_COLORSHIFT && ticks < 600) //if white

{

mrp(0, 100, -2); //turn left

mrp(2, 100, 2);

bmd(0);

bmd(2);

ticks += 10; //keeps track of how many ticks turned

}

}

return 0;

}



//claw start up (color camera on the claw) & open??(depending on starting box restrictions)


int main()

{ //main

printf("Move out of start box until edge\n");

while (digital(0) == 0) 

{ //touch sensor not pressed

mav(0,600); //move forward

mav(2,600);

}

ao();

printf("Back up\n");

backward(5.5);

printf("Knock out PVC cupler from ramp\n");

turn_left(110);

turn_right(20);

printf("Go up ramp\n");

while (digital(0) == 0) 

{ //touch sensor not pressed

if (analog(0) < TOPHAT_COLORSHIFT) 

{ //if white (not sensing black tape)

ao();

align(); //function to find black tape

printf("Align to find black tape\n");

}

if (analog(0) > TOPHAT_COLORSHIFT) 

{ //if black

printf("Following black line\n");

mav(0,600); //move forward up ramp

mav(2,600);

msleep(500);

}

}


//at top of ramp

backward(2);

msleep(500);

turn_left(45);

msleep(500);

forward(6);

msleep(500);

turn_left(45);

msleep(500);

// turn_left(30);


//INSTEAD OF RANDOM TURNING^^^ USE TOP HAT SENSOR

set_servo_position(0,RAISE_CLAW_MORE);


printf("Go to botguy");

//float diameter = 4.3; //diameter of wheels in cm


//detect botguy and adjust until centered

camera_open_black();

while (get_object_center_x(0, 0) != 80) 

{ //iterate until obj is centered

camera_update();

while (get_object_center_x(0, 0) < 80) 

{ //if obj on left move left

printf("Object is on the left!\n");

mav(0,-200);

mav(2,200);

camera_update();

printf("%d\n", get_object_center_x(0, 0));

}

printf("Object is on the right!\n"); //else move right

mav(2,-200);

mav(0,200);

camera_update();

printf("%d\n", get_object_center_x(0, 0));

}

ao();

camera_close();

printf("object centered\n");


//move forward until @ obj

printf("move towards object\n");

float distance = analog(2); //ET sensor

float ticks = 22390219*pow(distance, -1.3) + 2292832*pow(distance,-1.16); //conversion equation

int ticksINT = (int) ticks;

printf("ticks: %d",ticksINT);

mrp(0, 250, ticksINT);

mrp(2, 250, ticksINT);

bmd(0);

bmd(2);

ao();


set_servo_position(1, CLOSE_CLAW);

//turn left and drop botguy on our side

turn_left(90);

set_servo_position(1, OPEN_CLAW);

ao();


printf("Operation complete\n");

return 0;

}

