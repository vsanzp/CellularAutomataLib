within CellularAutomataLib.Examples.CS_2D.C17;
function FHPOutputR "FHP output function for R"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputR(space, x, y, z);
  annotation (
    Include = "#include <c17fhp.c>", Documentation(info="<html>
<p>FHP output function for R</p>
</html>"));
end FHPOutputR;
