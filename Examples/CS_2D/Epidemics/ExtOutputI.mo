within CellularAutomataLib.Examples.CS_2D.Epidemics;
function ExtOutputI "Output function for I"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputI(space, x, y, z);
  annotation (
    Include = "#include <epidemics.c>", Documentation(info="<html>
<p>Output function for the I value</p>
</html>"));
end ExtOutputI;
