within CellularAutomataLib.Test;
model Test_RowExtInit "Test based on the GOL CA model using external initialization"
  extends Modelica.Icons.Example;
  CellularAutomataLib.Examples.CS_2D.GameOfLife.CSGol_row cSGol_row(
    X=10,
    Y=20,
    initial_step=0,
    init_cells=fill(0, 0, 2))
    annotation (Placement(transformation(extent={{-46,-20},{-26,0}})));

  CellularAutomataLib.Components.Interfaces.OutputRegionM O(
    XFromRange={4,6},
    YFromRange={6,13},
    output_rate=1,
    redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-46,18},{-26,38}})));
  constant Integer result[3,8] = [1,1,1,1,1,1,1,1; 1,0,1,1,1,1,0,1; 1,1,1,1,1,1,1,1]; // at step 4
  Boolean fail( start = false);
  CellularAutomataLib.Components.Interfaces.ExtInitRegion extInitRegion(XRange={5,5}, YRange={5,14},                                 redeclare
      function ExtInit =
                GOLExtInit)
    annotation (Placement(transformation(extent={{-72,-10},{-52,10}})));
  Modelica.Blocks.Sources.Constant const(k=1)
    annotation (Placement(transformation(extent={{-98,-10},{-78,10}})));
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
    annotation (Line(points={{-35,1},{-42.2,1},{-42.2,28}},
                                                        color={0,0,0}));
  connect(extInitRegion.TO, cSGol_row.Space) annotation (Line(points={{-56,0},{
          -35,0},{-35,1}},               color={0,0,0}));
  connect(const.y, extInitRegion.u)
    annotation (Line(points={{-77,0},{-70,0}}, color={0,0,127}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_row model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
<p>Note that in this model the graphical animation is delayed to facilitate the observation of simulation (d<span style=\"font-family: monospace;\">isplayDelay=100000).</span></p>
</html>"),
    experiment(StopTime=15, __Dymola_Algorithm="Dassl"));
end Test_RowExtInit;
