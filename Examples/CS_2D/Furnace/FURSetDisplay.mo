within CellularAutomataLib.Examples.CS_2D.Furnace;
function FURSetDisplay "Furnace model display function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input Anim animation;
  input CS space;
  external "C" FURSetDisplay(animation,space);
  annotation (
    Include = "#include <furnace.c>", Documentation(info="<html>
<p>Display function used in the graphical animations.</p>
</html>"));
end FURSetDisplay;
