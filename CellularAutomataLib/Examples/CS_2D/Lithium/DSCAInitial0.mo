within CellularAutomataLib.Examples.CS_2D.Lithium;
function DSCAInitial0 "Initialization function"
  input Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z;

  external "C" DSCAInitial0(space, x,y,z);
  annotation (
    Include = "#include \"lithium.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
end DSCAInitial0;
