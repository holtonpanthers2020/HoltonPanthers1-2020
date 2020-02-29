#include <kipr/wombat.h>
int forward(double inches) { //in inches
    double milimeters = inches*25.4;
    set_create_distance(0);
    while(get_create_distance() < milimeters){ // milimeters 
        create_drive_direct(100,96); 
    } 
    create_stop(); 
    printf("go forward %d inches\n", inches);
    
    return 0;
}

int backward(double inches){
    double milimeters = inches*25.4;
    set_create_distance(0);
    while(get_create_distance() < milimeters){ // milimeters 
        create_drive_direct(100,96); 
    } 
    create_stop(); 
 	printf("go backward %d inches\n", inches);
    
    return 0;
}

int turnRight (int degrees){
    set_create_total_angle(0);
    while(-get_create_total_angle() < degrees) // degrees 
        {
            create_drive_direct(100,-100);
        }
	create_stop();
    printf("turn right %d degrees\n", degrees);
    
    return 0;
}

int turnLeft (int degrees){ //check signs if this fails
    set_create_total_angle(0);
    while(get_create_total_angle() < degrees) // degrees 
        {
            create_drive_direct(-100,100);
        }
	create_stop();
    printf("turn left %d degrees\n", degrees);
    
    return 0;
}
const int CLOSE_CLAW = 1426;
const int OPEN_CLAW = 926;
const int OPEN_CLAW_FULL = 0;

//start w/ open claw
int main() {
    create_connect();
    enable_servos();
    
	printf("servo position: %d\n", get_servo_position(1));
    printf("Open claw\n");
    set_servo_position(1, 1000);
    msleep(500);
    
    printf("Go forward to 1st block\n");
    forward(15); //move straight out of start block 

    printf("Grab 1st block\n");
    set_servo_position(0, CLOSE_CLAW);
    
    printf("Go back to start box\n");
    backward(6);
    turnLeft(180);
    forward(10);
    
    //drop lack in starting box
    printf("Drop 1st block in start box\n");
    set_servo_position(0, OPEN_CLAW_FULL);
    
    printf("Go towards 2nd block\n");
    backward(5);
    turnRight(90);
    forward(10);
    turnRight(90);
    set_servo_position(0, OPEN_CLAW);
    forward(15);
    
    printf("Grab 2nd block\n");
    set_servo_position(0, CLOSE_CLAW);
    
    printf("Go back to start box\n");
    backward(6);
    turnRight(90);
    forward(10);
    turnRight(90);
    forward(10);
    
    printf("Drop 2nd block in start box\n");
    set_servo_position(0, OPEN_CLAW_FULL);
    
    printf("Go to 3rd block\n");
    backward(5);
    turnRight(90);
    forward(20);
    turnRight(90);
    forward(15);
    
    printf("Grab 3rd black\n");
    set_servo_position(0, CLOSE_CLAW);
    
    printf("Go back to the starting box\n");
    backward(6);
    turnRight(90);
    forward(20);
    turnRight(90);
    forward(10);
    
    printf("Place third block down\n");
    set_servo_position(0, OPEN_CLAW_FULL);

    create_disconnect(); 
    return 0; 
}



