$fn = 100;

motor_lengte      = 65;
motor_hoogte      = 22.3;
motor_breedte     = 18.5;

motor_as_lengte   = 38;
motor_as_diameter = 5.3;

motor_as_afstand_rand = motor_hoogte / 2;

module motor() {
  translate([0, -motor_as_afstand_rand, -motor_as_afstand_rand]) { cube([motor_breedte, motor_lengte, motor_hoogte]); }
  translate([-(motor_as_lengte - motor_breedte)/2, 0, 0]) {
    rotate([0,90,0]) { cylinder(motor_as_lengte, d=motor_as_diameter); }
  }
}

wiel_breedte     = 26;
wiel_diameter    = 70;
wiel_as_breedte  = 30;
wiel_as_diameter = 14;

module wiel() {
  cylinder(wiel_breedte,    d=wiel_diameter);
  cylinder(wiel_as_breedte, d=wiel_as_diameter);
}

module motor_met_wiel() {
  translate([-wiel_as_breedte,0,0]) { rotate([0, 90, 0]) { wiel(); } }
  motor();
}

module demo() {
  translate([-50,0,0]) { motor_met_wiel(); }
  translate([50, 0, ]) { rotate([0, 180, 0]) { motor_met_wiel(); } }
}

demo();
