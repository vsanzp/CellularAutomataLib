within CellularAutomataLib.Examples.CS_2D.C17;
function HPPOutputI "HPP output function for I"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = HPPOutputI(space, x, y, z);
  annotation (
    Include = "#include <c17hpp.c>", Documentation(info="<html>
<p>HPP output function for I</p>
</html>"));
end HPPOutputI;
