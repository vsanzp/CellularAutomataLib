within CellularAutomataLib.Examples.CS_1D;
model CSR110 "Rule 110"
  import CellularAutomataLib.Components.*;
  extends CellSpace(X = 100, neighborhood = [-1; 1], wrapped_borders = 1, Tstep = 1, initial_step = 1, init_cells = [50], name = "Rule 110",
      redeclare function Default = R110Default,
      redeclare function Initial = R110Init,
      redeclare function Rule = R110Step);

  function R110Default "Rule 110 default state function"
    input CS space;
    output Integer out;

    external "C" out = RInitDefault(space);
    annotation (
      Include = "#include <wolfram.c>");
  end R110Default;

  function R110Init "Rule 110 initalization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    external "C" RInit(space, x, y, z);
    annotation (
      Include = "#include <wolfram.c>");
  end R110Init;

  function R110Step "Rule 110 transition function"
    input CS space;
    output Integer out;

    external "C" out = R110Step(space);
    annotation (
      Include = "#include <wolfram.c>");
  end R110Step;
  annotation (
    Documentation(info="<html>
<p>This model represents a one-dimensional cellular space following the Rule 110 as defined by Stephen Wolfram. </p>
<h4>Description</h4>
<p>This model respresents a cellular space of 100 cells, using the two adjacent cells as neighborhood and open (un-wrapped) borders. Only the cell located in the position 50 is initialized.</p>
<p>The new state of a cell is computed using the following table, that considers the current state of the cell (center) and its two neighbors (right and left): </p>
<table cellspacing=\"2\" cellpadding=\"0\" border=\"1\"><tr>
<td><p align=\"center\"><h4>current state (left,center,right)</h4></p></td>
<td><p>111</p></td>
<td><p>110</p></td>
<td><p>101</p></td>
<td><p>100</p></td>
<td><p>011</p></td>
<td><p>010</p></td>
<td><p>001</p></td>
<td><p>000</p></td>
</tr>
<tr>
<td><p align=\"center\"><h4>new state for center cell</h4></p></td>
<td><p>0</p></td>
<td><p>1</p></td>
<td><p>1</p></td>
<td><p>0</p></td>
<td><p>1</p></td>
<td><p>1</p></td>
<td><p>1</p></td>
<td><p>0</p></td>
</tr>
</table>
<p><br><br>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/wolfram.c</span> </p>
</html>"),
    experiment(StopTime = 50),
    __Dymola_experimentSetupOutput);
end CSR110;
