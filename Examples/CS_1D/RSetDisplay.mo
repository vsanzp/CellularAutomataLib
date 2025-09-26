within CellularAutomataLib.Examples.CS_1D;
function RSetDisplay "Display function for Wolfram models"
  input CellularAutomataLib.Components.ExternalObj.Anim animation;
  input CellularAutomataLib.Components.ExternalObj.CS space;

  external "C" RSetDisplay(animation,space);
  annotation (
    Include = "#include <wolfram-anim.c>", Documentation(info="<html>
<p>Display function for elementary CA models.</p>
</html>"));
end RSetDisplay;
