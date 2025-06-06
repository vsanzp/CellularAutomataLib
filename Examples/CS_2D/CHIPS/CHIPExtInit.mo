within CellularAutomataLib.Examples.CS_2D.CHIPS;
function CHIPExtInit
    import CellularAutomataLib.Components.*;
  input CS space;
  input Integer x;
  input Integer y;
  input Integer z;
  input Real value;

  external "C" CHIPExtInit(space, x, y, z, value);
  annotation (
    Include = "#include <chip.c>", Documentation(info="<html>
<p>External initalization function.</p>
</html>"));
end CHIPExtInit;
