within CellularAutomataLib.Test;
model Test_Input "Simple input test"
  extends Modelica.Icons.Example;
  CellularAutomataLib.Examples.CS_1D.CSR30 cSR30_1(
    n_inputs=0,
    wrapped_borders=0,
    name="Rule30_FROM",
    X=6,
    init_cells=[3],
    initial_step=1)
    annotation (Placement(transformation(extent={{-94,-10},{-36,30}})));
  CellularAutomataLib.Examples.CS_1D.CSR30 cSR30_2(
    n_inputs=1,
    wrapped_borders=0,
    name="Rule30_TO",
    X=30,
    init_cells=[20],
    initial_step=1)
    annotation (Placement(transformation(extent={{24,-10},{82,30}})));
   CellularAutomataLib.Components.Interfaces.InputRegion inputRegion(
    comm_start=0,
    redeclare function SetInput = Examples.CS_1D.RSetInput,
    XFromRange={3,3},
    XTo=5) annotation (Placement(transformation(extent={{-18,32},{2,52}})));
  CellularAutomataLib.Components.Interfaces.OutputRegionM O(
    XFromRange={1,30},
    output_rate=1,
    redeclare function ExtOutput = ROutput)
    annotation (Placement(transformation(extent={{46,60},{66,80}})));
  constant Integer result[30] = {1,0,1,0,1,0,0,1,0,0,1,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0};//
  Boolean fail( start = false);
algorithm
  when terminal() then
    for i in 1:30 loop
      if result[i] <> integer(O.yM[i,1,1]) then
        Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell["+String(i+O.XFromRange[1]-1)+"]: is "+String(O.yM[i,1,1])+" instead of "+String(result[i]));
        fail := true;
      end if;
    end for;
    if not fail then
        Modelica.Utilities.Streams.print("*******************");
        Modelica.Utilities.Streams.print("******* -- TEST OK!");
        Modelica.Utilities.Streams.print("*******************");
    end if;
  end when;
equation
  connect(cSR30_1.Space, inputRegion.FROM) annotation (
    Line(points={{-62.1,32},{-62.1,42},{-14,42}},
                                          color = {0, 0, 255}, smooth = Smooth.None));
  connect(inputRegion.TO, cSR30_2.Space) annotation (
    Line(points={{-2,42},{55.9,42},{55.9,32}},
                                        color = {0, 0, 255}, smooth = Smooth.None));
  connect(O.FROM, cSR30_2.Space) annotation (Line(points={{49.8,70},{49.8,42},{
          55.9,42},{55.9,32}},
                          color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=7, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>This model is composed of two cellular spaces (two CSR30  models) that communicate using an Input Region model. </p>
<p>The size of the first space is X=3, and the second X=10. The input region translates the state of cell [3] from the first space to the cell [8] in the second space. </p>
<p>The animation model displays the evolution of the second space. </p>
</html>"));
end Test_Input;
