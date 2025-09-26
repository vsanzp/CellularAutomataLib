within CellularAutomataLib.Examples.CS_2D.C17;
function HPPOutputR "HPP output function for R"
  import CellularAutomataLib.Components.ExternalObj.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  output Real value;

  external "C" value = HPPOutputR(space, x, y, z);
  annotation (
    Include = "#include <c17hpp.c>", Documentation(info="<html>
<p>HPP output function for R</p>
</html>"));
end HPPOutputR;
