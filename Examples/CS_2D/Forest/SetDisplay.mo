within CellularAutomataLib.Examples.CS_2D.Forest;
function SetDisplay
    import CellularAutomataLib.Components.*;
    input Anim animation;
  input CS space;
  external "C" SetDisplay(animation,space);
  annotation (
    Include = "#include <forest.c>", Documentation(info="<html>
<p>Display function</p>
</html>"));
end SetDisplay;
