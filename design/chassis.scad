include <config.scad>

module t(dikte=1) {
  union() {
    translate([-vijs_diameter/2,0,0]) {
      cube([vijs_diameter, vijs_lengte, dikte]);
    }
    translate([-moer_diameter/2, vijs_lengte/2,0]) {
      cube([moer_diameter, moer_hoogte, dikte]);
    }
  }
}

// t();

module motor() {
  translate([0, -motor_as_afstand_rand, -motor_as_afstand_rand]) {
    cube([motor_breedte, motor_lengte, motor_hoogte]);
  }
  translate([-(motor_as_lengte - motor_breedte)/2, 0, 0]) {
    rotate([0,90,0]) { cylinder(motor_as_lengte, d=motor_as_diameter); }
  }
}

module wiel() {
  cylinder(wiel_breedte,    d=wiel_diameter);
  cylinder(wiel_as_breedte, d=wiel_as_diameter);
}

module motor_met_wiel() {
  translate([-wiel_as_breedte,0,0]) { rotate([0, 90, 0]) { wiel(); } }
  motor();
}

// door de afronding, wordt het chassis groter. deze hulp-variabelen zijn de 
// netto waarden.
breedte = chassis_breedte / 2 - chassis_afronding;
lengte  = chassis_lengte - 2 * chassis_afronding;
dikte   = chassis_dikte / 2; // later bij afronding komt dit er terug bij

// het chassis is symmertrisch, dus we kunnen een half chassis modelleren en dan
// tweemaal naast elkaar plaatsen om een heel chassis te bekomen.
module half_chassis() {
  difference() {
    // half chassis
    cube([ breedte, lengte, dikte ]);
    // uitsparing voor wiel op 1/3 van voorkant, halve wiel breedte diep
    translate([0, (lengte/3)-(wiel_uitsparing/2), 0]) {
      cube([wiel_breedte/2, wiel_uitsparing, dikte]);
    }
  }
}

module motor_steun() {

  module vleugel() { cube([motor_lengte/6, chassis_dikte, chassis_dikte]); }

  difference() {
    union() {
      cube([motor_lengte, motor_hoogte, chassis_dikte]);
      // vleugels bovenkant
      translate([ motor_lengte/6*1.5,  motor_hoogte,  0 ]) { vleugel(); }
      translate([ motor_lengte/6*3.5,  motor_hoogte,  0 ]) { vleugel(); }
      // vleugels onderkant
      translate([ motor_lengte/6*0.5, -chassis_dikte, 0 ]) { vleugel(); }
      translate([ motor_lengte/6*2.5, -chassis_dikte, 0 ]) { vleugel(); }
      translate([ motor_lengte/6*4.5, -chassis_dikte, 0 ]) { vleugel(); }
    }
    // t-verbindingen bovenkant
    translate([motor_lengte/6*3, motor_hoogte, 0]) {
      mirror([0,1,0]) { t(chassis_dikte); }
    }
    translate([motor_lengte/6*5, motor_hoogte, 0]) {
      mirror([0,1,0]) { t(chassis_dikte); }
    }
    // // t-verbindingen onderkant
    translate([motor_lengte/6*2, 0, 0]) {
      t(chassis_dikte);
    }
    translate([motor_lengte/6*4, 0, 0]) {
      t(chassis_dikte);
    }
  }
}

// motor_steun();

// Deze module wordt alleen gebruikt om de uitsparingen in de platen te maken.
// Normaal gezien zouden we hiervoor gewoon de module van de steun zelf
// gebruiken. Zie https://github.com/openscad/openscad/issues/1974 voor meer
// info omtrent wat waarschijnlijk een bug is. Het probleem lijkt verbonden aan
// rotatie, dus deze module implementeert de rotatie "manueel".

module motor_steun_vleugels() {

  module vleugel() { cube([chassis_dikte, motor_lengte/6, chassis_dikte]); }

  // vleugels bovenkant
  translate([0, motor_lengte/6*1.5, motor_hoogte])   { vleugel(); }
  translate([0, motor_lengte/6*3.5, motor_hoogte])   { vleugel(); }
  // vleugels onderkant
  translate([0, motor_lengte/6*0.5, -chassis_dikte]) { vleugel(); }
  translate([0, motor_lengte/6*2.5, -chassis_dikte]) { vleugel(); }
  translate([0, motor_lengte/6*4.5, -chassis_dikte]) { vleugel(); }
  
  module vijs() { cylinder(d=vijs_diameter, h=vijs_lengte); }
  
  // vijzen
  translate([chassis_dikte/2, 0, 0]) {        // midden dikte steun
    // boven
    translate([0, 0, motor_hoogte+chassis_dikte-vijs_lengte]) {       // door plaat
      translate([0, motor_lengte/6*3, 0]) { vijs(); }
      translate([0, motor_lengte/6*5, 0]) { vijs(); }
    }
    // onder
    translate([0, 0, -chassis_dikte]) {       // door plaat
      translate([0, motor_lengte/6*2, 0]) { vijs(); }
      translate([0, motor_lengte/6*4, 0]) { vijs(); }
    }
  }
}

// motor_steun_vleugels();

module afgeronde_plaat() {
  // gecentreerd op middelpunt van wiel-as van robot
  translate([-breedte, -lengte/3, 0 ]) {
    minkowski() {
      union() {
        half_chassis();
        translate([chassis_breedte-2*chassis_afronding, 0, 0]) {
          mirror([1,0,0]) { half_chassis(); }
        }
      }
      cylinder(r=chassis_afronding, h=dikte);
    }
  }
}

// afgeronde_plaat();

module plaat_boven() {
  difference() {
    afgeronde_plaat();
    // uitsparingen voor wiel-steunen
    translate([
      -(chassis_breedte/2 - wiel_breedte/2 - motor_breedte),
      -motor_as_afstand_rand,
      -motor_hoogte
    ]) {
      motor_steun_vleugels();
    }
    translate([
      chassis_breedte/2 - wiel_breedte/2 - motor_breedte - chassis_dikte,
      -motor_as_afstand_rand,
      -motor_hoogte
    ]) {
      motor_steun_vleugels();
    }
  }
}

// plaat_boven();

module plaat_onder() {
  difference() {
    afgeronde_plaat();
    // uitsparingen voor wiel-steunen
    translate([
      -(chassis_breedte/2 - wiel_breedte/2 - motor_breedte),
      -motor_as_afstand_rand,
      chassis_dikte
    ]) {
      motor_steun_vleugels();
    }
    translate([
      chassis_breedte/2 - wiel_breedte/2 - motor_breedte - chassis_dikte,
      -motor_as_afstand_rand,
      chassis_dikte
    ]) {
      motor_steun_vleugels();
    }
  }
}

// plaat_onder();

module demo() {
  translate([-(chassis_breedte/2-wiel_breedte/2),0,0]) { motor_met_wiel(); }
  translate([chassis_breedte/2-wiel_breedte/2, 0, 0]) {
    mirror([1, 0, 0]) { motor_met_wiel(); }
  }

  translate([0,0, motor_as_afstand_rand]) {
    color("red") { plaat_boven(); }
  }
  translate([0,0,-(motor_as_afstand_rand+chassis_dikte)]) {
    color("red") { plaat_onder(); }
  }
  color("blue") {
    translate([
      -(chassis_breedte/2-wiel_breedte/2-motor_breedte),
      -motor_as_afstand_rand,
      -motor_as_afstand_rand,
    ]) {
      rotate([90,0,90]) { motor_steun(); }
    }
    translate([
      chassis_breedte/2-wiel_breedte/2-motor_breedte-chassis_dikte,
      -motor_as_afstand_rand,
      -motor_as_afstand_rand,
    ]) {
      rotate([90,0,90]) { motor_steun(); }
    }
  }
}

demo();

$vpt = [ 8.88, 12.71, 27.73 ];
$vpr = [ 83.30, 0.00, 34.30 ];
$vpd = 500;
