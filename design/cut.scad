include <config.scad>
use <chassis.scad>

spacing = 10;

projection(cut = true) {
  plaat_boven();
  translate([chassis_breedte + spacing,0,0]) { plaat_onder(); }
  translate([0,0,-0.1]) {    // TEMP: fix issue after rotation of motor
    translate([-motor_lengte/6*3 - spacing, chassis_lengte/3*2 + spacing, 0]) {
      motor_steun();
    }
    translate([motor_lengte, chassis_lengte/3*2 + 10, 0]) {
      motor_steun();
    }
  }
}

$vpt = [ 76.46, 62.66, 30.14 ];
$vpr = [ 0.00, 0.00, 0.00 ];
$vpd = 800;
