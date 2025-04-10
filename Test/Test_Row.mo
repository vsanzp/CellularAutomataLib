within CellularAutomataLib.Test;
model Test_Row
  Examples.CS_2D.GameOfLife.CSGol_row cSGol_row(
    X=10,
    Y=20,
    init_cells=[5,5; 5,6; 5,7; 5,8; 5,9; 5,10; 5,11; 5,12; 5,13; 5,14])
    annotation (Placement(transformation(extent={{-46,-20},{-26,0}})));

  Components.OutputRegionM O(
    XFromRange={4,6},
    YFromRange={6,13},
    output_rate=1,
    redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-46,18},{-26,38}})));
  constant Integer result[3,8] = [1,1,1,1,1,1,1,1; 1,0,1,1,1,1,0,1; 1,1,1,1,1,1,1,1]; // at step 4
  Boolean fail( start = false);
algorithm
  when terminal() then
    for i in 1:3 loop
      for j in 1:8 loop
        if result[i,j] <> integer(O.yM[i,j,1]) then
          Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell["+String(i+O.XFromRange[1]-1)+","+String(j+O.YFromRange[1]-1)+"]: is "+String(O.yM[i,j,1])+" instead of "+String(result[i,j]));
          fail := true;
        end if;
      end for;
    end for;
    if not fail then
        Modelica.Utilities.Streams.print("*******************");
        Modelica.Utilities.Streams.print("******* -- TEST OK!");
        Modelica.Utilities.Streams.print("*******************");
    end if;
  end when;
equation
  connect(cSGol_row.Space, O.FROM)
    annotation (Line(points={{-35,1},{-36,1},{-36,28}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_row model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
<p>Note that in this model the graphical animation is delayed to facilitate the observation of simulation (d<span style=\"font-family: monospace;\">isplayDelay=100000).</span></p>
</html>"),
    experiment(StopTime=15, __Dymola_Algorithm="Dassl"));
end Test_Row;
