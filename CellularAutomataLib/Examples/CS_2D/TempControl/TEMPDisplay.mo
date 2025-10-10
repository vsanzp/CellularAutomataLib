within CellularAutomataLib.Examples.CS_2D.TempControl;
function TEMPDisplay "Temperature controller model display function"
extends Modelica.Icons.Function;
    import CellularAutomataLib.Components.ExternalObj.*;
    input Anim animation;
  input CS space;
  external "C" TEMPSetDisplay(animation,space);
  annotation (
    Include = "#include <tempcontrol.c>", Documentation(info="<html>
<p>Display function for the chip model.</p>
</html>"));
end TEMPDisplay;
