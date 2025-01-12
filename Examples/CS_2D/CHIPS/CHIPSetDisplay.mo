within CellularAutomataLib.Examples.CS_2D.CHIPS;
function CHIPSetDisplay
    import CellularAutomataLib.Components.*;
  input CS space;
  external "C" CHIPSetDisplay(space);
  annotation (
    Include = "#include <chip.c>", Documentation(info="<html>
<p>Display function for the chip model.</p>
</html>"));
end CHIPSetDisplay;
