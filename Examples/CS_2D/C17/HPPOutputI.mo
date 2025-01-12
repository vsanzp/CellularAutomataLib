within CellularAutomataLib.Examples.CS_2D.C17;
function HPPOutputI
  import CellularAutomataLib.Components.*;
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
