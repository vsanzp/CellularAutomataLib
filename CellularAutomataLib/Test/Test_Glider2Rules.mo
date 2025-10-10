within CellularAutomataLib.Test;
model Test_Glider2Rules "Test with two rules using the GOL model"
  extends Modelica.Icons.Example;

CellularAutomataLib.Examples.CS_2D.GameOfLife.CSGol_glider cSGol_glider(
    X=6,
    Y=6,
    initial_step=1,
    max_step=4,
    init_cells=[1,2; 2,3; 3,1; 3,2; 3,3])
    annotation (Placement(transformation(extent={{-58,-20},{-38,0}})));
  CellularAutomataLib.Components.Interfaces.OutputRegionM O(
    XFromRange={3,5},
    YFromRange={3,5},
    output_rate=1,
    redeclare function ExtOutput = GOLOutput)
    annotation (Placement(transformation(extent={{-56,18},{-36,38}})));
  constant Integer result[3,3] = [0,1,0; 0,0,1; 1,1,1]; // at step 4
  Boolean fail( start = false);
  GliderRule gliderRule(initial_step=5)
    annotation (Placement(transformation(extent={{-20,-20},{0,0}})));
algorithm
  when terminal() then
    for i in 1:3 loop
      for j in 1:3 loop
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
  connect(cSGol_glider.Space, O.FROM) annotation (Line(points={{-47,1},{-48,1},
          {-48,14},{-52.2,14},{-52.2,28}},
                                      color={0,0,0}));
  connect(cSGol_glider.Space, gliderRule.Space)
    annotation (Line(points={{-47,1},{-47,8},{-10,8},{-10,1}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_glider model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
</html>"),
    experiment(StopTime=8, __Dymola_Algorithm="Dassl"));
end Test_Glider2Rules;
