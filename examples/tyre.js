function createTyre(diskDiameter, width, profilePerCent) {
  var profile = width * profilePerCent / 100.00;
  var radius = diskDiameter * 25.4 / 2.0 + profile;
  return scad.Difference(
    scad.Cylinder(width, {r: radius, center: true}),
    scad.Cylinder(width + 2, {r: radius - profile, center: true})
  );
}

var sportTyre = createTyre(18, 220, 50);
sportTyre.rotate([90, 0, 0]).translate([0, 250, 0]);
var cityTyre = createTyre(13, 155, 65);
cityTyre.rotate([90, 0, 0]);
