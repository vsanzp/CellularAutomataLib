within CellularAutomataLib.Examples.CS_2D.C17.LBM;
function LBMDisplay "LBM display function"
extends Modelica.Icons.Function;
  import CellularAutomataLib.Components.ExternalObj.*;
  input Anim animation;
  input CS space;

  external "C" D2Q9SetDisplay(animation,space);
  annotation (Include = "#include <LBM.c>", Documentation(info="<html>
<p>Display function</p>
</html>"));

end LBMDisplay;
