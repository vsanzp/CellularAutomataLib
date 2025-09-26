within CellularAutomataLib.Examples.CS_2D.CHIPS;
function CHIPSetDisplay "Chip model display function"
    import CellularAutomataLib.Components.ExternalObj.*;
    input Anim animation;
  input CS space;
  external "C" CHIPSetDisplay(animation,space);
  annotation (
    Include = "#include <chip.c>", Documentation(info="<html>
<p>Display function for the chip model.</p>
</html>"));
end CHIPSetDisplay;
