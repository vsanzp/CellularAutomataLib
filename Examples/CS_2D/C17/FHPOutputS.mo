within CellularAutomataLib.Examples.CS_2D.C17;
function FHPOutputS
  import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = OutputS(space, x, y, z);
  annotation (
    Include = "#include <c17fhp.c>", Documentation(info="<html>
<p>FHP output function for S</p>
</html>"));
end FHPOutputS;
