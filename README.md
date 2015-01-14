# JS2SCAD - JavaScript to OpenSCAD translator

**js2scad** provides a library and a CLI tool for converting JavaScript code into [OpenSCAD][1] input format.
This tool is for those, who like JavaScript and want to create [OpenSCAD][1] 3D models using this language.

## Example of use

Suppose we want to draw a couple of tyres:

```javascript
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
```

Then, translate JS code into [OpenSCAD][1] format and open result in [OpenSCAD][1]:

```
$ js2scad -i tyre.js -o tyre.scad
$ openscad tyre.scad
```

Press F5 in [OpenSCAD][1] GUI and you will get something like this:

![Tyre][1]

[1]: http://www.openscad.org/

[1]: examples/tyre.png
