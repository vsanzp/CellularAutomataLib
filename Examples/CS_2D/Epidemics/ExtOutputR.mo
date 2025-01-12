within CellularAutomataLib.Examples.CS_2D.Epidemics;
function ExtOutputR
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputR(space, x, y, z);
  annotation (
    Include = "#include <epidemics.c>", Documentation(info="<html>
<p>Output function for the R value.</p>
</html>"));
end ExtOutputR;
