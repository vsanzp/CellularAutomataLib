within CellularAutomataLib.Examples.CS_2D.C17;
function HPPOutputS
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = HPPOutputS(space, x, y, z);
  annotation (
    Include = "#include <c17hpp.c>", Documentation(info="<html>
<p>HPP output function for S</p>
</html>"));
end HPPOutputS;
