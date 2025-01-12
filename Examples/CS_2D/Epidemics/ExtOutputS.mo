within CellularAutomataLib.Examples.CS_2D.Epidemics;
function ExtOutputS
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputS(space, x, y, z);
  annotation (
    Include = "#include <epidemics.c>", Documentation(info="<html>
<p>Output function for the S value</p>
</html>"));
end ExtOutputS;
