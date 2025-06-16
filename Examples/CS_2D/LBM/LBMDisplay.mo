within CellularAutomataLib.Examples.CS_2D.LBM;
function LBMDisplay
  input Components.Anim animation;
  input Components.CS space;

  external "C" D2Q9SetDisplay(animation,space);
  annotation (Include = "#include <LBM.c>", Documentation(info="<html>
<p>Display function</p>
</html>"));

end LBMDisplay;
