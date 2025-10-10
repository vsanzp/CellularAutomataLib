within CellularAutomataLib.Examples.CS_2D.Lithium;
function DSCADisplayC "DSCA display function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input Anim animation;
  input CS space;

  external "C" DSCASetDisplayC(animation,space);
  annotation (Include = "#include <lithium.c>", Documentation(info="<html>
<p>Display function</p>
</html>"));

end DSCADisplayC;
