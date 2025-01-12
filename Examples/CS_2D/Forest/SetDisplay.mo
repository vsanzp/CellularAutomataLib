within CellularAutomataLib.Examples.CS_2D.Forest;
function SetDisplay
    import CellularAutomataLib.Components.*;
  input CS space;
  external "C" SetDisplay(space);
  annotation (
    Include = "#include <forest.c>", Documentation(info="<html>
<p>Display function</p>
</html>"));
end SetDisplay;
