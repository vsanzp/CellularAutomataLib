within CellularAutomataLib.Examples.CS_2D.C17;
function FHPOutputI "FHP output function for I"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputI(space, x, y, z);
  annotation (
    Include = "#include <c17fhp.c>", Documentation(info="<html>
<p>FHP output function for I</p>
</html>"));
end FHPOutputI;
