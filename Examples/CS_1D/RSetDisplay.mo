within CellularAutomataLib.Examples.CS_1D;
function RSetDisplay "Display function for Wolfram models"
  input CellularAutomataLib.Components.CS space;

  external "C" RSetDisplay(space);
  annotation (
    Include = "#include <wolfram.c>", Documentation(info="<html>
<p>Display function for elementary CA models.</p>
</html>"));
end RSetDisplay;
