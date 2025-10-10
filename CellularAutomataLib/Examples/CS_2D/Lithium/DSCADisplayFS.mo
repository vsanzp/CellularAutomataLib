within CellularAutomataLib.Examples.CS_2D.Lithium;
function DSCADisplayFS "DSCA display function"
  import CellularAutomataLib.Components.ExternalObj.*;
  input Anim animation;
  input CS space;

  external "C" DSCASetDisplayFS(animation,space);
  annotation (Include = "#include <lithium.c>", Documentation(info="<html>
<p>Display function</p>
</html>"));

end DSCADisplayFS;
