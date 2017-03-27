include <config.scad>
use <chassis.scad>

spacing = 10;

module steun() {
  rotate([0,0,0]) { motor_steun(); }
}

projection(cut = true) {
  plaat_boven();
  translate([chassis_breedte + spacing,0,0]) { plaat_onder(); }
  translate([-motor_lengte - spacing, chassis_lengte/3*2 + spacing, 0]) { steun(); }
  translate([spacing, chassis_lengte/3*2 + 10, 0]) { steun(); }
}

$vpt = [ 76.46, 62.66, 30.14 ];
$vpr = [ 0.00, 0.00, 0.00 ];
$vpd = 800;
